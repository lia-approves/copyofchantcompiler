/*
 Copyright (c) 2018, Team-Chant
 */
#include <string>
#include <iostream>
#include "frontend/v2/frontend.h"
#include "abstract_syntax/abstract_syntax.h"
#include "abstract_syntax/print_visitor_v2.h"

namespace cs160 {
namespace frontend {
namespace Parse {

namespace ast = cs160::abstract_syntax::frontend;
using ValueVec = std::vector<Value>;
using std::unique_ptr;
using std::string;
using std::move;
using Parser = std::function<Result(State)>;

abstract_syntax::frontend::PrintVisitor printer_;

template<typename TO, typename FROM>
unique_ptr<TO> static_unique_pointer_cast(unique_ptr<FROM>&& old) {
    return unique_ptr<TO>{static_cast<TO*>(old.release())};
    // conversion: unique_ptr<FROM>->FROM*->TO*->unique_ptr<TO>
}

Frontend::~Frontend(void) {}

Parser Variable() {
  std::cout << "making variable" << std::endl;
  return OnePlus(Range("az"), [](ValueVec values) {
    Value v = ConcatVector(std::move(values));
    auto node =
      unique_ptr<ast::AstNode>(new ast::VariableExpr(v.GetString()));
    return Value(move(node));
  });
}

Parser Frontend::Assign() {
  std::cout << "making assign" << std::endl;
  return Sequence(Variable(), Literal('='), Expression(), [](ValueVec values) {
    auto v = values[0].GetNodeUnique();
    unique_ptr<const ast::VariableExpr> var =
      unique_cast<ast::VariableExpr>(move(v));
    auto e = values[2].GetNodeUnique();
    unique_ptr<const ast::ArithmeticExpr> expression =
      unique_cast<ast::VariableExpr>(move(e));
    unique_ptr<ast::AstNode> ret(new ast::Assignment(move(var),
      move(expression)));
    return Value(move(ret));
  });
}

Parser Frontend::Expression() {
  std::cout << "making expression" << std::endl;
  return Add();
}

Parser Frontend::Add() {
  std::cout << "making add" << std::endl;
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
        }),  // end of And()

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
              move(lastAsArithExpr)));
          } else if (op == "-") {
            newNodePtr.reset(new ast::SubtractExpr(
              move(currAsArithExpr),
              move(lastAsArithExpr)));
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
          auto expression = unique_cast
            <ast::VariableExpr, ast::AstNode>(move(v));
          Value ret(std::move(expression));
          ret.SetString(op);
          return ret;
        }
        throw std::logic_error("Couldn't coalesce values into 1 expression");
      }));  // End of Star()
    // Callback for And():
    // [](Value multVal, Value starVal) {
    //   // We know starVal has a string, because it's set in the star callback.
    //   std::string op
    // }
}

Parser Frontend::Multiply() {
  std::cout << "making multiply" << std::endl;
  return And(
    Unary(),
    Star(
      And(
        Or(Literal('/'), Literal('*')),
        Unary(),
        [](Value v1, Value v2) {
          // First value will be a literal, second value will be a node
          auto v2Node = v2.GetNodeUnique();
          Value ret(move(v2Node));
          ret.SetString(v1.GetString());
          return ret;
        }),  // end of And()

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
          if (op == "*") {
            newNodePtr.reset(new ast::MultiplyExpr(
              move(currAsArithExpr),
              move(lastAsArithExpr)));
          } else if (op == "/") {
            newNodePtr.reset(new ast::DivideExpr(
              move(currAsArithExpr),
              move(lastAsArithExpr)));
          } else {
            throw std::logic_error("Mult() operator is neither a / nor a *");
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
          auto expression = unique_cast
            <ast::VariableExpr, ast::AstNode>(move(v));
          Value ret(std::move(expression));
          ret.SetString(op);
          return ret;
        }
        throw std::logic_error("Couldn't coalesce values into 1 expression");
      }));  // End of Star()
}

Parser Frontend::Unary() {
  std::cout << "making unary" << std::endl;
  // return
  //   Or(
  //     Lazy(&Frontend::Primary),
  //     And(
  //       Literal('-'),
  //       Lazy(&Frontend::Unary),
  //     // Callback for And()
  //     [](Value v1, Value v2) -> Value{
  //       std::cout << "in unary callback" << std::endl;
  // // Concatenate a Subtract expression containing 0 and the second value
  //       std::string s1 = v1.GetString();
  //       std::string s2 = v2.GetString();
  //
  //       auto Zero = Value("0");
  //
  //       auto n1 = v1.GetNodeUnique();
  //       auto n2 = v2.GetNodeUnique();
  //       auto zero_node = Zero.GetNodeUnique();
  //
  //       std::cout << "made nodes" << std::endl;
  //
  //       auto ArithExpr2 =
  //         unique_cast<const ast::ArithmeticExpr>(move(n2));
  //       auto ZeroArithExpr =
  //         unique_cast<const ast::ArithmeticExpr>(move(zero_node));
  //
  //       std::cout << "made arithmetic expressions" << std::endl;
  //       std::cout << s1 << ", " << s2 << std::endl;
  //       unique_ptr<ast::AstNode> newNodePtr;
  //       newNodePtr.reset(new ast::SubtractExpr(
  //         move(ZeroArithExpr),
  //         move(ArithExpr2)));
  //
  //       Value ret(std::move(newNodePtr));
  //       return ret;
  //     }));
  return And(Star(Literal('-'),
    [](ValueVec values) {
      std::cout << "in star callback" << std::endl;
      if (values.size() == 0) {
        return Value("+");
      }
      int counter = values.size();
      // counter tells us how many - signs there are
      if (counter % 2 == 0) {
        // there is an even number of negative signs
        // return an add expression (?)
        Value ret("+");
        return ret;
      } else {
        std::cout << "odd number of -" << std::endl;
        // there is an odd number of negative signs
        // should be a negative number in the end
        Value ret("-");
        return ret;
      }
    }
), Int(),
  [](Value v1, Value v2) {
    std::cout << "in and callback" << std::endl;
    // And callback
    // v1 should be '-' or '+' depending on the output of star
    // get value
    std::string v1_str = v1.GetString();
    auto v2_ptr = v2.GetNodeUnique();
    auto v2_int_expr = unique_cast
      <ast::IntegerExpr, ast::AstNode>(move(v2_ptr));
    std::cout << "v2: " << v2_int_expr->value() << std::endl;

    // make Zero Int value
    // auto zero = Value("0");
    // auto zero_node = zero.GetNodeUnique();
    // auto ZeroArithExpr =
    //     unique_cast<const ast::IntegerExpr>(move(zero_node));
    // std::cout << "zero: " << ZeroArithExpr->value() << std::endl;
    auto parse_zero = Int();
    State state("0");
    auto result = parse_zero(state);
    Value zero = result.value();
    // result should be a Value
    auto zero_node = zero.GetNodeUnique();
    auto ZeroArithExpr =
        unique_cast<const ast::IntegerExpr>(move(zero_node));
    std::cout << "zero: " << ZeroArithExpr->value() << std::endl;

    auto v2_ArithExpr =
        unique_cast<const ast::ArithmeticExpr>(move(v2_ptr));

    unique_ptr<ast::AstNode> newNodePtr;

    if (v1_str.at(0) == '+') {
      // make an add expression
      newNodePtr.reset(new ast::AddExpr(
        move(ZeroArithExpr),
        move(v2_int_expr)));
    } else {
      // make a sub expression
      newNodePtr.reset(new ast::SubtractExpr(
        move(ZeroArithExpr),
        move(v2_int_expr)));
    }

    Value v(std::move(newNodePtr));
    return v;
  }
);
}


// Creates a Program
Parser Frontend::Program() {
  std::cout << "making program" << std::endl;
  return And(
  Star(Lazy(&Frontend::Assign),
  // Callback for Star().
  [](ValueVec values) {
    // If there are no matches in the Star, return an empty value.
    if (values.size() == 0) {
      return Value();
    }
    // As long as there are multiple matches, coalesce them into 1.
    std::vector<std::unique_ptr<const ast::Assignment>> assignments;
    while (values.size() > 1) {
      // Get the current assignment
      std::string op = values.back().GetString();
      auto curr = values.back().GetNodeUnique();
      auto currAssignment =
        unique_cast<const ast::Assignment>(move(curr));

        // push to the vector
      assignments.push_back(move(currAssignment));

      // Replace the last element with newNodePtr
      values.pop_back();
    }
    // If there is 1 match, return it and the result of the And() (casted).
    if (values.size() == 1) {
      // This Value is an ArithmeticExp
      std::string exp = values[0].GetString();
      auto v = values[0].GetNodeUnique();
      auto v2 = unique_cast<ast::ArithmeticExpr, ast::AstNode>(move(v));

      auto ProgExpression = new ast::Program(move(assignments), move(v2));
      auto expression = make_unique<ast::Program>(move(*ProgExpression));
      Value ret(std::move(expression));
      ret.SetString(exp);
      return ret;
    }
    throw std::logic_error("Couldn't coalesce values into 1 expression");
  }), Lazy(&Frontend::Expression));
}

Parser Frontend::Primary() {
  std::cout << "making primary" << std::endl;
  return Or(
      Int(),
      Or(
          Variable(),
            And(Literal('('),
                And(Lazy(&Frontend::Expression),  Literal(')')))));
  // return Or(p_vec);
}

// Parser Frontend::Test_Function() {
// // void (MyClass::*func)(int);
// // func = &MyClass::buttonClickedEvent;
//
// //  Parser (*a_ptr)() = Test_Function;
//   // Parser (Frontend::*func)();
//   // func = &Frontend::Test_Function;
//
//   std::cout << "in A()" << std::endl;
//   // return Or(And(Literal('-'), Lazy(func)), Int());
//   Parser (Frontend::*func)();
//   func = &Frontend::Unary;
//   return Lazy(func);
// }

Parser Frontend::Lazy(Parser (Frontend::*function)() ) {
  // takes a pointer to a parser function
  // returns a parser which, when called, calls the function pointer
  return [function](State state) -> Result{
    Frontend f;
    std::cout << "lazy is running" << std::endl;
    Parser p = (f.*function)();

    auto result = p(state);
    if (result.success()) {
      return result;
    } else {
      return Result(state, false, "no match");
    }
  };
}

template<class Op1Node, class Op2Node>
std::function<Value(ValueVec)> makeCoalescer(string op1, string op2) {
  return [op1, op2](ValueVec values) {
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
      if (op == op1) {
        newNodePtr.reset(new Op1Node(
          move(currAsArithExpr),
          move(lastAsArithExpr)));
      } else if (op == op2) {
        newNodePtr.reset(new Op2Node(
          move(currAsArithExpr),
          move(lastAsArithExpr)));
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
  };
}

Node Frontend::stringToAst(std::string s) {
  State state(s);
  auto parse = Unary();
  auto result = parse(state);
  // std::unique_ptr<ast::AstNode> n(new ast::IntegerExpr(1));
  // std::unique_ptr<ast::IntegerExpr> p = unique_cast<std::unique_ptr
  // <ast::AstNode>, std::unique_ptr<ast::IntegerExpr>> (n);

  // std::unique_ptr<ast::AstNode> a(new ast::IntegerExpr(1));
  // std::unique_ptr<ast::IntegerExpr> b = unique_cast<ast::IntegerExpr>
  // (std::move(a));

  // auto ptr = result.value().GetNodePointer();

  auto val = result.value();
  return val.GetNodeUnique();
}

}  // namespace Parse
}  // namespace frontend
}  // namespace cs160
