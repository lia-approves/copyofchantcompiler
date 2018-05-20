/*
 Copyright (c) 2018, Team-Chant
 */
#include <string>
#include <iostream>
#include "frontend/v2/frontend.h"

namespace cs160 {
namespace frontend {

namespace ast = cs160::abstract_syntax::frontend;

Frontend::~Frontend(void) {}

Parse::Node Frontend::stringToAst(std::string s) {
  State state(s);
  auto parse = Parse::Literal('h');
  auto result = parse(state);
  Parse::Node ret;
  ret.reset(result.value().GetNodePointer());
  return ret;
}

}  // namespace frontend
}  // namespace cs160
