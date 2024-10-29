#include "sql/operator/update_physical_operator.h"
#include <unordered_set>
#include "storage/trx/trx.h"
RC  UpdatePhysicalOperator::open(Trx *trx) {
  RC rc = RC::SUCCESS;
  if (children_.empty()) {
    return RC::SUCCESS;
  }
  auto child = children_[0].get();
  rc = child->open(trx);
  if (OB_FAIL(rc)) {
    LOG_ERROR("failed to open update phy operator's child operator:%s", strrc(rc));
    return rc;
  }
  // 先從所有的子查詢獲取到結果.
  // case1. 子查詢返回多列
  // case2. 子查詢返回多個值
  // case3. 子查詢返回null 但是某一額column不允許null
  // case1 應該直接返回false 而 case2 和case3再發現有值時才返回false，如果外部查詢沒有值則返回SUCCESS
  auto tb_meta = table_->table_meta();
  value_ptrs_.resize(assignments_->size());
  for (size_t i = 0; i < assignments_->size(); i++) {
    Assignment * assign = (*assignments_)[i];
    if (assign->right_hand_side->type() == ExprType::VALUE) {
      auto value = static_cast<ValueExpr*>(assign->right_hand_side)->get_value();
      value_ptrs_[i] = value;
    } else if (assign->right_hand_side->type() == ExprType::SUB_QUERY) {
      auto expr = (static_cast<SubQueryExpr*>(assign->right_hand_side))->physical_sub_query_;
      TupleSchema schema;
      expr->tuple_schema(schema);
      if (schema.cell_num() > 1) {
        // case 1
        return RC::SUB_QUERY_RETURNS_MULTIPLE_COLUMNS;
      }
      if (!expr->children().empty()) {
        expr->children()[0]->open(trx);
      }
      std::vector<Value> values_from_sub_query;
      while ((rc = expr->next()) == RC::SUCCESS) {
        auto tuple = expr->current_tuple();
        Value v;
        tuple->cell_at(0,v);
        values_from_sub_query.emplace_back(v);
      }
      expr->close();
      if (values_from_sub_query.size() > 1) {
        // case 2
        invalid_  = true;
        break;
      } else if (values_from_sub_query.empty() && !tb_meta.field((*assignments_)[i]->attr_name.c_str())->nullable()) {
        // case 3
        invalid_ = true;
      }
      value_ptrs_[i] = values_from_sub_query[0];
    }
  }


  std::list<Record> delete_records;
  std::list<Record> insert_records;
  while ((rc = children_[0]->next()) == RC::SUCCESS) {
    if (invalid_) {
      return RC::INTERNAL;
    }
    auto tuple = static_cast<RowTuple*>(children_[0]->current_tuple());
    auto record = tuple->record();
    // trx->delete_record(table_, record);
    Record old_record;
    old_record.copy_data(record.data(), record.len());
    old_record.set_rid(record.rid());
    rc = table_->delete_record(record);
    delete_records.push_back(std::move(old_record));
    for (size_t i = 0; i < assignments_->size(); i++) {
      auto field = tb_meta.field((*assignments_)[i]->attr_name.c_str());
      Value real_value;
      if (value_ptrs_[i].attr_type() == field->type()) {
        real_value = value_ptrs_[i];
      } else {
        Value::cast_to(value_ptrs_[i], field->type(), real_value);
      }
      rc = table_->set_value_to_record(record.data(), real_value, field);
      if (!OB_SUCC(rc)) {
        return rc;
      }
    }
    Record new_one;
    new_one.copy_data(record.data(), record.len());
    new_one.set_rid(record.rid());
    rc = table_->insert_record(record);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to insert record by transaction. rc=%s", strrc(rc));
      if (rc == RC::RECORD_DUPLICATE_KEY) {
        for (auto &r : insert_records)
          table_->delete_record(r);
        for (auto &r : delete_records)
          table_->insert_record(r);
      }
      return rc;
    }
    insert_records.push_back(new_one);
  }
  return RC::SUCCESS;
}
RC UpdatePhysicalOperator::next() {
  return RC::RECORD_EOF;
}
RC UpdatePhysicalOperator::close() {
  children_[0]->close();
  return RC::SUCCESS;
}