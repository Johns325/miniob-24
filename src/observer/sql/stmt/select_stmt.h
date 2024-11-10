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
#include <list>
#include "common/rc.h"
#include "sql/stmt/stmt.h"
#include "storage/field/field.h"
#include <unordered_map>
class FieldMeta;
class FilterStmt;
class Db;
class Table;
class rel_info;
class Expression;
class ExpressionBinder;
class BinderContext;
class ComparisonExpr;
class ConjunctionExpr;
class UnboundFieldExpr;
class OrderByStmt;
class Index;
class SubQueryExpr;
class View;
using UEXPR = std::unique_ptr<Expression>;
using std::unordered_map;
// 用来记录一个select语句相应的查询信息
// 1 查询中涉及到的tables
// 2 table_name 到 Table的映射
struct Bound_Info {
  Bound_Info(/* args */) = default;
  ~Bound_Info() = default;
  std::vector<Table*> tables;
  unordered_map<string, Table*> name_2_tables;
  unordered_map<string, Table*> alias_2_tables;
  unordered_map<string, Expression*> alias_2_expressions;
};



/**
 * @brief 表示select语句
 * @ingroup Statement
 */
class SelectStmt : public Stmt
{
public:
  friend class LogicalPlanGenerator;
  friend class ExpressionBinder;
  SelectStmt() = default;
  SelectStmt(std::vector<Table*>&& tables, std::vector<std::unique_ptr<ConjunctionExpr>>&&join_expres,std::vector<std::unique_ptr<Expression>>&& query_expressions, std::vector<std::unique_ptr<Expression>>&& condition_expressions, std::vector<std::unique_ptr<Expression>>&& group_by_expressions, std::vector<std::unique_ptr<Expression>>&& having)
  : tables_(std::move(tables)),join_expres_(std::move(join_expres)),query_expressions_(std::move(query_expressions)),condition_expressions_(std::move(condition_expressions)), group_by_(std::move(group_by_expressions)), having_(std::move(having)) {}
  ~SelectStmt() override;

  StmtType type() const override { return StmtType::SELECT; }
  void set_sub_queries(std::list<SubQueryExpr*>& other);
  static bool alias_check(SelectSqlNode& sql_node);
  std::list<SubQueryExpr*>& sub_queries() { return sub_queries_;}
public:
  static RC create(Db *db, SelectSqlNode &select_sql, Stmt *&stmt, Bound_Info* upper_info);
  
private:
  
public:
  bool convert_to_vector_index(Index* index);
  const std::vector<Table *> &tables() const { return tables_; }
  FilterStmt                 *filter_stmt() const { return filter_stmt_; }
  void set_order_by_stmt(OrderByStmt* stmt) {order_by_stmt = stmt;}
  void set_having(vector<unique_ptr<Expression>>&& having) { having_ = std::move(having);}
  std::vector<std::unique_ptr<Expression>> &query_expressions() { return query_expressions_; }
  std::vector<std::unique_ptr<Expression>> &group_by() { return group_by_; }
  RC predicates_push_down(const char *table_name, std::vector<std::unique_ptr<Expression>>& predicates);
  RC remaining_predicates(std::vector<std::unique_ptr<Expression>>& predicates);
private:
  std::vector<Table *>                     tables_;                  // Tables to reference
  std::vector<std::unique_ptr<ConjunctionExpr>>join_expres_;         // Join conditions.Joining n tables has n-1 join condtions.
  std::vector<std::unique_ptr<Expression>> query_expressions_;       // 
  std::vector<std::unique_ptr<Expression>> condition_expressions_; // where
  FilterStmt                              *filter_stmt_ = nullptr; //
  std::list<SubQueryExpr*>                 sub_queries_; // 包含的所以子查詢.These sub_queries need to construct logical & physical plans too.
  std::vector<std::unique_ptr<Expression>> group_by_; // group by
  std::vector<std::unique_ptr<Expression>> having_;   // having
  OrderByStmt                             *order_by_stmt{nullptr};  // order by specifications
  std::list<Expression*>                   reference_expressions_;  // expressions to references from outer query, currently we only support FieldExpr.
  bool and_flag_{true};                   // whether conditions in WHERE clause are connected using AND. false indicates OR.
  bool using_outer_field_{false};         // example: select * from t1 where t1.id < (select avg(t2.sum) from t2 where t2.id > t1.id). so the sub query references the column of outer query, therefore using_outer_field is true for sub query.
  bool break_pipeline_{false};            // the same thing as using_outer_field_;

public:
  int limit;
  bool is_view_=false;
  int limit{-1};
};



std::pair<RC, ExpressionBinder*> bind_from(Db* db, std::vector<rel_info*>& relations, std::unordered_map<string, Table*>&table_map, unordered_map<string, Table*>& alias2name, BinderContext& ctx, std::vector<Table*>& tables, std::vector<unique_ptr<ConjunctionExpr>>& join_exprs,bool* is_view);
RC bind_select(ExpressionBinder* binder, std::vector<std::unique_ptr<Expression>>& relations, vector<unique_ptr<Expression>>&bound_expressions,  std::unordered_map<string, Expression*>& alias_to_expressions);
RC bind_join_conditions(ExpressionBinder &binder, std::vector<rel_info>& relations, std::vector<unique_ptr<Expression>>& bound_join_exprs);
RC check_join_validation(UnboundFieldExpr* expr,std::unordered_map<string, Table*>& alias_to_table_name, std::vector<Table*>&tables, size_t index);
RC bind_where(Db*db, ExpressionBinder* binder, std::vector<Expression*>* expressions, vector<unique_ptr<Expression>>&bound_expressions);
RC bind_group_by(ExpressionBinder* binder, std::vector<unique_ptr<Expression>>* expressions, vector<unique_ptr<Expression>>&bound_expressions);
// RC create_sub_query_stmt(Db* db,Expression* cmp_expr);
