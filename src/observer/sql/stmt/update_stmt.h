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
  UpdateStmt(Table *table, std::vector<Assignment*>*assignments, std::vector<unique_ptr<Expression>>&&exprs);
  
public:
  static RC create(Db *db, UpdateSqlNode &update_sql, Stmt *&stmt);
  StmtType type() const override { return StmtType::UPDATE; }
public:
  Table *table() const { return table_; }
  // auto filter() -> FilterStmt* { return filter_;}
  auto assignments() -> std::vector<Assignment*>*  { return assignments_; }
  size_t    value_amount() const { return assignments_->size(); }

private:
  Table                              *table_{nullptr};
  std::vector<Assignment*>           *assignments_{nullptr};
  std::vector<unique_ptr<Expression>> expressions_;
};
