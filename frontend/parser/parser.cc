// copyright msg for cpplint
#include "frontend/parser/parser.h"

namespace cs160 {
namespace frontend {

Parser::Parser(std::vector<Token> tokens) {
  this->tokens = tokens;
}
Parser::~Parser() {}
}  // namespace frontend
}  // namespace cs160
