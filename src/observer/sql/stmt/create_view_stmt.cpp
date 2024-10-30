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
// Created by Wangyunlai on 2023/6/13.
//

#include "common/log/log.h"
#include "common/types.h"
#include "sql/stmt/create_view_stmt.h"
#include "event/sql_debug.h"
#include "sql/stmt/select_stmt.h""

RC CreateViewStmt::create(Db *db, const CreateViewSqlNode &create_table, Stmt *&stmt) {
  Stmt *sel_stmt;
  auto rc = SelectStmt::create(db, create_table.query->selection, sel_stmt);
  if (RC::SUCCESS != rc) {
    return rc;
  }
  stmt = new CreateViewStmt(create_table.view_name, static_cast<SelectStmt*>(sel_stmt));
  return RC::SUCCESS;
}
