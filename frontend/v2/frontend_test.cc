// Copyright (c) 2018, Team-Chant

#include <string>
#include "gtest/gtest.h"
#include "frontend/v2/frontend.h"

namespace cs160 {
namespace frontend {

class FrontendTest : public ::testing::Test {
 protected:
   bool test = false;
};

// TEST_F(FrontendTest, BasicIntegerTest) {
//   // make a basic expression and parse
//   Frontend f;
//   auto ret = f.stringToAst("1");
//   ret->Visit(&printer_);
//   ASSERT_EQ(printer_.GetOutput(), "1");
// }
// 
// TEST_F(FrontendTest, BasicAdditionTest) {
//   // make a basic expression and parse
//   Frontend f;
//   auto ret = f.stringToAst("1+2");
//   ret->Visit(&printer_);
//   ASSERT_EQ(printer_.GetOutput(), "(+ 1 2)");
// }
//
// TEST_F(FrontendTest, BasicParenthesisTest) {
//   Frontend f;
//   auto ret = f.stringToAst("(1+2)");
//   ret->Visit(&printer_);
//   ASSERT_EQ(printer_.GetOutput(), "(+ 1 2)");
// }

}  // namespace frontend
}  // namespace cs160
