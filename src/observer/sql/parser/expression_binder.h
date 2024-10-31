
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

#include <vector>

#include "sql/expr/expression.h"

class BinderContext
{
public:
  friend class ExpressionBinder;
  friend class SelectStmt;
  BinderContext()          = default;
  virtual ~BinderContext() = default;

  void add_table(Table *table) { query_tables_.push_back(table); }

  Table *find_table(const char *table_name) const;

  const std::vector<Table *> &query_tables() const { return query_tables_; }
  // name = true :by name. name = false:by alias
  auto find_table_by_name(const char* tb_name) const -> Table* {
    auto pos = info_->name_2_tables.find(tb_name);
    return (pos == info_->name_2_tables.end() ? nullptr : pos->second);
  }
  auto find_table_by_alias(const char* tb_name) const -> Table* {
    auto pos = info_->alias_2_tables.find(tb_name);
    return (pos == info_->alias_2_tables.end() ? nullptr : pos->second);
  }
  auto find_table_from_outer_query(const char *tb_name) const -> Table* {
    auto pos = outer_info_->name_2_tables.find(tb_name);
    if (pos != outer_info_->name_2_tables.end()) {
      return pos->second;
    }
    pos = outer_info_->alias_2_tables.find(tb_name);
    return (pos == outer_info_->alias_2_tables.end() ? nullptr : pos->second);
  }
  void set_upper_info(Bound_Info * info) {info_ = info;}
  auto bound_info() -> Bound_Info*{ return info_; }
private:
  std::vector<Table *> query_tables_;
  Bound_Info *info_{nullptr};
  Bound_Info *outer_info_{nullptr}; //外面一层查询的信息
};

/**
 * @brief 绑定表达式
 * @details 绑定表达式，就是在SQL解析后，得到文本描述的表达式，将表达式解析为具体的数据库对象
 */
class ExpressionBinder
{
public:
  friend class SelectStmt;
  ExpressionBinder(BinderContext &context) : context_(context) {}
  virtual ~ExpressionBinder() = default;

  RC bind_expression(std::unique_ptr<Expression> &expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);

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
private:
  BinderContext &context_;
  std::list<SubQueryExpr*> sub_querys_; // 存放所有的子查詢
  bool reference_outer_query_{false};
};
