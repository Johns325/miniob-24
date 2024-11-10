#pragma once

#include <unordered_map>
#include "sql/stmt/stmt.h"
class Table;
class FieldMeta;

class Db;
class OrderByUnit {
 public:
  OrderByUnit(Table* table, const FieldMeta* field, bool asc) : table_(table), field_(field), asc_(asc)  {}
  OrderByUnit(Table* table, const FieldMeta* field, bool asc, int type, Value &&base_vector) : table_(table), field_(field), asc_(asc), distance_type_(type), base_vector_(base_vector)  {}
  
 public:
  Table *table_;
  const FieldMeta *field_;
  bool asc_;
  int distance_type_; //默认0，当出现vector search变真正距离
  Value base_vector_;
};
class OrderByStmt : public Stmt {

 public:
  friend class OrderByLogicalOperator;
 public:
  OrderByStmt() = default;
  StmtType type() const override { return StmtType::ORDER_BY; }
  OrderByStmt(std::vector<std::unique_ptr<OrderByUnit>>&& units) : units_(std::move(units)) {}
  static RC create(std::unordered_map<string,Table*>& name_to_tables , std::vector<OrderBySqlNode>& order_by_specs, OrderByStmt *&stmt);
  std::vector<std::unique_ptr<OrderByUnit>>& units() { return units_; }
  
 private:
  std::vector<std::unique_ptr<OrderByUnit>> units_;
};