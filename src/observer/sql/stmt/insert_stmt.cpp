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
#include "sql/expr/expression.h"

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
  View *view=db->find_view(table_name);
  Table *table = db->find_table(table_name);
  if (nullptr == table&&view==nullptr) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }
  if (view!=nullptr) {
    std::vector<Table*> tables=view->get_select()->tables();
    if (tables.size()!=1) {
      LOG_WARN("only select_stmt with one table can be inserted,view=%s",view->name());
      return RC::INVALID_ARGUMENT;
    }
     
    table=tables[0];
    std::vector<std::unique_ptr<Expression>> &exprs=view->get_select()->query_expressions();
    if (exprs.empty()) {
      LOG_WARN("no fields selected, view=%s",view->name());
      return RC::INVALID_ARGUMENT;
    }
    // check the fields number
    Value     *values     = inserts.values.data();
    int        value_num  = static_cast<int>(inserts.values.size());
    const TableMeta &table_meta = table->table_meta();
    const int        field_num  = table_meta.field_num() - table_meta.sys_field_num();
    if (exprs[0]->type()==ExprType::STAR) {}
    else if (exprs[0]->type()==ExprType::FIELD) {
      std::vector<Value>     insert_values     = inserts.values;
      int i=0;
      std::vector<Value> total_values;
      for (int j=0;j<field_num;j++) {
        if (exprs[i]->type()!=ExprType::FIELD) {
          LOG_WARN("wrong expr type");
          return RC::INVALID_ARGUMENT;
        }
        FieldExpr* expr=dynamic_cast<FieldExpr*>(exprs[i].get());
        auto field = table_meta.field(table_meta.sys_field_num() + j);
        if (expr->field().field_name()==field->name()) {
          total_values.push_back(insert_values[i]);
          i++;
        }
        else {
          Value* nullval=new Value();
          nullval->set_null();
          total_values.push_back(*nullval);
        }
      }
      values= total_values.data();
      value_num=field_num;
    }
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
          if(inserts.values[i].attr_type() != AttrType::VECTORS ||
            inserts.values[i].length() != field->len())
              return RC::SCHEMA_FIELD_TYPE_MISMATCH;
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
        values[i].set_date(date_val);
      }
    }
    // everything alright
    stmt = new InsertStmt(table, values, value_num); 
    return RC::SUCCESS;  
  }
    
    
  
  Value     *values     = inserts.values.data();
  int        value_num  = static_cast<int>(inserts.values.size());
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
    if(field->type() == AttrType::TEXTS) {
      if (65535 < values[i].length()) {
        LOG_WARN("Text length:%d, over max_length 65535", values[i].length());
        return RC::INVALID_ARGUMENT;
        }
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
      
      values[i].set_date(date_val);
    }
  }
  // everything alright
  stmt = new InsertStmt(table, values, value_num);
  return RC::SUCCESS;
}
