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
// Created by WenkaiDing on 2024/11/11.
//

#pragma once

#include "sql/operator/physical_operator.h"
#include "sql/parser/parse.h"
#include <vector>

class InsertStmt;
class OrderByUnit;
/**
 * @brief 插入物理算子
 * @ingroup PhysicalOperator
 */
class IvfflatPhysicalOperator : public PhysicalOperator
{
public:
  IvfflatPhysicalOperator(OrderByUnit* unit, int limit): unit_(unit), limit_(limit) {}

  virtual ~IvfflatPhysicalOperator() = default;

  PhysicalOperatorType type() const override { return PhysicalOperatorType::IVFFLAT_INDEX_SCAN; }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  Tuple *current_tuple() override { return &current_tuple_; }

private:
  OrderByUnit             *unit_ {nullptr};
  int limit_{0};
  RowTuple   current_tuple_;
  Record     current_record_;
  std::vector<RID> rids_; //存放ann_search 返回的所有rids.
  size_t index_{0};
  
};
