/*
 Copyright (c) 2018, Team-Chant
 */
#include <string>
#include <iostream>
#include "frontend/v2/frontend.h"
#include "abstract_syntax/abstract_syntax.h"

namespace cs160 {
namespace frontend {
namespace Parse {

namespace ast = cs160::abstract_syntax::frontend;

Frontend::~Frontend(void) {}

Parser Variable() {
  return OnePlus(Range("az"), [](std::vector<Value> values) {
    Value v = ConcatVector(std::move(values));
    auto node =
      std::unique_ptr<ast::AstNode>(new ast::VariableExpr(v.GetString()));
    return Value(std::move(node));
    // return v;
  });
}

// Parser Frontend::Assign() {
//   return Sequence(Id(), Literal('='), Expression(), [](std::vector<Value> values) {
//     auto ret = std::unique_ptr<AstNode>(new Assignment(
//
//     ))
//   });
// }

Parser Frontend::Expression() {
  return Add();
}

// Parser Frontend::Add() {
//   return And(
//     Multiply(),
//     Star(And(
//       Or(Literal('-'), Literal('+')),
//       Multiply()
//     ))
//   );
// }

Node Frontend::stringToAst(std::string s) {
  State state(s);

  auto parse = Variable();
  auto result = parse(state);
  // auto ptr = result.value().GetNodePointer();
  auto val = result.value();
  return val.GetNodeUnique();
}

}  // namespace Parse
}  // namespace frontend
}  // namespace cs160
