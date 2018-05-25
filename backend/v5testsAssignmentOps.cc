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
using cs160::backend::Label;
using cs160::backend::Constant;
using cs160::backend::Variable;


using cs160::make_unique;
using cs160::backend::AsmProgram;


TEST(Assignment, OfVariable) {
  FunctionDef::Block function_defs;
  Statement::Block statements;
  statements.push_back(std::move(make_unique<const AssignmentFromArithExp>(
      make_unique<const VariableExpr>("a"),
      make_unique<const IntegerExpr>(12))));

  auto ae = make_unique<const AddExpr>(
    make_unique<const IntegerExpr>(12),
    make_unique<const IntegerExpr>(30));

  auto ast = make_unique<const Program>(std::move(function_defs),
  std::move(statements), std::move(ae));

  IrGenVisitor irGen;
  ast->Visit(&irGen);
  AsmProgram testasm;
  testasm.IrToAsm(&irGen);


  std::ofstream test_output_file;
  test_output_file.open("testfile.s");
  test_output_file << testasm.GetASMString();
  test_output_file.close();
  // std::cout << testasm.GetASMString();
  system("gcc testfile.s && ./a.out > test_output.txt");

  std::ifstream output_file;
  output_file.open("test_output.txt");
  std::string output;
  output_file >> output;
  // std::cout << output;
  output_file.close();
  system("rm testfile.s test_output.txt");

  EXPECT_EQ("42", output);
}

TEST(Assignment, OfDereference) {
  FunctionDef::Block function_defs;
  Statement::Block statements;
  statements.push_back(std::move(make_unique<const AssignmentFromArithExp>(
      make_unique<const VariableExpr>("a"),
      make_unique<const IntegerExpr>(12))));

  statements.push_back(std::move(make_unique<const AssignmentFromNewTuple>(
    make_unique<const VariableExpr>("b"),
    make_unique<const IntegerExpr>(3))));

  statements.push_back(std::move(make_unique<const AssignmentFromArithExp>(
    std::move(make_unique<const Dereference>(
      make_unique<const VariableExpr>("b"),
      make_unique<const IntegerExpr>(2))),
    make_unique<const IntegerExpr>(5))));

  auto ae = make_unique<const AddExpr>(
    make_unique<const VariableExpr>("a"),
    make_unique<const IntegerExpr>(30));

  auto ast = make_unique<const Program>(std::move(function_defs),
  std::move(statements), std::move(ae));

  IrGenVisitor irGen;
  ast->Visit(&irGen);
  AsmProgram testasm;
  testasm.IrToAsm(&irGen);
  // irGen.PrintIR();

  std::ofstream test_output_file;
  test_output_file.open("testfile.s");
  test_output_file << testasm.GetASMString();
  test_output_file.close();
  // std::cout << testasm.GetASMString();
  system("gcc testfile.s && ./a.out > test_output.txt");

  std::ifstream output_file;
  output_file.open("test_output.txt");
  std::string output;
  output_file >> output;
  // std::cout << output;
  output_file.close();
  system("rm testfile.s test_output.txt");

  EXPECT_EQ("42", output);
}

TEST(Access, OfDereference) {
  FunctionDef::Block function_defs;
  Statement::Block statements;

  statements.push_back(std::move(make_unique<const AssignmentFromNewTuple>(
    make_unique<const VariableExpr>("b"),
    make_unique<const IntegerExpr>(3))));

  statements.push_back(std::move(make_unique<const AssignmentFromArithExp>(
    std::move(make_unique<const Dereference>(
      make_unique<const VariableExpr>("b"),
      make_unique<const IntegerExpr>(2))),
    make_unique<const IntegerExpr>(30))));

  auto ae = make_unique<const AddExpr>(
    make_unique<const IntegerExpr>(12),
    make_unique<const Dereference>(
      make_unique<const VariableExpr>("b"),
      make_unique<const IntegerExpr>(2)));

  auto ast = make_unique<const Program>(std::move(function_defs),
  std::move(statements), std::move(ae));

  IrGenVisitor irGen;
  ast->Visit(&irGen);
  AsmProgram testasm;
  testasm.IrToAsm(&irGen);
  // irGen.PrintIR();

  std::ofstream test_output_file;
  test_output_file.open("testfile.s");
  test_output_file << testasm.GetASMString();
  test_output_file.close();
  // std::cout << testasm.GetASMString();
  system("gcc testfile.s && ./a.out > test_output.txt");

  std::ifstream output_file;
  output_file.open("test_output.txt");
  std::string output;
  output_file >> output;
  // std::cout << output;
  output_file.close();
  system("rm testfile.s test_output.txt");

  EXPECT_EQ("42", output);
}

// TEST(Create, Function) {
//   Statement::Block foo_statements;
//   foo_statements.push_back(std::move(make_unique<const AssignmentFromArithExp>(
//     make_unique<const VariableExpr>("local_b"),
//     make_unique<const AddExpr>(
//       make_unique<const VariableExpr>("param_a"),
//       make_unique<const IntegerExpr>(5)))));
//
//   auto foo_retval = make_unique<const AddExpr>(
//     make_unique<const VariableExpr>("local_b"),
//     make_unique<const IntegerExpr>(5));
//
//   auto foo_params = std::vector<std::unique_ptr<const VariableExpr>>();
//   foo_params.push_back(std::move(make_unique<const VariableExpr>("param_a")));
//
//   auto foo_def = make_unique<const FunctionDef>(
//     "foo", std::move(foo_params),
//     std::move(foo_statements),
//     std::move(foo_retval));
//
//   FunctionDef::Block function_defs;
//   function_defs.push_back(std::move(foo_def));
//   // foo(a)
//       // b = a + 5;
//       // return b + 5;
//   Statement::Block statements;
//   statements.push_back(std::move(make_unique<const AssignmentFromArithExp>(
//       make_unique<const VariableExpr>("a"),
//       make_unique<const IntegerExpr>(12))));
//
//   auto ae = make_unique<const AddExpr>(
//     make_unique<const  VariableExpr>("a"),
//     make_unique<const IntegerExpr>(30));
//
//   auto ast = make_unique<const Program>(std::move(function_defs),
//   std::move(statements), std::move(ae));
//
//   IrGenVisitor irGen;
//   ast->Visit(&irGen);
//   AsmProgram testasm;
//   testasm.IrToAsm(&irGen);
//
//
//   std::ofstream test_output_file;
//   test_output_file.open("testfile.s");
//   test_output_file << testasm.GetASMString();
//   test_output_file.close();
//   std::cout << testasm.GetASMString();
//   system("gcc testfile.s && ./a.out > test_output.txt");
//
//   std::ifstream output_file;
//   output_file.open("test_output.txt");
//   std::string output;
//   output_file >> output;
//   // std::cout << output;
//   output_file.close();
//   system("rm testfile.s test_output.txt");
//
//   EXPECT_EQ("42", output);
// }

// TEST(Call, Function) {
//   Statement::Block foo_statements;
//   foo_statements.push_back(std::move(make_unique<const AssignmentFromArithExp>(
//     make_unique<const VariableExpr>("local_b"),
//     make_unique<const AddExpr>(
//       make_unique<const VariableExpr>("param_a"),
//       make_unique<const IntegerExpr>(5)))));
//
//   auto foo_retval = make_unique<const AddExpr>(
//     make_unique<const VariableExpr>("local_b"),
//     make_unique<const IntegerExpr>(5));
//
//   auto foo_params = std::vector<std::unique_ptr<const VariableExpr>>();
//   foo_params.push_back(std::move(make_unique<const VariableExpr>("param_a")));
//
//   auto foo_def = make_unique<const FunctionDef>(
//     "foo", std::move(foo_params),
//     std::move(foo_statements),
//     std::move(foo_retval));
//
//   FunctionDef::Block function_defs;
//   function_defs.push_back(std::move(foo_def));
//   // foo(a)
//       // b = a + 5;
//       // return b + 5;
//   Statement::Block statements;
//   statements.push_back(std::move(make_unique<const AssignmentFromArithExp>(
//       make_unique<const VariableExpr>("a"),
//       make_unique<const IntegerExpr>(12))));
//
//   auto arguments = std::vector<std::unique_ptr<const ArithmeticExpr>>();
//   arguments.push_back(std::move(make_unique<const IntegerExpr>(12)));
//
//   statements.push_back(std::move(make_unique<const FunctionCall>(
//     make_unique<const VariableExpr>("foo_retval"),
//     "foo",
//     std::move(arguments))));
//
//   auto ae = make_unique<const AddExpr>(
//     make_unique<const VariableExpr>("foo_retval"),
//     make_unique<const IntegerExpr>(20));
//
//   auto ast = make_unique<const Program>(std::move(function_defs),
//   std::move(statements), std::move(ae));
//
//   IrGenVisitor irGen;
//   ast->Visit(&irGen);
//   // irGen.PrintIR();
//   AsmProgram testasm;
//   testasm.IrToAsm(&irGen);
//
//
//   std::ofstream test_output_file;
//   test_output_file.open("testfile.s");
//   test_output_file << testasm.GetASMString();
//   test_output_file.close();
//   // std::cout << testasm.GetASMString();
//   system("gcc testfile.s && ./a.out > test_output.txt");
//
//   std::ifstream output_file;
//   output_file.open("test_output.txt");
//   std::string output;
//   output_file >> output;
//   // std::cout << output;
//   output_file.close();
//   system("rm testfile.s test_output.txt");
//
//   EXPECT_EQ("42", output);
// }
//
// TEST(Call, FunctionTwice) {
//   Statement::Block foo_statements;
//   foo_statements.push_back(std::move(make_unique<const AssignmentFromArithExp>(
//     make_unique<const VariableExpr>("local_b"),
//     make_unique<const AddExpr>(
//       make_unique<const VariableExpr>("param_a"),
//       make_unique<const IntegerExpr>(5)))));
//
//   auto foo_retval = make_unique<const AddExpr>(
//     make_unique<const VariableExpr>("local_b"),
//     make_unique<const IntegerExpr>(5));
//
//   auto foo_params = std::vector<std::unique_ptr<const VariableExpr>>();
//   foo_params.push_back(std::move(make_unique<const VariableExpr>("param_a")));
//
//   auto foo_def = make_unique<const FunctionDef>(
//     "foo", std::move(foo_params),
//     std::move(foo_statements),
//     std::move(foo_retval));
//
//   FunctionDef::Block function_defs;
//   function_defs.push_back(std::move(foo_def));
//   // foo(a)
//       // b = a + 5;
//       // return b + 5;
//   Statement::Block statements;
//   statements.push_back(std::move(make_unique<const AssignmentFromArithExp>(
//       make_unique<const VariableExpr>("a"),
//       make_unique<const IntegerExpr>(12))));
//   statements.push_back(std::move(make_unique<const AssignmentFromArithExp>(
//       make_unique<const VariableExpr>("B"),
//       make_unique<const IntegerExpr>(12))));
//
//   auto arguments = std::vector<std::unique_ptr<const ArithmeticExpr>>();
//   arguments.push_back(std::move(make_unique<const IntegerExpr>(12)));
//
//   statements.push_back(std::move(make_unique<const FunctionCall>(
//     make_unique<const VariableExpr>("foo_retval"),
//     "foo",
//     std::move(arguments))));
//
//   auto arguments2 = std::vector<std::unique_ptr<const ArithmeticExpr>>();
//   arguments2.push_back(std::move(make_unique<const IntegerExpr>(22)));
//
//   statements.push_back(std::move(make_unique<const FunctionCall>(
//     make_unique<const VariableExpr>("foo_retval"),
//     "foo",
//     std::move(arguments2))));
//
//   auto ae = make_unique<const AddExpr>(
//     make_unique<const VariableExpr>("foo_retval"),
//     make_unique<const IntegerExpr>(20));
//
//   auto ast = make_unique<const Program>(std::move(function_defs),
//   std::move(statements), std::move(ae));
//
//   IrGenVisitor irGen;
//   ast->Visit(&irGen);
//   // irGen.PrintIR();
//   AsmProgram testasm;
//   testasm.IrToAsm(&irGen);
//
//
//   std::ofstream test_output_file;
//   test_output_file.open("testfile.s");
//   test_output_file << testasm.GetASMString();
//   test_output_file.close();
//   // std::cout << testasm.GetASMString();
//   system("gcc testfile.s && ./a.out > test_output.txt");
//
//   std::ifstream output_file;
//   output_file.open("test_output.txt");
//   std::string output;
//   output_file >> output;
//   // std::cout << output;
//   output_file.close();
//   system("rm testfile.s test_output.txt");
//
//   EXPECT_EQ("52", output);
// }
