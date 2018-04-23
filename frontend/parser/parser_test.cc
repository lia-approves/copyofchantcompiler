#include "gtest/gtest.h"
#include "frontend/parser/parser.h"

namespace cs160 {
namespace parser {

namespace token = cs160::scanner::token;

TEST(ParserTest, InstantiateParser) {
  std::vector<token::Token> tokens;
  Parser p(tokens);
}

}  // namespace parser
}  // namespace cs160