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

TEST_F(FrontendTest, VariableTest1) {
  // make a basic expression and parse
  Frontend f;
  auto ret = f.stringToAst("a");
  ret->Visit(&printer_);
  ASSERT_EQ(printer_.GetOutput(), "a");
}

TEST_F(FrontendTest, VariableTest2) {
  // make a basic expression and parse
  Frontend f;
  auto ret = f.stringToAst("abcd");
  ret->Visit(&printer_);
  ASSERT_EQ(printer_.GetOutput(), "abcd");
}

TEST_F(FrontendTest, VariableTest3) {
  // make a basic expression and parse
  Frontend f;
  auto ret = f.stringToAst("abcd123");
  ret->Visit(&printer_);
  ASSERT_EQ(printer_.GetOutput(), "abcd123");
}

TEST_F(FrontendTest, VariableTest4) {
  // make a basic expression and parse
  Frontend f;
  auto ret = f.stringToAst("abcd_123");
  ret->Visit(&printer_);
  ASSERT_EQ(printer_.GetOutput(), "abcd_123");
}



// TEST_F(FrontendTest, BasicUnaryTest) {
//   // make a basic expression and parse
//   Frontend f;
//   auto ret = f.stringToAst("1");
//   ret->Visit(&printer_);
//   ASSERT_EQ(printer_.GetOutput(), "1");
// }
//
// TEST_F(FrontendTest, BasicUnary2Test) {
//   // make a basic expression and parse
//   Frontend f;
//   auto ret = f.stringToAst("-1");
//   std::cout << "done with stringToAst" << std::endl;
//   ret->Visit(&printer_);
//   std::cout << "done with print visitor" << std::endl;
//   ASSERT_EQ(printer_.GetOutput(), "(- 0 1)");
// }
//
// TEST_F(FrontendTest, NegativeUnaryTest) {
//   // make a basic expression and parse
//   Frontend f;
//   auto ret = f.stringToAst("---1");
//   std::cout << "done with stringToAst" << std::endl;
//   ret->Visit(&printer_);
//   std::cout << "done with print visitor" << std::endl;
//   ASSERT_EQ(printer_.GetOutput(), "(- 0 1)");
// }
//
//
// TEST_F(FrontendTest, PositiveUnaryTest) {
//   // make a basic expression and parse
//   Frontend f;
//   auto ret = f.stringToAst("----1");
//   std::cout << "done with stringToAst" << std::endl;
//   ret->Visit(&printer_);
//   std::cout << "done with print visitor" << std::endl;
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
// TEST_F(FrontendTest, BasicSubtractionTest) {
//   // make a basic expression and parse
//   Frontend f;
//   auto ret = f.stringToAst("1-2");
//   ret->Visit(&printer_);
//   ASSERT_EQ(printer_.GetOutput(), "(- 1 2)");
// }
//
// TEST_F(FrontendTest, HardAdditionTest) {
//   // make a basic expression and parse
//   Frontend f;
//   auto ret = f.stringToAst("1+2+3+4+5");
//   ret->Visit(&printer_);
//   ASSERT_EQ(printer_.GetOutput(), "(+ 1 (+ 2 (+ 3 (+ 4 5))))");
// }
//
// TEST_F(FrontendTest, HardSubtractionTest) {
//   // make a basic expression and parse
//   Frontend f;
//   auto ret = f.stringToAst("1-2-3-4-5");
//   ret->Visit(&printer_);
//   ASSERT_EQ(printer_.GetOutput(), "(- 1 (- 2 (- 3 (- 4 5))))");
// }
//
// TEST_F(FrontendTest, MultAdditionTest) {
//   // make a basic expression and parse
//   Frontend f;
//   auto ret = f.stringToAst("5*4+6*7");
//   ret->Visit(&printer_);
//   ASSERT_EQ(printer_.GetOutput(), "(+ (* 5 4) (* 6 7))");
// }
//
// TEST_F(FrontendTest, DivAdditionTest) {
//   // make a basic expression and parse
//   Frontend f;
//   auto ret = f.stringToAst("5/4+6-7/8");
//   ret->Visit(&printer_);
//   ASSERT_EQ(printer_.GetOutput(), "(+ (/ 5 4) (- 6 (/ 7 8)))");
// }
//
// TEST_F(FrontendTest, BasicMultiplicationTest) {
//   // make a basic expression and parse
//   Frontend f;
//   auto ret = f.stringToAst("1*2");
//   std::cout << "done with stringToAST" << std::endl;
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
// TEST_F(FrontendTest, TripleMultiplicationTest) {
//   // make a basic expression and parse
//   Frontend f;
//   auto ret = f.stringToAst("1*2*3");
//   std::cout << "done with stringToAST" << std::endl;
//   ret->Visit(&printer_);
//   ASSERT_EQ(printer_.GetOutput(), "(* 1 (* 2 3))");
// }
//
// TEST_F(FrontendTest, TripleDivideTest) {
//   // make a basic expression and parse
//   Frontend f;
//   auto ret = f.stringToAst("1/2/3");
//   std::cout << "done with stringToAST" << std::endl;
//   ret->Visit(&printer_);
//   ASSERT_EQ(printer_.GetOutput(), "(/ 1 (/ 2 3))");
// }
//
// TEST_F(FrontendTest, MultDivCombinedTest) {
//   // make a basic expression and parse
//   Frontend f;
//   auto ret = f.stringToAst("1*2/3*5");
//   std::cout << "done with stringToAST" << std::endl;
//   ret->Visit(&printer_);
//   ASSERT_EQ(printer_.GetOutput(), "(* 1 (/ 2 (* 3 5)))");
// }
//
// TEST_F(FrontendTest, AdvancedAdditionTest) {
//   // make a basic expression and parse
//   Frontend f;
//   auto ret = f.stringToAst("2+2+3+4");
//   ret->Visit(&printer_);
//   ASSERT_EQ(printer_.GetOutput(), "(+ 2 (+ 2 (+ 3 4)))");
// }
//
// TEST_F(FrontendTest, AdvancedEquation1Test) {
//   // make a basic expression and parse
//   Frontend f;
//   auto ret = f.stringToAst("2+3-4");
//   ret->Visit(&printer_);
//   ASSERT_EQ(printer_.GetOutput(), "(+ 2 (- 3 4))");
// }


}  // namespace Parse
}  // namespace frontend
}  // namespace cs160
