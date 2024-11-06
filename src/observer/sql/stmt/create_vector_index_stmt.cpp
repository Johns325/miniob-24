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

#include "sql/stmt/create_vector_index_stmt.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "storage/db/db.h"
#include "storage/table/table.h"

using namespace std;
using namespace common;


RC CreateVectorIndexStmt::create(Db *db, CreateVectorIndexSqlNode &create_index, Stmt *&stmt)
{
  stmt = nullptr;

  const char *table_name = create_index.relation_name.c_str();
  if (is_blank(table_name) || is_blank(create_index.index_name.c_str()) ||
      is_blank(create_index.attribute_name.c_str())) {
    LOG_WARN("invalid argument. db=%p, table_name=%p, index name=%s, or maybe attrbute names are blank",
        db, table_name, create_index.index_name.c_str());
    return RC::INVALID_ARGUMENT;
  }

  // check whether the table exists
  Table *table = db->find_table(table_name);
  if (nullptr == table) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }
  std::vector<const FieldMeta*> metas;
  // std::vector<const FieldMeta*> metas;
  const FieldMeta *field_meta = table->table_meta().field(create_index.attribute_name.c_str());
  if (nullptr == field_meta) {
    LOG_WARN("no such field in table. db=%s, table=%s, field name=%s", db->name(), table_name, create_index.attribute_name.c_str());
    return RC::SCHEMA_FIELD_NOT_EXIST;
  }
  if (field_meta->type() != AttrType::VECTORS) {
    return RC::SCHEMA_FIELD_TYPE_MISMATCH;
  }
  metas.push_back(field_meta);
  Index *index = table->find_index(create_index.index_name.c_str());
  if (nullptr != index) {
    LOG_WARN("index with name(%s) already exists. table name=%s", create_index.index_name.c_str(), table_name);
    return RC::SCHEMA_INDEX_NAME_REPEAT;
  }
  // negative one indicates invalid value for all these four parameters.
  int lists{-1};
  int probes{-1};
  int distance{-1};
  int type{-1}; // 1 indicates ivfflat.
  if (create_index.args) {
    auto &mp = *create_index.args;
    if (mp.find("type") != mp.end()) {
      auto str = mp.find("type")->second;
      if (str == "ivfflat")
        type = 1;
    }
    if (mp.find("distance") != mp.end()) {
      auto val = mp.find("distance")->second;
      if (val == "l2")
        distance = 1;
      else if (val == "cosine")
        distance = 2;
      else if (val == "inner")
        distance = 3;
    }
    if (mp.find("probes") != mp.end()) {
      auto val = mp.find("probes")->second;
      probes = std::stoi(val);
    }
    if (mp.find("lists") != mp.end()) {
      lists = std::stoi(mp.find("lists")->second);
    }
  }
  printf("%d %d %d %d\n", lists,probes, distance, type);
  delete create_index.args;
  stmt = new CreateVectorIndexStmt(table, metas, create_index.index_name, distance, type, lists, probes);
  return RC::SUCCESS;
}
