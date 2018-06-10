/*
 Copyright (c) 2018, Team-Chant
 */
#include <string>
#include <iostream>
#include "frontend/v5/frontend.h"
#include "abstract_syntax/abstract_syntax.h"
#include "abstract_syntax/print_visitor_v5.h"


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

        auto v_node = v.GetNodeUnique();
        auto v_int_expr = unique_cast
            <ast::IntegerExpr, ast::AstNode>(std::move(v_node));
        // get integer value
        int v_int = v_int_expr->value();

        ret = std::to_string(v_int) + ret;
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
      std::cout << "make v: " << v1_str + v2_str << std::endl;

      // make a new AstNode with the concatenated strings
      std::unique_ptr<ast::AstNode> NodePtr;
      NodePtr.reset(new ast::VariableExpr(v1_str+v2_str));

      Value v(move(NodePtr));
      v.SetString(v1_str+v2_str);
      return v;
    });

    g->Fn = And(Range("az"),  Star(Or(variable_vec),
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

//     //assignable, either variable or dereferenced variable
// lhs --> v | deref
// //for accessing tuple elements (on heap)
// deref --> lhs "->" ae
g-> lhs = Or(Frontend::Lazy(g->V), Frontend::Lazy(g->dref));
g->dref = Sequence(Frontend::Lazy(g->lhs),
              And(Literal('-'), Literal('>'),
                [] (Value v1, Value v2) {
                  return Value("->");
                }),
              Frontend::Lazy(g->ae),
            [] (ValueVec values) {
              std::cout << "dref callback" << std::endl;
              auto v1 = std::move(values.at(0));
              auto v2 = std::move(values.at(2));

              // return Dereference Expression with
              // v1 as the lhs and v2 as the rhs

              // make v1 into an Assignable
              auto v1_node = v1.GetNodeUnique();
              auto v1_assignable = unique_cast
                  <const ast::Assignable>(std::move(v1_node));
                  // make v2 into an Assignable
              auto v2_node = v2.GetNodeUnique();
              auto v2_arith = unique_cast
                  <const ast::ArithmeticExpr>(std::move(v2_node));
              Printer p2;
              v2_arith->Visit(&p2);
              std::cout << "v2 is: " << p2.GetOutput() << std::endl;
              // Make Dereference Node
              std::unique_ptr<ast::AstNode> NodePtr;
              NodePtr.reset(new ast::Dereference(std::move(v1_assignable),
                            std::move(v2_arith)));

              Value retval(std::move(NodePtr));
              return retval;
            });

// primary --> n | v | lhs | "(" expr ")"

std::vector<Parser> primary_vec;
primary_vec.push_back(Frontend::Lazy(g->N));
primary_vec.push_back(Frontend::Lazy(g->V));
primary_vec.push_back(And(Literal('('),
      And(Frontend::Lazy(g->ae),  Literal(')'),
      [] (Value v1, Value v2) {
        // And(Expression_, Literal) callback
        // Put expression node in node_ part
          std::unique_ptr<ast::AstNode> newNodePtr;
          auto v1_node = v1.GetNodeUnique();
          // Ignore literal; Expression should put parenthesis
          // around the expression anyways
          Value ret(std::move(v1_node));
          return ret;
      }),
    [] (Value v1, Value v2) {
      // Expression should put parenthesis around expression anyways
      // So just return v2
      std::unique_ptr<ast::AstNode> newNodePtr;
      auto v2_node = v2.GetNodeUnique();
      Value ret(std::move(v2_node));
      return ret;
    }));
primary_vec.push_back(Frontend::Lazy(g->lhs));
  g->primary = Or(primary_vec);


  // unary --> ("-") primary
  g->unary = And(Star(Literal('-'),
      [](ValueVec values) {
        // star callback
        // counts the number of '-' signs and returns '+' if there is an even
        // number of them, returns '-' if there is an odd number of them
        if (values.size() == 0) {
          return Value("+");
        }

        int counter = values.size();
        // counter tells us how many '-' signs there are

        if (counter % 2 == 0) {
          // there is an even number of negative signs
          // return a +
          Value ret("+");
          return ret;
        } else {
          // there is an odd number of negative signs
          // should be a negative number in the end
          Value ret("-");

          return ret;
        }
      }), Frontend::Lazy(g->primary),

    [](Value v1, Value v2) {
      // And callback
      // v1 should be '-' or '+' depending on the output of star
      std::string v1_str = v1.GetString();

      if (v1_str[0] == '+') {
        // return the Primary output
        auto v2_ptr = v2.GetNodeUnique();
        Value ret(std::move(v2_ptr));
        return ret;
      }

      auto v2_ptr = v2.GetNodeUnique();

      // make Zero Int value
      auto parse_zero = Int();
      State state("0");
      auto result = parse_zero(state);
      Value zero = result.value();
      auto zero_node = zero.GetNodeUnique();
      auto ZeroArithExpr =
          unique_cast<const ast::IntegerExpr>(move(zero_node));

      // Turn the primary output into an Arith Expression
      auto v2_ArithExpr =
          unique_cast<const ast::ArithmeticExpr>(move(v2_ptr));

      std::unique_ptr<ast::AstNode> newNodePtr;

        // make a sub expression
        newNodePtr.reset(new ast::SubtractExpr(
          std::move(ZeroArithExpr),
          std::move(v2_ArithExpr)));
        // To represent a negative number we
        // Subtract the primary output from 0

        Value v(std::move(newNodePtr));
        return v;
    });
g->multiply = And(
    Frontend::Lazy(g->unary),
    Star(
      And(
        Or(Literal('/'), Literal('*')),
        Frontend::Lazy(g->unary),
        [](Value v1, Value v2) {
          // First And callback
          // First value will be a literal, second value will be a Unary
          // make new value
          // put the unary value into the node_ part of the value
          auto v2Node = v2.GetNodeUnique();
          Value ret(move(v2Node));
          // put the operation into the string_ part of the value
          ret.SetString(v1.GetString());
          return ret;
        }),  // end of And()

      // Callback for Star().
      [](ValueVec values) {
        // If there are no matches in the Star, return an empty value.
        // values[0] is the single unary
        // save the list of values to the mult_vec global variable
        // These will be used in the second and callback
        mult_vec_ = std::move(values);
        return Value();
    }),

      [](Value v1, Value v2) {
        // Get the vector of values from the Star callback
        ValueVec values = std::move(mult_vec_);
        // each value has the unary node in the node_ and the
        // operator in the string

        if (values.size() == 0) {
          // No Star output, so return just the unary output from v1
          auto v1_node = v1.GetNodeUnique();
          Value ret(std::move(v1_node));
          return ret;
        } else if (values.size() == 1) {
          // Only one other Unary output, so return one Mult or Div Expr
          // Get the rhs Unary expression & operator from values
          auto last = std::move(values.back());
          std::string last_str = last.GetString();
          char op = last_str[0];
          last_str = last_str.substr(1, last_str.size());

          // Get node for last & make arithmetic expression
          auto val_node = last.GetNodeUnique();
          auto ValArithExpr =
              unique_cast<const ast::ArithmeticExpr>(move(val_node));

          // Get node from v1 & make arithmetic expression
          auto v1_node = v1.GetNodeUnique();
          auto v1_ArithExpr =
              unique_cast<const ast::ArithmeticExpr>(move(v1_node));

          // Make mult & div expression depending on operator
          std::unique_ptr<ast::AstNode> newNodePtr;
          if (op == '*') {
            // multiplication expression
            newNodePtr.reset(new ast::MultiplyExpr(
              move(v1_ArithExpr),
              move(ValArithExpr)));
          } else {
            // division expression
            newNodePtr.reset(new ast::DivideExpr(
              move(v1_ArithExpr),
              move(ValArithExpr)));
          }
          Value v(std::move(newNodePtr));
          return v;
        }

        // if there is more than 1 Unary operator in values
        // Get the very back unary operator
        auto last = std::move(values.back());
        auto last_node = last.GetNodeUnique();
        auto last_ArithExpr =
          unique_cast<const ast::ArithmeticExpr>(move(last_node));

        std::unique_ptr<ast::AstNode> NodePtr;

        while (values.size() > 1) {
          // last has the operator
          // second to last element is the number
          // Concatenate with last_ArithExpr

          last = std::move(values.back());
          values.pop_back();
          // get op
          std::string op_str = last.GetString();
          char op_char = op_str[0];

          // get number & make number Arith Expr
          auto left_num_val = std::move(values.back());
          auto number_node = left_num_val.GetNodeUnique();
          auto num_expr =
              unique_cast<const ast::ArithmeticExpr>(move(number_node));

          if (op_char == '*') {
            NodePtr.reset(new ast::MultiplyExpr(
              move(num_expr), move(last_ArithExpr)));
          } else {
            // division expression
            NodePtr.reset(new ast::DivideExpr(
              move(num_expr), move(last_ArithExpr)));
          }

          // update last_ArithExpr
          last_ArithExpr = unique_cast<const ast::ArithmeticExpr>
            (move(NodePtr));
        }  // end while loop

        // use the last op and the resulting ArithmeticExpr
        // with v1 to make the retval

        // get op
        Value last_op = std::move(values.back());
        std::string last_op_str = last_op.GetString();

        auto first_unary_node = v1.GetNodeUnique();
        auto first_unary_expr =
          unique_cast<const ast::ArithmeticExpr>(move(first_unary_node));

        if (last_op_str[0] == '*') {
          NodePtr.reset(new ast::MultiplyExpr(
            move(first_unary_expr), move(last_ArithExpr)));
        } else {
          NodePtr.reset(new ast::DivideExpr(
            move(first_unary_expr), move(last_ArithExpr)));
        }

        Value v(std::move(NodePtr));
        return v;

        // v1 is the unary for the front of the rule
        // values are all of the strings that are concatenated to the back
      });

    g->add = And(
        Frontend::Lazy(g->multiply),
        Star(
          And(
            Or(Literal('-'), Literal('+')),
            Frontend::Lazy(g->multiply),
            [](Value v1, Value v2) {
              // First and callback
              // First value will be a literal, second value will be a node
            auto v2Node = v2.GetNodeUnique();
             Value ret(std::move(v2Node));
             ret.SetString(v1.GetString());
             return ret;
            }),  // end of And()

          // Callback for Star().
          [](ValueVec values) {
            // similar to mult, put the values in a global variable
            add_vec_ = std::move(values);
            return Value();
          }),
          [](Value v1, Value v2) {
            ValueVec values = std::move(add_vec_);
            // each value has the node in the node
            // and the operator in the string

            if (values.size() == 0) {
              // if there is no values, then the whole thing is just the mult
              // expression in v1
              auto v1_node = v1.GetNodeUnique();
              Value ret(std::move(v1_node));
              return ret;
            } else if (values.size() == 1) {
              // one add or sub expression

              // Get mult value from values
              // And op
              auto last = std::move(values.back());
              std::string last_str = last.GetString();
              char op = last_str[0];
              last_str = last_str.substr(1, last_str.size());

              // Get last node and expression
              auto val_node = last.GetNodeUnique();
              auto ValArithExpr =
                  unique_cast<const ast::ArithmeticExpr>(move(val_node));

            // Get v1 node and expression
              auto v1_node = v1.GetNodeUnique();
              auto v1_ArithExpr =
                  unique_cast<const ast::ArithmeticExpr>(move(v1_node));

              // val hows the value of the unary
              // make expression
              std::unique_ptr<ast::AstNode> newNodePtr;
              if (op == '+') {
                // addition expression
                newNodePtr.reset(new ast::AddExpr(
                  move(v1_ArithExpr),
                  move(ValArithExpr)));
              } else {
                // subtraction expression
                newNodePtr.reset(new ast::SubtractExpr(
                  move(v1_ArithExpr),
                  move(ValArithExpr)));
              }

              Value v(std::move(newNodePtr));
              return v;
            }

            // if it gets down here than size > 1

            auto last = std::move(values.back());
            std::unique_ptr<ast::AstNode> NodePtr;
            auto last_node = last.GetNodeUnique();
            auto last_ArithExpr =
              unique_cast<const ast::ArithmeticExpr>(move(last_node));


            while (values.size() > 1) {
              // last element has the operator
              // second to last element is the number
              // Concatenate with last_ArithExpr

              // get last, num & op
              last = std::move(values.back());
              values.pop_back();
              // get op
              std::string op_str = last.GetString();
              char op_char = op_str[0];

              // get number
              auto left_num_val = std::move(values.back());

              // Make rhs Arithmetic Expr
              auto number_node = left_num_val.GetNodeUnique();
              auto num_expr =
                  unique_cast<const ast::ArithmeticExpr>(move(number_node));

            // Make new add/sub expression & put in NodePtr
              if (op_char == '+') {
                NodePtr.reset(new ast::AddExpr(
                  move(num_expr), move(last_ArithExpr)));
              } else {
                // division expression
                NodePtr.reset(new ast::SubtractExpr(
                  move(num_expr), move(last_ArithExpr)));
              }

              // update last_ArithExpr
              last_ArithExpr = unique_cast<const ast::ArithmeticExpr>
                (move(NodePtr));
            }    // End while loop

            // use the last op and the resulting ArithmeticExpr
            // with v1 to make the retval

            // get op
            Value last_op = std::move(values.back());
            std::string last_op_str = last_op.GetString();

            auto first_unary_node = v1.GetNodeUnique();
            auto first_unary_expr =
              unique_cast<const ast::ArithmeticExpr>(move(first_unary_node));

              // Make last Add/Sub expression
            if (last_op_str[0] == '+') {
              NodePtr.reset(new ast::AddExpr(
                move(first_unary_expr), move(last_ArithExpr)));
            } else {
              NodePtr.reset(new ast::SubtractExpr(
                move(first_unary_expr), move(last_ArithExpr)));
            }

            Value v(std::move(NodePtr));
            return v;

            // v1 is the unary for the front of the rule
            // values are all of the strings that are concatenated to the back
          });

    g->ae = Frontend::Lazy(g->add);
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
    std::cout << "parse state: " << s << std::endl;
    auto result = g.dref(state);
    auto val = result.value();
    return val.GetNodeUnique();
  }

}  // namespace Frontend




}  // namespace Parse
}  // namespace frontend
}  // namespace cs160
