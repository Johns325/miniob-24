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
// Created by WangYunlai on 2022/6/27.
//

#include "sql/operator/predicate_physical_operator.h"
#include "common/log/log.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/field/field.h"
#include "storage/record/record.h"
#include "sql/expr/expression.h"
#include "event/sql_debug.h"
PredicatePhysicalOperator::PredicatePhysicalOperator(std::unique_ptr<Expression> expr) : expression_(std::move(expr))
{
  ASSERT(expression_->value_type() == AttrType::BOOLEANS, "predicate's expression should be BOOLEAN type");
}

    // auto cmp_expr = static_cast<ComparisonExpr*>(expr.get());
    // if (cmp_expr->left()->type() == ExprType::SUB_QUERY) {
    //   auto sub_query = static_cast<SubQueryExpr*>(cmp_expr->left().get());
    //   if (!sub_query->break_pipeline())
    //     rc = cmp_expr->handle_sub_query(sub_query->get_physical_operator(), cmp_expr->value_list(true), true);
    //   if (!OB_SUCC(rc)) 
    //   return rc;
    // }
    // if (cmp_expr->right()->type() == ExprType::SUB_QUERY) {
    //   auto sub_query = static_cast<SubQueryExpr*>(cmp_expr->right().get());
    //   if (!sub_query->break_pipeline())
    //     rc = cmp_expr->handle_sub_query(sub_query->get_physical_operator(), cmp_expr->value_list(false), false);
    //   if (!OB_SUCC(rc))
    //     return rc;
    // }
RC PredicatePhysicalOperator::hand_all_sub_queries() {
  RC rc{RC::SUCCESS};
  if (expression_->type() == ExprType::CONJUNCTION) {
    auto conj_expr = static_cast<ConjunctionExpr*>(expression_.get());
    for (auto& child : conj_expr->children()) {
      if (child->type() == ExprType::COMPARISON) {
        auto cmp_expr = static_cast<ComparisonExpr*>(child.get());
        // if (cmp_expr->left()->type() == ExprType::SUB_QUERY && !static_cast<SubQueryExpr*>(cmp_expr->left().get())->break_pipeline()) {
        if (cmp_expr->left()->type() == ExprType::SUB_QUERY ) {
          rc = cmp_expr->handle_sub_query(static_cast<SubQueryExpr*>(cmp_expr->left().get())->get_physical_operator(), cmp_expr->value_list(true),  true);
        }
        if (!OB_SUCC(rc))
          return rc;
        // if (cmp_expr->right()->type() == ExprType::SUB_QUERY && !static_cast<SubQueryExpr*>(cmp_expr->right().get())->break_pipeline()) {
        if (cmp_expr->right()->type() == ExprType::SUB_QUERY) {
         rc = cmp_expr->handle_sub_query(static_cast<SubQueryExpr*>(cmp_expr->right().get())->get_physical_operator(), cmp_expr->value_list(false),  false);
         if (!OB_SUCC(rc))
          return rc;
        }
        if (cmp_expr->left()->type() == ExprType::VALUE && cmp_expr->right()->type() == ExprType::VALUE) {
          Value cell;
          if (RC::SUCCESS != cmp_expr->try_get_value(cell))
            continue;
          if (cell.get_boolean() && (conj_expr->children().size() == 1 || conj_expr->conjunction_type() == ConjunctionExpr::Type::OR)) {
            predicates_always_true_ = true;
            break;
          }
          else if (!cell.get_boolean() && (conj_expr->children().size() == 1 || conj_expr->conjunction_type() == ConjunctionExpr::Type::AND)){
            predicates_always_false_ = true;
            break;
          }
        }
      }
    }
  } else if (expression_->type() == ExprType::COMPARISON) {
    auto cmp_expr = static_cast<ComparisonExpr*>(expression_.get());
    if (cmp_expr->left()->type() == ExprType::SUB_QUERY && !static_cast<SubQueryExpr*>(cmp_expr->left().get())->break_pipeline()) {
      rc =cmp_expr->handle_sub_query(static_cast<SubQueryExpr*>(cmp_expr->left().get())->get_physical_operator(), cmp_expr->value_list(true),  true);
      if (!OB_SUCC(rc))
        return rc;
    }
    if (cmp_expr->right()->type() == ExprType::SUB_QUERY && !static_cast<SubQueryExpr*>(cmp_expr->right().get())->break_pipeline()) {
      rc = cmp_expr->handle_sub_query(static_cast<SubQueryExpr*>(cmp_expr->right().get())->get_physical_operator(), cmp_expr->value_list(false),  false);
      if (!OB_SUCC(rc))
        return rc;
    }
    if (cmp_expr->left()->type() == ExprType::VALUE && cmp_expr->right()->type() == ExprType::VALUE) {
      Value cell;
      if (RC::SUCCESS == cmp_expr->try_get_value(cell)) {  
        // 因为predicate只有一个，左右直接根据CELL的值设置always_true or always_false
        if (cell.get_boolean()) {
          predicates_always_true_ = true;
        } else
          predicates_always_false_ = true;
      }
    }
  }
  return rc;
}

RC PredicatePhysicalOperator::hand_all_sub_queries_every_time(Tuple *t) {
  RC rc{RC::SUCCESS};
  if (expression_->type() == ExprType::CONJUNCTION) {
    auto conj_expr = static_cast<ConjunctionExpr*>(expression_.get());
    for (auto& child : conj_expr->children()) {
      if (child->type() == ExprType::COMPARISON) {
        auto cmp_expr = static_cast<ComparisonExpr*>(child.get());
        // if (cmp_expr->left()->type() == ExprType::SUB_QUERY && static_cast<SubQueryExpr*>(cmp_expr->left().get())->break_pipeline()) {
        if (cmp_expr->left()->type() == ExprType::SUB_QUERY) {
          rc = cmp_expr->handle_sub_query_from_scrath(static_cast<SubQueryExpr*>(cmp_expr->left().get()), trx_, cmp_expr->value_list(true),  true, t);
          if (!OB_SUCC(rc))
            return rc;
        }
        // if (cmp_expr->right()->type() == ExprType::SUB_QUERY && static_cast<SubQueryExpr*>(cmp_expr->right().get())->break_pipeline()) {
        if (cmp_expr->right()->type() == ExprType::SUB_QUERY) {
          rc = cmp_expr->handle_sub_query_from_scrath(static_cast<SubQueryExpr*>(cmp_expr->right().get()),trx_, cmp_expr->value_list(false),  false, t);
          if (!OB_SUCC(rc))
            return rc;
        }
      }
    }
  } else if (expression_->type() == ExprType::COMPARISON) {
    auto cmp_expr = static_cast<ComparisonExpr*>(expression_.get());
    // if (cmp_expr->left()->type() == ExprType::SUB_QUERY && static_cast<SubQueryExpr*>(cmp_expr->left().get())->break_pipeline()) {
    if (cmp_expr->left()->type() == ExprType::SUB_QUERY) {
      rc = cmp_expr->handle_sub_query_from_scrath(static_cast<SubQueryExpr*>(cmp_expr->left().get()), trx_, cmp_expr->value_list(true),  true, t);
      if (!OB_SUCC(rc))
        return rc;
    }
    if (cmp_expr->right()->type() == ExprType::SUB_QUERY) {
      rc = cmp_expr->handle_sub_query_from_scrath(static_cast<SubQueryExpr*>(cmp_expr->right().get()),trx_, cmp_expr->value_list(false),  false, t);
      if (!OB_SUCC(rc))
        return rc;
    }
  }
  return rc;
}

RC PredicatePhysicalOperator::simplify_comparisons() {
   RC rc{RC::SUCCESS};
  if (expression_->type() == ExprType::CONJUNCTION) {
    auto conj_expr = static_cast<ConjunctionExpr*>(expression_.get());
    for (auto& child : conj_expr->children()) {
      if (child->type() == ExprType::COMPARISON) {
        auto cmp_expr = static_cast<ComparisonExpr*>(child.get());
        if (cmp_expr->left()->type() == ExprType::VALUE && cmp_expr->right()->type() == ExprType::VALUE) {
          Value cell;
          if (RC::SUCCESS != cmp_expr->try_get_value(cell))
            continue;
          if (cell.get_boolean() && (conj_expr->children().size() == 1 || conj_expr->conjunction_type() == ConjunctionExpr::Type::OR)) {
            predicates_always_true_ = true;
            break;
          }
          else if (!cell.get_boolean() && (conj_expr->children().size() == 1 || conj_expr->conjunction_type() == ConjunctionExpr::Type::AND)){
            predicates_always_false_ = true;
            break;
          }
        }
      }
    }
  } else if (expression_->type() == ExprType::COMPARISON) {
    auto cmp_expr = static_cast<ComparisonExpr*>(expression_.get());
    if (cmp_expr->left()->type() == ExprType::VALUE && cmp_expr->right()->type() == ExprType::VALUE) {
      Value cell;
      if (RC::SUCCESS == cmp_expr->try_get_value(cell)) {  
        // 因为predicate只有一个，左右直接根据CELL的值设置always_true or always_false
        if (cell.get_boolean()) {
          predicates_always_true_ = true;
        } else
          predicates_always_false_ = true;
      }
    }
  }
  return rc;
}

RC PredicatePhysicalOperator::open(Trx *trx)
{
  if (children_.size() != 1) {
    LOG_WARN("predicate operator must has one child");
    return RC::INTERNAL;
  }
  trx_ = trx;
  auto rc = children_[0]->open(trx);
  if (!OB_SUCC(rc)) {
    return rc;
  }
  // rc = hand_all_sub_queries();
  rc = simplify_comparisons();
  if (!OB_SUCC(rc))
    return rc;
  return RC::SUCCESS;
}

RC PredicatePhysicalOperator::next()
{
  if (predicates_always_false_) { // predicates are always false.
    return RC::RECORD_EOF;
  }
  RC                rc   = RC::SUCCESS;
  PhysicalOperator *oper = children_.front().get();
  while (RC::SUCCESS == (rc = oper->next())) {
    Tuple *tuple = oper->current_tuple();
    if (nullptr == tuple) {
      rc = RC::INTERNAL;
      LOG_WARN("failed to get tuple from operator");
      break;
    }
    if (predicates_always_true_) { //不用过滤，conditions可能返回true
      return RC::SUCCESS;
    }
    for (auto expr : expressions_to_set_each_time_) {
      if (expr->type() == ExprType::FIELD) {
        static_cast<FieldExpr*>(expr)->put_tuple(tuple);
      } else {
        sql_debug("oh my gosh,we only support reference outer field.");
      }
    }
    // for (auto query : sub_queries_)
    rc = hand_all_sub_queries_every_time(tuple);
    if (!OB_SUCC(rc))
      return rc;
    Value value;
    rc = expression_->get_value(*tuple, value);
    if (rc == RC::DIVIDE_ZERO) {
      continue;
    }
    if (rc != RC::SUCCESS) {
      return rc;
    }

    if (value.get_boolean()) {
      sql_debug("get a tuple: %s ", tuple->to_string().c_str());
      return rc;
    }
  }
  return rc;
}

RC PredicatePhysicalOperator::close()
{
  children_[0]->close();
  return RC::SUCCESS;
}

Tuple *PredicatePhysicalOperator::current_tuple() { return children_[0]->current_tuple(); }

RC PredicatePhysicalOperator::tuple_schema(TupleSchema &schema) const
{
  return children_[0]->tuple_schema(schema);
}
