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

#include "sql/operator/create_select_physical_operator.h"
#include "common/log/log.h"
#include "storage/table/table.h"
#include "storage/trx/trx.h"
#include "storage/db/db.h"
#include "storage/table/table_meta.h"

RC CreateTableSelectPhysicalOperator::open(Trx *trx)
{
  auto table = db_->find_table(table_name_.c_str());
  if (table != nullptr) {
    return RC::SCHEMA_TABLE_EXIST;
  }
  auto rc = db_->create_table(table_name_.c_str(), infos_);
  if (rc != RC::SUCCESS) {
    return rc;
  }
  if (children().empty()) {
    return RC::SUCCESS;
  }
  table = db_->find_table(table_name_.c_str());
  auto child = children_.front().get();
  if ((rc = child->open(trx)) != RC::SUCCESS) {
    return rc;
  }
  auto meta = table->table_meta();
  TupleSchema schema;
  child->tuple_schema(schema);
  while ((rc = child->next()) == RC::SUCCESS) {
    auto tuple = child->current_tuple();
    // char *data = new char[meta.record_size()];
    std::vector<Value>values;
    for (int i = 0; i < schema.cell_num(); i++) {
      Value v;
      tuple->cell_at(i, v);
      values.emplace_back(v);
    }
    Record r;
    table->make_record(values.size(), values.data(), r);
    rc = table->insert_record(r);
    if (!OB_SUCC(rc)) {
      return rc;
    }
  }
  return RC::SUCCESS;
}

RC CreateTableSelectPhysicalOperator::next() {
  return RC::RECORD_EOF;
}

RC CreateTableSelectPhysicalOperator::close()
{
  return children_.front()->close();
}
