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
  auto field = table_->table_meta().field(attr_name_.c_str());
  // if (field == nullptr || field) {
  //   return RC::SCHEMA_FIELD_NOT_EXIST;
  // }
  
  while ((rc = children_[0]->next()) == RC::SUCCESS) {
    if (OB_SUCC(rc)) {
      auto tuple = static_cast<RowTuple*>(children_[0]->current_tuple());
      auto record = tuple->record();
      // if (children_[0]->type() == PhysicalOperatorType::INDEX_SCAN) 
      auto rc = table_->set_value_to_record(record.data(), *values_[0].get(), field);
      if (!OB_SUCC(rc)) {
        return rc;
      }
    }
  }
  return rc;
}
RC UpdatePhysicalOperator::close() {
  children_[0]->close();
  return RC::SUCCESS;
}