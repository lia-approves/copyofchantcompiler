#include "frontend/parser/parser.h"

namespace cs160 {
namespace frontend {

namespace token = cs160::frontend;

Parser::Parser(std::vector<token::Token> tokens) {
  this->tokens = tokens;
}
Parser::~Parser() {}
}  // namespace frontend
}  // namespace cs160
