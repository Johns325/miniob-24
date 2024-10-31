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
// Created by Wangyunlai on 2022/6/6.
//

#include "sql/stmt/select_stmt.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/db/db.h"
#include "storage/table/table.h"
#include "sql/parser/expression_binder.h"
#include "sql/stmt/order_by_stmt.h"

using namespace std;
using namespace common;

SelectStmt::~SelectStmt()
{
  if (nullptr != filter_stmt_) {
    delete filter_stmt_;
    filter_stmt_ = nullptr;
  }
}

// bind_from 需要处理这样一些东西
// 1 需要完成table的绑定，也就是查DB找对应的Table，并建立起table name与Table的mapping
// 2 需要设置相应的alias(若有).  是不是也建立一个alias与table name的映射方便后续的解析？
// 3 需要处理join(inner join, cross product是目前考虑的两类join)，以及相应的join conditions. (//TODO 后续可能会考虑把where中的join conditions下推的情形) 
// 4 待补充

RC SelectStmt::predicates_push_down(const char *table_name, std::vector<std::unique_ptr<Expression>>& predicates) {
  for (auto &expr : condition_expressions_) {
    if (expr == nullptr)
      continue;
    if (expr->type() == ExprType::COMPARISON) {
      auto cmp_expr = static_cast<ComparisonExpr*>(expr.get());
      FieldExpr  *field_expr{nullptr};
      ValueExpr  *val_expr{nullptr};
      if (cmp_expr->left()->type() == ExprType::FIELD && cmp_expr->right()->type() == ExprType::VALUE) {
        field_expr = static_cast<FieldExpr*>(cmp_expr->left().get());
        val_expr = static_cast<ValueExpr*>(cmp_expr->right().get());
      } else if (cmp_expr->left()->type() == ExprType::VALUE && cmp_expr->right()->type() == ExprType::FIELD) {
        field_expr = static_cast<FieldExpr*>(cmp_expr->right().get());
        val_expr = static_cast<ValueExpr*>(cmp_expr->right().get());
      }
      if (field_expr && val_expr && (0 == strcmp(field_expr->field().table_name(), table_name))) {
        predicates.emplace_back(expr.release());
      }
    }
  }
  return RC::SUCCESS;
}
RC SelectStmt::remaining_predicates(std::vector<std::unique_ptr<Expression>>& predicates) {
  for (auto &expr : condition_expressions_) {
    if (expr != nullptr) {
      predicates.emplace_back(expr.release());
    }
  }
  return RC::SUCCESS;
}
std::pair<RC, ExpressionBinder*> bind_from(Db* db, std::vector<rel_info*>& relations, std::unordered_map<string, Table*>&table_map, unordered_map<string, Table*>& alias2table, BinderContext& ctx, std::vector<Table*>& tables, std::vector<unique_ptr<ConjunctionExpr>>& join_exprs) {
  for (size_t i = 0; i < relations.size(); i++) {
    auto table_name = (*relations[i]).relation_name.c_str();
    if (nullptr == table_name) {
      LOG_WARN("invalid argument. relation name is null. index=%d", i);
      return {RC::INVALID_ARGUMENT,nullptr};
    }

    Table *table = db->find_table(table_name);
    if (nullptr == table) {
      LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
      return {RC::SCHEMA_TABLE_NOT_EXIST, nullptr};
    }
    ctx.add_table(table);
    tables.push_back(table);
    table_map.insert({table_name, table});
    if (!(*relations[i]).relation_alias.empty()) {
      auto alias = (*relations[i]).relation_alias.c_str();
      alias2table.insert({alias, table});
    }
  }
  auto info  = ctx.bound_info();
  info->tables.insert(info->tables.end(), tables.begin(), tables.end());
  for (auto& pos : table_map)
    info->name_2_tables.insert({pos.first, pos.second});
  for (auto& pos : alias2table) 
    info->alias_2_tables.insert({pos.first, pos.second});
  auto binder = new ExpressionBinder(ctx);
  // bind join condtions.
  if ((*relations[0]).on_conditions != nullptr) {
    // almost impossible.
    return {RC::INTERNAL, nullptr};
  }
  // tabe[i].on_conditions refers table_i and the joined table which is the join table of tables before table_i.
  // 应该先对on_conditions中的表达式进行绑定后再判定有效性
  // std::vector<unique_ptr<ComparisonExpr>> join_exprs;
  for (size_t k = 1; k < relations.size(); ++k) {
    auto & rel_info = *relations[k];
    if (rel_info.on_conditions != nullptr) {
      std::vector<unique_ptr<Expression>> bound_expres;
      for (auto expr : *rel_info.on_conditions) {
        // cmp shall be a ComparisonExpr.
        // 现在假设on 中的条件只包含ValueExpr 和 FieldExpr.
        auto cmp = static_cast<ComparisonExpr*>(expr);
        if (cmp->left()->type() == ExprType::UNBOUND_FIELD) {
          auto unbound_expr = static_cast<UnboundFieldExpr*>(cmp->left().get());
          auto rc = check_join_validation(unbound_expr, alias2table, tables, k);
          if (!OB_SUCC(rc)) {
            return {rc, nullptr};
          }
        }
        if (cmp->right()->type() == ExprType::UNBOUND_FIELD) {
          auto unbound_expr = static_cast<UnboundFieldExpr*>(cmp->left().get());
          auto rc = check_join_validation(unbound_expr, alias2table, tables, k);
          if (!OB_SUCC(rc)) {
            return {rc, nullptr};
          }
        }
        std::unique_ptr<Expression> expr1(cmp);
        auto rc = binder->bind_expression(expr1, bound_expres);
        if (OB_FAIL(rc)) {
          LOG_INFO("bind expression failed. rc=%s", strrc(rc));
          return {rc, nullptr};
        }
      }
      // 再做一个ConjunctionExpression
      auto ptr = std::unique_ptr<ConjunctionExpr>(new ConjunctionExpr(ConjunctionExpr::Type::AND, std::move(bound_expres)));
      join_exprs.emplace_back(std::move(ptr));
    } else {
      join_exprs.emplace_back(nullptr);
    }
  }
  return {RC::SUCCESS, std::move(binder)};
}
// 现在tables[index]找是否发现了该字段，若没有再到table[0-index-1]找
RC check_join_validation(UnboundFieldExpr* expr,std::unordered_map<string, Table*>& alias_to_table_name, std::vector<Table*>&tables, size_t index) {
  Table * table;
  if (!is_blank(expr->table_name())) {
    // table name不为空有两种情况，第一种是直接给的表名，第二中情况下是别名
    if (0 == strcmp(expr->table_name(), tables[index]->name()))  {
      table = tables[index];
      auto field = table->table_meta().field(expr->field_name());
      if (field != nullptr) 
        return RC::SUCCESS;
    } else {
      for (auto k = static_cast<int>(index-1); k>=0 ;--k) {
        table = nullptr;
        if (0 == strcmp(expr->table_name(), tables[k]->name())) {
          table = tables[k];
          if (table->table_meta().field(expr->field_name()) != nullptr) {
            return RC::SUCCESS;
          }
        }
      }
    }
    //处理第二中情况:
    auto pos = alias_to_table_name.find(expr->table_name());
    if (pos == alias_to_table_name.end()) {
      // 所有查询中找不到
      return RC::SCHEMA_FIELD_NOT_EXIST;
    }
    table = pos->second;
    // 如果alias有对应的table，那么table必须在0~index这个范围内
    for (int k = static_cast<int>(index); k >=0; --k) {
      if (table == tables[k])
        return RC::SUCCESS;
    }
    // that's to say the your input is ID.ID while it cannot match any field.
    return RC::SCHEMA_FIELD_NOT_EXIST;
  }
  // only specify the field_name;
  const FieldMeta* meta{nullptr};
  for (int k = static_cast<int>(index); k >=0;--k) {
    table = tables[k];
    if (table->table_meta().field(expr->field_name())) {
      if (meta != nullptr) {
        // field is ambiguous
        return RC::SCHEMA_FIELD_AMBIGUOUS;
      }
      meta = table->table_meta().field(expr->field_name());
    }
  }
  return (meta == nullptr ? RC::SCHEMA_DB_NOT_EXIST : RC::SUCCESS);
}

RC bind_select(ExpressionBinder* binder, std::vector<std::unique_ptr<Expression>>& expressions, vector<unique_ptr<Expression>>&bound_expressions, std::unordered_map<string, Expression*>& alias_to_expressions) {
  for (unique_ptr<Expression> &expression : expressions) {
    if (!is_blank(expression->alias())) {
      alias_to_expressions.insert({expression->alias(), expression.get()}); // 完成expr_alias 到expression的映射
    }
    RC rc = binder->bind_expression(expression, bound_expressions);
    if (OB_FAIL(rc)) {
      LOG_INFO("bind expression failed. rc=%s", strrc(rc));
      return rc;
    }
  } 
  return RC::SUCCESS;
}

RC bind_where(Db*db, ExpressionBinder* binder, std::vector<Expression*>* expressions, vector<unique_ptr<Expression>>&bound_expressions) {
  if (nullptr == expressions) {
    return RC::SUCCESS;
  }
  for (auto expression : *expressions) {
    auto expr = std::unique_ptr<Expression>(expression);
    RC rc = binder->bind_expression(expr, bound_expressions);
    if (OB_FAIL(rc)) {
      LOG_INFO("bind expression failed. rc=%s", strrc(rc));
      return rc;
    }
  } 
  return RC::SUCCESS;
}



// RC create_sub_query_stmt(Db* db, Expression *expr) {
//   RC rc{RC::SUCCESS};
//   if (expr->type() == ExprType::COMPARISON) {
//     auto cmp_expr = static_cast<ComparisonExpr*>(expr);
//     if (cmp_expr->left()->type() == ExprType::SUB_QUERY) {
//       auto sub_query_expr = static_cast<SubQueryExpr*>(cmp_expr->left().get());
//       Stmt *stmt;
//       auto rc = SelectStmt::create(db, sub_query_expr->get_sql_node()->selection, stmt);
//       if (!OB_SUCC(rc)) {
//         return rc;
//       }
//       sub_query_expr->set_select_stmt(static_cast<SelectStmt*>(stmt));
//     } 
//     if (cmp_expr->right()->type() == ExprType::SUB_QUERY) {
//       auto sub_query_expr = static_cast<SubQueryExpr*>(cmp_expr->right().get());
//       Stmt *stmt;
//       auto rc = SelectStmt::create(db, sub_query_expr->get_sql_node()->selection, stmt);
//       if (!OB_SUCC(rc)) {
//         return rc;
//       }
//       sub_query_expr->set_select_stmt(static_cast<SelectStmt*>(stmt));
//     }
//     rc = create_sub_query_stmt(db,cmp_expr->left().get());
//     if (!OB_SUCC(rc)) {
//       return rc;
//     }
//     rc = create_sub_query_stmt(db,cmp_expr->right().get());
//     if (!OB_SUCC(rc)) {
//       return rc;
//     }
//   } else if (ExprType::ARITHMETIC ==  expr->type()) {
//     // TODO 和ComparisonExpr的代碼高度相同，請優化一下
//     auto arithmetic_expr = static_cast<ArithmeticExpr*>(expr);
//     if (arithmetic_expr->left()->type() == ExprType::SUB_QUERY) {
//       auto sub_query_expr = static_cast<SubQueryExpr*>(arithmetic_expr->left().get());
//       Stmt *stmt;
//       auto rc = SelectStmt::create(db, sub_query_expr->get_sql_node()->selection, stmt);
//       if (!OB_SUCC(rc)) {
//         return rc;
//       }
//       sub_query_expr->set_select_stmt(static_cast<SelectStmt*>(stmt));
//     } 
//     if (arithmetic_expr->right()->type() == ExprType::SUB_QUERY) {
//       auto sub_query_expr = static_cast<SubQueryExpr*>(arithmetic_expr->right().get());
//       Stmt *stmt;
//       auto rc = SelectStmt::create(db, sub_query_expr->get_sql_node()->selection, stmt);
//       if (!OB_SUCC(rc)) {
//         return rc;
//       }
//       sub_query_expr->set_select_stmt(static_cast<SelectStmt*>(stmt));
//     }
//     rc = create_sub_query_stmt(db,arithmetic_expr->left().get());
//     if (!OB_SUCC(rc)) {
//       return rc;
//     }
//     rc = create_sub_query_stmt(db,arithmetic_expr->right().get());
//     if (!OB_SUCC(rc)) {
//       return rc;
//     }
//   }
//   return RC::SUCCESS;
// }

RC bind_join_conditions(ExpressionBinder &binder, std::vector<rel_info>& relations, std::vector<unique_ptr<Expression>>& bound_join_exprs) {
  
  return RC::SUCCESS;
}

RC bind_group_by(ExpressionBinder* binder, std::vector<unique_ptr<Expression>>* expressions, vector<unique_ptr<Expression>>&bound_expressions) {
  if (nullptr == expressions) {
    return RC::SUCCESS;
  }
  for (auto &expression : *expressions) {
    RC rc = binder->bind_expression(expression, bound_expressions);
    if (OB_FAIL(rc)) {
      LOG_INFO("bind expression failed. rc=%s", strrc(rc));
      return rc;
    }
  } 
  return RC::SUCCESS;
}

void SelectStmt::set_sub_queries(std::list<SubQueryExpr*>& other) {
    for (auto iter = other.begin(); iter != other.end(); ++iter) {
      sub_queries_.push_back(*iter);
      *iter = nullptr;
    }
  }

// bind_from
// bind_select
// bind_where
// bind_group_by
// bind_order_by
RC SelectStmt::create(Db *db, SelectSqlNode &select_sql, Stmt *&stmt, Bound_Info* upper_info)
{
  if (nullptr == db) {
    LOG_WARN("invalid argument. db is null");
    return RC::INVALID_ARGUMENT;
  }
  Bound_Info info;
  /* ******************************************************{bind_from}*********************************************************************/ 
  // step1 开始绑定FROM
  BinderContext context;
  if (upper_info) {
    context.set_upper_info(upper_info);
  }
  context.info_ = &info;
  vector<Table *>                tables;
  unordered_map<string, Table *> table_map; //
  unordered_map<string, Table*> alias_to_table;
  std::vector<std::unique_ptr<ConjunctionExpr>> join_expres;
  auto res = bind_from(db, select_sql.relations, table_map, alias_to_table, context, tables, join_expres);
  if (!OB_SUCC(res.first)) {
    LOG_WARN("bound table ref failed");
    return res.first;
  }
  unique_ptr<ExpressionBinder> binder(res.second);
  
  // 已经保存好本次查询所需要的所有Table信息包括别名和名字到table的映射

  /* ******************************************************{bind_select}*******************************************************************/ 
  // collect query fields in `select` statement
  vector<unique_ptr<Expression>> bound_expressions; // 可能直接丢给Projection opeator
  RC rc{RC::SUCCESS};
  if (rc = bind_select(binder.get(), select_sql.expressions, bound_expressions, info.alias_2_expressions); !OB_SUCC(rc)) {
    return rc;
  }

  /* ******************************************************{bind_where}*******************************************************************/ 
  vector<unique_ptr<Expression>> bound_where_expressions; // 可以直接丢给Predicate Operator
  if (rc = bind_where(db, binder.get(), select_sql.conditions, bound_where_expressions); !OB_SUCC(rc)) {
    return rc;
  }
  
  
  
  // actually we can convert all expressions in bound_where_expressions to ComparisonExprs
  
  vector<unique_ptr<Expression>> bound_group_by_expressions; // 可以直接丢给Predicate Operator
  if (rc = bind_group_by(binder.get(), select_sql.group_by, bound_group_by_expressions); !OB_SUCC(rc)) {
    return rc;
  }

  /* ******************************************************{bind_having}*******************************************************************/ 
  // having 中只能有出现在select后面的聚合表达式以及出现在group by后面的字段
  vector<unique_ptr<Expression>> bound_having_expressions; // 可以直接丢给Predicate Operator
  if (nullptr != select_sql.having) {
    for (auto &expr : *select_sql.having) {
      if (!is_blank(expr->alias())) {
        info.alias_2_expressions.insert({expr->alias(), expr});
      }
      std::unique_ptr<Expression> uniq_expr(expr);
      rc = binder->bind_expression(uniq_expr, bound_having_expressions);
      if (!OB_SUCC(rc)) {
        return rc;
      }
    }
  }

  /* ******************************************************{bind_order_by}*******************************************************************/ 
  OrderByStmt *order_by_stmt = nullptr;
  if (select_sql.order_by != nullptr) {
    if (rc = OrderByStmt::create(table_map, *select_sql.order_by, order_by_stmt); rc != RC::SUCCESS) {
      LOG_WARN("cannot construct filter stmt");
      return rc;
    }
  }
  

  auto sel_stmt = new SelectStmt(std::move(tables), std::move(join_expres), std::move(bound_expressions), std::move(bound_where_expressions), std::move(bound_group_by_expressions), std::move(bound_having_expressions));
  sel_stmt->set_order_by_stmt(order_by_stmt);
  // 這個sub_queris list中包含了where和on後面的所有子查詢。
  std::list<SubQueryExpr*> sub_queries;
  if (!binder->sub_querys_.empty()) {
    sub_queries.insert(sub_queries.end(), binder->sub_querys_.begin(), binder->sub_querys_.end());
  }
  if (!bound_having_expressions.empty()) {
    sel_stmt->set_having(std::move(bound_having_expressions));
  }
  //TODO现在已经对于当前的查询处理完所有的bind 工作，因此需要在递归的解析子查询之前将所有的以及处理的tables,expresssions以及相应的名字映射设置到ExpressionBinder中.
  sel_stmt->using_outer_field_ = binder->reference_outer_query_;
  for (auto query : sub_queries) {
    Stmt* select_stmt;
    rc = SelectStmt::create(db, query->sql_node_->selection, select_stmt, &info);
  if (!OB_SUCC(rc)) {
      return rc;
    }
    auto ss = static_cast<SelectStmt*>(select_stmt);
    query->set_select_stmt(ss);
  }
  sel_stmt->sub_queries_.insert(sel_stmt->sub_queries().end(), sub_queries.begin(), sub_queries.end());
  stmt = sel_stmt;
  return RC::SUCCESS;
}//select * from exp_table where 0 < col1-2 and col5 >'2023-11-11'
