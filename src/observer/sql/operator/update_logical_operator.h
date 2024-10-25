
#pragma once

#include "sql/operator/logical_operator.h"
#include "common/value.h"
#include <vector>
// class AssignmentUnit;
class Assignment;
class SubQueryLogicalExpr;

class UpdateLogicalOperator : public LogicalOperator{
 public:
  using value_vector = std::vector<std::unique_ptr<Value>>;
  UpdateLogicalOperator() = default;
  // UpdateLogicalOperator(Table*table, std::string attr_name, int value_count, value_vector&& values): table_(table), attr_name_(std::move(attr_name)), value_amount_(value_count), values_(std::move(values)) {}
  UpdateLogicalOperator(Table*table, vector<Assignment*>* assignments): table_(table), assignments_(assignments) {}
    // int index{0};
    // while (index < value_amount_) {
    //   values_.emplace_back(new Value(values[index]));
    //   ++index;
    // }
  // UpdateLogicalOperator(Table*, const Value*,int ,const FieldMeta*);
  // UpdateLogicalOperator(Table*, std::vector<std::unique_ptr<AssignmentUnit>>&&  assignments, std::vector<size_t>&& indices, std::vector<std::unique_ptr<SubQueryLogicalExpr>>&& queries ,const FieldMeta*);
  // virtual ~UpdateLogicalOperator() = default;
  LogicalOperatorType type() const override {return LogicalOperatorType::UPDATE;}
  Table* table() {return table_;}
  auto assignments() -> std::vector<Assignment*>*  { return assignments_; }
  // std::string attr_name() { return attr_name_;}
  // value_vector &values() {return values_;}
  // int value_count() const {return value_amount_;}
  // const FieldMeta * field_meta() {return field_meta_;}
  // std::vector<std::unique_ptr<SubQueryLogicalExpr>>& sub_queries() { return sub_queries_; }
  // std::vector<size_t>& indices() { return sub_query_indices_; }
  // std::vector<std::unique_ptr<AssignmentUnit>>& assignments() { return assignments_; }
 private:
  Table                            *table_ = nullptr;
  std::vector<Assignment*>         *assignments_{nullptr};
  // value_vector                      values_;       
  // std::vector<size_t> sub_query_indices_;
  // std::vector<std::unique_ptr<SubQueryLogicalExpr>> sub_queries_;
  // const FieldMeta *field_meta_;
  
};