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
std::pair<RC, ExpressionBinder*> bind_from(Db* db, std::vector<rel_info>& relations, std::unordered_map<string, Table*>&table_map, unordered_map<string, string>& alias2name, BinderContext& ctx, std::vector<Table*>& tables, std::vector<unique_ptr<ConjunctionExpr>>& join_exprs) {
  for (size_t i = 0; i < relations.size(); i++) {
    auto table_name = relations[i].relation_name.c_str();
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
    if (!relations[i].relation_alias.empty()) {
      // TODO是否mapping[alias, Table*]更好
      alias2name.insert({relations[i].relation_alias, relations[i].relation_name});
    }
  }
  auto binder = new ExpressionBinder(ctx);
  // bind join condtions.
  if (relations[0].on_conditions != nullptr) {
    // almost impossible.
    return {RC::INTERNAL, nullptr};
  }
  // tabe[i].on_conditions refers table_i and the joined table which is the join table of tables before table_i.
  // 应该先对on_conditions中的表达式进行绑定后再判定有效性
  // std::vector<unique_ptr<ComparisonExpr>> join_exprs;
  for (size_t k = 1; k < relations.size(); ++k) {
    auto & rel_info = relations[k];
    if (rel_info.on_conditions != nullptr) {
      std::vector<unique_ptr<Expression>> bound_expres;
      for (auto expr : *rel_info.on_conditions) {
        // cmp shall be a ComparisonExpr.
        // 现在假设on 中的条件只包含ValueExpr 和 FieldExpr.
        auto cmp = static_cast<ComparisonExpr*>(expr);
        if (cmp->left()->type() == ExprType::UNBOUND_FIELD) {
          auto unbound_expr = static_cast<UnboundFieldExpr*>(cmp->left().get());
          auto rc = check_join_validation(unbound_expr, alias2name, tables, k);
          if (!OB_SUCC(rc)) {
            return {rc, nullptr};
          }
        }
        if (cmp->right()->type() == ExprType::UNBOUND_FIELD) {
          auto unbound_expr = static_cast<UnboundFieldExpr*>(cmp->left().get());
          auto rc = check_join_validation(unbound_expr, alias2name, tables, k);
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
RC check_join_validation(UnboundFieldExpr* expr,std::unordered_map<std::string, std::string>& alias_to_table_name, std::vector<Table*>&tables, size_t index) {
  Table * table;
  if (!is_blank(expr->table_name())) {
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

RC bind_select(ExpressionBinder* binder, std::vector<std::unique_ptr<Expression>>& expressions, vector<unique_ptr<Expression>>&bound_expressions) {
  for (unique_ptr<Expression> &expression : expressions) {
    RC rc = binder->bind_expression(expression, bound_expressions);
    if (OB_FAIL(rc)) {
      LOG_INFO("bind expression failed. rc=%s", strrc(rc));
      return rc;
    }
  } 
  return RC::SUCCESS;
}

RC bind_where(ExpressionBinder* binder, std::vector<Expression*>* expressions, vector<unique_ptr<Expression>>&bound_expressions) {
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

// bind_from
// bind_select
// bind_where
// bind_group_by
// bind_order_by
RC SelectStmt::create(Db *db, SelectSqlNode &select_sql, Stmt *&stmt)
{
  if (nullptr == db) {
    LOG_WARN("invalid argument. db is null");
    return RC::INVALID_ARGUMENT;
  }

  BinderContext binder_context;
  vector<Table *>                tables;
  unordered_map<string, Table *> table_map;
  unordered_map<string, string> alias_to_tb_name;
  std::vector<std::unique_ptr<ConjunctionExpr>> join_expres;
  /* ******************************************************{bind_from}*********************************************************************/ 
  
  auto res = bind_from(db, select_sql.relations, table_map, alias_to_tb_name, binder_context, tables, join_expres);
  if (!OB_SUCC(res.first)) {
    LOG_WARN("bound table ref failed");
    return res.first;
  }

  /* ******************************************************{bind_select}*******************************************************************/ 
  // collect query fields in `select` statement
  vector<unique_ptr<Expression>> bound_expressions; // 可能直接丢给Projection opeator
  unique_ptr<ExpressionBinder> expression_binder(res.second);
  RC rc{RC::SUCCESS};
  if (rc = bind_select(expression_binder.get(), select_sql.expressions, bound_expressions); !OB_SUCC(rc)) {
    return rc;
  }

  /* ******************************************************{bind_where}*******************************************************************/ 
  vector<unique_ptr<Expression>> bound_where_expressions; // 可以直接丢给Predicate Operator
  if (rc = bind_where(expression_binder.get(), select_sql.conditions, bound_where_expressions); !OB_SUCC(rc)) {
    return rc;
  }
  // actually we can convert all expressions in bound_where_expressions to ComparisonExprs
  
  vector<unique_ptr<Expression>> bound_group_by_expressions; // 可以直接丢给Predicate Operator
  if (rc = bind_group_by(expression_binder.get(), select_sql.group_by, bound_group_by_expressions); !OB_SUCC(rc)) {
    return rc;
  }
  auto sel_stmt = new SelectStmt(std::move(tables), std::move(join_expres), std::move(bound_expressions), std::move(bound_where_expressions), std::move(bound_group_by_expressions));
  stmt = sel_stmt;
  return RC::SUCCESS;
}//select * from exp_table where 0 < col1-2 and col5 >'2023-11-11'
