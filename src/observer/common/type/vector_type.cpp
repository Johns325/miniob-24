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
#include "common/type/vector_type.h"
#include "common/value.h"

#include <cmath>
int VectorType::compare(const Value &left, const Value &right) const
{
  ASSERT(left.attr_type() == AttrType::VECTORS, "left type is not vector");
  ASSERT(right.attr_type() == AttrType::VECTORS, "right type is not vector");
  ASSERT(left.length_ == right.length_, "left vector len != right vector len");
  return common::compare_vector(left.value_.vector_value_, left.length_, right.value_.vector_value_, right.length_);
}

RC VectorType::add(const Value &left, const Value &right, Value &result) const
{
  ASSERT(left.attr_type() == AttrType::VECTORS, "left type is not vector");
  ASSERT(right.attr_type() == AttrType::VECTORS, "right type is not vector");
  ASSERT(left.length_ == right.length_, "left vector len != right vector len");
  float *value = new float[left.length_/4];
  for(int i = 0; i < left.length_/4 ;i++) {
    value[i] = left.value_.vector_value_[i] + right.value_.vector_value_[i];
  }
  result.set_vector(value, left.length_);
  delete[] value;
  return RC::SUCCESS;
}

RC VectorType::subtract(const Value &left, const Value &right, Value &result) const
{
  ASSERT(left.attr_type() == AttrType::VECTORS, "left type is not vector");
  ASSERT(right.attr_type() == AttrType::VECTORS, "right type is not vector");
  ASSERT(left.length_ == right.length_, "left vector len != right vector len");
  float *value = new float[left.length_/4];
  for(int i = 0; i < left.length_/4 ;i++) {
    value[i] = left.value_.vector_value_[i] - right.value_.vector_value_[i];
  }
  result.set_vector(value, left.length_);
  delete[] value;
  return RC::SUCCESS;
}

RC VectorType::multiply(const Value &left, const Value &right, Value &result) const
{
  ASSERT(left.attr_type() == AttrType::VECTORS, "left type is not vector");
  ASSERT(right.attr_type() == AttrType::VECTORS, "right type is not vector");
  ASSERT(left.length_ == right.length_, "left vector len != right vector len");
  float *value = new float[left.length_/4];
  for(int i = 0; i < left.length_/4 ;i++) {
    value[i] = left.value_.vector_value_[i] * right.value_.vector_value_[i];
    value[i] = round(value[i] * 100) / 100;
  }
  result.set_vector(value, left.length_);
  delete[] value;
  return RC::SUCCESS;
}

RC VectorType::divide(const Value &left, const Value &right, Value &result) const
{
  ASSERT(left.attr_type() == AttrType::VECTORS, "left type is not vector");
  float *value = new float[left.length_/4];
  for(int i = 0; i < left.length_/4 ;i++) {
    value[i] = left.value_.vector_value_[i] / right.value_.int_value_;
    value[i] = round(value[i] * 100) / 100;
  }
  result.set_vector(value, left.length_);
  delete[] value;
  return RC::SUCCESS;
}

RC VectorType::to_string(const Value &val, string &result) const
{
  stringstream ss;
  ss << "[";
  for (size_t i = 0; i < val.length_/4; ++i) {
        ss << val.value_.vector_value_[i];  // 输出 float 值到 stringstream
        if (i < val.length_/4 - 1) {
            ss << ",";   // 添加逗号和空格作为分隔符
        }
    }
  ss << "]";
  result = ss.str();
  return RC::SUCCESS;
}

RC VectorType::l2_distance(const Value &left, const Value &right, Value &result) const {
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
 RC VectorType::inner_product(const Value &left, const Value &right, Value &result) const
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
  RC VectorType::cosine_distance(const Value &left, const Value &right, Value &result) const
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



