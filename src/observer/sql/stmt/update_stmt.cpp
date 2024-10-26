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
#include "sql/stmt/select_stmt.h"
UpdateStmt::UpdateStmt(Table *table, std::vector<Assignment*>*assignments, std::vector<unique_ptr<Expression>>&&exprs)
: table_(table), assignments_(assignments), expressions_(std::move(exprs)) {}

RC UpdateStmt::create(Db *db, UpdateSqlNode &update, Stmt *&stmt)
{
  // TODO
  auto table = db->find_table(update.relation_name.c_str());
  if (table == nullptr){
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }
  for(auto assign : *update.assignments) {

    auto field = table->table_meta().field(assign->attr_name.c_str());
    if (field == nullptr) {
      return RC::SCHEMA_FIELD_NOT_EXIST;
    }
    // TODO add support of updating multiple fields simultaneously.
    // if(assign->right_hand_side->type() != ExprType::VALUE)
    //   continue;
    if (assign->right_hand_side->type() == ExprType::SUB_QUERY) {
      Stmt * stmt;
      auto sub_query_expr = static_cast<SubQueryExpr*>(assign->right_hand_side); 
      auto sql_node = sub_query_expr->get_sql_node();
      auto rc = SelectStmt::create(db, sql_node->selection, stmt);
      if (!OB_SUCC(rc)) {
      return rc;
      }
      // auto select_stmt = static_cast<SelectStmt*>(stmt);
      sub_query_expr->set_select_stmt(static_cast<SelectStmt*>(stmt));
      // sub_query_expr->clean_sql_node();
      continue;
    }
    // only constant value need to check type contriant.
    auto &v = static_cast<ValueExpr*>(assign->right_hand_side)->get_value();
     if (!field->nullable() && v.attr_type() == AttrType::NULLS) {
      // field is not null while insert value is null.
      return RC::INSERT_NULL_VALUE;
    }
    if(field->type() == AttrType::VECTORS) {
      if(v.attr_type() != AttrType::VECTORS || v.length() != field->len())
        return RC::SCHEMA_FIELD_TYPE_MISMATCH;
    }
    if (field->type() == AttrType::DATES) {
      if (field->nullable()) {
        if (v.attr_type() == AttrType::NULLS)
          continue;
      }
      if (v.attr_type() != AttrType::CHARS) {
        return RC::SCHEMA_FIELD_TYPE_MISMATCH;
      }
      int date_val{0};
      std::string date_str(v.data());
      auto rc = date_str_to_int(date_str, date_val);
      if (RC::SUCCESS != rc) {
        return rc;
      }
      v.set_date(date_val);
    }
  }
  

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
  

  auto u_stmt = new UpdateStmt(table, update.assignments, std::move(bound_where_expressions));
  stmt = u_stmt;
  return RC::SUCCESS;
}
