// Copyright (c) 2018, Team-Chant
#ifndef FRONTEND_V2_FRONTEND_H_
#define FRONTEND_V2_FRONTEND_H_

#include <vector>
#include <string>
#include <memory>
#include "abstract_syntax/abstract_syntax.h"
#include "frontend/combinator/parser.h"
#include "utility/memory.h"
#include "abstract_syntax/print_visitor_v2.h"


template<class R, class T>
std::unique_ptr<R> unique_cast(std::unique_ptr<T> &&p) {
  T* ptr = p.release();
  return std::unique_ptr<R>(static_cast<R*>(ptr));
}

namespace cs160 {
namespace frontend {
namespace Parse {
  using Parser = std::function<Result(State)>;
  using ValueVec = std::vector<Value>;
  using Printer = abstract_syntax::frontend::PrintVisitor;
  namespace ast = cs160::abstract_syntax::frontend;

namespace Frontend {

  Node stringToAst(std::string input);

  ValueVec mult_vec;
  ValueVec add_vec;

  // Parser Program();
  // Parser Assign();
  // Parser Expression();
  // Parser Add();
  // Parser Multiply();
  // Parser Unary();
  // Parser Primary();
  // Parser Test_Function();
  Parser Lazy(std::function<Result(State)> &function);
  void Test_Function();
struct Grammar {
  Parser Program_;
  Parser Assign_;
  Parser Expression_;
  Parser Add_;
  Parser Multiply_;
  Parser Unary_;
  Parser Primary_;
  Parser Variable_;
};

  void InitializeParsers(Grammar *g) {
    // Initialize Variable
    std::vector<Parser> variable_vec;
    variable_vec.push_back(Range("az"));
    variable_vec.push_back(Range("09"));
    variable_vec.push_back(Literal('_'));
    g->Variable_ = And(Range("az"),  Star(Or(variable_vec),
      [](ValueVec values) {
        // star callback
        if (values.size() == 0) {
          std::cout << "size is 0" << std::endl;
          Value v("");
          return v;
        }
        // values.size() >=1
        std::string ret = "";

        while (values.size() > 0) {
          // push value to string
          auto last = std::move(values.back());
          values.pop_back();

          std::string last_str = last.GetString();
          ret = last_str + ret;
        }
        Value v(ret);
        return v;
      }),
    [](Value v1, Value v2) {
      // Callback for and
      std::string v1_str = v1.GetString();
      std::string v2_str = v2.GetString();
      std::unique_ptr<ast::AstNode> NodePtr;
      NodePtr.reset(new ast::VariableExpr(v1_str+v2_str));

      Value v(move(NodePtr));
      v.SetString(v1_str+v2_str);
      return v;
    });

    g->Unary_ = And(Star(Literal('-'),
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
            // there is an odd number of negative signs
            // should be a negative number in the end
            Value ret("-");

            return ret;
          }
        }), Int(),
      [](Value v1, Value v2) {
        // And callback
        // v1 should be '-' or '+' depending on the output of star
        // get value
        std::string v1_str = v1.GetString();
        auto v2_ptr = v2.GetNodeUnique();

        auto v2_int_expr = unique_cast
          <ast::IntegerExpr, ast::AstNode>(move(v2_ptr));

        // make Zero Int value
        auto parse_zero = Int();
        State state("0");
        auto result = parse_zero(state);
        Value zero = result.value();
        // result should be a Value
        auto zero_node = zero.GetNodeUnique();
        auto ZeroArithExpr =
            unique_cast<const ast::IntegerExpr>(move(zero_node));

        auto v2_ArithExpr =
            unique_cast<const ast::ArithmeticExpr>(move(v2_ptr));

        std::unique_ptr<ast::AstNode> newNodePtr;

        if (v1_str.at(0) == '+') {
          // make an add expression
          newNodePtr.reset(new ast::IntegerExpr(
            std::move(v2_int_expr->value())));
        } else {
          // make a sub expression
          newNodePtr.reset(new ast::SubtractExpr(
            std::move(ZeroArithExpr),
            std::move(v2_int_expr)));
        }

        Value v(std::move(newNodePtr));
        return v;
      });

      g->Multiply_ =  And(
          Frontend::Lazy(g->Unary_),
          Star(
            And(
              Or(Literal('/'), Literal('*')),
              Frontend::Lazy(g->Unary_),
              [](Value v1, Value v2) {
                // First value will be a literal, second value will be a node
                // First value will be a literal, second value will be a node
                auto v2Node = v2.GetNodeUnique();
                Value ret(move(v2Node));
                ret.SetString(v1.GetString());
                return ret;
              }),  // end of And()

            // Callback for Star().
            [](ValueVec values) {
              // If there are no matches in the Star, return an empty value.
              // values[0] is the single unary
              mult_vec = std::move(values);
              return Value();
          }),

            [](Value v1, Value v2) {
              ValueVec values = std::move(mult_vec);
      // each value has the node in the node and the operator in the string
              std::cout << "in and callback " << values.size() << std::endl;

              if (values.size() == 0) {
                return v1;
              } else if (values.size() == 1) {
                auto last = std::move(values.back());
                std::cout << "got last" << std::endl;
                std::string last_str = last.GetString();
                char op = last_str[0];
                last_str = last_str.substr(1, last_str.size());
                std::cout << "got last str: " << last_str << std::endl;
                std::cout << "op is: " <<  op << std::endl;

                // parse the Unary string
                Printer p1;
                Printer p2;

                auto val_node = last.GetNodeUnique();
                std::cout << "got val node" << std::endl;
                val_node->Visit(&p1);
                std::string val_str = p1.GetOutput();
                std::cout << "val_str output: " << val_str << std::endl;
                auto ValArithExpr =
                    unique_cast<const ast::ArithmeticExpr>(move(val_node));
                auto v1_node = v1.GetNodeUnique();
                v1_node->Visit(&p2);
                std::string v1_str = p2.GetOutput();
                std::cout << "v1_str is: " << v1_str << std::endl;
                auto v1_ArithExpr =
                    unique_cast<const ast::ArithmeticExpr>(move(v1_node));

                // val hows the value of the unary
                // make expression
                std::unique_ptr<ast::AstNode> newNodePtr;
                if (op == '*') {
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

              std::cout << "past if statements" << std::endl;
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
                std::cout << "in while loop" << std::endl;
                // Printer print;
                // last_ArithExpr->Visit(&print);
                // std::string print_str = print.GetOutput();
                // std::cout << print_str << std::endl;

                last = std::move(values.back());
                values.pop_back();
                // get op
                std::string op_str = last.GetString();
                std::cout << "operation string is: " << op_str << std::endl;
                char op_char = op_str[0];

                // get number
                auto left_num_val = std::move(values.back());
                std::cout << "got left_num_val" << std::endl;

                auto number_node = left_num_val.GetNodeUnique();
                auto num_expr =
                    unique_cast<const ast::ArithmeticExpr>(move(number_node));

                std::cout << "OPERATOR IS: " << op_char << std::endl;
                if (op_char == '*') {
                  NodePtr.reset(new ast::MultiplyExpr(
                    move(num_expr), move(last_ArithExpr)));
                } else {
                  // division expression
                  NodePtr.reset(new ast::DivideExpr(
                    move(num_expr), move(last_ArithExpr)));
                }
                Printer p;
               NodePtr->Visit(&p);
               std::string node_str = p.GetOutput();

                // update last_ArithExpr
                last_ArithExpr = unique_cast<const ast::ArithmeticExpr>
                  (move(NodePtr));
              }

              // use the last op and the resulting ArithmeticExpr
              // with v1 to make the retval

              // get op
              Value last_op = std::move(values.back());
              std::string last_op_str = last_op.GetString();

              auto first_unary_node = v1.GetNodeUnique();
              auto first_unary_expr =
                unique_cast<const ast::ArithmeticExpr>(move(first_unary_node));

                std::cout << "OPERATOR IS: " << last_op_str[0] << std::endl;
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

    g-> Add_ = And(
        Frontend::Lazy(g->Multiply_),
        Star(
          And(
            Or(Literal('-'), Literal('+')),
            Frontend::Lazy(g->Multiply_),
            [](Value v1, Value v2) {
              // First value will be a literal, second value will be a node
            auto v2Node = v2.GetNodeUnique();
             Value ret(std::move(v2Node));
             ret.SetString(v1.GetString());
             return ret;
            }),  // end of And()

          // Callback for Star().
          [](ValueVec values) {
            add_vec = std::move(values);
            return Value();
          }),
          [](Value v1, Value v2) {
            ValueVec values = std::move(add_vec);
            // each value has the node in the node
            // and the operator in the string
            std::cout << "in add callback " << values.size() << std::endl;

            if (values.size() == 0) {
              Printer p;
              auto v1_node = v1.GetNodeUnique();
              v1_node->Visit(&p);
              v1.SetString("OUT OF ADD CALLBACK");
              std::cout << "v1 is : " << p.GetOutput() << std::endl;
              return v1;
            } else if (values.size() == 1) {
              auto last = std::move(values.back());
              std::cout << "got last" << std::endl;
              std::string last_str = last.GetString();
              char op = last_str[0];
              last_str = last_str.substr(1, last_str.size());
              std::cout << "got last str: " << last_str << std::endl;
              std::cout << "op is: " <<  op << std::endl;

              // parse the Unary string
              Printer p1;
              Printer p2;

              auto val_node = last.GetNodeUnique();
              std::cout << "got val node" << std::endl;
              val_node->Visit(&p1);
              std::string val_str = p1.GetOutput();
              std::cout << "val_str output: " << val_str << std::endl;
              auto ValArithExpr =
                  unique_cast<const ast::ArithmeticExpr>(move(val_node));
              auto v1_node = v1.GetNodeUnique();
              v1_node->Visit(&p2);
              std::string v1_str = p2.GetOutput();
              std::cout << "v1_str is: " << v1_str << std::endl;
              auto v1_ArithExpr =
                  unique_cast<const ast::ArithmeticExpr>(move(v1_node));

              // val hows the value of the unary
              // make expression
              std::unique_ptr<ast::AstNode> newNodePtr;
              if (op == '+') {
                newNodePtr.reset(new ast::AddExpr(
                  move(v1_ArithExpr),
                  move(ValArithExpr)));
              } else {
                // division expression
                newNodePtr.reset(new ast::SubtractExpr(
                  move(v1_ArithExpr),
                  move(ValArithExpr)));
              }
              std::cout << "print me pls" << std::endl;
              Value v(std::move(newNodePtr));
              return v;
            }

            std::cout << "past if statements" << std::endl;
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
              std::cout << "in while loop" << std::endl;
              // Printer print;
              // last_ArithExpr->Visit(&print);
              // std::string print_str = print.GetOutput();
              // std::cout << print_str << std::endl;

              last = std::move(values.back());
              values.pop_back();
              // get op
              std::string op_str = last.GetString();
              std::cout << "operation string is: " << op_str << std::endl;
              char op_char = op_str[0];

              // get number
              auto left_num_val = std::move(values.back());

              auto number_node = left_num_val.GetNodeUnique();
              auto num_expr =
                  unique_cast<const ast::ArithmeticExpr>(move(number_node));

              std::cout << "OPERATOR IS: " << op_char << std::endl;
              if (op_char == '+') {
                NodePtr.reset(new ast::AddExpr(
                  move(num_expr), move(last_ArithExpr)));
              } else {
                // division expression
                NodePtr.reset(new ast::SubtractExpr(
                  move(num_expr), move(last_ArithExpr)));
              }
              Printer p;
             NodePtr->Visit(&p);
             std::string node_str = p.GetOutput();
             std::cout << "VALUE OF NODEPTR IS: " << node_str << std::endl;

              // update last_ArithExpr
              last_ArithExpr = unique_cast<const ast::ArithmeticExpr>
                (move(NodePtr));
            }

            // use the last op and the resulting ArithmeticExpr
            // with v1 to make the retval

            // get op
            Value last_op = std::move(values.back());
            std::string last_op_str = last_op.GetString();

            auto first_unary_node = v1.GetNodeUnique();
            auto first_unary_expr =
              unique_cast<const ast::ArithmeticExpr>(move(first_unary_node));

              std::cout << "OPERATOR IS: " << last_op_str[0] << std::endl;
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
  }



Node test_function(std::string s) {
    State state(s);
    Grammar g;
    InitializeParsers(&g);

    // A = Or(And(Literal('-'), Frontend::Lazy(A),
    //   [](Value v1, Value v2) {
    //     std::cout << v2.GetString() << std::endl;
    //     return v1;
    //   }), Int());
    auto result = g.Add_(state);
    std::cout << "parsed!" << std::endl;
    auto val = result.value();
    return val.GetNodeUnique();
  }

}  // namespace Frontend

}  // namespace Parse
}  // namespace frontend
}  // namespace cs160



#endif  // FRONTEND_V2_FRONTEND_H_
