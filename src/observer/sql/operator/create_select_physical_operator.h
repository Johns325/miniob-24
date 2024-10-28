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
// Created by WangYunlai on 2022/6/9.
//

#pragma once

#include "sql/operator/physical_operator.h"

class Trx;
class DeleteStmt;

/**
 * @brief 物理算子，删除
 * @ingroup PhysicalOperator
 */
class CreateTableSelectPhysicalOperator : public PhysicalOperator
{
public:
  CreateTableSelectPhysicalOperator(Db* db, std::string table_name, std::vector<AttrInfoSqlNode> infos): db_(db), table_name_(table_name), infos_(std::move(infos)) {}

  virtual ~CreateTableSelectPhysicalOperator() = default;

  PhysicalOperatorType type() const override { return PhysicalOperatorType::CREATE_TABLE_SELECT; }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  Tuple *current_tuple() override { return nullptr; }

private:
  Db              *db_ = nullptr;
  string                 table_name_;
  std::vector<AttrInfoSqlNode> infos_;
};
