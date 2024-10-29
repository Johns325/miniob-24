/* Copyright (c) 2023 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2023/08/16.
//

#include "sql/optimizer/logical_plan_generator.h"

#include <common/log/log.h>

#include "sql/operator/calc_logical_operator.h"
#include "sql/operator/delete_logical_operator.h"
#include "sql/operator/explain_logical_operator.h"
#include "sql/operator/insert_logical_operator.h"
#include "sql/operator/join_logical_operator.h"
#include "sql/operator/logical_operator.h"
#include "sql/operator/predicate_logical_operator.h"
#include "sql/operator/project_logical_operator.h"
#include "sql/operator/table_get_logical_operator.h"
#include "sql/operator/group_by_logical_operator.h"
#include "sql/operator/update_logical_operator.h"
#include "sql/operator/order_by_logical_operator.h"
#include "sql/operator/create_select_logical_operator.h"

#include "sql/stmt/calc_stmt.h"
#include "sql/stmt/create_select_stmt.h"
#include "sql/stmt/delete_stmt.h"
#include "sql/stmt/explain_stmt.h"
#include "sql/stmt/filter_stmt.h"
#include "sql/stmt/insert_stmt.h"
#include "sql/stmt/select_stmt.h"
#include "sql/stmt/update_stmt.h"
#include "sql/stmt/order_by_stmt.h"
#include "sql/stmt/stmt.h"
#include "sql/expr/expression.h"
#include "sql/expr/expression_iterator.h"

using namespace std;
using namespace common;

RC LogicalPlanGenerator::create(Stmt *stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  RC rc = RC::SUCCESS;
  switch (stmt->type()) {
    case StmtType::CALC: {
      CalcStmt *calc_stmt = static_cast<CalcStmt *>(stmt);

      rc = create_plan(calc_stmt, logical_operator);
    } break;

    case StmtType::SELECT: {
      SelectStmt *select_stmt = static_cast<SelectStmt *>(stmt);

      rc = create_plan(select_stmt, logical_operator);
    } break;

    case StmtType::INSERT: {
      InsertStmt *insert_stmt = static_cast<InsertStmt *>(stmt);

      rc = create_plan(insert_stmt, logical_operator);
    } break;

    case StmtType::CREATE_TABLE_SELECT: {
      rc = create_plan(static_cast<CreateTableSelectStmt*>(stmt), logical_operator);
    } break;

    case StmtType::ORDER_BY: {
      OrderByStmt *order_stmt = static_cast<OrderByStmt*>(stmt);
      rc = create_plan(order_stmt, logical_operator);
    } break;

    case StmtType::DELETE: {
      DeleteStmt *delete_stmt = static_cast<DeleteStmt *>(stmt);

      rc = create_plan(delete_stmt, logical_operator);
    } break;

    case StmtType::UPDATE :{
      rc = create_plan(static_cast<UpdateStmt*>(stmt), logical_operator);
    } break;

    case StmtType::EXPLAIN: {
      ExplainStmt *explain_stmt = static_cast<ExplainStmt *>(stmt);

      rc = create_plan(explain_stmt, logical_operator);
    } break;
    default: {
      rc = RC::UNIMPLEMENTED;
    }
  }
  return rc;
}

RC LogicalPlanGenerator::create_plan(CreateTableSelectStmt *cts_stmt, std::unique_ptr<LogicalOperator> &logical_operator) {
  unique_ptr<LogicalOperator> logical_oper;
  auto rc = create(cts_stmt->sbu_query_stmt_, logical_oper);
  if (!OB_SUCC(rc)) {
    return rc;
  }
  logical_operator.reset(new CreateTableSelectLogicalOperator(cts_stmt->db_, cts_stmt->table_name_, std::move(cts_stmt->info_)));
  logical_operator->add_child(std::move(logical_oper));
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(OrderByStmt *order_stmt, std::unique_ptr<LogicalOperator> &logical_operator) {
  if (order_stmt != nullptr) {
    LogicalOperator *oper = new OrderByLogicalOperator(std::move(order_stmt->units()));
    logical_operator.reset(oper);
  }
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(CalcStmt *calc_stmt, std::unique_ptr<LogicalOperator> &logical_operator)
{
  logical_operator.reset(new CalcLogicalOperator(std::move(calc_stmt->expressions())));
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(SelectStmt *select_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  unique_ptr<LogicalOperator> *last_oper = nullptr;
  RC rc{RC::SUCCESS};
  unique_ptr<LogicalOperator> table_oper(nullptr);
  last_oper = &table_oper;

  const std::vector<Table *> &tables = select_stmt->tables();
  int join_pred_index{0};
  for (Table *table : tables) {
    std::vector<std::unique_ptr<Expression>> push_down_preds;
    select_stmt->predicates_push_down(table->name(), push_down_preds);
    auto tb_get_ptr = new TableGetLogicalOperator(table, ReadWriteMode::READ_ONLY);
    if (!push_down_preds.empty()) {
      tb_get_ptr->set_predicates(std::move(push_down_preds));
    }
    unique_ptr<LogicalOperator> table_get_oper(tb_get_ptr);
    if (table_oper == nullptr) {
      table_oper = std::move(table_get_oper);
    } else {
      JoinLogicalOperator *join_oper = new JoinLogicalOperator;
      join_oper->add_child(std::move(table_oper));
      join_oper->add_child(std::move(table_get_oper));
      if (select_stmt->join_expres_[join_pred_index] != nullptr) {
        join_oper->set_predicates(std::move(select_stmt->join_expres_[join_pred_index])); 
      }
      table_oper = unique_ptr<LogicalOperator>(join_oper);
      ++join_pred_index;
    }
  }

  unique_ptr<LogicalOperator> predicate_oper;
  std::vector<std::unique_ptr<Expression>> condition_expressions;
  select_stmt->remaining_predicates(condition_expressions);
  if (!condition_expressions.empty()) {
    unique_ptr<ConjunctionExpr> conjunction_expr(new ConjunctionExpr(ConjunctionExpr::Type::AND, std::move(condition_expressions)));
    predicate_oper = unique_ptr<PredicateLogicalOperator>(new PredicateLogicalOperator(std::move(conjunction_expr)));
  }
  // 對這個查詢的所有子查詢生產查詢計劃. 並且把所有的子查詢都放到ProjectPhysicalOperator中，這樣可以統一執行open操作
  for (auto query : select_stmt->sub_queries()) {
    UptrLogOper sub_query_log_oper;
    auto rc = create(query->select_stmt_, sub_query_log_oper);
    if (!OB_SUCC(rc)) {
      return rc;
    }
    query->logical_sub_query_ = sub_query_log_oper.release();
  }

  if (predicate_oper) {
    if (*last_oper) {
      predicate_oper->add_child(std::move(*last_oper));
    }

    last_oper = &predicate_oper;
  }

  unique_ptr<LogicalOperator> group_by_oper;
  rc = create_group_by_plan(select_stmt, group_by_oper);
  if (OB_FAIL(rc)) {
    LOG_WARN("failed to create group by logical plan. rc=%s", strrc(rc));
    return rc;
  }

  if (group_by_oper) {
    if (*last_oper) {
      group_by_oper->add_child(std::move(*last_oper));
    }

    last_oper = &group_by_oper;
  }

  unique_ptr<LogicalOperator> order_by_oper;
  if (select_stmt->order_by_stmt != nullptr) {
    rc = create(select_stmt->order_by_stmt, order_by_oper);
    if (OB_FAIL(rc)) {
      LOG_WARN("failed to create group by logical plan. rc=%s", strrc(rc));
      return rc;
    }
  }
  if (order_by_oper) {
    if (*last_oper) {
      order_by_oper->add_child(std::move(*last_oper));
    }
    last_oper = &order_by_oper;
  }

  auto project_oper = make_unique<ProjectLogicalOperator>(std::move(select_stmt->query_expressions()));
  if (*last_oper) {
    project_oper->add_child(std::move(*last_oper));
  }
  if (!select_stmt->sub_queries().empty()) {
    project_oper->set_sub_queries(select_stmt->sub_queries());
  }
  logical_operator = std::move(project_oper);
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(FilterStmt *filter_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  RC                                  rc = RC::SUCCESS;
  std::vector<unique_ptr<Expression>> cmp_exprs;
  const std::vector<FilterUnit *>    &filter_units = filter_stmt->filter_units();
  for (const FilterUnit *filter_unit : filter_units) {
    const FilterObj &filter_obj_left  = filter_unit->left();
    const FilterObj &filter_obj_right = filter_unit->right();

    unique_ptr<Expression> left(filter_obj_left.is_attr
                                    ? static_cast<Expression *>(new FieldExpr(filter_obj_left.field))
                                    : static_cast<Expression *>(new ValueExpr(filter_obj_left.value)));

    unique_ptr<Expression> right(filter_obj_right.is_attr
                                     ? static_cast<Expression *>(new FieldExpr(filter_obj_right.field))
                                     : static_cast<Expression *>(new ValueExpr(filter_obj_right.value)));

    // if (left->value_type() != right->value_type()) {
    //   auto left_to_right_cost = implicit_cast_cost(left->value_type(), right->value_type());
    //   auto right_to_left_cost = implicit_cast_cost(right->value_type(), left->value_type());
    //   if (left_to_right_cost <= right_to_left_cost && left_to_right_cost != INT32_MAX) {
    //     ExprType left_type = left->type();
    //     auto cast_expr = make_unique<CastExpr>(std::move(left), right->value_type());
    //     if (left_type == ExprType::VALUE) {
    //       Value left_val;
    //       if (OB_FAIL(rc = cast_expr->try_get_value(left_val)))
    //       {
    //         LOG_WARN("failed to get value from left child", strrc(rc));
    //         return rc;
    //       }
    //       left = make_unique<ValueExpr>(left_val);
    //     } else {
    //       left = std::move(cast_expr);
    //     }
    //   } else if (right_to_left_cost < left_to_right_cost && right_to_left_cost != INT32_MAX) {
    //     ExprType right_type = right->type();
    //     auto cast_expr = make_unique<CastExpr>(std::move(right), left->value_type());
    //     if (right_type == ExprType::VALUE) {
    //       Value right_val;
    //       if (OB_FAIL(rc = cast_expr->try_get_value(right_val)))
    //       {
    //         LOG_WARN("failed to get value from right child", strrc(rc));
    //         return rc;
    //       }
    //       right = make_unique<ValueExpr>(right_val);
    //     } else {
    //       right = std::move(cast_expr);
    //     }

    //   } else {
    //     rc = RC::UNSUPPORTED;
    //     LOG_WARN("unsupported cast from %s to %s", attr_type_to_string(left->value_type()), attr_type_to_string(right->value_type()));
    //     return rc;
    //   }
    // }

    ComparisonExpr *cmp_expr = new ComparisonExpr(filter_unit->comp(), std::move(left), std::move(right));
    cmp_exprs.emplace_back(cmp_expr);
  }

  unique_ptr<PredicateLogicalOperator> predicate_oper;
  if (!cmp_exprs.empty()) {
    unique_ptr<ConjunctionExpr> conjunction_expr(new ConjunctionExpr(ConjunctionExpr::Type::AND, cmp_exprs));
    predicate_oper = unique_ptr<PredicateLogicalOperator>(new PredicateLogicalOperator(std::move(conjunction_expr)));
  }

  logical_operator = std::move(predicate_oper);
  return rc;
}

int LogicalPlanGenerator::implicit_cast_cost(AttrType from, AttrType to)
{
  if (from == to) {
    return 0;
  }
  return DataType::type_instance(from)->cast_cost(to);
}

RC LogicalPlanGenerator::create_plan(InsertStmt *insert_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  Table        *table = insert_stmt->table();
  vector<Value> values(insert_stmt->values(), insert_stmt->values() + insert_stmt->value_amount());

  InsertLogicalOperator *insert_operator = new InsertLogicalOperator(table, values);
  logical_operator.reset(insert_operator);
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(DeleteStmt *delete_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  Table                      *table       = delete_stmt->table();
  
  unique_ptr<LogicalOperator> table_get_oper(new TableGetLogicalOperator(table, ReadWriteMode::READ_WRITE));

  unique_ptr<LogicalOperator> predicate_oper;

  if (!delete_stmt->expressions_.empty()) {
    unique_ptr<ConjunctionExpr> conjunction_expr(new ConjunctionExpr(ConjunctionExpr::Type::AND, std::move(delete_stmt->expressions_)));
    predicate_oper = unique_ptr<PredicateLogicalOperator>(new PredicateLogicalOperator(std::move(conjunction_expr)));
  }

  unique_ptr<LogicalOperator> delete_oper(new DeleteLogicalOperator(table));

  if (predicate_oper) {
    predicate_oper->add_child(std::move(table_get_oper));
    delete_oper->add_child(std::move(predicate_oper));
  } else {
    delete_oper->add_child(std::move(table_get_oper));
  }

  logical_operator = std::move(delete_oper);
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(ExplainStmt *explain_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  unique_ptr<LogicalOperator> child_oper;

  Stmt *child_stmt = explain_stmt->child();

  RC rc = create(child_stmt, child_oper);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create explain's child operator. rc=%s", strrc(rc));
    return rc;
  }

  logical_operator = unique_ptr<LogicalOperator>(new ExplainLogicalOperator);
  logical_operator->add_child(std::move(child_oper));
  return rc;
}

RC LogicalPlanGenerator::create_plan(UpdateStmt *update_stmt, std::unique_ptr<LogicalOperator> &logical_operator) {
  
  auto table = update_stmt->table();
  
  UptrLogOper table_scan(new TableGetLogicalOperator(table, ReadWriteMode::READ_WRITE));
  UptrLogOper pred_oper;
  if (!update_stmt->expressions_.empty()) {
    unique_ptr<ConjunctionExpr> conjunction_expr(new ConjunctionExpr(ConjunctionExpr::Type::AND, std::move(update_stmt->expressions_)));
    pred_oper = unique_ptr<PredicateLogicalOperator>(new PredicateLogicalOperator(std::move(conjunction_expr)));
  }
  for (auto assign : *update_stmt->assignments()) {
    if (assign->right_hand_side->type() == ExprType::SUB_QUERY) {
      auto sub_query_expr = static_cast<SubQueryExpr*>(assign->right_hand_side);
      // UptrLogOper sub_query_log_oper;
      UptrLogOper sub_query_log_oper;
      auto rc = create(sub_query_expr->select_stmt_, sub_query_log_oper);
      if (!OB_SUCC(rc)) {
        return rc;
      }
      sub_query_expr->logical_sub_query_ = sub_query_log_oper.release();
    }
  }
  UptrLogOper update_oper (new UpdateLogicalOperator(table, update_stmt->assignments()));
  if (pred_oper) {
    pred_oper->add_child(std::move(table_scan));
    update_oper->add_child(std::move(pred_oper));
  } else {
    update_oper->add_child(std::move(table_scan));
  }
  logical_operator = std::move(update_oper);
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_group_by_plan(SelectStmt *select_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  vector<unique_ptr<Expression>> &group_by_expressions = select_stmt->group_by();
  vector<Expression *> aggregate_expressions;
  vector<unique_ptr<Expression>> &query_expressions = select_stmt->query_expressions();
  vector<unique_ptr<Expression>> &having_expressions = select_stmt->having_;
  function<RC(std::unique_ptr<Expression>&)> collector = [&](unique_ptr<Expression> &expr) -> RC {
    RC rc = RC::SUCCESS;
    if (expr->type() == ExprType::AGGREGATION) {
      expr->set_pos(aggregate_expressions.size() + group_by_expressions.size());
      aggregate_expressions.push_back(expr.get());
    }
    rc = ExpressionIterator::iterate_child_expr(*expr, collector);
    return rc;
  };

  function<RC(std::unique_ptr<Expression>&)> bind_group_by_expr = [&](unique_ptr<Expression> &expr) -> RC {
    RC rc = RC::SUCCESS;
    for (size_t i = 0; i < group_by_expressions.size(); i++) {
      auto &group_by = group_by_expressions[i];
      if (expr->type() == ExprType::AGGREGATION) {
        break;
      } else if (expr->equal(*group_by)) {
        expr->set_pos(i);
        continue;
      } else {
        rc = ExpressionIterator::iterate_child_expr(*expr, bind_group_by_expr);
      }
    }
    return rc;
  };

 bool found_unbound_column = false;
  function<RC(std::unique_ptr<Expression>&)> find_unbound_column = [&](unique_ptr<Expression> &expr) -> RC {
    RC rc = RC::SUCCESS;
    if (expr->type() == ExprType::AGGREGATION) {
      // do nothing
    } else if (expr->pos() != -1) {
      // do nothing
    } else if (expr->type() == ExprType::FIELD) {
      found_unbound_column = true;
    }else {
      rc = ExpressionIterator::iterate_child_expr(*expr, find_unbound_column);
    }
    return rc;
  };
  

  for (unique_ptr<Expression> &expression : query_expressions) {
    bind_group_by_expr(expression);
  }

  for (unique_ptr<Expression> &expression : query_expressions) {
    find_unbound_column(expression);
  }

  // collect all aggregate expressions
  for (unique_ptr<Expression> &expression : query_expressions) {
    collector(expression);
  }

  if (group_by_expressions.empty() && aggregate_expressions.empty()) {
    // 既没有group by也没有聚合函数，不需要group by
    return RC::SUCCESS;
  }

  auto size = aggregate_expressions.size();
  for (auto &expr : having_expressions) {
    collector(expr);
  }
  size = aggregate_expressions.size() - size;
  if (found_unbound_column) {
    LOG_WARN("column must appear in the GROUP BY clause or must be part of an aggregate function");
    return RC::INVALID_ARGUMENT;
  }

  // 如果只需要聚合，但是没有group by 语句，需要生成一个空的group by 语句

  auto group_by_oper = make_unique<GroupByLogicalOperator>(std::move(group_by_expressions),
                                                           std::move(aggregate_expressions));
  if (size != 0) {
    group_by_oper->set_having_aggregation_size(aggregate_expressions.size() - size);
  }
  if (!select_stmt->having_.empty()) {
    group_by_oper->set_having_expressions(std::move(select_stmt->having_));
  }
  logical_operator = std::move(group_by_oper);
  return RC::SUCCESS;
}