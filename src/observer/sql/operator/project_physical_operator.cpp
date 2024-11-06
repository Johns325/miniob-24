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
// Created by WangYunlai on 2022/07/01.
//

#include "sql/operator/project_physical_operator.h"
#include "common/log/log.h"
#include "storage/record/record.h"
#include "common/lang/string.h"
#include "storage/table/table.h"

using namespace std;

ProjectPhysicalOperator::ProjectPhysicalOperator(vector<unique_ptr<Expression>> &&expressions, int limit)
  : expressions_(std::move(expressions)), tuple_(expressions_), limit_(limit)
{
}

RC ProjectPhysicalOperator::open(Trx *trx)
{
  RC rc {RC::SUCCESS};
  for (auto query : sub_queries_) {
    rc = query->get_physical_operator()->open(trx);
    // if (!OB_SUCC(rc)) {
    //   return rc;
    // }
  }
  if (children_.empty()) {
    return RC::SUCCESS;
  }

  PhysicalOperator *child = children_[0].get();
  rc    = child->open(trx);
  if (rc != RC::SUCCESS && rc != RC::NOTFOUND) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
   return rc;
  }
  // 對所有子查詢執行open
  return RC::SUCCESS;
}

RC ProjectPhysicalOperator::next()
{
  if (limit_ < 0) {
    return children_[0]->next();
  }
  if (children_.empty() || limit_-- == 0) {
    return RC::RECORD_EOF;
  }
  return children_[0]->next();
}

RC ProjectPhysicalOperator::close()
{
  for (auto query: sub_queries_) {
    query->get_physical_operator()->close();
  }
  if (!children_.empty()) {
    children_[0]->close();
  }
  return RC::SUCCESS;
}
Tuple *ProjectPhysicalOperator::current_tuple()
{
  tuple_.set_tuple(children_[0]->current_tuple());
  return &tuple_;
}

RC ProjectPhysicalOperator::tuple_schema(TupleSchema &schema) const
{
  for (const unique_ptr<Expression> &expression : expressions_) {
    if (!common::is_blank(expression->alias())) {
      schema.append_cell(expression->alias());
    } else 
      schema.append_cell(expression->name());
  }
  return RC::SUCCESS;
}

void ProjectPhysicalOperator::set_sub_queries(std::list<SubQueryExpr*>& other) {
  for (auto iter = other.begin(); iter != other.end(); ++iter) {
    sub_queries_.push_back(*iter);
    *iter = nullptr;
  }
}