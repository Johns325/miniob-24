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

#include "sql/stmt/update_stmt.h"
#include "common/value.h"
#include "storage/db/db.h"
#include "storage/table/table.h"
#include "storage/table/table_meta.h"
#include "sql/stmt/filter_stmt.h"
#include "sql/parser/expression_binder.h"
UpdateStmt::UpdateStmt(Table *table, std::string attr_name, int value_amount, std::vector<unique_ptr<Expression>>&&exprs, Value* values) 
: table_(table), attr_name_(attr_name), value_amount_(value_amount), expressions_(std::move(exprs)) {
  int k{0};
  while (k < value_amount_) {
    values_.emplace_back(new Value(values[k]));
    ++k;
  }
}

RC UpdateStmt::create(Db *db, const UpdateSqlNode &update, Stmt *&stmt)
{
  // TODO
  auto table = db->find_table(update.relation_name.c_str());
  if (table == nullptr){
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }
  auto field = table->table_meta().field(update.attribute_name.c_str());
  if (field == nullptr) {
    return RC::SCHEMA_FIELD_NOT_EXIST;
  }
  // TODO add support of updating multiple fields simultaneously.
  Value v(update.value);
  if (field->type() == AttrType::DATES) {
    if (v.attr_type() != AttrType::CHARS) {
      return RC::SCHEMA_FIELD_TYPE_MISMATCH;
    }
    int date_val{0};
    std::string date_str(v.data());
    auto rc = date_str_to_int(date_str, date_val);
    if (!OB_SUCC(rc)) {
      LOG_ERROR("update error, filed is date type while input is invalid. rc=%s", strrc(rc));
      return rc;
    }
    v.set_date(date_val);
  } else if (field->type() != v.attr_type()) {
    auto rc = DataType::type_instance(field->type())->cast_to(update.value, field->type(), v);
    if (!OB_SUCC(rc)) {
      LOG_ERROR("update error, type dismatch and cannot type B cannot cast to type A.... rc=%s", strrc(rc));
      return rc;
    }
  }
  
  // std::unordered_map<std::string, Table*> table_map{{update.relation_name, table}};
  BinderContext ctx;
  ctx.add_table(table);
  ExpressionBinder binder(ctx);
  vector<unique_ptr<Expression>> bound_where_expressions;
  if (update.conditions != nullptr) {
    for (auto expr : *update.conditions) {
      std::unique_ptr<Expression> expr_ptr(expr);
      auto rc = binder.bind_expression(expr_ptr, bound_where_expressions);
      if (!OB_SUCC(rc)) {
        return rc;
      }
    }
  }

  auto u_stmt = new UpdateStmt(table, update.attribute_name, 1, std::move(bound_where_expressions), &v);
  stmt = u_stmt;
  return RC::SUCCESS;
}
