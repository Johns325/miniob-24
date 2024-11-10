#include "sql/operator/ivfflat_index_physical_operator.h"
#include "sql/stmt/order_by_stmt.h"
#include "storage/index/ivfflat_index.h"
#include "common/types.h"
RC IvfflatPhysicalOperator::open(Trx*trx) {
  auto index = unit_->table_->ivfflat_index(unit_->field_);
  ASSERT(index != nullptr, "ivfflat index shall be null");
  auto n = unit_->base_vector_.length() / 4;
  (void)n;
  vector<float> v(unit_->base_vector_.length() / 4);
  memcpy(v.data(), (char*)unit_->base_vector_.get_vector(), unit_->base_vector_.length());
  rids_ = index->ann_search(v, limit_);
  return RC::SUCCESS;
}



RC IvfflatPhysicalOperator::next() {
  if (index_ == rids_.size()) {
    return RC::RECORD_EOF;
  }
  unit_->table_->get_record(rids_[index_], current_record_);
  current_tuple_.set_record(&current_record_);
  ++index_;
  return RC::SUCCESS;
}
RC IvfflatPhysicalOperator::close() {
  return RC::SUCCESS;
}