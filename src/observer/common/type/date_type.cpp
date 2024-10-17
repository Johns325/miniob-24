
#include "common/type/date_type.h"
#include "common/value.h"
int DateType::compare(const Value &left, const Value &right) const {
  auto date_val1 = static_cast<uint32_t>(left.value_.int_value_);
  auto date_val2 = static_cast<uint32_t>(right.value_.int_value_);
  return date_val1 - date_val2;
}


RC DateType::to_string(const Value &val, string &result) const {
  stringstream ss;
  auto date_val = static_cast<uint32_t>(val.value_.int_value_);
  string s = std::to_string((date_val >> 16) & 0xffff) + "-";
  auto month = (date_val >> 8) & 0xff;
  if (month < 10)
    s += "0";
  s = s + std::to_string(month) + "-";
  auto day = (date_val & 0xff);
  if (day < 10)
    s += "0";
  s = s + std::to_string(day);
  result = s;
  return RC::SUCCESS;
}
