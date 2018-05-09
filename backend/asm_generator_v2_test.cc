// Copyright msg for cpplint
#include <iostream>
#include <fstream>
#include <string>
#include "abstract_syntax/abstract_syntax.h"
#include "backend/ir_v3.h"
#include "gtest/gtest.h"
#include "utility/memory.h"
#include "backend/asm_generator_v3.h"
#include "backend/lowerer_v3.h"


using cs160::abstract_syntax::version_3::IntegerExpr;
using cs160::abstract_syntax::version_3::AddExpr;
using cs160::abstract_syntax::version_3::SubtractExpr;
using cs160::abstract_syntax::version_3::MultiplyExpr;
using cs160::abstract_syntax::version_3::DivideExpr;

using cs160::backend::Operator;
using cs160::backend::Operand;
using cs160::backend::Register;
using cs160::backend::Constant;
using cs160::backend::Variable;
using cs160::backend::Label;
using cs160::backend::StatementNode;
using cs160::backend::AsmProgram;
using cs160::backend::IrGenVisitor;

using cs160::make_unique;


TEST(IRv2, Assign1Variable) {
  // a = 2;
  // a * 3

auto a_var = new Variable("a");

  StatementNode *expr2 = new StatementNode(
    new Label(2),
    new Register(3),
    new Operator(Operator::kMultiply),
    a_var,
    new Constant(2),
    nullptr);
  StatementNode *expr1 = new StatementNode(
    new Label(1),
    a_var,
    new Operator(Operator::kAssign),
    new Constant(3),
    nullptr,
    expr2);

  AsmProgram testasm;
  testasm.IrToAsm(expr1);

  std::ofstream test_output_file;
  test_output_file.open("testfile.s");
  test_output_file << testasm.GetASMString();
  // std::cout << testasm.GetASMString();

  test_output_file.close();
  system("gcc testfile.s && ./a.out > test_output.txt");

  std::ifstream output_file;
  output_file.open("test_output.txt");
  std::string output;
  output_file >> output;
  output_file.close();
  system("rm testfile.s test_output.txt");

  EXPECT_EQ("6", output);
}


TEST(IRv2, Assign2Variables) {
  // a = 2;
  // b = 3;
  // a + b

auto a_var = new Variable("a");
auto b_var = new Variable("b");

  StatementNode *expr3 = new StatementNode(
    new Label(3),
    new Register(3),
    new Operator(Operator::kAdd),
    a_var,
    b_var,
    nullptr);
  StatementNode *expr2 = new StatementNode(
    new Label(2),
    b_var,
    new Operator(Operator::kAssign),
    new Constant(2),
    nullptr,
    expr3);
  StatementNode *expr1 = new StatementNode(
    new Label(1),
    a_var,
    new Operator(Operator::kAssign),
    new Constant(3),
    nullptr,
    expr2);

  AsmProgram testasm;
  testasm.IrToAsm(expr1);

  std::ofstream test_output_file;
  test_output_file.open("testfile.s");
  test_output_file << testasm.GetASMString();
  test_output_file.close();
  system("gcc testfile.s && ./a.out > test_output.txt");

  std::ifstream output_file;
  output_file.open("test_output.txt");
  std::string output;
  output_file >> output;
  // std::cout << output;
  output_file.close();
  system("rm testfile.s test_output.txt");

  EXPECT_EQ("5", output);
}
