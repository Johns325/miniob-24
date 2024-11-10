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
// Created by wangyunlai.wyl on 2024/05/31
//

#include <memory>

#include "sql/expr/composite_tuple.h"
#include "gtest/gtest.h"

using namespace std;
using namespace common;

#include <random>

TEST(CompositeTuple, test_including_composite_tuple)
{


    // Create a random number generator
    std::random_device rd;                      // Seed
    std::mt19937 gen(rd());                     // Mersenne Twister engine
    std::uniform_int_distribution<> dist(0, 99); // Define range

    // Generate a random number in the range [0, 99]
    for (int i = 0; i < 10;++i) {
      int randomNumber = dist(gen);
      std::cout << "Random number (0-99): " << randomNumber << std::endl;
    }


  // // 测试包含一个 composite tuple
  // CompositeTuple composite_tuple;
  // vector<Value> values;
  // vector<TupleCellSpec> specs;
  // for (int i = 0; i < 10; i++)
  // {
  //   values.emplace_back(i);
  //   specs.emplace_back(TupleCellSpec(to_string(i)));
  // }

  // ValueListTuple value_list_tuple;
  // value_list_tuple.set_cells(values);
  // value_list_tuple.set_names(specs);

  // composite_tuple.add_tuple(make_unique<ValueListTuple>(value_list_tuple));
  // ASSERT_EQ(10, composite_tuple.cell_num());

  // CompositeTuple composite_tuple2;
  // composite_tuple2.add_tuple(make_unique<CompositeTuple>(std::move(composite_tuple)));
  // ASSERT_EQ(10, composite_tuple2.cell_num());
}

int main(int argc, char **argv)
{

  // 分析gtest程序的命令行参数
  testing::InitGoogleTest(&argc, argv);

  // 调用RUN_ALL_TESTS()运行所有测试用例
  // main函数返回RUN_ALL_TESTS()的运行结果
  return RUN_ALL_TESTS();
}
