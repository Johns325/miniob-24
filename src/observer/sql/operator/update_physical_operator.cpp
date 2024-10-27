#include "sql/operator/update_physical_operator.h"
#include <unordered_set>
#include "storage/trx/trx.h"
RC  UpdatePhysicalOperator::open(Trx *trx) {
  RC rc = RC::SUCCESS;
  if (!children_.empty()) {
    auto child = children_[0].get();
    rc = child->open(trx);
    if (OB_FAIL(rc)) {
      LOG_ERROR("failed to open update phy operator's child operator:%s", strrc(rc));
      return rc;
    }
  }

  value_ptrs_.resize(assignments_->size());
  for (size_t i = 0; i < assignments_->size(); i++) {
    Assignment * assign = (*assignments_)[i];
    if (assign->right_hand_side->type() == ExprType::VALUE) {
      value_ptrs_[i] = static_cast<ValueExpr*>(assign->right_hand_side)->get_value();
    } else {
      auto expr = (static_cast<SubQueryExpr*>(assign->right_hand_side))->physical_sub_query_;
      if (!expr->children().empty()) {
        expr->children()[0]->open(trx);
      }
      sub_query_indices_.insert({i, expr});
    }
  }
  this->trx = trx;
  return rc;
}
RC UpdatePhysicalOperator::next() {
  RC rc = RC::SUCCESS;
  auto tb_meta = table_->table_meta();
  
  // 先從所有的子查詢獲取到結果.
  // case1. 子查詢返回多列
  // case2. 子查詢返回多個值
  // case3. 子查詢返回null 但是某一額column不允許null
  for(auto &pr : sub_query_indices_) {
    auto phy_oper = pr.second;
    TupleSchema schema;
    phy_oper->tuple_schema(schema);
    if (schema.cell_num() > 1) {
      // case 1
      return RC::SUB_QUERY_RETURNS_MULTIPLE_COLUMNS;
    }
    std::vector<Value> values_from_sub_query;
    while ((rc = phy_oper->next()) == RC::SUCCESS) {
      auto tuple = phy_oper->current_tuple();
      Value v;
      tuple->cell_at(0,v);
       values_from_sub_query.emplace_back(std::move(v));
    }

    phy_oper->close();
    if (values_from_sub_query.size() > 1) {
      // case 2
      return RC::SUB_QUERY_RETURNS_MULTIPLE_VALUES;
    } else if (values_from_sub_query.empty() && !tb_meta.field((*assignments_)[pr.first]->attr_name.c_str())->nullable()) {
      // case 3
      return RC::ASSIGNMENT_NULL_VALUE;
    }
    value_ptrs_[pr.first] = std::move(values_from_sub_query[0]);
  }
  while ((rc = children_[0]->next()) == RC::SUCCESS) {
    if (OB_SUCC(rc)) {
      auto tuple = static_cast<RowTuple*>(children_[0]->current_tuple());
      auto record = tuple->record();
      // trx->delete_record(table_, record);
      table_->delete_record(record);
      for (size_t i = 0; i < assignments_->size(); i++) {
        auto field = tb_meta.field((*assignments_)[i]->attr_name.c_str());
        rc = table_->set_value_to_record(record.data(), value_ptrs_[i], field);
        if (!OB_SUCC(rc)) {
          return rc;
        }
      }
      rc = table_->insert_record(record);
      if (rc != RC::SUCCESS) {
        LOG_WARN("failed to insert record by transaction. rc=%s", strrc(rc));
      }
      // for (size_t k = 0; k < assignments_->size(); ++k) {
      //   auto assign = (*assignments_)[k];
      //   auto field = tb_meta.field(assign->attr_name.c_str());
      //   RC rc = RC::SUCCESS;
      //   if (assign->right_hand_side->type() == ExprType::VALUE) {
      //     auto v = static_cast<ValueExpr*>(assign->right_hand_side)->get_value();   
      //     rc = table_->set_value_to_record(record.data(), v, field);
      //   } else if (assign->right_hand_side->type() == ExprType::SUB_QUERY) {
      //     // TODO handle sub query.
          
      //   }
      //   if (!OB_SUCC(rc)) {
      //     return rc;
      //   }
      // }
    }
  }
  return rc;
}
RC UpdatePhysicalOperator::close() {
  children_[0]->close();
  return RC::SUCCESS;
}