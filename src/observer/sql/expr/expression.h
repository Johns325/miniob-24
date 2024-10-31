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
// Created by Wangyunlai on 2022/07/05.
//

#pragma once

#include <memory>
#include <string>

#include "common/value.h"
#include "storage/field/field.h"
#include "sql/expr/aggregator.h"
#include "storage/common/chunk.h"
#include "sql/stmt/select_stmt.h"
// #include "sql/operator/physical_operator.h"
// #include "sql/operator/logical_operator.h"

class Tuple;
class ParsedSqlNode;
/**
 * @defgroup Expression
 * @brief 表达式
 */

/**
 * @brief 表达式类型
 * @ingroup Expression
 */
enum class ExprType
{
  NONE,
  STAR,                 ///< 星号，表示所有字段
  UNBOUND_FIELD,        ///< 未绑定的字段，需要在resolver阶段解析为FieldExpr
  UNBOUND_AGGREGATION,  ///< 未绑定的聚合函数，需要在resolver阶段解析为AggregateExpr

  FIELD,        ///< 字段。在实际执行时，根据行数据内容提取对应字段的值
  VALUE,        ///< 常量值
  CAST,         ///< 需要做类型转换的表达式
  COMPARISON,   ///< 需要做比较的表达式
  CONJUNCTION,  ///< 多个表达式使用同一种关系(AND或OR)来联结
  ARITHMETIC,   ///< 算术运算
  SUB_QUERY,
  ALISAS,   //这个类型没有具体的类，只是用作一个标识告诉select_stmt在解析时应该alias映射中找相应的表达式或者table。
  CONSTANT_VALUE_LIST,
  AGGREGATION,  ///< 聚合运算
};

/**
 * @brief 表达式的抽象描述
 * @ingroup Expression
 * @details 在SQL的元素中，任何需要得出值的元素都可以使用表达式来描述
 * 比如获取某个字段的值、比较运算、类型转换
 * 当然还有一些当前没有实现的表达式，比如算术运算。
 *
 * 通常表达式的值，是在真实的算子运算过程中，拿到具体的tuple后
 * 才能计算出来真实的值。但是有些表达式可能就表示某一个固定的
 * 值，比如ValueExpr。
 *
 * TODO 区分unbound和bound的表达式
 */
class Expression
{
public:
  Expression()          = default;
  virtual ~Expression() = default;

  /**
   * @brief 判断两个表达式是否相等
   */
  virtual bool equal(const Expression &other) const { return false; }
  /**
   * @brief 根据具体的tuple，来计算当前表达式的值。tuple有可能是一个具体某个表的行数据
   */
  virtual RC get_value(const Tuple &tuple, Value &value) const = 0;

  /**
   * @brief 在没有实际运行的情况下，也就是无法获取tuple的情况下，尝试获取表达式的值
   * @details 有些表达式的值是固定的，比如ValueExpr，这种情况下可以直接获取值
   */
  virtual RC try_get_value(Value &value) const { return RC::UNIMPLEMENTED; }

  /**
   * @brief 从 `chunk` 中获取表达式的计算结果 `column`
   */
  virtual RC get_column(Chunk &chunk, Column &column) { return RC::UNIMPLEMENTED; }

  /**
   * @brief 表达式的类型
   * 可以根据表达式类型来转换为具体的子类
   */
  virtual ExprType type() const = 0;

  /**
   * @brief 表达式值的类型
   * @details 一个表达式运算出结果后，只有一个值
   */
  virtual AttrType value_type() const = 0;

  /**
   * @brief 表达式值的长度
   */
  virtual int value_length() const { return -1; }
  virtual RC deep_copy(unique_ptr<Expression> &other) const {return RC::UNIMPLEMENTED;}

  /**
   * @brief 表达式的名字，比如是字段名称，或者用户在执行SQL语句时输入的内容
   */
  virtual const char *name() const { return name_.c_str(); }
  virtual void        set_name(std::string name) { name_ = name; }
  virtual const char *alias()  const { return alias_.c_str(); }
  virtual void        set_alias(std::string alias) {alias_ = alias; }

  /**
   * @brief 表达式在下层算子返回的 chunk 中的位置
   */
  virtual int  pos() const { return pos_; }
  virtual void set_pos(int pos) { pos_ = pos; }

  /**
   * @brief 用于 ComparisonExpr 获得比较结果 `select`。
   */
  virtual RC eval(Chunk &chunk, std::vector<uint8_t> &select) { return RC::UNIMPLEMENTED; }
  virtual std::string to_string() const {return "";}
protected:
  /**
   * @brief 表达式在下层算子返回的 chunk 中的位置
   * @details 当 pos_ = -1 时表示下层算子没有在返回的 chunk 中计算出该表达式的计算结果，
   * 当 pos_ >= 0时表示在下层算子中已经计算出该表达式的值（比如聚合表达式），且该表达式对应的结果位于
   * chunk 中 下标为 pos_ 的列中。
   */
  int pos_ = -1;

private:
  std::string name_;
  std::string alias_;
};

class StarExpr : public Expression
{
public:
  StarExpr() : table_name_() {}
  StarExpr(const char *table_name) : table_name_(table_name) {}
  virtual ~StarExpr() = default;

  ExprType type() const override { return ExprType::STAR; }
  AttrType value_type() const override { return AttrType::UNDEFINED; }

  RC get_value(const Tuple &tuple, Value &value) const override { return RC::UNIMPLEMENTED; }  // 不需要实现

  const char *table_name() const { return table_name_.c_str(); }
  std::string to_string() const override { return "[star:*]"; }
private:
  std::string table_name_;
};

class AliasExpr : public Expression {
public:
  AliasExpr() : alias_name_() {}
  AliasExpr(const char *alias_name) : alias_name_(alias_name) {}
  virtual ~AliasExpr() = default;

  ExprType type() const override { return ExprType::ALISAS; }
  AttrType value_type() const override { return AttrType::CHARS; }

  RC get_value(const Tuple &tuple, Value &value) const override { 
    value.set_string(alias_name_.c_str(), alias_name_.length()); 
    return RC::SUCCESS;
  }

  const char *alias_name() const { return alias_name_.c_str(); }
  std::string to_string() const override { return "[star:*]"; }
private:
  std::string alias_name_;
};

class UnboundFieldExpr : public Expression
{
public:
  UnboundFieldExpr(const std::string &table_name, const std::string &field_name)
      : table_name_(table_name), field_name_(field_name)
  {}

  virtual ~UnboundFieldExpr() = default;

  ExprType type() const override { return ExprType::UNBOUND_FIELD; }
  AttrType value_type() const override { return AttrType::UNDEFINED; }

  RC get_value(const Tuple &tuple, Value &value) const override { return RC::INTERNAL; }

  const char *table_name() const { return table_name_.c_str(); }
  const char *field_name() const { return field_name_.c_str(); }
  std::string to_string() const override { 
    stringstream ss;
    if (!table_name_.empty()) ss << table_name_ << '.';
    if (!field_name_.empty()) ss << field_name_;
    return ss.str();
  }
private:
  std::string table_name_;
  std::string field_name_;
};

/**
 * @brief 字段表达式
 * @ingroup Expression
 */
class FieldExpr : public Expression
{
public:
  FieldExpr() = default;
  FieldExpr(const Table *table, const FieldMeta *field) : field_(table, field) {}
  FieldExpr(const Field &field) : field_(field) {}

  virtual ~FieldExpr() = default;

  bool equal(const Expression &other) const override;

  ExprType type() const override { return ExprType::FIELD; }
  AttrType value_type() const override { return field_.attr_type(); }
  int      value_length() const override { return field_.meta()->len(); }

  Field &field() { return field_; }

  const Field &field() const { return field_; }
  RC deep_copy(unique_ptr<Expression> &other) const override {
    auto field_expr = new FieldExpr(field_);
    field_expr->using_outer_field_ = using_outer_field_;
    other.reset(field_expr);
    return RC::SUCCESS;
  }
  const char *table_name() const { return field_.table_name(); }
  const char *field_name() const { return field_.field_name(); }

  RC get_column(Chunk &chunk, Column &column) override;
  auto set_using_outer_field() {using_outer_field_ = true;}
  auto using_outer_field() const { return using_outer_field_; }
  RC get_value(const Tuple &tuple, Value &value) const override;

private:
  bool using_outer_field_{false};
  Field field_;
};

/**
 * @brief 常量值表达式
 * @ingroup Expression
 */
class ValueExpr : public Expression
{
public:
  ValueExpr() = default;
  explicit ValueExpr(const Value &value) : value_(value) {}

  virtual ~ValueExpr() = default;

  bool equal(const Expression &other) const override;

  RC get_value(const Tuple &tuple, Value &value) const override;
  RC get_column(Chunk &chunk, Column &column) override;
  RC try_get_value(Value &value) const override
  {
    value = value_;
    return RC::SUCCESS;
  }
  RC deep_copy(unique_ptr<Expression> &other) const override{
    other.reset(new ValueExpr(value_));
    return RC::SUCCESS;
  }
  ExprType type() const override { return ExprType::VALUE; }
  AttrType value_type() const override { return value_.attr_type(); }
  int      value_length() const override { return value_.length(); }

  void         get_value(Value &value) const { value = value_; }
  const Value &get_value() const { return value_; }
  Value &get_value() { return value_; }

private:
  Value value_;
};
class SelectStmt;
class LogicalOperator;
class PhysicalOperator;
class SubQueryExpr : public Expression 
{
public:
  friend class LogicalPlanGenerator;
  friend class PhysicalPlanGenerator;
  friend class UpdatePhysicalOperator;
  friend class PredicatePhysicalOperator;
  friend class SelectStmt;
  ~SubQueryExpr() {
    if (sql_node_)
      delete sql_node_;
    // if (logical_sub_query_)
    //   delete logical_sub_query_;
    // if (physical_sub_query_)
    //   delete physical_sub_query_;
    if (select_stmt_)
      delete select_stmt_;
  }
  SubQueryExpr() = default;
  explicit SubQueryExpr(ParsedSqlNode* sql_node) : sql_node_(sql_node){}
  ExprType type() const override { return ExprType::SUB_QUERY; }
  AttrType value_type() const override { return (select_stmt_->query_expressions().front())->value_type(); }
  int      value_length() const override { return 0; }
  RC get_value(const Tuple &tuple, Value &value) const override { return RC::SUCCESS; }
  auto get_sql_node() -> ParsedSqlNode* { return sql_node_;}
  auto select_stmt() -> SelectStmt* {return select_stmt_;}
  void set_select_stmt(SelectStmt* stmt) {select_stmt_ = stmt;}
  PhysicalOperator* get_physical_operator() {return physical_sub_query_;}
  // void clean_sql_node() { delete sql_node_; }
private:
  ParsedSqlNode *sql_node_{nullptr};
  SelectStmt* select_stmt_{nullptr};
  LogicalOperator *logical_sub_query_{nullptr};
  PhysicalOperator* physical_sub_query_{nullptr};
};


class ConstantValueListExpr : public Expression {
public:
  ConstantValueListExpr() = default;
  ConstantValueListExpr(std::vector<Value*>* values);
  RC get_value(const Tuple &tuple, Value &value) const override;
  std::vector<std::unique_ptr<Value>>& values() { return values_; }
  ExprType type() const override { return ExprType::CONSTANT_VALUE_LIST; }
  // we assume all values in list have the same type
  AttrType value_type() const override { return (values_.empty() ? AttrType::UNDEFINED : values_[0]->attr_type()); }
private:
  std::vector<std::unique_ptr<Value>> values_;
};

/**
 * @brief 类型转换表达式
 * @ingroup Expression
 */
class CastExpr : public Expression
{
public:
  CastExpr(std::unique_ptr<Expression> child, AttrType cast_type);
  virtual ~CastExpr();

  ExprType type() const override { return ExprType::CAST; }

  RC get_value(const Tuple &tuple, Value &value) const override;

  RC try_get_value(Value &value) const override;

  AttrType value_type() const override { return cast_type_; }

  std::unique_ptr<Expression> &child() { return child_; }

private:
  RC cast(const Value &value, Value &cast_value) const;

private:
  std::unique_ptr<Expression> child_;      ///< 从这个表达式转换
  AttrType                    cast_type_;  ///< 想要转换成这个类型
};

/**
 * @brief 比较表达式
 * @ingroup Expression
 */
class ComparisonExpr : public Expression
{
public:
  ComparisonExpr(CompOp comp, std::unique_ptr<Expression> left, std::unique_ptr<Expression> right);
  virtual ~ComparisonExpr();

  ExprType type() const override { return ExprType::COMPARISON; }
  RC       get_value(const Tuple &tuple, Value &value) const override;
  AttrType value_type() const override { return AttrType::BOOLEANS; }
  CompOp   comp() const { return comp_; }

  /**
   * @brief 根据 ComparisonExpr 获得 `select` 结果。
   * select 的长度与chunk 的行数相同，表示每一行在ComparisonExpr 计算后是否会被输出。
   */
  RC eval(Chunk &chunk, std::vector<uint8_t> &select) override;

  std::unique_ptr<Expression> &left() { return left_; }
  std::unique_ptr<Expression> &right() { return right_; }

  /**
   * 尝试在没有tuple的情况下获取当前表达式的值
   * 在优化的时候，可能会使用到
   */
  RC try_get_value(Value &value) const override;
  bool is_range_comparator() const { return  comp_ == CompOp::IN_OP || comp_ == CompOp::NOT_IN;}
  RC handle_sub_query(PhysicalOperator*query_phy_oper , std::vector<Value>&values, bool);
  /**
   * compare the two tuple cells
   * @param value the result of comparison
   */
  RC compare_value(const Value &left, const Value &right, bool &value) const;

  template <typename T>
  RC compare_column(const Column &left, const Column &right, std::vector<uint8_t> &result) const;
  std::vector<Value>& value_list(bool left) { return left ? left_values_ : right_values_; }
  void set_emited(bool left) {
    if (left)
      left_sub_query_emited = true;
    else 
      right_sub_query_emited = true;
  }
  bool isMatch(std::string s, std::string p) const;
private:
  void hand_null(int &) const;
  RC get_operand(bool left, Tuple& tuple, Value& value);
private:
  CompOp                      comp_;
  std::unique_ptr<Expression> left_;
  std::unique_ptr<Expression> right_;
  bool left_sub_query_emited{false};
  bool right_sub_query_emited{false};
  std::vector<Value> left_values_;
  std::vector<Value> right_values_;
};

/**
 * @brief 联结表达式
 * @ingroup Expression
 * 多个表达式使用同一种关系(AND或OR)来联结
 * 当前miniob仅有AND操作
 */
class ConjunctionExpr : public Expression
{
public:
  enum class Type
  {
    AND,
    OR,
  };

public:
  ConjunctionExpr(Type type, std::vector<std::unique_ptr<Expression>> &children);
  ConjunctionExpr(ConjunctionExpr && other) : conjunction_type_(other.conjunction_type_), children_(std::move(other.children_)) {}
  ConjunctionExpr(Type type, std::vector<std::unique_ptr<Expression>> &&children): conjunction_type_(type), children_(std::move(children)) {}
  virtual ~ConjunctionExpr() = default;

  ExprType type() const override { return ExprType::CONJUNCTION; }
  AttrType value_type() const override { return AttrType::BOOLEANS; }
  RC       get_value(const Tuple &tuple, Value &value) const override;

  Type conjunction_type() const { return conjunction_type_; }

  std::vector<std::unique_ptr<Expression>> &children() { return children_; }

private:
  Type                                     conjunction_type_;
  std::vector<std::unique_ptr<Expression>> children_;
};

/**
 * @brief 算术表达式
 * @ingroup Expression
 */
class ArithmeticExpr : public Expression
{
public:
  enum class Type
  {
    ADD,
    SUB,
    MUL,
    DIV,
    NEGATIVE,
    L2_DISTANCE,
    INNER_PRODUCT,
    COSINE_DISTANCE,
  };

public:
  ArithmeticExpr(Type type, Expression *left, Expression *right);
  ArithmeticExpr(Type type, std::unique_ptr<Expression> left, std::unique_ptr<Expression> right);
  virtual ~ArithmeticExpr() = default;

  bool     equal(const Expression &other) const override;
  ExprType type() const override { return ExprType::ARITHMETIC;}

  AttrType value_type() const override;
  int      value_length() const override
  {
    if(arithmetic_type_ == Type::L2_DISTANCE || arithmetic_type_ == Type::COSINE_DISTANCE || arithmetic_type_ == Type::INNER_PRODUCT)
      return 4;
    if (!right_) {
      return left_->value_length();
    }
    return 4;  // sizeof(float) or sizeof(int)
  };
  virtual RC deep_copy(unique_ptr<Expression> &other) const override {
    std::unique_ptr<Expression> left_expr;
    std::unique_ptr<Expression> right_expr;
    left_->deep_copy(left_expr);
    right_->deep_copy(right_expr);
    other.reset(new ArithmeticExpr(arithmetic_type_, std::move(left_expr), std::move(right_expr)));
    return RC::SUCCESS;
  }
  RC get_value(const Tuple &tuple, Value &value) const override;

  RC get_column(Chunk &chunk, Column &column) override;

  RC try_get_value(Value &value) const override;


  Type arithmetic_type() const { return arithmetic_type_; }

  std::unique_ptr<Expression> &left() { return left_; }
  std::unique_ptr<Expression> &right() { return right_; }

private:
  RC calc_value(const Value &left_value, const Value &right_value, Value &value) const;

  RC calc_column(const Column &left_column, const Column &right_column, Column &column) const;

  template <bool LEFT_CONSTANT, bool RIGHT_CONSTANT>
  RC execute_calc(const Column &left, const Column &right, Column &result, Type type, AttrType attr_type) const;

private:
  Type                        arithmetic_type_;
  std::unique_ptr<Expression> left_;
  std::unique_ptr<Expression> right_;
};

class UnboundAggregateExpr : public Expression
{
public:
  UnboundAggregateExpr(const char *aggregate_name, Expression *child);
  virtual ~UnboundAggregateExpr() = default;

  ExprType type() const override { return ExprType::UNBOUND_AGGREGATION; }

  const char *aggregate_name() const { return aggregate_name_.c_str(); }

  std::unique_ptr<Expression> &child() { return child_; }

  RC       get_value(const Tuple &tuple, Value &value) const override { return RC::INTERNAL; }
  AttrType value_type() const override { return child_->value_type(); }

private:
  std::string                 aggregate_name_;
  std::unique_ptr<Expression> child_;
};

class AggregateExpr : public Expression
{
public:
  enum class Type
  {
    COUNT,
    SUM,
    AVG,
    MAX,
    MIN,
  };

public:
  AggregateExpr(Type type, Expression *child);
  AggregateExpr(Type type, std::unique_ptr<Expression> child);
  virtual ~AggregateExpr() = default;

  bool equal(const Expression &other) const override;

  ExprType type() const override { return ExprType::AGGREGATION; }

  AttrType value_type() const override { return child_->value_type(); }
  int      value_length() const override { return child_->value_length(); }

  RC get_value(const Tuple &tuple, Value &value) const override;

  RC get_column(Chunk &chunk, Column &column) override;

  Type aggregate_type() const { return aggregate_type_; }

  std::unique_ptr<Expression> &child() { return child_; }
  RC deep_copy(unique_ptr<Expression> &other) const override {
    std::unique_ptr<Expression> child;
    child_->deep_copy(child);
    other.reset(new AggregateExpr(aggregate_type_, std::move(child)));
    return RC::SUCCESS;
  }
  const std::unique_ptr<Expression> &child() const { return child_; }

  std::unique_ptr<Aggregator> create_aggregator() const;

public:
  static RC type_from_string(const char *type_str, Type &type);

private:
  Type                        aggregate_type_;
  std::unique_ptr<Expression> child_;
};