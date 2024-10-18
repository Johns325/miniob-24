/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */


#include "common/lang/string.h"
#include "common/type/attr_type.h"
#include "common/rc.h"


// const char *ATTR_TYPE_NAME[] = {"undefined", "chars", "ints", "floats", "booleans", "dates"};
const char *ATTR_TYPE_NAME[] = {"undefined", "chars", "ints", "floats", "vectors", "booleans", "dates", "nulls"};

const char *attr_type_to_string(AttrType type)
{
  if (type >= AttrType::UNDEFINED && type < AttrType::MAXTYPE) {
    return ATTR_TYPE_NAME[static_cast<int>(type)];
  }
  return "unknown";
}

AttrType attr_type_from_string(const char *s)
{
  for (unsigned int i = 0; i < sizeof(ATTR_TYPE_NAME) / sizeof(ATTR_TYPE_NAME[0]); i++) {
    if (0 == strcasecmp(ATTR_TYPE_NAME[i], s)) {
      return (AttrType)i;
    }
  }
  return AttrType::UNDEFINED;
}

RC date_str_to_int(const std::string& val, int& date_int_val) {
   try {
    // auto val = values[i].get_string();
    int day,month,year;
    day = month = year = -1;
    int ret = sscanf(val.c_str(), "%d-%d-%d",&year,&month,&day);
    
    if ((ret != 3) || (year < 0) || (month < 1) || (month > 12) || (day < 1) || (day > 31)) {
      return RC::INTERNAL;
    }
    bool is_leap_year = year % 100 == 0 ? (year % 400 == 0) : (year % 4 == 0);
    switch (month)
    {
    case 4:
    case 6:
    case 9:
    case 11:
      if (day > 30) {
        return RC::INTERNAL;
      }
      break;
    case 2:
      if ((is_leap_year && day > 29) || (!is_leap_year && day > 28)) {
        return RC::INTERNAL;
      }
    default:
      break;
    }
    int time_val = ((year & 0xffff) << 16) | ((month & 0xff) << 8) | (day & 0xff); 
    date_int_val = time_val;
  } catch(std::exception& e) {
    return RC::INTERNAL;
  }
  return RC::SUCCESS;
}
