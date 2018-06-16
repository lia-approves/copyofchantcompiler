// Copyright msg for cpplint
#include <iostream>
#include <fstream>
#include <sstream>

#include <string>
#include "abstract_syntax/abstract_syntax.h"
#include "backend/ir_v5.h"
#include "gtest/gtest.h"
#include "utility/memory.h"
#include "backend/asm_generator_v5.h"
#include "backend/lowerer_v5.h"


using cs160::abstract_syntax::version_5::AstVisitor;
using cs160::abstract_syntax::version_5::ArithmeticExpr;
using cs160::abstract_syntax::version_5::Assignable;
using cs160::abstract_syntax::version_5::AddExpr;
using cs160::abstract_syntax::version_5::SubtractExpr;
using cs160::abstract_syntax::version_5::MultiplyExpr;
using cs160::abstract_syntax::version_5::DivideExpr;
using cs160::abstract_syntax::version_5::IntegerExpr;
using cs160::abstract_syntax::version_5::VariableExpr;
using cs160::abstract_syntax::version_5::Dereference;
using cs160::abstract_syntax::version_5::LessThanExpr;
using cs160::abstract_syntax::version_5::LessThanEqualToExpr;
using cs160::abstract_syntax::version_5::GreaterThanExpr;
using cs160::abstract_syntax::version_5::GreaterThanEqualToExpr;
using cs160::abstract_syntax::version_5::EqualToExpr;
using cs160::abstract_syntax::version_5::LogicalAndExpr;
using cs160::abstract_syntax::version_5::LogicalOrExpr;
using cs160::abstract_syntax::version_5::LogicalNotExpr;
using cs160::abstract_syntax::version_5::Statement;
using cs160::abstract_syntax::version_5::AssignmentFromArithExp;
using cs160::abstract_syntax::version_5::AssignmentFromNewTuple;
using cs160::abstract_syntax::version_5::Conditional;
using cs160::abstract_syntax::version_5::Loop;
using cs160::abstract_syntax::version_5::FunctionCall;
using cs160::abstract_syntax::version_5::FunctionDef;
using cs160::abstract_syntax::version_5::Program;

using cs160::backend::Operand;
using cs160::backend::Register;
using cs160::backend::StatementNode;
using cs160::backend::AsmProgram;
using cs160::backend::IrGenVisitor;
using cs160::backend::Text;
using cs160::backend::Label;
using cs160::backend::Constant;
using cs160::backend::Variable;


using cs160::make_unique;
using cs160::backend::AsmProgram;


TEST(Version4, IntegrationTest) {
  Statement::Block foo_statements;
  foo_statements.push_back(std::move(make_unique<const AssignmentFromArithExp>(
    make_unique<const VariableExpr>("a"),
    make_unique<const IntegerExpr>(45))));
  foo_statements.push_back(std::move(make_unique<const AssignmentFromArithExp>(
    make_unique<const VariableExpr>("bob"),
    make_unique<const AddExpr>(
      make_unique<const VariableExpr>("bob"),
      make_unique<const IntegerExpr>(8)))));
  foo_statements.push_back(std::move(make_unique<const AssignmentFromArithExp>(
    make_unique<const VariableExpr>("h"),
    make_unique<const IntegerExpr>(45))));
  foo_statements.push_back(std::move(make_unique<const AssignmentFromArithExp>(
    make_unique<const VariableExpr>("j"),
    make_unique<const IntegerExpr>(45))));
  foo_statements.push_back(std::move(make_unique<const AssignmentFromArithExp>(
    make_unique<const VariableExpr>("mike"),
    make_unique<const IntegerExpr>(45))));
  foo_statements.push_back(std::move(make_unique<const AssignmentFromArithExp>(
    make_unique<const VariableExpr>("ab"),
    make_unique<const IntegerExpr>(45))));
  auto foo_retval = make_unique<const AddExpr>(
    make_unique<const VariableExpr>("bob"),
    make_unique<const IntegerExpr>(5));
  auto foo_params = std::vector<std::unique_ptr<const VariableExpr>>();
  foo_params.push_back(std::move(make_unique<const VariableExpr>("bob")));
  foo_params.push_back(std::move(make_unique<const VariableExpr>("jim")));
  foo_params.push_back(std::move(make_unique<const VariableExpr>("mike")));
  auto foo_def = make_unique<const FunctionDef>(
    "foo", std::move(foo_params),
    std::move(foo_statements),
    std::move(foo_retval));
  FunctionDef::Block function_defs;
  function_defs.push_back(std::move(foo_def));
  auto arguments = std::vector<std::unique_ptr<const ArithmeticExpr>>();
  arguments.push_back(std::move(make_unique<const IntegerExpr>(17)));
  arguments.push_back(std::move(make_unique<const IntegerExpr>(17)));
  arguments.push_back(std::move(make_unique<const IntegerExpr>(17)));
  Statement::Block statements;
  statements.push_back(std::move(make_unique<const AssignmentFromArithExp>(
    make_unique<const VariableExpr>("y"),
    make_unique<const IntegerExpr>(9))));
  statements.push_back(std::move(make_unique<const AssignmentFromArithExp>(
    make_unique<const VariableExpr>("x"),
    make_unique<const IntegerExpr>(1))));
  statements.push_back(std::move(make_unique<const FunctionCall>(
    make_unique<const VariableExpr>("foo_retval"),
    "foo",
    std::move(arguments))));
  auto ae = make_unique<const AddExpr>(
    make_unique<const IntegerExpr>(12),
    make_unique<const VariableExpr>("foo_retval"));

  auto ast = make_unique<const Program>(std::move(function_defs),
  std::move(statements), std::move(ae));
  /*
  function definition:
  def foo(bob,jim,mike) {
  a=45
  bob = bob + 8
  h=45
  j=45
  mike=45
  ab=45
  return bob + 5
  }

  //main function:
  y=9
  x=1
  foo_retval=foo(17,17,17)
  12+foo_retval
  */

  IrGenVisitor irGen;
  ast->Visit(&irGen);
  AsmProgram testasm;
  testasm.IrToAsm(&irGen);

  std::ofstream test_output_file;
  test_output_file.open("testfile.s");
  test_output_file << testasm.GetASMString();
  std::cout << testasm.GetASMString();
  system("gcc testfile.s && ./a.out > test_output.txt");

  std::ifstream output_file;
  output_file.open("test_output.txt");
  std::string output;
  output_file >> output;

  EXPECT_EQ("42", output);
}
//
// TEST(Version4, IntegrationTest2) {
//   Statement::Block foo_statements;
//   foo_statements.push_back(std::move(make_unique<const AssignmentFromArithExp>(
//     make_unique<const VariableExpr>("a"),
//     make_unique<const IntegerExpr>(45))));
//   foo_statements.push_back(std::move(make_unique<const AssignmentFromArithExp>(
//     make_unique<const VariableExpr>("bob"),
//     make_unique<const AddExpr>(
//       make_unique<const VariableExpr>("bob"),
//       make_unique<const IntegerExpr>(8)))));
//   foo_statements.push_back(std::move(make_unique<const AssignmentFromArithExp>(
//     make_unique<const VariableExpr>("h"),
//     make_unique<const IntegerExpr>(45))));
//   foo_statements.push_back(std::move(make_unique<const AssignmentFromArithExp>(
//     make_unique<const VariableExpr>("j"),
//     make_unique<const IntegerExpr>(45))));
//   foo_statements.push_back(std::move(make_unique<const AssignmentFromArithExp>(
//     make_unique<const VariableExpr>("mike"),
//     make_unique<const IntegerExpr>(45))));
//   foo_statements.push_back(std::move(make_unique<const AssignmentFromArithExp>(
//     make_unique<const VariableExpr>("ab"),
//     make_unique<const IntegerExpr>(45))));
//   auto foo_retval = make_unique<const AddExpr>(
//     make_unique<const VariableExpr>("bob"),
//     make_unique<const AddExpr>(
//       make_unique<const VariableExpr>("h"),
//       make_unique<const MultiplyExpr>(
//         make_unique<const VariableExpr>("jim"),
//         make_unique<const VariableExpr>("mike"))));
//   auto foo_params = std::vector<std::unique_ptr<const VariableExpr>>();
//   foo_params.push_back(std::move(make_unique<const VariableExpr>("bob")));
//   foo_params.push_back(std::move(make_unique<const VariableExpr>("jim")));
//   foo_params.push_back(std::move(make_unique<const VariableExpr>("mike")));
//
//   auto foo_def = make_unique<const FunctionDef>(
//     "foo", std::move(foo_params),
//     std::move(foo_statements),
//     std::move(foo_retval));
//
//   FunctionDef::Block function_defs;
//   function_defs.push_back(std::move(foo_def));
//   auto arguments = std::vector<std::unique_ptr<const ArithmeticExpr>>();
//   arguments.push_back(std::move(make_unique<const IntegerExpr>(17)));
//   arguments.push_back(std::move(make_unique<const IntegerExpr>(17)));
//   arguments.push_back(std::move(make_unique<const IntegerExpr>(17)));
//
//   Statement::Block statements;
//   statements.push_back(std::move(make_unique<const AssignmentFromArithExp>(
//     make_unique<const VariableExpr>("y"),
//     make_unique<const IntegerExpr>(9))));
//   statements.push_back(std::move(make_unique<const AssignmentFromArithExp>(
//     make_unique<const VariableExpr>("x"),
//     make_unique<const IntegerExpr>(1))));
//   statements.push_back(std::move(make_unique<const FunctionCall>(
//     make_unique<const VariableExpr>("foo_retval"),
//     "foo",
//     std::move(arguments))));
//
//   auto ae = make_unique<const AddExpr>(
//     make_unique<const IntegerExpr>(12),
//     make_unique<const VariableExpr>("foo_retval"));
//
//   auto ast = make_unique<const Program>(std::move(function_defs),
//     std::move(statements), std::move(ae));
//   /*    function definition:
//   def foo(bob,jim,mike) {
//   a=45
//   bob = bob + 8
//   h=45
//   j=45
//   mike=45
//   ab=45
//   return bob + h + jim*mike
//   }
//   //main function:
//   y=9
//   x=1
//   foo_retval=foo(17,17,17)
//   12+foo_retval
//   */
//
//   IrGenVisitor irGen;
//   ast->Visit(&irGen);
//   AsmProgram testasm;
//   testasm.IrToAsm(&irGen);
//
//   std::ofstream test_output_file;
//   test_output_file.open("testfile.s");
//   test_output_file << testasm.GetASMString();
//   system("gcc testfile.s && ./a.out > test_output.txt");
//
//   std::ifstream output_file;
//   output_file.open("test_output.txt");
//   std::string output;
//   output_file >> output;
//
//   EXPECT_EQ("847", output);
// }
//
// TEST(Version4, IntegrationTest3) {
//   Statement::Block foo_statements;
//
//   foo_statements.push_back(std::move(make_unique<const Conditional>(
//     make_unique<const LogicalOrExpr>(
//       make_unique<const LogicalAndExpr>(
//         make_unique<const LessThanExpr>(
//           make_unique<const VariableExpr>("bob"),
//           make_unique<const IntegerExpr>(100)),
//         make_unique<const GreaterThanExpr>(
//           make_unique<const VariableExpr>("bob"),
//           make_unique<const IntegerExpr>(0))),
//       make_unique<const LogicalAndExpr>(
//         make_unique<const LessThanEqualToExpr>(
//           make_unique<const VariableExpr>("bob"),
//           make_unique<const IntegerExpr>(100)),
//         make_unique<const GreaterThanEqualToExpr>(
//           make_unique<const VariableExpr>("bob"),
//           make_unique<const IntegerExpr>(0)))),
//     Statement::Block(), Statement::Block())));
//
//   Statement::Block loop_body;
//   loop_body.push_back(std::move(make_unique<const AssignmentFromArithExp>(
//     make_unique<const VariableExpr>("bob"),
//     make_unique<const SubtractExpr>(make_unique<const VariableExpr>("bob"),
//       make_unique<const IntegerExpr>(1)))));
//
//   foo_statements.push_back(std::move(make_unique<const Loop>(
//     make_unique<const LogicalNotExpr>(
//       make_unique<const EqualToExpr>(make_unique<const VariableExpr>("bob"),
//         make_unique<const IntegerExpr>(0))),
//     std::move(loop_body))));
//
//   auto foo_retval = make_unique<const AddExpr>(
//     make_unique<const SubtractExpr>(
//       make_unique<const DivideExpr>(make_unique<const IntegerExpr>(12),
//         make_unique<const IntegerExpr>(3)),
//       make_unique<const IntegerExpr>(4)),
//     make_unique<const MultiplyExpr>(make_unique<const IntegerExpr>(3),
//       make_unique<const IntegerExpr>(2)));
//
//   auto foo_params = std::vector<std::unique_ptr<const VariableExpr>>();
//   foo_params.push_back(std::move(make_unique<const VariableExpr>("bob")));
//
//   auto foo_def = make_unique<const FunctionDef>("foo", std::move(foo_params),
//     std::move(foo_statements),
//     std::move(foo_retval));
//
//   FunctionDef::Block function_defs;
//   function_defs.push_back(std::move(foo_def));
//
//   auto arguments = std::vector<std::unique_ptr<const ArithmeticExpr>>();
//   arguments.push_back(std::move(make_unique<const IntegerExpr>(42)));
//
//   Statement::Block statements;
//
//   statements.push_back(std::move(make_unique<const FunctionCall>(
//     make_unique<const VariableExpr>("foo_retval"), "foo",
//     std::move(arguments))));
//
//   auto ae = make_unique<const VariableExpr>("foo_retval");
//
//   auto ast = make_unique<const Program>(std::move(function_defs),
//     std::move(statements), std::move(ae));
//   /*
//   function definition:
//   def foo(bob,jim,mike) {
//   a=45
//   bob = bob + 8
//   h=45
//   j=45
//   mike=45
//   ab=45
//   return bob + 5
//   }
//
//   //main function:
//   y=9
//   x=1
//   foo_retval=foo(17,17,17)
//   12+foo_retval
//   */
//
//   IrGenVisitor irGen;
//   ast->Visit(&irGen);
//   AsmProgram testasm;
//   testasm.IrToAsm(&irGen);
//
//   std::ofstream test_output_file;
//   test_output_file.open("testfile.s");
//   test_output_file << testasm.GetASMString();
//   system("gcc testfile.s && ./a.out > test_output.txt");
//
//   std::ifstream output_file;
//   output_file.open("test_output.txt");
//   std::string output;
//   output_file >> output;
//
//   EXPECT_EQ("6", output);
// }
