#include "sql/stmt/create_view_stmt.h"
#include "sql/stmt/select_stmt.h"
#include "sql/expr/expression.h"
#include "deps/common/lang/string.h"
#include "common/type/attr_type.h"
#include "sql/parser/expression_binder.h"

RC CreateViewStmt::create(Db *db, const CreateViewSqlNode &create_view, Stmt *&stmt) {
  Stmt *s=new SelectStmt();
  if (Stmt::create_stmt(db,*create_view.query,s)!=RC::SUCCESS) {
    delete s;
    return RC::UNIMPLEMENTED;
  }//如果成功，s就成为我们需要的select_stmt
  SelectStmt* ss=(SelectStmt*)s;
  if (create_view.has_schema) {
    std::vector<std::string> infos;
    infos.assign(create_view.infos.begin(),create_view.infos.end());
    stmt=new CreateViewStmt(create_view.view_name,ss,std::move(infos),create_view.has_schema);
    return RC::SUCCESS;
  }
  std::vector<std::string> infos;
  stmt = new CreateViewStmt(create_view.view_name,ss,std::move(infos),create_view.has_schema);
  //sql_debug("create view statement: view name %s", create_view.view_name.c_str());
  //delete s;
  return RC::SUCCESS;
}