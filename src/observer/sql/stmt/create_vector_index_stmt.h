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
// Created by Wangyunlai on 2023/4/25.
//

#pragma once

#include <string>

#include "sql/stmt/stmt.h"

struct CreateIndexSqlNode;
class Table;
class FieldMeta;

/**
 * @brief 创建索引的语句
 * @ingroup Statement
 */
class CreateVectorIndexStmt : public Stmt
{
public:
  friend class Table;
  friend class IvfflatIndex;
  CreateVectorIndexStmt(Table *table, std::vector<const FieldMeta*> field_metas, const std::string &index_name, int distance, int type, int lists, int probes)
      : table_(table), field_metas_(field_metas), index_name_(index_name),distance_(distance), type_(type), lists_(lists), probes_(probes)
  {}

  virtual ~CreateVectorIndexStmt() = default;

  StmtType type() const override { return StmtType::CREATE_VECTOR_INDEX; }

  Table             *table() const { return table_; }
  std::vector<const FieldMeta*>& field_meta() { return field_metas_; }
  const std::string &index_name() const { return index_name_; }
public:
  static RC create(Db *db, CreateVectorIndexSqlNode &create_index, Stmt *&stmt);
private:
  Table                             *table_      = nullptr;
  std::vector<const FieldMeta*>      field_metas_;
  std::string                        index_name_;
  int distance_{0};
  int type_{0};
  int lists_{0};
  int probes_{0};
};
