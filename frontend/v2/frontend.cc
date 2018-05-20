/*
 Copyright (c) 2018, Team-Chant
 */
#include <string>
#include <iostream>
#include "frontend/v2/frontend.h"

namespace cs160 {
namespace frontend {
namespace Parse {

namespace ast = cs160::abstract_syntax::frontend;

Frontend::~Frontend(void) {}

Result Variable(State s) {
  auto parse = OnePlus(Range("az"), ConcatVector);
  return parse(s);
}

Node Frontend::stringToAst(std::string s) {
  State state(s);

  auto parse = Variable;
  auto result = parse(state);
  Node ret;
  ret.reset(result.value().GetNodePointer());
  return ret;
}

}  // namespace Parse
}  // namespace frontend
}  // namespace cs160
