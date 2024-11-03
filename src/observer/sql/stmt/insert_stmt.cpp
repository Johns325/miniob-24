/* Copyright (c) 2021OceanBase and/or its affiliates. All rights reserved.
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

#include "sql/stmt/insert_stmt.h"
#include "common/log/log.h"
#include "storage/db/db.h"
#include "storage/table/table.h"
#include "common/type/attr_type.h"
#include "common/global_context.h"

InsertStmt::InsertStmt(Table *table, const Value *values, int value_amount)
    : table_(table), values_(values), value_amount_(value_amount)
{}

RC InsertStmt::create(Db *db, InsertSqlNode &inserts, Stmt *&stmt)
{
  const char *table_name = inserts.relation_name.c_str();
  if (nullptr == db || nullptr == table_name || inserts.values.empty()) {
    LOG_WARN("invalid argument. db=%p, table_name=%p, value_num=%d",
        db, table_name, static_cast<int>(inserts.values.size()));
    return RC::INVALID_ARGUMENT;
  }

  // check whether the table exists
  Table *table = db->find_table(table_name);
  if (nullptr == table) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  // check the fields number
  Value     *values     = inserts.values.data();
  const int        value_num  = static_cast<int>(inserts.values.size());
  const TableMeta &table_meta = table->table_meta();
  const int        field_num  = table_meta.field_num() - table_meta.sys_field_num();
  if (field_num != value_num) {
    LOG_WARN("schema mismatch. value num=%d, field num in schema=%d", value_num, field_num);
    return RC::SCHEMA_FIELD_MISSING;
  }
  for (int i = 0; i < field_num; ++i) {
    auto field = table_meta.field(table_meta.sys_field_num() + i);
    if (!field->nullable() && values[i].attr_type() == AttrType::NULLS) {
      // field is not null while insert value is null.
      return RC::INSERT_NULL_VALUE;
    }
    if(field->type() == AttrType::VECTORS) {
        if(inserts.values[i].attr_type() != AttrType::VECTORS) {
            return RC::SCHEMA_FIELD_TYPE_MISMATCH;
        }

        auto s = table_name + string(field->name());
        auto it = vector_map().find(s);
        if(it == vector_map().end() || it->second != inserts.values[i].length())  return RC::SCHEMA_FIELD_TYPE_MISMATCH;
      }
    if (field->type() == AttrType::DATES) {
      if (field->nullable()) {
        if (values[i].attr_type() == AttrType::NULLS)
          continue;
      }
      if (values[i].attr_type() != AttrType::CHARS) {
        return RC::SCHEMA_FIELD_TYPE_MISMATCH;
      }
      int date_val{0};
      std::string date_str(values[i].data());
      auto rc = date_str_to_int(date_str, date_val);
      if (RC::SUCCESS != rc) {
        return rc;
      }
      if(field->type() == AttrType::TEXTS) {
      if (65535 < values[i].length()) {
        LOG_WARN("Text length:%d, over max_length 65535", values[i].length());
        return RC::INVALID_ARGUMENT;
        }
      }
      values[i].set_date(date_val);
    }
  }
  // everything alright
  stmt = new InsertStmt(table, values, value_num);
  return RC::SUCCESS;
}
