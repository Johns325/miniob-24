/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#include "common/lang/comparator.h"
#include "common/lang/sstream.h"
#include "common/log/log.h"
#include "common/type/float_type.h"
#include "common/value.h"
#include "common/lang/limits.h"
#include "common/value.h"

#include<cmath>
int FloatType::compare(const Value &left, const Value &right) const
{
  ASSERT(left.attr_type() == AttrType::FLOATS, "left type is not integer");
  ASSERT(right.attr_type() == AttrType::INTS || right.attr_type() == AttrType::FLOATS, "right type is not numeric");
  float left_val  = left.get_float();
  float right_val = right.get_float();
  return common::compare_float((void *)&left_val, (void *)&right_val);
}

RC FloatType::add(const Value &left, const Value &right, Value &result) const
{
  result.set_float(left.get_float() + right.get_float());
  return RC::SUCCESS;
}
RC FloatType::subtract(const Value &left, const Value &right, Value &result) const
{
  result.set_float(left.get_float() - right.get_float());
  return RC::SUCCESS;
}
RC FloatType::multiply(const Value &left, const Value &right, Value &result) const
{
  result.set_float(left.get_float() * right.get_float());
  return RC::SUCCESS;
}

RC FloatType::divide(const Value &left, const Value &right, Value &result) const
{
  if (right.get_float() > -EPSILON && right.get_float() < EPSILON) {
    // NOTE:
    // 设置为浮点数最大值是不正确的。通常的做法是设置为NULL，但是当前的miniob没有NULL概念，所以这里设置为浮点数最大值。
    result.set_float(numeric_limits<float>::max());
  } else {
    result.set_float(left.get_float() / right.get_float());
  }
  return RC::SUCCESS;
}

RC FloatType::cast_to(const Value &val, AttrType type, Value &result) const {
  switch (type)
  {
  case AttrType::INTS: {
    auto int_val = static_cast<int>(val.get_float());
    result.set_int(int_val);
  } break;
  case AttrType::CHARS: {
    auto str = std::to_string(val.get_float());
    result.set_string(str.c_str(), str.length());
  } break;
  
  default: {
    return RC::SCHEMA_FIELD_TYPE_MISMATCH;
  } break;
  }
  return RC::SUCCESS;
}

RC FloatType::negative(const Value &val, Value &result) const
{
  result.set_float(-val.get_float());
  return RC::SUCCESS;
}

RC FloatType::set_value_from_str(Value &val, const string &data) const
{
  RC                rc = RC::SUCCESS;
  stringstream deserialize_stream;
  deserialize_stream.clear();
  deserialize_stream.str(data);

  float float_value;
  deserialize_stream >> float_value;
  if (!deserialize_stream || !deserialize_stream.eof()) {
    rc = RC::SCHEMA_FIELD_TYPE_MISMATCH;
  } else {
    val.set_float(float_value);
  }
  return rc;
}

RC FloatType::to_string(const Value &val, string &result) const
{
  stringstream ss;
  ss << common::double_to_str(val.value_.float_value_);
  result = ss.str();
  return RC::SUCCESS;
}

RC FloatType::l2_distance(const Value &left, const Value &right, Value &result) const {
  ASSERT(left.attr_type() == AttrType::VECTORS, "left type is not vector");
  ASSERT(right.attr_type() == AttrType::VECTORS, "right type is not vector");
  ASSERT(left.length_ == right.length_, "left vector len != right vector len");
  ASSERT(result.attr_type() == AttrType::FLOATS,"result should be float");
  // 计算 L2 距离
  float sum = 0.0f;
  int num_elements = left.length_ / sizeof(float);  // 确保使用 sizeof(float) 以提高可移植性
  
  for(int i = 0; i < num_elements; ++i) {
    float diff = left.value_.vector_value_[i] - right.value_.vector_value_[i];
    sum += diff * diff;
  }
  
   // 计算 L2 距离
    float distance = std::sqrt(sum);
    
    // 四舍五入到两位小数
    float rounded_distance = std::round(distance * 100.0f) / 100.0f;
    
    // 将结果设置到 result 中
    result.set_float(rounded_distance);
    return RC::SUCCESS;
}
 RC FloatType::inner_product(const Value &left, const Value &right, Value &result) const
{
    // 确保左操作数和右操作数都是向量类型
    ASSERT(left.attr_type() == AttrType::VECTORS, "left type is not vector");
    ASSERT(right.attr_type() == AttrType::VECTORS, "right type is not vector");
    
    // 确保两个向量的长度相同
    ASSERT(left.length_ == right.length_, "left vector length != right vector length");
    
    // 计算向量元素的数量
    int num_elements = left.length_ / sizeof(float);
    
    // 计算内积
    float sum = 0.0f;
    for(int i = 0; i < num_elements; ++i) {
        sum += left.value_.vector_value_[i] * right.value_.vector_value_[i];
    }
    
    // 四舍五入到两位小数
    float rounded_sum = std::round(sum * 100.0f) / 100.0f;
    
    // 将结果设置到 result 中
    result.set_float(rounded_sum);
    
    return RC::SUCCESS;
}
  RC FloatType::cosine_distance(const Value &left, const Value &right, Value &result) const
{
    // 确保左操作数和右操作数都是向量类型
    ASSERT(left.attr_type_ == AttrType::VECTORS, "left type is not vector");
    ASSERT(right.attr_type_ == AttrType::VECTORS, "right type is not vector");
    
    // 确保两个向量的长度相同
    ASSERT(left.length_ == right.length_, "left vector length != right vector length");
    
    // 计算向量元素的数量
    int num_elements = left.length_ / sizeof(float);
    
    // 计算内积和范数
    float dot_product = 0.0f;
    float norm_left = 0.0f;
    float norm_right = 0.0f;
    
    for(int i = 0; i < num_elements; ++i) {
        dot_product += left.value_.vector_value_[i] * right.value_.vector_value_[i];
        norm_left += left.value_.vector_value_[i] * left.value_.vector_value_[i];
        norm_right += right.value_.vector_value_[i] * right.value_.vector_value_[i];
    }
    
    // 计算范数乘积
    float norm_product = std::sqrt(norm_left) * std::sqrt(norm_right);
    
    // 避免除以零
    if(norm_product == 0.0f) {
        // 可以选择返回一个错误码，或者定义一个特定的行为
        return RC::INVALID_ARGUMENT;
    }
    
    // 计算余弦相似度
    float cosine_similarity = dot_product / norm_product;
    
    // 计算余弦距离
    float cosine_distance = 1.0f - cosine_similarity;
    
    // 四舍五入到两位小数
    float rounded_cosine_distance = std::round(cosine_distance * 100.0f) / 100.0f;
    
    // 将结果设置到 result 中
    result.set_float(rounded_cosine_distance);
    
    return RC::SUCCESS;
}



