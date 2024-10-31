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

#pragma once
#include <unordered_map>
#include <vector>
#include <list>
#include "sql/expr/expression.h"

class BinderContext
{
public:
  friend class ExpressionBinder;
  BinderContext()          = default;
  virtual ~BinderContext() = default;

  void add_table(Table *table) { query_tables_.push_back(table); }

  
  auto set_tables(std::vector<Table*>*tables) {tables_in_outer_query_ = tables;}
  const std::vector<Table *> &query_tables() const { return query_tables_; }

private:
  std::vector<Table *> query_tables_;
  std::vector<Table*>* tables_in_outer_query_;
};

/**
 * @brief 绑定表达式
 * @details 绑定表达式，就是在SQL解析后，得到文本描述的表达式，将表达式解析为具体的数据库对象
 */
class ExpressionBinder
{
public:
  friend class SelectStmt;
  friend class DeleteStmt;
  friend class UpdateStmt;
  friend RC bind_from(Db* db, std::vector<rel_info*>& relations, std::unordered_map<const char*, Table*>&table_map, std::unordered_map<const char*, Table*>& alias2name, unique_ptr<ExpressionBinder>&binder, std::vector<Table*>& tables, std::vector<unique_ptr<ConjunctionExpr>>& join_exprs);
  explicit ExpressionBinder() {}
  virtual ~ExpressionBinder() = default;

  RC bind_expression(std::unique_ptr<Expression> &expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);
  std::list<SubQueryExpr*>& sub_queries() { return sub_querys_; }
private:
  RC bind_star_expression(
      std::unique_ptr<Expression> &star_expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);
  RC bind_unbound_field_expression(
      std::unique_ptr<Expression> &unbound_field_expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);
  RC bind_field_expression(
      std::unique_ptr<Expression> &field_expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);
  RC bind_value_expression(
      std::unique_ptr<Expression> &value_expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);
  RC bind_cast_expression(
      std::unique_ptr<Expression> &cast_expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);
  RC bind_comparison_expression(
      std::unique_ptr<Expression> &comparison_expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);
  RC bind_conjunction_expression(
      std::unique_ptr<Expression> &conjunction_expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);
  RC bind_arithmetic_expression(
      std::unique_ptr<Expression> &arithmetic_expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);
  RC bind_aggregate_expression(
      std::unique_ptr<Expression> &aggregate_expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);
  Table *find_table(const char *table_name) const;
  Table *find_in_bound_tables(const char*table_name);
private:
  // BinderContext &context_;
  // std::vector<Table *> tables_from_outer_queries_;
  std::unordered_map<const char*,Table*> table_names_from_outer_queries_;
  std::unordered_map<const char*,Table*> table_alias_from_outer_queries_;
  std::unordered_map<const char*,Expression*> expre_alias_from_outer_queries_;
  //现在当前查询的tables中查找，然后再从outer queries中查找tables

  std::vector<Table *> tables_from_current_query_; 
  std::unordered_map<const char*,Table*> table_names_from_current_query_;
  std::unordered_map<const char*,Table*> table_alias_from_current_query_;
  std::unordered_map<const char*,Expression*> expre_alias_from_current_query_;


  std::list<SubQueryExpr*> sub_querys_; // 存放所有的子查詢
  bool using_outer_field_{false};
};