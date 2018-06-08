/*
 Copyright (c) 2018, Team-Chant
 */
#include <string>
#include <iostream>
#include "frontend/v2/frontend.h"
#include "abstract_syntax/abstract_syntax.h"
#include "abstract_syntax/print_visitor_v2.h"

// Unary works
// Add works
// Multiply works
// Expression works
// Assign works

namespace cs160 {
namespace frontend {
namespace Parse {

namespace ast = cs160::abstract_syntax::frontend;
using ValueVec = std::vector<Value>;
using std::unique_ptr;
using std::string;
using std::move;
using Parser = std::function<Result(State)>;
using Printer = abstract_syntax::frontend::PrintVisitor;

ValueVec mult_vec;
ValueVec add_vec;

template<typename TO, typename FROM>
unique_ptr<TO> static_unique_pointer_cast(unique_ptr<FROM>&& old) {
    return unique_ptr<TO>{static_cast<TO*>(old.release())};
    // conversion: unique_ptr<FROM>->FROM*->TO*->unique_ptr<TO>
}

//

// Parser Variable() {
//   // std::cout << "making variable" << std::endl;
//   std::vector<Parser> p_vec;
//   p_vec.push_back(Range("az"));
//   p_vec.push_back(Range("09"));
//   p_vec.push_back(Literal('_'));
//
//   return And(Range("az"),  Star(Or(p_vec),
//   [](ValueVec values) {
//     // star callback
//     if (values.size() == 0) {
//       std::cout << "size is 0" << std::endl;
//       return Value("");
//     }
//     // values.size() >=1
//     std::string ret = "";
//
//     while (values.size() > 0) {
//       // push value to string
//       auto last = move(values.back());
//       values.pop_back();
//
//       std::string last_str = last.GetString();
//       ret = last_str + ret;
//     }
//     Value v(ret);
//     return v;
//   }  // end star callback
// ),
// [](Value v1, Value v2) {
//   // Callback for and
//   std::string v1_str = v1.GetString();
//   std::string v2_str = v2.GetString();
//   unique_ptr<ast::AstNode> NodePtr;
//   NodePtr.reset(new ast::VariableExpr(v1_str+v2_str));
//
//   Value v(move(NodePtr));
//   v.SetString(v1_str+v2_str);
//   return v;
// });
//   // return OnePlus(Range("az"), [](ValueVec values) {
//   //   Value v = ConcatVector(std::move(values));
//   //   auto node =
//   //     unique_ptr<ast::AstNode>(new ast::VariableExpr(v.GetString()));
//   //   return Value(move(node));
//   // });
// }
//
// Parser Frontend::Assign() {
//   // std::cout << "making assign" << std::endl;
//   return Sequence(Variable(), Literal('='), Expression(), [](ValueVec values) {
//     auto v = values[0].GetNodeUnique();
//     unique_ptr<const ast::VariableExpr> var =
//       unique_cast<ast::VariableExpr>(move(v));
//     auto e = values[2].GetNodeUnique();
//     unique_ptr<const ast::ArithmeticExpr> expression =
//       unique_cast<ast::VariableExpr>(move(e));
//     unique_ptr<ast::AstNode> ret(new ast::Assignment(move(var),
//       move(expression)));
//     return Value(move(ret));
//   });
// }
//
// Parser Frontend::Expression() {
//   // std::cout << "making expression" << std::endl;
//   return Add();
// }
//
//
// Parser Frontend::Add() {
//   // std::cout << "making add" << std::endl;
//   return And(
//     Multiply(),
//     Star(
//       And(
//         Or(Literal('-'), Literal('+')),
//         Multiply(),
//         [](Value v1, Value v2) {
//           // First value will be a literal, second value will be a node
//         auto v2Node = v2.GetNodeUnique();
//          Value ret(move(v2Node));
//          ret.SetString(v1.GetString());
//          return ret;
//         }),  // end of And()
//
//       // Callback for Star().
//       [](ValueVec values) {
//         add_vec = std::move(values);
//         return Value();
//       }),
//       [](Value v1, Value v2) {
//         ValueVec values = std::move(add_vec);
//         // each value has the node in the node and the operator in the string
//         std::cout << "in add callback " << values.size() << std::endl;
//
//         if (values.size() == 0) {
//           Printer p;
//           auto v1_node = v1.GetNodeUnique();
//           v1_node->Visit(&p);
//           std::cout << "v1 is : " << p.GetOutput() << std::endl;
//           return v1;
//         } else if (values.size() == 1) {
//           auto last = std::move(values.back());
//           std::cout << "got last" << std::endl;
//           std::string last_str = last.GetString();
//           char op = last_str[0];
//           last_str = last_str.substr(1, last_str.size());
//           std::cout << "got last str: " << last_str << std::endl;
//           std::cout << "op is: " <<  op << std::endl;
//
//           // parse the Unary string
//           Printer p1;
//           Printer p2;
//
//           auto val_node = last.GetNodeUnique();
//           std::cout << "got val node" << std::endl;
//           val_node->Visit(&p1);
//           std::string val_str = p1.GetOutput();
//           std::cout << "val_str output: " << val_str << std::endl;
//           auto ValArithExpr =
//               unique_cast<const ast::ArithmeticExpr>(move(val_node));
//           auto v1_node = v1.GetNodeUnique();
//           v1_node->Visit(&p2);
//           std::string v1_str = p2.GetOutput();
//           std::cout << "v1_str is: " << v1_str << std::endl;
//           auto v1_ArithExpr =
//               unique_cast<const ast::ArithmeticExpr>(move(v1_node));
//
//           // val hows the value of the unary
//           // make expression
//           unique_ptr<ast::AstNode> newNodePtr;
//           if (op == '+') {
//             newNodePtr.reset(new ast::AddExpr(
//               move(v1_ArithExpr),
//               move(ValArithExpr)));
//           } else {
//             // division expression
//             newNodePtr.reset(new ast::SubtractExpr(
//               move(v1_ArithExpr),
//               move(ValArithExpr)));
//           }
//           std::cout << "print me pls" << std::endl;
//           Value v(std::move(newNodePtr));
//           return v;
//         }
//
//         std::cout << "past if statements" << std::endl;
//         // if it gets down here than size > 1
//
//         auto last = std::move(values.back());
//
//         unique_ptr<ast::AstNode> NodePtr;
//
//         auto last_node = last.GetNodeUnique();
//         auto last_ArithExpr =
//           unique_cast<const ast::ArithmeticExpr>(move(last_node));
//
//
//         while (values.size() > 1) {
//           // last element has the operator
//           // second to last element is the number
//           // Concatenate with last_ArithExpr
//           std::cout << "in while loop" << std::endl;
//           // Printer print;
//           // last_ArithExpr->Visit(&print);
//           // std::string print_str = print.GetOutput();
//           // std::cout << print_str << std::endl;
//
//           last = std::move(values.back());
//           values.pop_back();
//           // get op
//           std::string op_str = last.GetString();
//           std::cout << "operation string is: " << op_str << std::endl;
//           char op_char = op_str[0];
//
//           // get number
//           auto left_num_val = std::move(values.back());
//
//           auto number_node = left_num_val.GetNodeUnique();
//           auto num_expr =
//               unique_cast<const ast::ArithmeticExpr>(move(number_node));
//
//           std::cout << "OPERATOR IS: " << op_char << std::endl;
//           if (op_char == '+') {
//             NodePtr.reset(new ast::AddExpr(
//               move(num_expr), move(last_ArithExpr)));
//           } else {
//             // division expression
//             NodePtr.reset(new ast::SubtractExpr(
//               move(num_expr), move(last_ArithExpr)));
//           }
//           Printer p;
//          NodePtr->Visit(&p);
//          std::string node_str = p.GetOutput();
//          std::cout << "VALUE OF NODEPTR IS: " << node_str << std::endl;
//
//           // update last_ArithExpr
//           last_ArithExpr = unique_cast<const ast::ArithmeticExpr>
//             (move(NodePtr));
//         }
//
//         // use the last op and the resulting ArithmeticExpr
//         // with v1 to make the retval
//
//         // get op
//         Value last_op = move(values.back());
//         std::string last_op_str = last_op.GetString();
//
//         auto first_unary_node = v1.GetNodeUnique();
//         auto first_unary_expr =
//           unique_cast<const ast::ArithmeticExpr>(move(first_unary_node));
//
//           std::cout << "OPERATOR IS: " << last_op_str[0] << std::endl;
//         if (last_op_str[0] == '+') {
//           NodePtr.reset(new ast::AddExpr(
//             move(first_unary_expr), move(last_ArithExpr)));
//         } else {
//           NodePtr.reset(new ast::SubtractExpr(
//             move(first_unary_expr), move(last_ArithExpr)));
//         }
//
//         Value v(std::move(NodePtr));
//         return v;
//
//         // v1 is the unary for the front of the rule
//         // values are all of the strings that are concatenated to the back
//       });  // End of And()
//     // Callback for And():
//     // [](Value multVal, Value starVal) {
//     //   // We know starVal has a string, because it's set in the star callback.
//     //   std::string op
//     // }
// }
//
//
// Parser Frontend::Multiply() {
// //   std::cout << "making multiply" << std::endl;
//   return And(
//     Unary(),
//     Star(
//       And(
//         Or(Literal('/'), Literal('*')),
//         Unary(),
//         [](Value v1, Value v2) {
//           // First value will be a literal, second value will be a node
//           // First value will be a literal, second value will be a node
//           auto v2Node = v2.GetNodeUnique();
//           Value ret(move(v2Node));
//           ret.SetString(v1.GetString());
//           return ret;
//         }),  // end of And()
//
//       // Callback for Star().
//       [](ValueVec values) {
//         // If there are no matches in the Star, return an empty value.
//         // values[0] is the single unary
//         mult_vec = std::move(values);
//         return Value();
//     }),
//
//       [](Value v1, Value v2) {
//         ValueVec values = std::move(mult_vec);
//         // each value has the node in the node and the operator in the string
//         std::cout << "in and callback " << values.size() << std::endl;
//
//         if (values.size() == 0) {
//           return v1;
//         } else if (values.size() == 1) {
//           auto last = std::move(values.back());
//           std::cout << "got last" << std::endl;
//           std::string last_str = last.GetString();
//           char op = last_str[0];
//           last_str = last_str.substr(1, last_str.size());
//           std::cout << "got last str: " << last_str << std::endl;
//           std::cout << "op is: " <<  op << std::endl;
//
//           // parse the Unary string
//           Printer p1;
//           Printer p2;
//
//           auto val_node = last.GetNodeUnique();
//           std::cout << "got val node" << std::endl;
//           val_node->Visit(&p1);
//           std::string val_str = p1.GetOutput();
//           std::cout << "val_str output: " << val_str << std::endl;
//           auto ValArithExpr =
//               unique_cast<const ast::ArithmeticExpr>(move(val_node));
//           auto v1_node = v1.GetNodeUnique();
//           v1_node->Visit(&p2);
//           std::string v1_str = p2.GetOutput();
//           std::cout << "v1_str is: " << v1_str << std::endl;
//           auto v1_ArithExpr =
//               unique_cast<const ast::ArithmeticExpr>(move(v1_node));
//
//           // val hows the value of the unary
//           // make expression
//           unique_ptr<ast::AstNode> newNodePtr;
//           if (op == '*') {
//             newNodePtr.reset(new ast::MultiplyExpr(
//               move(v1_ArithExpr),
//               move(ValArithExpr)));
//           } else {
//             // division expression
//             newNodePtr.reset(new ast::DivideExpr(
//               move(v1_ArithExpr),
//               move(ValArithExpr)));
//           }
//           Value v(std::move(newNodePtr));
//           return v;
//         }
//
//         std::cout << "past if statements" << std::endl;
//         // if it gets down here than size > 1
//
//         auto last = std::move(values.back());
//
//         unique_ptr<ast::AstNode> NodePtr;
//
//         auto last_node = last.GetNodeUnique();
//         auto last_ArithExpr =
//           unique_cast<const ast::ArithmeticExpr>(move(last_node));
//
//
//         while (values.size() > 1) {
//           // last element has the operator
//           // second to last element is the number
//           // Concatenate with last_ArithExpr
//           std::cout << "in while loop" << std::endl;
//           // Printer print;
//           // last_ArithExpr->Visit(&print);
//           // std::string print_str = print.GetOutput();
//           // std::cout << print_str << std::endl;
//
//           last = std::move(values.back());
//           values.pop_back();
//           // get op
//           std::string op_str = last.GetString();
//           std::cout << "operation string is: " << op_str << std::endl;
//           char op_char = op_str[0];
//
//           // get number
//           auto left_num_val = std::move(values.back());
//           std::cout << "got left_num_val" << std::endl;
//
//           auto number_node = left_num_val.GetNodeUnique();
//           auto num_expr =
//               unique_cast<const ast::ArithmeticExpr>(move(number_node));
//
//           std::cout << "OPERATOR IS: " << op_char << std::endl;
//           if (op_char == '*') {
//             NodePtr.reset(new ast::MultiplyExpr(
//               move(num_expr), move(last_ArithExpr)));
//           } else {
//             // division expression
//             NodePtr.reset(new ast::DivideExpr(
//               move(num_expr), move(last_ArithExpr)));
//           }
//           Printer p;
//          NodePtr->Visit(&p);
//          std::string node_str = p.GetOutput();
//
//           // update last_ArithExpr
//           last_ArithExpr = unique_cast<const ast::ArithmeticExpr>
//             (move(NodePtr));
//         }
//
//         // use the last op and the resulting ArithmeticExpr
//         // with v1 to make the retval
//
//         // get op
//         Value last_op = move(values.back());
//         std::string last_op_str = last_op.GetString();
//
//         auto first_unary_node = v1.GetNodeUnique();
//         auto first_unary_expr =
//           unique_cast<const ast::ArithmeticExpr>(move(first_unary_node));
//
//           std::cout << "OPERATOR IS: " << last_op_str[0] << std::endl;
//         if (last_op_str[0] == '*') {
//           NodePtr.reset(new ast::MultiplyExpr(
//             move(first_unary_expr), move(last_ArithExpr)));
//         } else {
//           NodePtr.reset(new ast::DivideExpr(
//             move(first_unary_expr), move(last_ArithExpr)));
//         }
//
//         Value v(std::move(NodePtr));
//         return v;
//
//         // v1 is the unary for the front of the rule
//         // values are all of the strings that are concatenated to the back
//       });  // End of Star()
// }
//
// Parser Frontend::Unary() {
//   // std::cout << "making unary" << std::endl;
//   return And(Star(Literal('-'),
//     [](ValueVec values) {
//       if (values.size() == 0) {
//         return Value("+");
//       }
//       int counter = values.size();
//       // counter tells us how many - signs there are
//       if (counter % 2 == 0) {
//         // there is an even number of negative signs
//         // return an add expression (?)
//         Value ret("+");
//         return ret;
//       } else {
//         // there is an odd number of negative signs
//         // should be a negative number in the end
//         Value ret("-");
//         return ret;
//       }
//     }
// ), Lazy(&Frontend::Primary()),
//   [](Value v1, Value v2) {
//     // And callback
//     // v1 should be '-' or '+' depending on the output of star
//     // get value
//     std::string v1_str = v1.GetString();
//     auto v2_ptr = v2.GetNodeUnique();
//
//     auto v2_int_expr = unique_cast
//       <ast::IntegerExpr, ast::AstNode>(move(v2_ptr));
//
//     // make Zero Int value
//     auto parse_zero = Int();
//     State state("0");
//     auto result = parse_zero(state);
//     Value zero = result.value();
//     // result should be a Value
//     auto zero_node = zero.GetNodeUnique();
//     auto ZeroArithExpr =
//         unique_cast<const ast::IntegerExpr>(move(zero_node));
//
//     auto v2_ArithExpr =
//         unique_cast<const ast::ArithmeticExpr>(move(v2_ptr));
//
//     unique_ptr<ast::AstNode> newNodePtr;
//
//     if (v1_str.at(0) == '+') {
//       // make an add expression
//       newNodePtr.reset(new ast::IntegerExpr(
//         move(v2_int_expr->value())));
//     } else {
//       // make a sub expression
//       newNodePtr.reset(new ast::SubtractExpr(
//         move(ZeroArithExpr),
//         move(v2_int_expr)));
//     }
//
//     Value v(std::move(newNodePtr));
//     return v;
//   }
// );
// }
//
//
// // Creates a Program
// Parser Frontend::Program() {
//   // std::cout << "making program" << std::endl;
//   return And(
//   Star(Lazy(&Frontend::Assign),
//   // Callback for Star().
//   [](ValueVec values) {
//     // If there are no matches in the Star, return an empty value.
//     if (values.size() == 0) {
//       return Value();
//     }
//     // As long as there are multiple matches, coalesce them into 1.
//     std::vector<std::unique_ptr<const ast::Assignment>> assignments;
//     while (values.size() > 1) {
//       // Get the current assignment
//       std::string op = values.back().GetString();
//       auto curr = values.back().GetNodeUnique();
//       auto currAssignment =
//         unique_cast<const ast::Assignment>(move(curr));
//
//         // push to the vector
//       assignments.push_back(move(currAssignment));
//
//       // Replace the last element with newNodePtr
//       values.pop_back();
//     }
//     // If there is 1 match, return it and the result of the And() (casted).
//     if (values.size() == 1) {
//       // This Value is an ArithmeticExp
//       std::string exp = values[0].GetString();
//       auto v = values[0].GetNodeUnique();
//       auto v2 = unique_cast<ast::ArithmeticExpr, ast::AstNode>(move(v));
//
//       auto ProgExpression = new ast::Program(move(assignments), move(v2));
//       auto expression = make_unique<ast::Program>(move(*ProgExpression));
//       Value ret(std::move(expression));
//       ret.SetString(exp);
//       return ret;
//     }
//     throw std::logic_error("Couldn't coalesce values into 1 expression");
//   }), Lazy(&Frontend::Expression));
// }
//
// Parser Frontend::Primary() {
//   // std::cout << "making primary" << std::endl;
//   return Or(
//       Int(),
//       Or(
//           Variable(),
//           And(Literal('('),
//                 And(Lazy(&Frontend::Expression),  Literal(')'),
//                 [] (Value v1, Value v2) {
//                   Printer p1;
//                   auto v1_node = v1.GetNodeUnique();
//                   v1_node->Visit(&p1);
//                   std::cout << "v1_node output: "
//                     << p1.GetOutput() << std::endl;
//                   return v1;
//                 }))));
// }

// A -> '-'A | Int()





Parser Frontend::Lazy(std::function<Result(State)> &function) {
  // takes a pointer to a parser function
  // returns a parser which, when called, calls the function pointer
  return [&](State state) -> Result{
    // std::cout << "lazy is running" << std::endl;
    auto result = function(state);

    // auto result = parse(state);
    // auto res_val = result.value();
    // auto res_node = res_val.GetNodeUnique();
    // Printer test_print;
    // res_node->Visit(&test_print);
    // std::cout << "res_node is: " << test_print.GetOutput() << std::endl;
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

// Node Frontend::stringToAst(std::string s) {
//   State state(s);
//   // auto parse = A(state);
//   // auto result = parse(state);
//   // std::unique_ptr<ast::AstNode> n(new ast::IntegerExpr(1));
//   // std::unique_ptr<ast::IntegerExpr> p = unique_cast<std::unique_ptr
//   // <ast::AstNode>, std::unique_ptr<ast::IntegerExpr>> (n);
//
//   // std::unique_ptr<ast::AstNode> a(new ast::IntegerExpr(1));
//   // std::unique_ptr<ast::IntegerExpr> b = unique_cast<ast::IntegerExpr>
//   // (std::move(a));
//
//   // auto ptr = result.value().GetNodePointer();
//
//
//   auto val = parse.value();
//   return val.GetNodeUnique();
// }

}  // namespace Parse
}  // namespace frontend
}  // namespace cs160
