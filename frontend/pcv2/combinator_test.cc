// Copyright (c) 2018, Team-Chant
#include "gtest/gtest.h"
#include <string>
#include "frontend/pcv2/parser.h"
#include "abstract_syntax/print_visitor_v1.h"

namespace cs160 {
namespace frontend {

TEST(CombinatorTest, InstantiateState) {
  State s("hi");
  std::cout << __cplusplus << std::endl;
  ASSERT_EQ(s.ReadChar(), 'h');
}

// TEST(CombinatorTest, ParseLiteral) {
//   State s("hi");
//   auto parse = Lit('h');
//   auto result = parse(s);
//   ASSERT_EQ(std::any_cast<char>(result.Value()), 'h');
// }



}  // namespace frontend
}  // namespace cs160
