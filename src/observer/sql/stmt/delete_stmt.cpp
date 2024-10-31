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

#include "sql/stmt/delete_stmt.h"
#include "common/log/log.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/db/db.h"
#include "storage/table/table.h"
#include "sql/parser/expression_binder.h"
DeleteStmt::DeleteStmt(Table *table, std::vector<unique_ptr<Expression>>&&exprs) : table_(table), expressions_(std::move(exprs)) {}

DeleteStmt::~DeleteStmt()
{
  // if (nullptr != expressions_) {
  //   delete filter_stmt_;
  //   filter_stmt_ = nullptr;
  // }
}

RC DeleteStmt::create(Db *db, const DeleteSqlNode &delete_sql, Stmt *&stmt)
{
  const char *table_name = delete_sql.relation_name.c_str();
  if (nullptr == db || nullptr == table_name) {
    LOG_WARN("invalid argument. db=%p, table_name=%p", db, table_name);
    return RC::INVALID_ARGUMENT;
  }

  // check whether the table exists
  Table *table = db->find_table(table_name);
  if (nullptr == table) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  std::unordered_map<std::string, Table *> table_map;
  table_map.insert(std::pair<std::string, Table *>(std::string(table_name), table));
  BinderContext ctx;
  ctx.add_table(table);
  ExpressionBinder binder(ctx);
  vector<unique_ptr<Expression>> bound_where_expressions;
  if (delete_sql.conditions != nullptr && !delete_sql.conditions->empty()) {
    for (auto expr : *delete_sql.conditions) {
      std::unique_ptr<Expression> expr_ptr(expr);
      auto rc = binder.bind_expression(expr_ptr, bound_where_expressions);
      if (!OB_SUCC(rc)) {
        return rc;
      }
    }
  }


  stmt = new DeleteStmt(table, std::move(bound_where_expressions));
  return RC::SUCCESS;
}