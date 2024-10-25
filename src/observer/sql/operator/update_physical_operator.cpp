#include "sql/operator/update_physical_operator.h"

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
  return rc;
}
RC UpdatePhysicalOperator::next() {
  RC rc = RC::SUCCESS;
  // auto field = table_->table_meta().field(attr_name_.c_str());
  // if (field == nullptr || field) {
  //   return RC::SCHEMA_FIELD_NOT_EXIST;
  // }
  // std::vector<const FieldMeta*> metas(assignments_->size());
  // for (auto assign : assignments_) {
  //   auto meta = table_->table_meta_
  // }
  auto tb_meta = table_->table_meta();
  while ((rc = children_[0]->next()) == RC::SUCCESS) {
    if (OB_SUCC(rc)) {
      auto tuple = static_cast<RowTuple*>(children_[0]->current_tuple());
      auto record = tuple->record();
      for (auto assign: *assignments_) {
        auto field = tb_meta.field(assign->attr_name.c_str());
        RC rc = RC::SUCCESS;
        if (assign->right_hand_side->type() == ExprType::VALUE) {
          auto v = static_cast<ValueExpr*>(assign->right_hand_side)->get_value();   
          rc = table_->set_value_to_record(record.data(), v, field);
        } else if (assign->right_hand_side->type() == ExprType::SUB_QUERY) {
          // TODO handle sub query.
          Value v;
          rc = table_->set_value_to_record(record.data(), v, field);
        }
        if (!OB_SUCC(rc)) {
          return rc;
        }
      }
    }
  }
  return rc;
}
RC UpdatePhysicalOperator::close() {
  children_[0]->close();
  return RC::SUCCESS;
}