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
// Created by Wangyunlai on 2022/5/22.
//

#pragma once

#include "common/rc.h"
#include "sql/stmt/stmt.h"

class Table;
class FilterStmt;
class FieldMeta;
/**
 * @brief 更新语句
 * @ingroup Statement
 */
class UpdateStmt : public Stmt
{
public:
  friend class LogicalPlanGenerator;
  using value_vector = std::vector<std::unique_ptr<Value>>;
  UpdateStmt() = default;
  UpdateStmt(Table *table, std::string attr_name, int value_amount, std::vector<unique_ptr<Expression>>&&exprs, Value* values);

public:
  static RC create(Db *db, const UpdateSqlNode &update_sql, Stmt *&stmt);
  StmtType type() const override { return StmtType::UPDATE; }
public:
  Table *table() const { return table_; }
  auto attr_name() -> std::string { return attr_name_; }
  // auto filter() -> FilterStmt* { return filter_;}
  value_vector &values()  { return values_; }
  int    value_amount() const { return value_amount_; }

private:
  Table                      *table_{nullptr};
  std::string                 attr_name_;
  int                         value_amount_{0};
  std::vector<unique_ptr<Expression>> expressions_;
  value_vector                values_;
};
