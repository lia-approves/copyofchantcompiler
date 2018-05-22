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
using ValueVec = std::vector<Value>;
using std::unique_ptr;

template<typename TO, typename FROM>
unique_ptr<TO> static_unique_pointer_cast (unique_ptr<FROM>&& old){
    return unique_ptr<TO>{static_cast<TO*>(old.release())};
    //conversion: unique_ptr<FROM>->FROM*->TO*->unique_ptr<TO>
}

Frontend::~Frontend(void) {}

Parser Variable() {
  return OnePlus(Range("az"), [](ValueVec values) {
    Value v = ConcatVector(std::move(values));
    auto node =
      unique_ptr<ast::AstNode>(new ast::VariableExpr(v.GetString()));
    return Value(std::move(node));
    // return v;
  });
}

// Parser Frontend::Assign() {
//   return Sequence(Variable(), Literal('='), Expression(), [](ValueVec values) {
//     // auto var = values[0].GetNodeUnique();
//     // auto expr = values[2].GetNodeUnique();
//     // auto oldVarPointer = values[0].GetNodeUnique();
//     // unique_ptr<ast::VariableExpr> var =
//     //   static_unique_pointer_cast<ast::VariableExpr>(std::move(oldVarPointer));
//     // auto node = std::unique_ptr<ast::AstNode>(new ast::Assignment(
//     //   std::dynamic_pointer_cast<ast::VariableExpr>(var),
//     //   std::dynamic_pointer_cast<ast::ArithmeticExpr>(expr)
//     // ));
//     // return Value(std::move(node));
//     return Value("hi");
//     // auto ret = std::unique_ptr<AstNode>(new Assignment(
//     //   std::move()
//     // ))
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

struct A {};
struct B : public A {};

Node Frontend::stringToAst(std::string s) {
  State state(s);

  auto parse = Variable();
  auto result = parse(state);

  // std::unique_ptr<ast::AstNode> n(new ast::IntegerExpr(1));
  // std::unique_ptr<ast::IntegerExpr> p = unique_cast<std::unique_ptr<ast::AstNode>, std::unique_ptr<ast::IntegerExpr>> (n);

  std::unique_ptr<ast::AstNode> a(new ast::IntegerExpr(1));
  std::unique_ptr<ast::IntegerExpr> b = unique_cast<ast::IntegerExpr>(std::move(a));

  // auto ptr = result.value().GetNodePointer();
  auto val = result.value();
  return val.GetNodeUnique();
}

}  // namespace Parse
}  // namespace frontend
}  // namespace cs160
