
#include "sql/stmt/create_select_stmt.h"
#include "sql/stmt/select_stmt.h"
#include "sql/expr/expression.h"
#include "deps/common/lang/string.h"
#include "common/type/attr_type.h"

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
RC CreateTableSelectStmt::create(Db *db, CreateTableSelectSqlNode &create_table, Stmt *&stmt) {
  Stmt* sel_stmt;
  auto rc = SelectStmt::create(db, create_table.query->selection, sel_stmt);
  if (!OB_SUCC(rc)) {
    return rc;
  }
  auto select_stmt = static_cast<SelectStmt*>(sel_stmt);
  if (create_table.has_schema) {
    stmt = new CreateTableSelectStmt(db, create_table.relation_name, sel_stmt, std::move(create_table.attr_infos));
    return RC::SUCCESS;
  }
  auto &expresssions = select_stmt->query_expressions();
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
  stmt = new CreateTableSelectStmt(db, create_table.relation_name, sel_stmt, std::move(infos));
  return RC::SUCCESS;
}

