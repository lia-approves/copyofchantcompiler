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


TEST(AE, CanAdd) {
  FunctionDef::Block function_defs;
  Statement::Block statements;
  auto ae = make_unique<const AddExpr>(
    make_unique<const IntegerExpr>(12),
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
TEST(AE, CanSubtract) {
  FunctionDef::Block function_defs;
  Statement::Block statements;
  auto ae = make_unique<const SubtractExpr>(
    make_unique<const IntegerExpr>(52),
    make_unique<const IntegerExpr>(10));

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
TEST(AE, CanMultiply) {
  FunctionDef::Block function_defs;
  Statement::Block statements;
  auto ae = make_unique<const MultiplyExpr>(
    make_unique<const IntegerExpr>(7),
    make_unique<const IntegerExpr>(6));

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
TEST(AE, CanDivide) {
  FunctionDef::Block function_defs;
  Statement::Block statements;
  auto ae = make_unique<const DivideExpr>(
    make_unique<const IntegerExpr>(84),
    make_unique<const IntegerExpr>(2));

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
