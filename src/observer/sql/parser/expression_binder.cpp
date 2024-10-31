/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2024/05/29.
//

#include <algorithm>

#include "common/log/log.h"
#include "common/lang/string.h"
#include "sql/parser/expression_binder.h"
#include "sql/expr/expression_iterator.h"
#include "common/type/attr_type.h"

using namespace std;
using namespace common;

Table *ExpressionBinder::find_table(const char *table_name) const
{
  auto pos = table_names_from_current_query_.find(table_name);
  if (pos == table_names_from_current_query_.end()) {
    pos = table_alias_from_current_query_.find(table_name);
    return (pos == table_alias_from_current_query_.end() ? nullptr : pos->second);
  }
  return pos->second;
}
Table *ExpressionBinder::find_in_bound_tables(const char*table_name) {
  auto pos = table_names_from_outer_queries_.find(table_name);
  if (pos == table_names_from_outer_queries_.end()) {
    pos = table_alias_from_outer_queries_.find(table_name);
    return (pos == table_alias_from_outer_queries_.end() ? nullptr : pos->second);
  }
  return pos->second;
}

////////////////////////////////////////////////////////////////////////////////
static void wildcard_fields(Table *table, vector<unique_ptr<Expression>> &expressions, bool more_than_one_table)
{
  const TableMeta &table_meta = table->table_meta();
  const int        field_num  = table_meta.field_num();
  for (int i = table_meta.sys_field_num(); i < field_num; i++) {
    Field      field(table, table_meta.field(i));
    FieldExpr *field_expr = new FieldExpr(field);
    field_expr->set_name(field.field_name());
    if (more_than_one_table) {
      field_expr->set_alias(string(table->name()) + "." + field.field_name());
    }
    expressions.emplace_back(field_expr);
  }
}

RC ExpressionBinder::bind_expression(unique_ptr<Expression> &expr, vector<unique_ptr<Expression>> &bound_expressions)
{
  if (nullptr == expr) {
    return RC::SUCCESS;
  }
  if (!is_blank(expr->alias())) {
    expre_alias_from_current_query_.insert({expr->alias(), expr.get()});
  }
  switch (expr->type()) {
    case ExprType::STAR: {
      return bind_star_expression(expr, bound_expressions);
    } break;

    case ExprType::UNBOUND_FIELD: {
      return bind_unbound_field_expression(expr, bound_expressions);
    } break;

    case ExprType::UNBOUND_AGGREGATION: {
      return bind_aggregate_expression(expr, bound_expressions);
    } break;

    case ExprType::FIELD: {
      return bind_field_expression(expr, bound_expressions);
    } break;

    case ExprType::VALUE: {
      return bind_value_expression(expr, bound_expressions);
    } break;

    case ExprType::CAST: {
      return bind_cast_expression(expr, bound_expressions);
    } break;

    case ExprType::COMPARISON: {
      return bind_comparison_expression(expr, bound_expressions);
    } break;

    case ExprType::CONJUNCTION: {
      return bind_conjunction_expression(expr, bound_expressions);
    } break;

    case ExprType::ARITHMETIC: {
      return bind_arithmetic_expression(expr, bound_expressions);
    } break;

    case ExprType::AGGREGATION: {
      ASSERT(false, "shouldn't be here");
    } break;
    case ExprType::SUB_QUERY: {
      // sub_query will be processed later.
      sub_querys_.push_back(static_cast<SubQueryExpr*>(expr.get()));
      bound_expressions.emplace_back(std::move(expr));
      return RC::SUCCESS;
    };
    case ExprType::CONSTANT_VALUE_LIST: {
      // nothing to do.
      bound_expressions.emplace_back(std::move(expr));
      return RC::SUCCESS;
    }
    case ExprType::ALISAS :{
      auto alias_expr = static_cast<AliasExpr*>(expr.get());
      auto alias = alias_expr->alias_name();
      if (expre_alias_from_current_query_.find(alias) == expre_alias_from_current_query_.end()) {
        return RC::ALIAS_NOT_EXISTS;
      }
      std::unique_ptr<Expression> new_expr;
      auto rc = expre_alias_from_current_query_.find(alias)->second->deep_copy(new_expr);
      if (rc != RC::SUCCESS) {
        return rc;
      }
      bound_expressions.emplace_back(std::move(new_expr));
      return RC::SUCCESS;
    }break;
    
    default: {
      LOG_WARN("unknown expression type: %d", static_cast<int>(expr->type()));
      return RC::INTERNAL;
    }
  }
  return RC::INTERNAL;
}

RC ExpressionBinder::bind_star_expression(
    unique_ptr<Expression> &expr, vector<unique_ptr<Expression>> &bound_expressions)
{
  if (nullptr == expr) {
    return RC::SUCCESS;
  }

  auto star_expr = static_cast<StarExpr *>(expr.get());

  vector<Table *> tables_to_wildcard;

  const char *table_name = star_expr->table_name();
  if (!is_blank(table_name) && 0 != strcmp(table_name, "*")) {
    Table *table = find_table(table_name);
    if (nullptr == table) {
      LOG_INFO("no such table in from list: %s", table_name);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }
    tables_to_wildcard.push_back(table);
  } else {
    tables_to_wildcard.insert(tables_to_wildcard.end(), tables_from_current_query_.begin(), tables_from_current_query_.end());
  }

  for (Table *table : tables_to_wildcard) {
    wildcard_fields(table, bound_expressions, tables_to_wildcard.size() > 1);
  }

  return RC::SUCCESS;
}

RC ExpressionBinder::bind_unbound_field_expression(unique_ptr<Expression> &expr, vector<unique_ptr<Expression>> &bound_expressions) {
  if (nullptr == expr) {
    return RC::SUCCESS;
  }

  auto unbound_field_expr = static_cast<UnboundFieldExpr *>(expr.get());

  const char *table_name = unbound_field_expr->table_name();
  const char *field_name = unbound_field_expr->field_name();
  
  string name = (is_blank(table_name) ? field_name : string(table_name) + "." + string(field_name));
  Table *table = nullptr;
  if (is_blank(table_name)) {
    if (tables_from_current_query_.size() != 1) {
      LOG_INFO("cannot determine table for field: %s", field_name);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }

    table = tables_from_current_query_[0];
  } else {
    table = find_table(table_name); // step 1 现在当前查询中找table
    if (table == nullptr) {
      table = find_in_bound_tables(table_name); //step 2 在外查询中找
      if (table == nullptr) {
          LOG_INFO("no such table in from list: %s", table_name);
          return RC::SCHEMA_TABLE_NOT_EXIST;
      }
      using_outer_field_ = true;
    }
  }

  if (0 == strcmp(field_name, "*")) {
    wildcard_fields(table, bound_expressions, false);
  } else {
    const FieldMeta *field_meta = table->table_meta().field(field_name);
    if (nullptr == field_meta) {
      LOG_INFO("no such field in table: %s.%s", table_name, field_name);
      return RC::SCHEMA_FIELD_MISSING;
    }
    Field      field(table, field_meta);
    FieldExpr *field_expr = new FieldExpr(field);
    bound_expressions.emplace_back(field_expr);
    field_expr->set_name((tables_from_current_query_.size() > 1 ? name:field_name));
  }

  return RC::SUCCESS;
}

RC ExpressionBinder::bind_field_expression(
    unique_ptr<Expression> &field_expr, vector<unique_ptr<Expression>> &bound_expressions)
{
  bound_expressions.emplace_back(std::move(field_expr));
  return RC::SUCCESS;
}

RC ExpressionBinder::bind_value_expression(
    unique_ptr<Expression> &value_expr, vector<unique_ptr<Expression>> &bound_expressions)
{
  bound_expressions.emplace_back(std::move(value_expr));
  return RC::SUCCESS;
}

RC ExpressionBinder::bind_cast_expression(
    unique_ptr<Expression> &expr, vector<unique_ptr<Expression>> &bound_expressions)
{
  if (nullptr == expr) {
    return RC::SUCCESS;
  }

  auto cast_expr = static_cast<CastExpr *>(expr.get());

  vector<unique_ptr<Expression>> child_bound_expressions;
  unique_ptr<Expression>        &child_expr = cast_expr->child();

  RC rc = bind_expression(child_expr, child_bound_expressions);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  if (child_bound_expressions.size() != 1) {
    LOG_WARN("invalid children number of cast expression: %d", child_bound_expressions.size());
    return RC::INVALID_ARGUMENT;
  }

  unique_ptr<Expression> &child = child_bound_expressions[0];
  if (child.get() == child_expr.get()) {
    return RC::SUCCESS;
  }

  child_expr.reset(child.release());
  bound_expressions.emplace_back(std::move(expr));
  return RC::SUCCESS;
}

RC ExpressionBinder::bind_comparison_expression(
    unique_ptr<Expression> &expr, vector<unique_ptr<Expression>> &bound_expressions)
{
  if (nullptr == expr) {
    return RC::SUCCESS;
  }

  auto comparison_expr = static_cast<ComparisonExpr *>(expr.get());

  vector<unique_ptr<Expression>> child_bound_expressions;
  unique_ptr<Expression>        &left_expr  = comparison_expr->left();
  unique_ptr<Expression>        &right_expr = comparison_expr->right();

  RC rc = bind_expression(left_expr, child_bound_expressions);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  if (child_bound_expressions.size() != 1) {
    LOG_WARN("invalid left children number of comparison expression: %d", child_bound_expressions.size());
    return RC::INVALID_ARGUMENT;
  }

  unique_ptr<Expression> &left = child_bound_expressions[0];
  if (left.get() != left_expr.get()) {
    left_expr.reset(left.release());
  }

  child_bound_expressions.clear();
  rc = bind_expression(right_expr, child_bound_expressions);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  if (child_bound_expressions.size() != 1) {
    LOG_WARN("invalid right children number of comparison expression: %d", child_bound_expressions.size());
    return RC::INVALID_ARGUMENT;
  }

  unique_ptr<Expression> &right = child_bound_expressions[0];
  if (right.get() != right_expr.get()) {
    right_expr.reset(right.release());
  }
  FieldExpr *field_expr{nullptr};
  ValueExpr *val_expr{nullptr};
  
  if (left_expr->type() == ExprType::FIELD && right_expr->type() == ExprType::VALUE) {
    field_expr = static_cast<FieldExpr*>(left_expr.get());
    val_expr = static_cast<ValueExpr*>(right_expr.get());
  } else if (left_expr->type() == ExprType::VALUE && right_expr->type() == ExprType::FIELD) {
    field_expr = static_cast<FieldExpr*>(right_expr.get());
    val_expr = static_cast<ValueExpr*>(left_expr.get());
  }
  if (field_expr && val_expr) {
    auto field = field_expr->field().meta();
    auto val = val_expr->get_value();
    if (!field->nullable()) {
      // field is not null while insert value is null.
      if (val.is_null())
        return RC::FIELD_NOT_NULLABLE;
      if (field_expr->field().attr_type() == AttrType::DATES) {
      
        if (val_expr->value_type() != AttrType::CHARS) {
          return RC::SCHEMA_FIELD_TYPE_MISMATCH;
        }
        int date_val{0};
        std::string date_str(val_expr->get_value().data());
        if (rc = date_str_to_int(date_str, date_val); rc != RC::SUCCESS) {
          return rc;
        }
        val_expr->get_value().set_date(date_val);
      }
    } else {
      if (!val.is_null()) {
        if (field_expr->field().attr_type() == AttrType::DATES) {
          if (val_expr->value_type() != AttrType::CHARS) {
            return RC::SCHEMA_FIELD_TYPE_MISMATCH;
          }
          int date_val{0};
          std::string date_str(val_expr->get_value().data());
          if (rc = date_str_to_int(date_str, date_val); rc != RC::SUCCESS) {
            return rc;
          }
          val_expr->get_value().set_date(date_val);
        }
      }
    }
  }
  bound_expressions.emplace_back(std::move(expr));
  return RC::SUCCESS;
}

RC ExpressionBinder::bind_conjunction_expression(
    unique_ptr<Expression> &expr, vector<unique_ptr<Expression>> &bound_expressions)
{
  if (nullptr == expr) {
    return RC::SUCCESS;
  }

  auto conjunction_expr = static_cast<ConjunctionExpr *>(expr.get());

  vector<unique_ptr<Expression>>  child_bound_expressions;
  vector<unique_ptr<Expression>> &children = conjunction_expr->children();

  for (unique_ptr<Expression> &child_expr : children) {
    child_bound_expressions.clear();

    RC rc = bind_expression(child_expr, child_bound_expressions);
    if (rc != RC::SUCCESS) {
      return rc;
    }

    if (child_bound_expressions.size() != 1) {
      LOG_WARN("invalid children number of conjunction expression: %d", child_bound_expressions.size());
      return RC::INVALID_ARGUMENT;
    }

    unique_ptr<Expression> &child = child_bound_expressions[0];
    if (child.get() != child_expr.get()) {
      child_expr.reset(child.release());
    }
  }

  bound_expressions.emplace_back(std::move(expr));

  return RC::SUCCESS;
}

RC ExpressionBinder::bind_arithmetic_expression(
    unique_ptr<Expression> &expr, vector<unique_ptr<Expression>> &bound_expressions)
{
  if (nullptr == expr) {
    return RC::SUCCESS;
  }

  auto arithmetic_expr = static_cast<ArithmeticExpr *>(expr.get());

  vector<unique_ptr<Expression>> child_bound_expressions;
  unique_ptr<Expression>        &left_expr  = arithmetic_expr->left();
  unique_ptr<Expression>        &right_expr = arithmetic_expr->right();

  RC rc = bind_expression(left_expr, child_bound_expressions);
  if (OB_FAIL(rc)) {
    return rc;
  }

  if (child_bound_expressions.size() != 1) {
    LOG_WARN("invalid left children number of comparison expression: %d", child_bound_expressions.size());
    return RC::INVALID_ARGUMENT;
  }

  unique_ptr<Expression> &left = child_bound_expressions[0];
  if (left.get() != left_expr.get()) {
    left_expr.reset(left.release());
  }

  child_bound_expressions.clear();
  rc = bind_expression(right_expr, child_bound_expressions);
  if (OB_FAIL(rc)) {
    return rc;
  }

  if (child_bound_expressions.size() != 1 && arithmetic_expr->arithmetic_type() != ArithmeticExpr::Type::NEGATIVE) {
    LOG_WARN("invalid right children number of comparison expression: %d", child_bound_expressions.size());
    return RC::INVALID_ARGUMENT;
  }

  unique_ptr<Expression> &right = child_bound_expressions[0];
  if (right.get() != right_expr.get()) {
    right_expr.reset(right.release());
  }
  // if (arithmetic_expr->arithmetic_type() == ArithmeticExpr::Type::DIV && right_expr->type() == ExprType::VALUE) {
  //   auto val = static_cast<ValueExpr*>(right_expr.get())->get_value();
  //   if ((val.attr_type() == AttrType::INTS || val.get_int() == 0) || (val.attr_type() == AttrType::FLOATS && val.get_float() == 0.0)) {
  //     return RC::DIVIDE_ZERO;
  //   }
  // }
  bound_expressions.emplace_back(std::move(expr));
  return RC::SUCCESS;
}

RC check_aggregate_expression(AggregateExpr &expression)
{
  // 必须有一个子表达式
  Expression *child_expression = expression.child().get();
  if (nullptr == child_expression) {
    LOG_WARN("child expression of aggregate expression is null");
    return RC::INVALID_ARGUMENT;
  }

  // 校验数据类型与聚合类型是否匹配
  AggregateExpr::Type aggregate_type   = expression.aggregate_type();
  AttrType            child_value_type = child_expression->value_type();
  switch (aggregate_type) {
    case AggregateExpr::Type::SUM:
    case AggregateExpr::Type::AVG: {
      // 仅支持数值类型
      if (child_value_type != AttrType::INTS && child_value_type != AttrType::FLOATS) {
        LOG_WARN("invalid child value type for aggregate expression: %d", static_cast<int>(child_value_type));
        return RC::INVALID_ARGUMENT;
      }
    } break;

    case AggregateExpr::Type::COUNT:
    case AggregateExpr::Type::MAX:
    case AggregateExpr::Type::MIN: {
      // 任何类型都支持
    } break;
  }

  // 子表达式中不能再包含聚合表达式
  function<RC(std::unique_ptr<Expression>&)> check_aggregate_expr = [&](unique_ptr<Expression> &expr) -> RC {
    RC rc = RC::SUCCESS;
    if (expr->type() == ExprType::AGGREGATION) {
      LOG_WARN("aggregate expression cannot be nested");
      return RC::INVALID_ARGUMENT;
    }
    rc = ExpressionIterator::iterate_child_expr(*expr, check_aggregate_expr);
    return rc;
  };

  RC rc = ExpressionIterator::iterate_child_expr(expression, check_aggregate_expr);

  return rc;
}

RC ExpressionBinder::bind_aggregate_expression(
    unique_ptr<Expression> &expr, vector<unique_ptr<Expression>> &bound_expressions)
{
  if (nullptr == expr) {
    return RC::SUCCESS;
  }

  auto unbound_aggregate_expr = static_cast<UnboundAggregateExpr *>(expr.get());
  const char *aggregate_name = unbound_aggregate_expr->aggregate_name();
  AggregateExpr::Type aggregate_type;
  RC rc = AggregateExpr::type_from_string(aggregate_name, aggregate_type);
  if (OB_FAIL(rc)) {
    LOG_WARN("invalid aggregate name: %s", aggregate_name);
    return rc;
  }

  unique_ptr<Expression>        &child_expr = unbound_aggregate_expr->child();
  vector<unique_ptr<Expression>> child_bound_expressions;

  if (child_expr->type() == ExprType::STAR && aggregate_type == AggregateExpr::Type::COUNT) {
    ValueExpr *value_expr = new ValueExpr(Value(1));
    child_expr.reset(value_expr);
  } else {
    rc = bind_expression(child_expr, child_bound_expressions);
    if (OB_FAIL(rc)) {
      return rc;
    }

    if (child_bound_expressions.size() != 1) {
      LOG_WARN("invalid children number of aggregate expression: %d", child_bound_expressions.size());
      return RC::INVALID_ARGUMENT;
    }

    if (child_bound_expressions[0].get() != child_expr.get()) {
      child_expr.reset(child_bound_expressions[0].release());
    }
  }

  auto aggregate_expr = make_unique<AggregateExpr>(aggregate_type, std::move(child_expr));
  aggregate_expr->set_name(unbound_aggregate_expr->name());
  rc = check_aggregate_expression(*aggregate_expr);
  if (OB_FAIL(rc)) {
    return rc;
  }

  bound_expressions.emplace_back(std::move(aggregate_expr));
  return RC::SUCCESS;
}
