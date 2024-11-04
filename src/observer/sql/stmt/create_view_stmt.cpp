#include "sql/stmt/create_view_stmt.h"


RC CreateViewStmt::create(Db *db, const CreateViewSqlNode &create_view, Stmt *&stmt) {
  Stmt *s=new Stmt();
  if (Stmt::create_stmt(db,create_view.query,s)!=RC::SUCCESS) return RC::UNIMPLEMENTED;//如果成功，s就成为我们需要的select_stmt
  stmt = new CreateViewStmt(create_view.view_name,s);
  sql_debug("create view statement: view name %s", create_view.view_name.c_str());
  return RC::SUCCESS;
}