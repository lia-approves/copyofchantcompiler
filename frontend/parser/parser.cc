#include "frontend/parser/parser.h"

namespace cs160 {
namespace parser {

namespace token = cs160::scanner::token;

Parser::Parser(std::vector<token::Token> tokens) {
  this->tokens = tokens;
}
Parser::~Parser() {}


}  // namespace parser
}  // namespace cs160