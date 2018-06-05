// Copyright (c) 2018, Team-Chant

#include <string>
#include "gtest/gtest.h"
#include "frontend/v2/frontend.h"
#include "abstract_syntax/print_visitor_v2.h"

namespace cs160 {
namespace frontend {
namespace Parse {

class FrontendTest : public ::testing::Test {
 protected:
  bool test = false;
  abstract_syntax::frontend::PrintVisitor printer_;
};
//
// TEST_F(FrontendTest, BasicTest) {
//   // make a basic expression and parse
//   Frontend f;
//   auto ret = f.stringToAst("a");
//   ret->Visit(&printer_);
//   ASSERT_EQ(printer_.GetOutput(), "a");
// }

// TEST_F(FrontendTest, BasicUnaryTest) {
//   // make a basic expression and parse
//   Frontend f;
//   auto ret = f.stringToAst("1");
//   ret->Visit(&printer_);
//   ASSERT_EQ(printer_.GetOutput(), "1");
// }
//
TEST_F(FrontendTest, BasicUnary2Test) {
  // make a basic expression and parse
  Frontend f;
  auto ret = f.stringToAst("-1");
  std::cout << "done with stringToAst" << std::endl;
  ret->Visit(&printer_);
  std::cout << "done with print visitor" << std::endl;
  ASSERT_EQ(printer_.GetOutput(), "-1");
}

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
//
// TEST_F(FrontendTest, BasicSubtractionTest) {
//   // make a basic expression and parse
//   Frontend f;
//   auto ret = f.stringToAst("1-2");
//   ret->Visit(&printer_);
//   ASSERT_EQ(printer_.GetOutput(), "(- 1 2)");
// }
//
// TEST_F(FrontendTest, BasicMultiplicationTest) {
//   // make a basic expression and parse
//   Frontend f;
//   auto ret = f.stringToAst("1*2");
//   ret->Visit(&printer_);
//   ASSERT_EQ(printer_.GetOutput(), "(* 1 2)");
// }
//
// TEST_F(FrontendTest, BasicDivisionTest) {
//   // make a basic expression and parse
//   Frontend f;
//   auto ret = f.stringToAst("2/1");
//   ret->Visit(&printer_);
//   ASSERT_EQ(printer_.GetOutput(), "(/ 2 1)");
// }
//
// TEST_F(FrontendTest, AdvancedAdditionTest) {
//   // make a basic expression and parse
//   Frontend f;
//   auto ret = f.stringToAst("2+2+3+4");
//   ret->Visit(&printer_);
//   ASSERT_EQ(printer_.GetOutput(), "(+ (+ (+ 2 2) 3) 4)");
// }
//
// TEST_F(FrontendTest, AdvancedEquation1Test) {
//   // make a basic expression and parse
//   Frontend f;
//   auto ret = f.stringToAst("2+3-4");
//   ret->Visit(&printer_);
//   ASSERT_EQ(printer_.GetOutput(), "(- (+ 2 3) 4)");
// }
//
// TEST_F(FrontendTest, AdvancedEquation2Test) {
//   // make a basic expression and parse
//   Frontend f;
//   auto ret = f.stringToAst("(4+5)*6");
//   ret->Visit(&printer_);
//   ASSERT_EQ(printer_.GetOutput(), "(* (+ 4 5) 6)");
// }
//
// TEST_F(FrontendTest, AdvancedEquation3Test) {
//   // make a basic expression and parse
//   Frontend f;
//   auto ret = f.stringToAst("(2+2)/(10-2)");
//   ret->Visit(&printer_);
//   ASSERT_EQ(printer_.GetOutput(), "(/ (+ 2 2) (- 10 2))");
// }

}  // namespace Parse
}  // namespace frontend
}  // namespace cs160
