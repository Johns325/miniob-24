#pragma once

#include "sql/stmt/select_stmt.h"
#include <memory>

class View
{
  explicit View(std::unique_ptr<SelectStmt> stmt) : stmt_(std::move(stmt)) {}

  SelectStmt *get_select_stmt() { return stmt_.get(); }

private:
  std::unique_ptr<SelectStmt> stmt_;
};