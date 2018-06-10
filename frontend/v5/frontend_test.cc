// Copyright (c) 2018, Team-Chant

#include <string>
#include "gtest/gtest.h"
#include "frontend/v5/frontend.h"
#include "abstract_syntax/print_visitor_v5.h"

namespace cs160 {
namespace frontend {
namespace Parse {

class FrontendTest : public ::testing::Test {
 protected:
  bool test = false;
  abstract_syntax::version_5::PrintVisitor printer_;
};

TEST_F(FrontendTest, IntegerTest1) {
  // make a basic expression and parse
  auto ret = Frontend::stringToAst("1");
  ret->Visit(&printer_);
  ASSERT_EQ(printer_.GetOutput(), "1");
}

TEST_F(FrontendTest, IntegerTest2) {
  // make a basic expression and parse
  auto ret = Frontend::stringToAst("1234");
  ret->Visit(&printer_);
  ASSERT_EQ(printer_.GetOutput(), "1234");
}

TEST_F(FrontendTest, IntegerTest3) {
  // make a basic expression and parse
  auto ret = Frontend::stringToAst("4321");
  ret->Visit(&printer_);
  ASSERT_EQ(printer_.GetOutput(), "4321");
}

// TEST_F(FrontendTest, VariableTest1) {
//   // make a basic expression and parse
//   auto ret = Frontend::stringToAst("a");
//   ret->Visit(&printer_);
//   ASSERT_EQ(printer_.GetOutput(), "a");
// }
//
// TEST_F(FrontendTest, VariableTest2) {
//   // make a basic expression and parse
//   auto ret = Frontend::stringToAst("abcd");
//   ret->Visit(&printer_);
//   ASSERT_EQ(printer_.GetOutput(), "abcd");
// }
//
// TEST_F(FrontendTest, VariableTest3) {
//   // make a basic expression and parse
//   auto ret = Frontend::stringToAst("abcd123");
//   ret->Visit(&printer_);
//   ASSERT_EQ(printer_.GetOutput(), "abcd123");
// }
//
// TEST_F(FrontendTest, VariableTest4) {
//   // make a basic expression and parse
//   auto ret = Frontend::stringToAst("abcd_123");
//   ret->Visit(&printer_);
//   ASSERT_EQ(printer_.GetOutput(), "abcd_123");
// }



}  // namespace Parse
}  // namespace frontend
}  // namespace cs160
