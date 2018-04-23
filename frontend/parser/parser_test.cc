#include "gtest/gtest.h"
#include "frontend/parser/parser.h"

namespace cs160 {
namespace parser {

namespace token = cs160::scanner::token;

TEST(ParserTest, InstantiateParser) {
  std::vector<token::Token> tokens;
  Parser p(tokens);
}

TEST(ExpressionTest, InstantiateExpressions) {
  Expression l;
  Expression r;
  token::Token t;
  BinaryExpr be(l, t, r);
  UnaryExpr ue(t, l);
  Group g(r);
  Literal lit(t);
}

}  // namespace parser
}  // namespace cs160