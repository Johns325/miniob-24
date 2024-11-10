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
#include "sql/stmt/create_vector_index_stmt.h"
#include "storage/db/db.h"
#include "sql/stmt/stmt.h"
#include "common/log/log.h"
#include "sql/stmt/calc_stmt.h"
#include "sql/stmt/create_index_stmt.h"
#include "sql/stmt/create_table_stmt.h"
#include "sql/stmt/delete_stmt.h"
#include "sql/stmt/desc_table_stmt.h"
#include "sql/stmt/exit_stmt.h"
#include "sql/stmt/explain_stmt.h"
#include "sql/stmt/help_stmt.h"
#include "sql/stmt/insert_stmt.h"
#include "sql/stmt/load_data_stmt.h"
#include "sql/stmt/select_stmt.h"
#include "sql/stmt/set_variable_stmt.h"
#include "sql/stmt/show_tables_stmt.h"
#include "sql/stmt/trx_begin_stmt.h"
#include "sql/stmt/trx_end_stmt.h"
#include "sql/stmt/drop_table_stmt.h"
#include "sql/stmt/create_select_stmt.h"
#include "sql/stmt/update_stmt.h"
#include "sql/parser/expression_binder.h"
#include "create_view_stmt.h"
#include "storage/db/db.h"
bool stmt_type_ddl(StmtType type)
{
  switch (type) {
    case StmtType::CREATE_TABLE:
    case StmtType::DROP_TABLE:
    case StmtType::DROP_INDEX:
    case StmtType::CREATE_INDEX: {
      return true;
    }
    default: {
      return false;
    }
  }
}
RC Stmt::create_stmt(Db *db, ParsedSqlNode &sql_node, Stmt *&stmt)
{
  stmt = nullptr;

  switch (sql_node.flag) {
    case SCF_INSERT: {
      return InsertStmt::create(db, sql_node.insertion, stmt);
    }
    case SCF_DELETE: {
      return DeleteStmt::create(db, sql_node.deletion, stmt);
    }
    case SCF_SELECT: {
      db->col_references.clear();
      if (sql_node.selection.relations.size() == 1) {
        auto rel_info = sql_node.selection.relations[0];
        auto view = db->find_view(rel_info->relation_name.c_str());
        if (view != nullptr) {
          // select by view
          for (auto &expr: sql_node.selection.expressions) {
            if (expr->type() == ExprType::UNBOUND_FIELD) {
              auto unbound_expr = static_cast<UnboundFieldExpr*>(expr.get());
              auto field_name = string(unbound_expr->name());
              if (view->name_to_meta.find(field_name) == view->name_to_meta.end()) {
                return RC::INTERNAL;
              }
            } else if (expr->type() == ExprType::UNBOUND_AGGREGATION) {
              auto aggre_expr = static_cast<UnboundAggregateExpr*>(expr.get());
              auto field_name = string(aggre_expr->child()->name());
              //printf("child=%s\n",field_name.c_str());
              if (strcmp(field_name.c_str(), "*") == 0) {
                string agg_name(aggre_expr->name());
                auto pos = agg_name.find("(");
                auto aggre_func_name = agg_name.substr(0, pos);
                if (aggre_func_name != "count") {
                  return RC::INVALID_ARGUMENT;
                }
                continue;
              }
              if (view->name_to_meta.find(field_name) == view->name_to_meta.end()) {
                return RC::INTERNAL;
              }
            } else if (expr->type() == ExprType::STAR) continue;
          }
        }
      }
      return SelectStmt::create(db, sql_node.selection, stmt, nullptr);
    }

    case SCF_EXPLAIN: {
      return ExplainStmt::create(db, sql_node.explain, stmt);
    }

    case SCF_CREATE_INDEX: {
      return CreateIndexStmt::create(db, sql_node.create_index, stmt);
    }

    case SCF_CREATE_TABLE: {
      return CreateTableStmt::create(db, sql_node.create_table, stmt);
    }

    case SCF_UPDATE:{
      return UpdateStmt::create(db, sql_node.update, stmt);
    }

    case SCF_DESC_TABLE: {
      return DescTableStmt::create(db, sql_node.desc_table, stmt);
    }

    case SCF_HELP: {
      return HelpStmt::create(stmt);
    }
    case SCF_CREATE_VECTOR_INDEX :{
      return CreateVectorIndexStmt::create(db, sql_node.create_vector_index, stmt);
    }
    case SCF_CREATE_TABLE_SELECT: {
      return CreateTableSelectStmt::create(db, sql_node.create_table_select, stmt);
    }
    case SCF_SHOW_TABLES: {
      return ShowTablesStmt::create(db, stmt);
    }

    case SCF_BEGIN: {
      return TrxBeginStmt::create(stmt);
    }

    case SCF_COMMIT:
    case SCF_ROLLBACK: {
      return TrxEndStmt::create(sql_node.flag, stmt);
    }

    case SCF_EXIT: {
      return ExitStmt::create(stmt);
    }

    case SCF_SET_VARIABLE: {
      return SetVariableStmt::create(sql_node.set_variable, stmt);
    }

    case SCF_LOAD_DATA: {
      return LoadDataStmt::create(db, sql_node.load_data, stmt);
    }

    case SCF_CALC: {
      return CalcStmt::create(sql_node.calc, stmt);
    }

    case SCF_DROP_TABLE: {
      return DropTableStmt::create(db, sql_node.drop_table, stmt);
    }

    case SCF_CREATE_VIEW: {
      return CreateViewStmt::create(db,sql_node.create_view,stmt);
    }
    default: {
      LOG_INFO("Command::type %d doesn't need to create statement.", sql_node.flag);
    } break;
  }
  return RC::UNIMPLEMENTED;
}
