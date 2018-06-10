/*
 Copyright (c) 2018, Team-Chant
 */
#include <string>
#include <iostream>
#include "frontend/v5/frontend.h"
#include "abstract_syntax/abstract_syntax.h"


namespace cs160 {
namespace frontend {
namespace Parse {

namespace ast = cs160::abstract_syntax::frontend;
using ValueVec = std::vector<Value>;
using std::unique_ptr;
using std::string;
using std::move;
using Parser = std::function<Result(State)>;
using Printer = abstract_syntax::version_5::PrintVisitor;



template<typename TO, typename FROM>
unique_ptr<TO> static_unique_pointer_cast(unique_ptr<FROM>&& old) {
    return unique_ptr<TO>{static_cast<TO*>(old.release())};
    // conversion: unique_ptr<FROM>->FROM*->TO*->unique_ptr<TO>
}

namespace Frontend {
void InitializeParsers(Frontend::Grammar *g) {
    g->N = OnePlus(Int(),
    [] (ValueVec values) {
      // Callback for OnePlus
      std::string ret = "";
      // concatenate all ints in string, then make into int

      while (values.size() > 0) {
        // get value
        auto v = std::move(values.back());
        values.pop_back();

        std::string last_str = v.GetString();

        // check that it's a digit
        if (!std::isdigit(last_str.at(0))) {
          throw std::logic_error("Tried to put non digit in an int");
        }

        ret = last_str + ret;
      }  // end while loop

      int ret_int = std::stoi(ret);

      std::unique_ptr<ast::AstNode> NodePtr;
      NodePtr.reset(new ast::IntegerExpr(ret_int));
      Value ret_value(std::move(NodePtr));

      return ret_value;
      // ret is the concatenation of all of the int values
    });  // end OnePlus

    std::vector<Parser> variable_vec;
    variable_vec.push_back(Range("az"));
    variable_vec.push_back(Range("09"));
    variable_vec.push_back(Literal('_'));

    g->V = And(Range("az"),  Star(Or(variable_vec),
      [](ValueVec values) {
        // star callback

        if (values.size() == 0) {
          // The variable is only 1 char long
          std::cout << "size is 0" << std::endl;
          Value v("");
          return v;
        }
        // values.size() >=1
        std::string ret = "";

        // While concatenates all of the variable chars into one string, ret
        while (values.size() > 0) {
          // push value to string
          auto last = std::move(values.back());
          values.pop_back();

          std::string last_str = last.GetString();
          ret = last_str + ret;
        }

        // now that ret contains all of the chars,
        // make it into a Value and return
        Value v(ret);
        return v;
      }),

    [](Value v1, Value v2) {
      // Callback for and

      // v1_str contains the string for the leading char
      std::string v1_str = v1.GetString();
      // v2_str contains ret from the Star callback
      std::string v2_str = v2.GetString();

      // make a new AstNode with the concatenated strings
      std::unique_ptr<ast::AstNode> NodePtr;
      NodePtr.reset(new ast::VariableExpr(v1_str+v2_str));

      Value v(move(NodePtr));
      v.SetString(v1_str+v2_str);
      return v;
    });
}





Parser Lazy(std::function<Result(State)> &function) {
  // takes a pointer to a parser function
  // returns a parser which, when called, calls the function pointer
  return [&](State state) -> Result{
    // std::cout << "lazy is running" << std::endl;
    auto result = function(state);

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

// Takes string, creates AST Node
unique_ptr<ast::AstNode> stringToAst(std::string s) {
    State state(s);
    // Make and initialize grammar
    Frontend::Grammar g;
    InitializeParsers(&g);

    // Parse
    auto result = g.N(state);
    auto val = result.value();
    return val.GetNodeUnique();
  }

}  // namespace Frontend




}  // namespace Parse
}  // namespace frontend
}  // namespace cs160
