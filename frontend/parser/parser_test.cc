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

TEST(ParserTest, SimpleAddition) {
  IntegerToken one("1");
  IntegerToken two("2");
  ArithmeticExpressionToken plus("+");
  std::vector<Token> t = {one, plus, two};
  Parser p(t);
  Expression e = Literal(one);
  std::cout << "Expression (not pointer): " << e.toString() << std::endl;
  Expression *pe = new Literal(one);
  std::cout << "Expression (pointer): " << pe->toString() << std::endl;
  p.parse();
}

TEST(ExpressionTest, InstantiateExpressions) {
  Expression l;
  Expression r;
  Token t;
  BinaryExpr be(l, t, r);
  UnaryExpr ue(t, l);
  Group g(r);
  Literal lit(t);
}

}  // namespace frontend
}  // namespace cs160
