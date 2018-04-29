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
  // std::cout << printer_.GetOutput() << std::endl;
  ASSERT_EQ(printer_.GetOutput(), "(+ 1 2)");
}

TEST_F(ParserTest, MultipleAdds) {
  std::shared_ptr<Token> one(new IntegerToken("1"));
  std::shared_ptr<Token> two(new IntegerToken("2"));
  std::shared_ptr<Token> three(new IntegerToken("3"));
  std::shared_ptr<Token> plus1(new ArithmeticExpressionToken("+"));
  std::shared_ptr<Token> plus2(new ArithmeticExpressionToken("+"));
  std::vector<std::shared_ptr<Token>> t = {one, plus1, two, plus2, three};
  Parser p(t);
  auto e = p.Parse();
  e->Visit(&printer_);
  ASSERT_EQ(printer_.GetOutput(), "(+ (+ 1 2) 3)");
}

TEST_F(ParserTest, NegativeNumbers) {
  std::shared_ptr<Token> one(new IntegerToken("1"));
  std::shared_ptr<Token> two(new IntegerToken("2"));
  std::shared_ptr<Token> minus1(new ArithmeticExpressionToken("-"));
  std::shared_ptr<Token> plus(new ArithmeticExpressionToken("+"));
  std::shared_ptr<Token> minus2(new ArithmeticExpressionToken("-"));
  std::vector<std::shared_ptr<Token>> t = {minus1, one, plus, minus2, two};
  Parser p(t);
  auto e = p.Parse();
  e->Visit(&printer_);
  // std::cout << printer_.GetOutput() << std::endl;
  ASSERT_EQ(printer_.GetOutput(), "(+ (- 0 1) (- 0 2))");
}

TEST_F(ParserTest, SimpleSubtraction) {
  std::shared_ptr<Token> one(new IntegerToken("1"));
  std::shared_ptr<Token> two(new IntegerToken("2"));
  std::shared_ptr<Token> minus(new ArithmeticExpressionToken("-"));
  std::vector<std::shared_ptr<Token>> t = {one, minus, two};
  Parser p(t);
  auto e = p.Parse();
  e->Visit(&printer_);
  // std::cout << printer_.GetOutput() << std::endl;
  ASSERT_EQ(printer_.GetOutput(), "(- 1 2)");
}

TEST_F(ParserTest, SimpleError) {
  std::shared_ptr<Token> one(new IntegerToken("1"));
  std::shared_ptr<Token> two(new IntegerToken("2"));
  std::shared_ptr<Token> minus(new ArithmeticExpressionToken("-"));
  std::vector<std::shared_ptr<Token>> t = {one, minus};
  Parser p(t);
  ASSERT_THROW(p.Parse(), std::logic_error);
}

TEST_F(ParserTest, SimpleMultiplication) {
  std::shared_ptr<Token> one(new IntegerToken("1"));
  std::shared_ptr<Token> two(new IntegerToken("2"));
  std::shared_ptr<Token> times(new ArithmeticExpressionToken("*"));
  std::vector<std::shared_ptr<Token>> t = {one, times, two};
  Parser p(t);
  auto e = p.Parse();
  e->Visit(&printer_);
  // std::cout << printer_.GetOutput() << std::endl;
  ASSERT_EQ(printer_.GetOutput(), "(* 1 2)");
}

TEST_F(ParserTest, SimpleDivision) {
  std::shared_ptr<Token> one(new IntegerToken("1"));
  std::shared_ptr<Token> two(new IntegerToken("2"));
  std::shared_ptr<Token> divide(new ArithmeticExpressionToken("/"));
  std::vector<std::shared_ptr<Token>> t = {one, divide, two};
  Parser p(t);
  auto e = p.Parse();
  e->Visit(&printer_);
  // std::cout << printer_.GetOutput() << std::endl;
  ASSERT_EQ(printer_.GetOutput(), "(/ 1 2)");
}

TEST_F(ParserTest, MultPrecedenceOverAdd) {
  std::shared_ptr<Token> one(new IntegerToken("1"));
  std::shared_ptr<Token> two(new IntegerToken("2"));
  std::shared_ptr<Token> three(new IntegerToken("3"));
  std::shared_ptr<Token> times(new ArithmeticExpressionToken("*"));
  std::shared_ptr<Token> plus(new ArithmeticExpressionToken("+"));
  std::vector<std::shared_ptr<Token>> t = {one, plus, two, times, three};
  Parser p(t);
  auto e = p.Parse();
  e->Visit(&printer_);
  // std::cout << "mpoa: " << printer_.GetOutput() << std::endl;
  ASSERT_EQ(printer_.GetOutput(), "(+ 1 (* 2 3))");
}

TEST_F(ParserTest, ParenthesesOverrideOperatorPrecedence) {
  std::shared_ptr<Token> one(new IntegerToken("1"));
  std::shared_ptr<Token> two(new IntegerToken("2"));
  std::shared_ptr<Token> three(new IntegerToken("3"));
  std::shared_ptr<Token> times(new ArithmeticExpressionToken("*"));
  std::shared_ptr<Token> plus(new ArithmeticExpressionToken("+"));
  std::shared_ptr<Token> openParen(new OpenParenthesisToken("("));
  std::shared_ptr<Token> closeParen(new ClosedParenthesisToken(")"));
  std::vector<std::shared_ptr<Token>> t =
    {openParen, one, plus, two, closeParen, times, three};
  Parser p(t);
  auto e = p.Parse();
  e->Visit(&printer_);
  // std::cout << "mpoa: " << printer_.GetOutput() << std::endl;
  ASSERT_EQ(printer_.GetOutput(), "(* (+ 1 2) 3)");
}

}  // namespace frontend
}  // namespace cs160
