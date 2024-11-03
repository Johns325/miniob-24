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
// Created by WangYunlai on 2023/06/28.
//

#include "common/value.h"

#include "common/lang/comparator.h"
#include "common/lang/exception.h"
#include "common/lang/sstream.h"
#include "common/lang/string.h"
#include "common/log/log.h"

Value::Value(int val) { set_int(val); }

Value::Value(float val) { set_float(val); }

Value::Value(bool val) { set_boolean(val); }

Value::Value(const char *s, int len /*= 0*/) { set_string(s, len); }

Value::Value(const float *vec,int len) {
  set_vector(vec,len);
}

Value::Value(const Value &other)
{
  this->attr_type_ = other.attr_type_;
  this->length_    = other.length_;
  this->own_data_  = other.own_data_;
  switch (this->attr_type_) {
    case AttrType::CHARS: {
      set_string_from_other(other);
    } break;
    case AttrType::TEXTS: {
      set_text_from_other(other);
    }
    case AttrType::VECTORS: {
       if (other.value_.vector_value_ != nullptr) {
        this->own_data_ = true;  // 我们拥有新分配的内存
        int num_elements = other.length_ / sizeof(float);
        value_.vector_value_ = new float[num_elements];
        memcpy(value_.vector_value_, other.value_.vector_value_, other.length_);
      } else {
        value_.vector_value_ = nullptr;
        this->own_data_ = false;
      }
    } break;
    default: {
      this->value_ = other.value_;
    } break;
  }
}

Value::Value(Value &&other)
{
  this->attr_type_ = other.attr_type_;
  this->length_    = other.length_;
  this->own_data_  = other.own_data_;
  this->value_     = other.value_;
  other.own_data_  = false;
  other.length_    = 0;
}

Value &Value::operator=(const Value &other)
{
  if (this == &other) {
    return *this;
  }
  reset();
  this->attr_type_ = other.attr_type_;
  this->length_    = other.length_;
  this->own_data_  = other.own_data_;
  switch (this->attr_type_) {
    case AttrType::CHARS: {
      set_string_from_other(other);
    } break;
    case AttrType::TEXTS :{
      set_text_from_other(other);
    }
    case AttrType::VECTORS: {
      if (other.value_.vector_value_ != nullptr) {
        this->own_data_ = true;  // 我们拥有新分配的内存
        int num_elements = other.length_ / sizeof(float);
        value_.vector_value_ = new float[num_elements];
        memcpy(value_.vector_value_, other.value_.vector_value_, other.length_);
      } else {
        value_.vector_value_ = nullptr;
        this->own_data_ = false;
      }
    } break;
    default: {
      this->value_ = other.value_;
    } break;
  }
  return *this;
}

Value &Value::operator=(Value &&other)
{
  if (this == &other) {
    return *this;
  }
  reset();
  this->attr_type_ = other.attr_type_;
  this->length_    = other.length_;
  this->own_data_  = other.own_data_;
  this->value_     = other.value_;
  other.own_data_  = false;
  other.length_    = 0;
  return *this;
}

void Value::reset()
{
  switch (attr_type_) {
    case AttrType::CHARS:
      if (own_data_ && value_.pointer_value_ != nullptr) {
        delete[] value_.pointer_value_;
        value_.pointer_value_ = nullptr;
      }
      break;
    case AttrType::TEXTS:
      if (own_data_ && value_.pointer_value_ != nullptr) {
        delete[] value_.pointer_value_;
        value_.pointer_value_ = nullptr;
      }break;
    case AttrType::VECTORS:
      if (own_data_ && value_.vector_value_ != nullptr) {
        delete[] value_.vector_value_;
        value_.vector_value_ = nullptr;
      }
      break;
    default: break;
  }

  attr_type_ = AttrType::UNDEFINED;
  length_    = 0;
  own_data_  = false;
}

void Value::set_data(char *data, int length)
{
  switch (attr_type_) {
    case AttrType::CHARS: {
      set_string(data, length);
    } break;
    case AttrType::TEXTS: {
      set_text(data, length);
    } break;
    case AttrType::INTS: {
      value_.int_value_ = *(int *)data;
      length_           = length;
    } break;
    case AttrType::FLOATS: {
      value_.float_value_ = *(float *)data;
      length_             = length;
    } break;
    case AttrType::BOOLEANS: {
      value_.bool_value_ = *(int *)data != 0;
      length_            = length;
    } break;
    case AttrType::DATES: {
      value_.int_value_ = *(int*)data;
      length_ = length;
    } break;
    case AttrType::VECTORS: {
      set_vector((float*)data,length);
    }
    default: {
      LOG_WARN("unknown data type: %d", attr_type_);
    } break;
  }
}

void Value::set_int(int val)
{
  reset();
  attr_type_        = AttrType::INTS;
  value_.int_value_ = val;
  length_           = sizeof(val);
}

void Value::set_float(float val)
{
  reset();
  attr_type_          = AttrType::FLOATS;
  value_.float_value_ = val;
  length_             = sizeof(val);
}
void Value::set_boolean(bool val)
{
  reset();
  attr_type_         = AttrType::BOOLEANS;
  value_.bool_value_ = val;
  length_            = sizeof(val);
}

void Value::set_date(int date_val) 
{
  reset();
  attr_type_ = AttrType::DATES;
  length_ = sizeof(int);
  value_.int_value_ = date_val;
}

void Value::set_string(const char *s, int len /*= 0*/)
{
  reset();
  attr_type_ = AttrType::CHARS;
  if (s == nullptr) {
    value_.pointer_value_ = nullptr;
    length_               = 0;
  } else {
    own_data_ = true;
    if (len > 0) {
      len = strnlen(s, len);
    } else {
      len = strlen(s);
    }
    value_.pointer_value_ = new char[len + 1];
    length_               = len;
    memcpy(value_.pointer_value_, s, len);
    value_.pointer_value_[len] = '\0';
  }
}

void Value::set_vector(const float* vec,int len)
{
  reset();
  attr_type_ = AttrType::VECTORS;
  if(vec == nullptr) {
    value_.vector_value_ = nullptr;
    length_ = 0;
  } else {
    own_data_ = true;
    length_ = len;
    value_.vector_value_ = new float[len/4];
    for(int i = 0; i < len/4; i++) {
      value_.vector_value_[i] = vec[i];
    }
  }
}


void Value::set_value(const Value &value)
{
  switch (value.attr_type_) {
    case AttrType::INTS: {
      set_int(value.get_int());
    } break;
    case AttrType::FLOATS: {
      set_float(value.get_float());
    } break;
    case AttrType::CHARS: {
      set_string(value.get_string().c_str());
    } break;
    case AttrType::TEXTS: {
      set_string(value.get_string().c_str());
    }break;
    case AttrType::BOOLEANS: {
      set_boolean(value.get_boolean());
    } break;
    case AttrType::VECTORS: {
      set_vector(value.get_vector(), value.length_);
    } break;
    default: {
      ASSERT(false, "got an invalid value type");
    } break;
  }
}

void Value::set_string_from_other(const Value &other)
{
  ASSERT(attr_type_ == AttrType::CHARS, "attr type is not CHARS");
  if (own_data_ && other.value_.pointer_value_ != nullptr && length_ != 0) {
    this->value_.pointer_value_ = new char[this->length_ + 1];
    memcpy(this->value_.pointer_value_, other.value_.pointer_value_, this->length_);
    this->value_.pointer_value_[this->length_] = '\0';
  }
}

const char *Value::data() const
{
  switch (attr_type_) {
    case AttrType::CHARS: {
      return value_.pointer_value_;
    } break;
    case AttrType::VECTORS: {
      return (char*)value_.vector_value_;
    } break;
    case AttrType::TEXTS: {
      return value_.pointer_value_;
    } break;
    default: {
      return (const char *)&value_;
    } break;
  }
}

string Value::to_string() const
{
  string res;
  // TODO optimize this case.
  if (attr_type_ == AttrType::NULLS) {
    return "NULL";
  }
  RC     rc = DataType::type_instance(this->attr_type_)->to_string(*this, res);
  if (OB_FAIL(rc)) {
    LOG_WARN("failed to convert value to string. type=%s", attr_type_to_string(this->attr_type_));
    return "";
  }
  return res;
}

int Value::compare(const Value &other) const { 
  if (this->attr_type_ == other.attr_type())
    return DataType::type_instance(this->attr_type_)->compare(*this, other); 
  else if (this->attr_type_ == AttrType::INTS && other.attr_type_ == AttrType::FLOATS) {
    float this_data = this->value_.int_value_;
    return common::compare_float((void *)&this_data, (void *)&other.value_.float_value_);
  } else if (this->attr_type_ == AttrType::FLOATS && other.attr_type_ == AttrType::INTS) {
    float other_data = other.value_.int_value_;
    return common::compare_float((void *)&this->value_.float_value_, (void *)&other_data);
  } else if (this->attr_type() == AttrType::CHARS) {
    if (other.attr_type() == AttrType::FLOATS) {
      auto f1 = get_float();
      auto f2 = other.get_float();
      return common::compare_float(&f1, &f2);
    } else if (other.attr_type() == AttrType::INTS) {
      int left = get_int();
      int right = other.get_int();
      return common::compare_int(&left, &right);
    }
  }
  return -1;
}

// RC get_specific_type_value(AttrType type, Value&v) {
//   switch (type`)
//   {
//   case AttrType::INTS:
//     int 
//     break;
  
//   default:
//     break;
//   }
// }

int Value::get_int() const
{
  switch (attr_type_) {
    case AttrType::CHARS: {
      try {
        return (int)(std::stol(value_.pointer_value_));
      } catch (exception const &ex) {
        LOG_TRACE("failed to convert string to number. s=%s, ex=%s", value_.pointer_value_, ex.what());
        return 0;
      }
    }
    case AttrType::INTS: {
      return value_.int_value_;
    }
    case AttrType::FLOATS: {
      return (int)(value_.float_value_);
    }
    case AttrType::BOOLEANS: {
      return (int)(value_.bool_value_);
    }
    default: {
      LOG_WARN("unknown data type. type=%d", attr_type_);
      return 0;
    }
  }
  return 0;
}

float Value::get_float() const
{
  switch (attr_type_) {
    case AttrType::CHARS: {
      try {
        return std::stof(value_.pointer_value_);
      } catch (exception const &ex) {
        LOG_TRACE("failed to convert string to float. s=%s, ex=%s", value_.pointer_value_, ex.what());
        return 0.0;
      }
    } break;
    case AttrType::INTS: {
      return float(value_.int_value_);
    } break;
    case AttrType::FLOATS: {
      return value_.float_value_;
    } break;
    case AttrType::BOOLEANS: {
      return float(value_.bool_value_);
    } break;
    default: {
      LOG_WARN("unknown data type. type=%d", attr_type_);
      return 0;
    }
  }
  return 0;
}

string Value::get_string() const { return this->to_string(); }

bool Value::get_boolean() const
{
  switch (attr_type_) {
    case AttrType::CHARS: {
      try {
        float val = std::stof(value_.pointer_value_);
        if (val >= EPSILON || val <= -EPSILON) {
          return true;
        }

        int int_val = std::stol(value_.pointer_value_);
        if (int_val != 0) {
          return true;
        }

        return value_.pointer_value_ != nullptr;
      } catch (exception const &ex) {
        LOG_TRACE("failed to convert string to float or integer. s=%s, ex=%s", value_.pointer_value_, ex.what());
        return value_.pointer_value_ != nullptr;
      }
    } break;
    case AttrType::INTS: {
      return value_.int_value_ != 0;
    } break;
    case AttrType::FLOATS: {
      float val = value_.float_value_;
      return val >= EPSILON || val <= -EPSILON;
    } break;
    case AttrType::BOOLEANS: {
      return value_.bool_value_;
    } break;
    default: {
      LOG_WARN("unknown data type. type=%d", attr_type_);
      return false;
    }
  }
  return false;
}

float* Value::get_vector() const {
  return value_.vector_value_;
}

void Value::init_int(int val) {
  this->attr_type_ = AttrType::INTS;
  this->value_.int_value_ = val;
}

void Value::set_text_from_other(const Value &other)
{
  ASSERT(attr_type_ == AttrType::TEXTS, "attr type is not CHARS");
  own_data_ = true;
  this->length_ = other.length();
  if (own_data_ && other.value_.pointer_value_ != nullptr && length_ != 0) {
    this->value_.pointer_value_ = new char[this->length_ + 1];
    memcpy(this->value_.pointer_value_, other.value_.pointer_value_, this->length_);
    this->value_.pointer_value_[this->length_] = '\0';
  }
}

void Value::set_vector_from_other(const Value &other)
{
  ASSERT(attr_type_ == AttrType::VECTORS, "attr type is not vector");
  if (own_data_ && other.value_.vector_value_ != nullptr && length_ != 0) {
    this->value_.vector_value_ = new float[this->length_];
    memcpy(this->value_.vector_value_, other.value_.vector_value_, this->length_);
    this->length_ = 16;
  }
}

void Value::set_text(const char *s, int len /*= 0*/)
{
  reset();
  attr_type_ = AttrType::TEXTS;
  if (s == nullptr) {
    value_.pointer_value_ = nullptr;
    length_               = 0;
  } else {
    own_data_ = true;
    if (len > 0) {
      len = strnlen(s, len);
    } else {
      len = strlen(s);
    }
    value_.pointer_value_ = new char[len + 1];
    length_               = len;
    memcpy(value_.pointer_value_, s, len);
    value_.pointer_value_[len] = '\0';
  }
}