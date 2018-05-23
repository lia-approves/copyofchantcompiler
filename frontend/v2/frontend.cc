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

Parser Frontend::Add() {
  return And(
    Multiply(),
    Star(
      And(
        Or(Literal('-'), Literal('+')),
        Multiply(),
        [](Value v1, Value v2) {
          // First value will be a literal, second value will be a node
          auto v2Node = v2.GetNodeUnique();
          Value ret(move(v2Node));
          ret.SetString(v1.GetString());
          return ret;
        }
      ),  // end of And()

      // Callback for Star().
      [](ValueVec values) {
        // If there are no matches in the Star, return an empty value.
        if (values.size() == 0) {
          return Value();
        }
        // As long as there are multiple matches, coalesce them into 1.
        while (values.size() > 1) {
          // We know it has a string because it comes from the And() callback
          std::string op = values.back().GetString();
          auto last = values.back().GetNodeUnique();
          values.pop_back();
          auto curr = values.back().GetNodeUnique();
          auto lastAsArithExpr =
            unique_cast<const ast::ArithmeticExpr>(move(last));
          auto currAsArithExpr =
            unique_cast<const ast::ArithmeticExpr>(move(curr));
          // Create a node from the last 2 elements (curr and last)
          unique_ptr<ast::AstNode> newNodePtr;
          if (op == "+") {
            newNodePtr.reset(new ast::AddExpr(
              move(currAsArithExpr),
              move(lastAsArithExpr)
            ));
          } else if (op == "-") {
            newNodePtr.reset(new ast::SubtractExpr(
              move(currAsArithExpr),
              move(lastAsArithExpr)
            ));
          } else {
            throw std::logic_error("Add() operator is neither a - nor a +");
          }
          // Replace the last element with newNodePtr
          values.pop_back();
          Value v(move(newNodePtr));
          values.push_back(move(v));
        }
        // If there is 1 match, return it and the result of the Or() (casted).
        if (values.size() == 1) {
          // This Value comes from the previous And(), so it contains a string.
          std::string op = values[0].GetString();
          auto v = values[0].GetNodeUnique();
          auto expression = unique_cast<ast::VariableExpr>(move(v));
          Value ret(std::move(expression));
          ret.SetString(op);
          return ret;
        }
        throw std::logic_error("Couldn't coalesce values into 1 expression");
      }
    )  // End of Star()
    // Callback for And():
    // [](Value multVal, Value starVal) {
    //   // We know starVal has a string, because it's set in the star callback.
    //   std::string op
    // }
  );
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

  // std::unique_ptr<ast::AstNode> a(new ast::IntegerExpr(1));
  // std::unique_ptr<ast::IntegerExpr> b = unique_cast<ast::IntegerExpr>(std::move(a));

  // auto ptr = result.value().GetNodePointer();
  auto val = result.value();
  return val.GetNodeUnique();
}

}  // namespace Parse
}  // namespace frontend
}  // namespace cs160
