// Copyright (c) 2018, Team-Chant

#define GTEST_COUT std::cerr << "[          ] [ INFO ]"

#include <iostream>
#include "gtest/gtest.h"
#include "frontend/parser/parser.h"
#include "frontend/scanner/token/IntegerToken.h"
#include "frontend/scanner/token/ArithmeticExpressionToken.h"
#include "frontend/scanner/token/OpenParenthesisToken.h"
#include "abstract_syntax/print_visitor_v1.h"
#include "frontend/scanner/token/ClosedParenthesisToken.h"

namespace cs160 {
namespace frontend {

class ParserTest : public ::testing::Test {
 protected:
  abstract_syntax::frontend::PrintVisitor printer_;
};

TEST_F(ParserTest, InstantiateParser) {
  std::shared_ptr<Token> one(new IntegerToken("1"));
  std::vector<std::shared_ptr<Token>> t = {one};
  Parser p(t);
}

TEST_F(ParserTest, ParseSingleInteger) {
  std::shared_ptr<Token> one(new IntegerToken("1"));
  std::vector<std::shared_ptr<Token>> t = {one};
  Parser p(t);
  auto e = p.Parse();
  e->Visit(&printer_);
  ASSERT_EQ(printer_.GetOutput(), "1");
}

TEST_F(ParserTest, SimpleAddition) {
  std::shared_ptr<Token> one(new IntegerToken("1"));
  std::shared_ptr<Token> two(new IntegerToken("2"));
  std::shared_ptr<Token> plus(new ArithmeticExpressionToken("+"));
  std::vector<std::shared_ptr<Token>> t = {one, plus, two};
  Parser p(t);
  auto e = p.Parse();
  e->Visit(&printer_);
  std::cout << printer_.GetOutput() << std::endl;
  //ASSERT_EQ(printer_.GetOutput(), "1+");
}

// TEST(ParserTest, SimpleAddition) {
//   IntegerToken one("1");
//   IntegerToken two("2");
//   ArithmeticExpressionToken plus("+");
//   std::vector<Token> t = {one, plus, two};
//   Parser p(t);
//   auto e = p.Parse();
//   ASSERT_EQ(e->ToString(), "(1+2)");
// }
//
// TEST(ParserTest, SimpleSubtraction) {
//   IntegerToken one("1");
//   IntegerToken two("2");
//   ArithmeticExpressionToken minus("-");
//   std::vector<Token> t = {one, minus, two};
//   Parser p(t);
//   auto e = p.Parse();
//   ASSERT_EQ(e->ToString(), "(1-2)");
// }
//
// TEST(ParserTest, SimpleMultiplication) {
//   IntegerToken one("1");
//   IntegerToken two("2");
//   ArithmeticExpressionToken times("*");
//   std::vector<Token> t = {one, times, two};
//   Parser p(t);
//   auto e = p.Parse();
//   ASSERT_EQ(e->ToString(), "(1*2)");
// }
//
// TEST(ParserTest, SimpleDivision) {
//   IntegerToken one("1");
//   IntegerToken two("2");
//   ArithmeticExpressionToken dividedBy("/");
//   std::vector<Token> t = {one, dividedBy, two};
//   Parser p(t);
//   auto e = p.Parse();
//   ASSERT_EQ(e->ToString(), "(1/2)");
// }
//
// TEST(ParserTest, MultPrecedenceOverAdd) {
//   IntegerToken one("1");
//   IntegerToken two("2");
//   IntegerToken three("3");
//   ArithmeticExpressionToken plus("+");
//   ArithmeticExpressionToken times("*");
//   std::vector<Token> t = {one, plus, two, times, three};
//   Parser p(t);
//   auto e = p.Parse();
//   // std::cout << e->toString() << std::endl;
//   ASSERT_EQ(e->ToString(), "(1+(2*3))");
// }
//
// TEST(ParserTest, ParenthesesOverrideOperatorPrecedence) {
//   IntegerToken one("1");
//   IntegerToken two("2");
//   IntegerToken three("3");
//   ArithmeticExpressionToken plus("+");
//   ArithmeticExpressionToken times("*");
//   OpenParenthesisToken openParen("(");
//   ClosedParenthesisToken closeParen(")");
//   std::vector<Token> t = {openParen, one, plus, two, closeParen, times, three};
//   Parser p(t);
//   auto e = p.Parse();
//   // std::cout << e->toString() << std::endl;
//   ASSERT_EQ(e->ToString(), "(((1+2))*3)");
// }
//
// TEST(ExpressionTest, InstantiateExpressions) {
//   auto l = std::unique_ptr<Expression>(new Expression);
//   auto r = std::unique_ptr<Expression>(new Expression);
//   Token t;
//   BinaryExpr be(std::move(l), t, std::move(r));
//   UnaryExpr ue(t, std::move(l));
//   Group g(std::move(r));
//   Literal lit(std::move(t));
// }

}  // namespace frontend
}  // namespace cs160
