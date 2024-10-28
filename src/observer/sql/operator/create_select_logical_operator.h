/* Copyright (c) OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by WangYunlai on 2022/12/26.
//

#pragma once

#include "sql/operator/logical_operator.h"

/**
 * @brief 逻辑算子，用于执行delete语句
 * @ingroup LogicalOperator
 */
class CreateTableSelectLogicalOperator : public LogicalOperator
{
public:
  friend class LogicalPlanGenerator;
  friend class PhysicalPlanGenerator;
  CreateTableSelectLogicalOperator(Db* db, std::string table_name, std::vector<AttrInfoSqlNode>&&info): db_(db), table_name_(table_name), infos_(std::move(info)) {}
  virtual ~CreateTableSelectLogicalOperator() = default;

  LogicalOperatorType type() const override { return LogicalOperatorType::CREATE_TABLE_SELECT; }
  

private:
  Db *db_;
  std::string table_name_;
  std::vector<AttrInfoSqlNode>infos_;
};
