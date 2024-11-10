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
// Created by Wangyunlai on 2022/12/07.
//

#pragma once

#include "sql/expr/expression.h"
#include "sql/operator/logical_operator.h"

/**
 * @brief 谓词/过滤逻辑算子
 * @ingroup LogicalOperator
 */
class PredicateLogicalOperator : public LogicalOperator
{
public:
  PredicateLogicalOperator(std::unique_ptr<Expression> expression);
  virtual ~PredicateLogicalOperator() = default;
  std::list<SubQueryExpr*>& sub_queries() { return sub_queries_; }
  void set_sub_queries(std::list<SubQueryExpr*>& other) {
    for (auto iter = other.begin(); iter != other.end(); ++iter) {
      sub_queries_.push_back(*iter);
      *iter = nullptr;
    }
  } 
  void put_expressions(std::list<Expression*>& expressions);
  std::list<Expression*>& get_special_expressions() {  return expressions_to_reset_;}
  LogicalOperatorType type() const override { return LogicalOperatorType::PREDICATE; }
private:
  std::list<SubQueryExpr*> sub_queries_;
  std::list<Expression*> expressions_to_reset_;
};
