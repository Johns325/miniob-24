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
// Created by Wangyunlai on 2022/6/5.
//

#pragma once

#include <memory>
#include <vector>
#include <optional>

#include "common/rc.h"
#include "sql/stmt/stmt.h"
#include "storage/field/field.h"

class FieldMeta;
class FilterStmt;
class Db;
class Table;
class rel_info;
class Expression;
class ExpressionBinder;
class BinderContext;
class ConjunctionExpr;
class UnboundFieldExpr;

/**
 * @brief 表示select语句
 * @ingroup Statement
 */
class SelectStmt : public Stmt
{
public:
  friend class LogicalPlanGenerator;
  SelectStmt() = default;
  SelectStmt(std::vector<Table*>&& tables, std::vector<std::unique_ptr<ConjunctionExpr>>&&join_expres,std::vector<std::unique_ptr<Expression>>&& query_expressions, std::vector<std::unique_ptr<Expression>>&& condition_expressions, std::vector<std::unique_ptr<Expression>>&& group_by_expressions, std::vector<std::unique_ptr<Expression>>&& having)
  : tables_(std::move(tables)),join_expres_(std::move(join_expres)),query_expressions_(std::move(query_expressions)),condition_expressions_(std::move(condition_expressions)), group_by_(std::move(group_by_expressions)), having_(std::move(having)) {}
  ~SelectStmt() override;

  StmtType type() const override { return StmtType::SELECT; }

public:
  static RC create(Db *db, SelectSqlNode &select_sql, Stmt *&stmt);
  
private:
  
public:
  const std::vector<Table *> &tables() const { return tables_; }
  FilterStmt                 *filter_stmt() const { return filter_stmt_; }

  std::vector<std::unique_ptr<Expression>> &query_expressions() { return query_expressions_; }
  std::vector<std::unique_ptr<Expression>> &group_by() { return group_by_; }

private:
  std::vector<Table *>                     tables_;
  std::vector<std::unique_ptr<ConjunctionExpr>>join_expres_;
  std::vector<std::unique_ptr<Expression>> query_expressions_;
  std::vector<std::unique_ptr<Expression>> condition_expressions_;
  FilterStmt                              *filter_stmt_ = nullptr;
  std::vector<std::unique_ptr<Expression>> group_by_;
  std::vector<std::unique_ptr<Expression>> having_;

};


std::pair<RC, ExpressionBinder*> bind_from(Db* db, std::vector<rel_info>& relations, std::unordered_map<string, Table*>&table_map, std::unordered_map<string, string>& alias2name, BinderContext& ctx, std::vector<Table*>& tables, std::vector<unique_ptr<ConjunctionExpr>>& join_exprs);
RC bind_select(ExpressionBinder* binder, std::vector<std::unique_ptr<Expression>>& relations, vector<unique_ptr<Expression>>&bound_expressions);
RC bind_join_conditions(ExpressionBinder &binder, std::vector<rel_info>& relations, std::vector<unique_ptr<Expression>>& bound_join_exprs);
RC check_join_validation(UnboundFieldExpr* expr,std::unordered_map<std::string, std::string>& alias_to_table_name, std::vector<Table*>&tables, size_t index);
RC bind_where(ExpressionBinder* binder, std::vector<Expression*>* expressions, vector<unique_ptr<Expression>>&bound_expressions);
RC bind_group_by(ExpressionBinder* binder, std::vector<unique_ptr<Expression>>* expressions, vector<unique_ptr<Expression>>&bound_expressions);

