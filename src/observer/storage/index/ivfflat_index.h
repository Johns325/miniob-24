/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#pragma once

#include "storage/index/index.h"
#include "sql/stmt/create_vector_index_stmt.h"
enum class Distance_Type:int32_t {
  L2_DISTANCE = 1,
  COSINE_DISTANCE,
  INNER_PRODUCT,
};

enum class Index_Type :int32_t {
  IVFFLAT = 1,
};
/**
 * @brief ivfflat 向量索引
 * @ingroup Index
 */
class IvfflatIndex : public Index
{
public:
  IvfflatIndex(){};
  virtual ~IvfflatIndex() noexcept {};

  RC create(Table *table,const IndexMeta &index_meta, CreateVectorIndexStmt& stmt)
  {
    table_ = table;
    Index::init(index_meta, stmt.field_metas_);
    lists_ = stmt.lists_;
    probes_ = stmt.probes_;
    type_ = Index_Type::IVFFLAT;
    distance_type_ = (stmt.distance_ == 1 ? Distance_Type::L2_DISTANCE : (stmt.distance_ == 2 ? Distance_Type::COSINE_DISTANCE : Distance_Type::INNER_PRODUCT));
    inited_ = true;
    field = stmt.field_meta()[0];
    return RC::SUCCESS;
  };
  RC open(Table *table, const char *file_name, const IndexMeta &index_meta, const FieldMeta &field_meta) override
  {

    return RC::SUCCESS;
  };

  bool is_vector_index() override { return true; }

  vector<RID> ann_search(const vector<float> &base_vector, size_t limit) { return vector<RID>(); }

  RC close() { return RC::SUCCESS; }

  RC insert_entry(const char *record, const RID *rid) override { return RC::SUCCESS; };
  RC delete_entry(const char *record, const RID *rid) override { return RC::SUCCESS; };
  IndexScanner *create_scanner(const char *left_key, int left_len, bool left_inclusive, const char *right_key,
      int right_len, bool right_inclusive) override {
        return nullptr;
      }
  RC sync() override { return RC::SUCCESS; };

public:
  bool   inited_ {false};
  Table *table_  {nullptr};
  Distance_Type distance_type_;
  Index_Type type_;
  int    lists_  = 1;
  int    probes_ = 1;
  const FieldMeta* field;
};
