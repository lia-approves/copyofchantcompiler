#define GTEST_COUT std::cerr << "[          ] [ INFO ]"

#include "gtest/gtest.h"
#include "frontend/parser/parser.h"
#include "frontend/scanner/token/IntegerToken.h"
#include "frontend/scanner/token/ArithmeticExpressionToken.h"
#include <iostream>

namespace cs160 {
namespace frontend {

TEST(ParserTest, InstantiateParser) {
  std::vector<Token> tokens;
  Parser p(tokens);
}

TEST(ParserTest, ParseSingleInteger) {
  IntegerToken one("1");
  std::vector<Token> t = {one};
  Parser p(t);
  auto e = p.parse();
  ASSERT_EQ(e->toString(), "(1)");
}

TEST(ParserTest, SimpleAddition) {
  IntegerToken one("1");
  IntegerToken two("2");
  ArithmeticExpressionToken plus("+");
  std::vector<Token> t = {one, plus, two};
  Parser p(t);
  auto e = p.parse();
  ASSERT_EQ(e->toString(), "((1)+(2))");
}

TEST(ParserTest, SimpleMultiplication) {
  IntegerToken one("1");
  IntegerToken two("2");
  ArithmeticExpressionToken plus("+");
  std::vector<Token> t = {one, plus, two};
  Parser p(t);
  auto e = p.parse();
  std::cout << e->toString() << std::endl;
  ASSERT_EQ(e->toString(), "((1)+(2))");
}

TEST(ExpressionTest, InstantiateExpressions) {
  auto l = std::shared_ptr<Expression>(new Expression);
  auto r = std::shared_ptr<Expression>(new Expression);
  Token t;
  BinaryExpr be(l, t, r);
  UnaryExpr ue(t, l);
  Group g(r);
  Literal lit(t);
}

}  // namespace frontend
}  // namespace cs160
