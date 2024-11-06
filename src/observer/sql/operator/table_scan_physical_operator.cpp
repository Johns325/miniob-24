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
// Created by WangYunlai on 2021/6/9.
//

#include "sql/operator/table_scan_physical_operator.h"
#include "event/sql_debug.h"
#include "storage/table/table.h"

using namespace std;

RC TableScanPhysicalOperator::open(Trx *trx)
{
  if (record_scanner_.get()) {
    record_scanner_.release();
  }
  record_scanner_.reset(new RecordFileScanner);
  RC rc = table_->get_record_scanner(*record_scanner_.get(), trx, mode_);
  if (rc == RC::SUCCESS) {  
    tuple_.set_schema(table_, table_->table_meta().field_metas());
  }
  trx_ = trx;
  // 先對ComparisonExpr中的子查詢執行相應的查詢. table scan的多個predicate也是用AND鏈接
  for (auto &expr : predicates_) { 
    if (expr->type() !=  ExprType::COMPARISON) {
      return RC::PREDICATE_IS_NOT_COMPARISON;
    }
    auto cmp_expr = static_cast<ComparisonExpr*>(expr.get());
    if (cmp_expr->left()->type() == ExprType::SUB_QUERY) {
      auto sub_query = static_cast<SubQueryExpr*>(cmp_expr->left().get());
      if (!sub_query->break_pipeline())
        rc = cmp_expr->handle_sub_query(sub_query->get_physical_operator(), cmp_expr->value_list(true), true);
      if (!OB_SUCC(rc)) 
      return rc;
    }
    if (cmp_expr->right()->type() == ExprType::SUB_QUERY) {
      auto sub_query = static_cast<SubQueryExpr*>(cmp_expr->right().get());
      if (!sub_query->break_pipeline())
        rc = cmp_expr->handle_sub_query(sub_query->get_physical_operator(), cmp_expr->value_list(false), false);
      if (!OB_SUCC(rc))
        return rc;
    }
  }
  // table scan 可能包含filter，filter都是一個個ComparisonExpr組成，而ComparisonExpr肯能包含子查詢，這些子查詢的open操作將會在ProjectPhysicalOperator中完成。
  return rc;
}

RC TableScanPhysicalOperator::next()
{
  RC rc = RC::SUCCESS;

  bool filter_result = false;
  
  while (OB_SUCC(rc = record_scanner_->next(current_record_))) {
    // LOG_TRACE("got a record. rid=%s", current_record_.rid().to_string().c_str());
    
    tuple_.set_record(&current_record_);
    rc = filter(tuple_, filter_result);
    if (rc != RC::SUCCESS) {
      LOG_TRACE("record filtered failed=%s", strrc(rc));
      return rc;
    }

    if (filter_result) {
      //sql_debug("get a tuple: %s from table %s", tuple_.to_string().c_str(), table_->name());
      break;
    } else {
     // sql_debug("a tuple is filtered: %s from table %s", tuple_.to_string().c_str(), table_->name());
    }
  }
  return rc;
}

RC TableScanPhysicalOperator::close() { return record_scanner_->close_scan(); }

Tuple *TableScanPhysicalOperator::current_tuple()
{
  tuple_.set_record(&current_record_);
  return &tuple_;
}

string TableScanPhysicalOperator::param() const { return table_->name(); }

void TableScanPhysicalOperator::set_predicates(vector<unique_ptr<Expression>> &&exprs)
{
  predicates_ = std::move(exprs);
}

RC TableScanPhysicalOperator::filter(RowTuple &tuple, bool &result)
{
  RC    rc = RC::SUCCESS;
  Value value;
  for (unique_ptr<Expression> &expr : predicates_) {
    
    auto cmp_expr = static_cast<ComparisonExpr*>(expr.get());
    if (cmp_expr->left()->type() == ExprType::SUB_QUERY) {
      auto sub_expr = static_cast<SubQueryExpr*>(cmp_expr->left().get());
      if (sub_expr->break_pipeline()) {
        sub_expr->hand_expressions(&tuple);
        rc = cmp_expr->handle_sub_query_from_scrath(sub_expr, trx_, cmp_expr->value_list(true), true, &tuple);
        if (!OB_SUCC(rc))
            return rc;
      }
    }
    if (cmp_expr->right()->type() == ExprType::SUB_QUERY) {
      auto sub_expr = static_cast<SubQueryExpr*>(cmp_expr->right().get());
      if (sub_expr->break_pipeline()) {
        sub_expr->hand_expressions(&tuple);
        rc = cmp_expr->handle_sub_query_from_scrath(sub_expr, trx_, cmp_expr->value_list(false), false, &tuple);
        if (!OB_SUCC(rc))
          return rc;
      }
    }
    rc = expr->get_value(tuple, value);    
    if (rc != RC::SUCCESS) {
      return rc;
    }

    bool tmp_result = value.get_boolean();
    if (!tmp_result) {
      result = false;
      return rc;
    }
  }

  result = true;
  return rc;
}
