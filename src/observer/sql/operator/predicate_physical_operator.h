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
// Created by WangYunlai on 2022/6/27.
//

#pragma once
#include <list>
#include "sql/expr/expression.h"
#include "sql/operator/physical_operator.h"

class FilterStmt;
class Trx;

/**
 * @brief 过滤/谓词物理算子
 * @ingroup PhysicalOperator
 */
class PredicatePhysicalOperator : public PhysicalOperator
{
public:
  PredicatePhysicalOperator(std::unique_ptr<Expression> expr);

  virtual ~PredicatePhysicalOperator() = default;

  PhysicalOperatorType type() const override { return PhysicalOperatorType::PREDICATE; }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;
  TupleSchema* schema() override { return children_[0]->schema(); }
  Tuple *current_tuple() override;

  RC tuple_schema(TupleSchema &schema) const override;
  RC hand_all_sub_queries();
  RC hand_all_sub_queries_every_time(Tuple *t);
private:
  std::unique_ptr<Expression> expression_; 
  Trx *trx_{nullptr};
  // std::list<SubQueryExpr*> sub_queries_;
};
