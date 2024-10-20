#pragma once

#include "sql/operator/physical_operator.h"
class UpdateStmt;
class AssignmentUnit;
class SubQueryPhysicalExpr;
class UpdatePhysicalOperator : public PhysicalOperator {
public:
  using value_vector = std::vector<std::unique_ptr<Value>>;
  // UpdatePhysicalOperator(Table* t, std::vector<std::unique_ptr<AssignmentUnit>>&&  assignments, std::vector<size_t>&& indices, std::vector<std::unique_ptr<SubQueryPhysicalExpr>>&& queries);
  UpdatePhysicalOperator(Table* table, std::string attr_name, int value_amount, value_vector&& values):table_(table), attr_name_(std::move(attr_name)), value_amount_(value_amount),values_(std::move(values)) {}
  PhysicalOperatorType type() const override { return PhysicalOperatorType::UPDATE;}
  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;
  Table* table() {return table_;}
  Tuple *current_tuple() override { 
    return nullptr; 
  }
private:
  // RC initialize_value(size_t index, const Value& new_value);
private:
  Table* table_;
  std::string attr_name_;
  RowTuple tuple_;
  int value_amount_;
  value_vector values_;
  // std::vector<std::unique_ptr<AssignmentUnit>> assignments_;
  // std::vector<size_t> indices_;
  // std::vector<std::unique_ptr<SubQueryPhysicalExpr>> sub_queries_;
  // std::vector<Value> new_values_;
  // std::set<std::string> cells_to_update_;
};