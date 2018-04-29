// Copyright (c) 2018, Team-Chant

#include "frontend/parser/parser.h"

namespace cs160 {
namespace frontend {

Parser::Parser(std::vector<std::shared_ptr<Token>> tokens) {
  this->tokens = tokens;
}
Parser::~Parser() {}
}  // namespace frontend
}  // namespace cs160
