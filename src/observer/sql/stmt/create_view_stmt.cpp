#include "sql/stmt/create_view_stmt.h"
#include "sql/stmt/select_stmt.h"
#include "sql/expr/expression.h"
#include "deps/common/lang/string.h"
#include "common/type/attr_type.h"
#include "sql/parser/expression_binder.h"

static int default_attr_length(AttrType type) {
  switch (type) {
    case AttrType::CHARS:
    case AttrType::INTS:
    case AttrType::FLOATS:
    case AttrType::DATES: {
      return 4;
    } break;
    case AttrType::BOOLEANS: {
      return 1;
    }
    case AttrType::VECTORS: {
      // TODO 
      return 65535;
    };
    default: {
      return -1;
    }
  }
}

RC CreateViewStmt::create(Db *db, const CreateViewSqlNode &create_view, Stmt *&stmt) {
  Stmt *s=new SelectStmt();
  if (Stmt::create_stmt(db,*create_view.query,s)!=RC::SUCCESS) {
    delete s;
    return RC::UNIMPLEMENTED;
  }//如果成功，s就成为我们需要的select_stmt
  SelectStmt* ss=(SelectStmt*)s;
  if (create_view.has_schema) {
    std::vector<AttrInfoSqlNode> infos;
    infos.assign(create_view.attr_infos.begin(),create_view.attr_infos.end());
    stmt=new CreateViewStmt(create_view.view_name,ss,std::move(infos),create_view.has_schema);
    return RC::SUCCESS;
  }
  auto &expresssions = ss->query_expressions();
  std::vector<AttrInfoSqlNode> infos(expresssions.size());
  int i = 0;
  for (auto &expr_uptr : expresssions) {
    auto expr = expr_uptr.get();
    infos[i].name = (common::is_blank(expr->alias()) ? expr->name() : expr->alias());
    infos[i].type = expr->value_type();
    infos[i].nullable = true; // 默认可以为nul，如果查询中某个字段要求不为null，在进行相应的设置
    if (expr->type() == ExprType::FIELD) {
      auto field_expr = static_cast<FieldExpr*>(expr);
      infos[i].length = field_expr->field().meta()->len();
      infos[i].nullable = field_expr->field().meta()->nullable();
    } else {
      if (expr->type() == ExprType::VALUE) {
        infos[i].length = static_cast<ValueExpr*>(expr)->get_value().length();
      } else {
        infos[i].length = default_attr_length(infos[i].type); // 使用默認長度。這裏需要考慮下vector
      }
      infos[i].nullable = true;
    }
    ++i;
  }
  stmt = new CreateViewStmt(create_view.view_name,ss,std::move(infos),create_view.has_schema);
  //sql_debug("create view statement: view name %s", create_view.view_name.c_str());
  //delete s;
  return RC::SUCCESS;
}