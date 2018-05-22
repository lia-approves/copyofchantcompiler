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
using std::move;

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
    return Value(move(node));
  });
}

Parser Frontend::Assign() {
  return Sequence(Variable(), Literal('='), Expression(), [](ValueVec values) {
    auto v = values[0].GetNodeUnique();
    unique_ptr<const ast::VariableExpr> var =
      unique_cast<ast::VariableExpr>(move(v));
    auto e = values[2].GetNodeUnique();
    unique_ptr<const ast::ArithmeticExpr> expression =
      unique_cast<ast::VariableExpr>(move(e));
    unique_ptr<ast::AstNode> ret(new ast::Assignment(move(var), move(expression)));
    return Value(move(ret));
  });
}

Parser Frontend::Expression() {
  return Add();
}

// Parser Frontend::Add() {
//   return And(
//     Mult(),
//     Star(And(
//       Or(Literal('-'), Literal('+')),
//       Mult()
//     ))
//   );
// }

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

  // std::unique_ptr<ast::AstNode> a(new ast::IntegerExpr(1));
  // std::unique_ptr<ast::IntegerExpr> b = unique_cast<ast::IntegerExpr>(std::move(a));

  // auto ptr = result.value().GetNodePointer();
  auto val = result.value();
  return val.GetNodeUnique();
}

}  // namespace Parse
}  // namespace frontend
}  // namespace cs160
