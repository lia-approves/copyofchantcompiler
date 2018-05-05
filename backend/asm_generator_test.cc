// Copyright msg for cpplint
#include <iostream>
#include <fstream>
#include <string>
#include "abstract_syntax/abstract_syntax.h"
#include "backend/ir_v1.h"
#include "gtest/gtest.h"
#include "utility/memory.h"
#include "backend/asm_generator_v1.h"
#include "backend/lowerer_v1.h"


using cs160::abstract_syntax::version_1::IntegerExpr;
using cs160::abstract_syntax::version_1::AddExpr;
using cs160::abstract_syntax::version_1::SubtractExpr;
using cs160::abstract_syntax::version_1::MultiplyExpr;
using cs160::abstract_syntax::version_1::DivideExpr;

using cs160::backend::Instruction;
using cs160::backend::Operand;
using cs160::backend::Register;
using cs160::backend::Constant;
using cs160::backend::StatementNode;
using cs160::backend::AsmProgram;
using cs160::backend::IrGenVisitor;

using cs160::make_unique;

TEST(IRv1, Add) {
  StatementNode *expr = new StatementNode(
    new Register(3),
    new Instruction(Instruction::kAdd),
    new Constant(3),
    new Constant(2),
    nullptr);

  AsmProgram testasm;
  testasm.IRv1(expr);

  std::ofstream test_output_file;
  test_output_file.open("testfile.s");
  test_output_file << testasm.GetASMString();
  test_output_file.close();
  system("gcc testfile.s && ./a.out > test_output.txt");

  std::ifstream output_file;
  output_file.open("test_output.txt");
  std::string output;
  output_file >> output;
  output_file.close();
  system("rm testfile.s test_output.txt");

  EXPECT_EQ("5", output);
}

TEST(IRv1, Subtract) {
  StatementNode *expr = new StatementNode(
    new Register(3),
    new Instruction(Instruction::kSubtract),
    new Constant(3),
    new Constant(2),
    nullptr);

  AsmProgram testasm;
  testasm.IRv1(expr);

  std::ofstream test_output_file;
  test_output_file.open("testfile.s");
  test_output_file << testasm.GetASMString();
  test_output_file.close();
  system("gcc testfile.s && ./a.out > test_output.txt");

  std::ifstream output_file;
  output_file.open("test_output.txt");
  std::string output;
  output_file >> output;
  output_file.close();
  system("rm testfile.s test_output.txt");

  EXPECT_EQ("1", output);
}

TEST(IRv1, Multiply) {
  StatementNode *expr = new StatementNode(
    new Register(3),
    new Instruction(Instruction::kMultiply),
    new Constant(3),
    new Constant(2),
    nullptr);

  AsmProgram testasm;
  testasm.IRv1(expr);

  std::ofstream test_output_file;
  test_output_file.open("testfile.s");
  test_output_file << testasm.GetASMString();
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

TEST(IRv1, Divide) {
  StatementNode *expr = new StatementNode(
    new Register(3),
    new Instruction(Instruction::kDivide),
    new Constant(30),
    new Constant(5),
    nullptr);

  AsmProgram testasm;
  testasm.IRv1(expr);

  std::ofstream test_output_file;
  test_output_file.open("testfile.s");
  test_output_file << testasm.GetASMString();
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

TEST(IRv1, Complex) {
  // ((3+2) * 2) - 4 = 6
  StatementNode *expr3 = new StatementNode(
    new Register(3),
    new Instruction(Instruction::kSubtract),
    new Register(3),
    new Constant(4),
    nullptr);
  StatementNode *expr2 = new StatementNode(
    new Register(3),
    new Instruction(Instruction::kMultiply),
    new Constant(2),
    new Register(2),
    expr3);
  StatementNode *expr1 = new StatementNode(
    new Register(3),
    new Instruction(Instruction::kAdd),
    new Constant(3),
    new Constant(2),
    expr2);

  AsmProgram testasm;
  testasm.IRv1(expr1);

  std::ofstream test_output_file;
  test_output_file.open("testfile.s");
  test_output_file << testasm.GetASMString();
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

TEST(IRv2, AssignVariables) {
  // a = 2;
  // b = 3;
  // a + b;


  StatementNode *expr3 = new StatementNode(
    new Register(3),
    new Instruction(Instruction::kSubtract),
    new Register(3),
    new Constant(4),
    nullptr);
  StatementNode *expr2 = new StatementNode(
    new Register(3),
    new Instruction(Instruction::kMultiply),
    new Constant(2),
    new Register(2),
    expr3);
  StatementNode *expr1 = new StatementNode(
    new Register(3),
    new Instruction(Instruction::kAdd),
    new Constant(3),
    new Constant(2),
    expr2);

  AsmProgram testasm;
  testasm.IRv1(expr1);

  std::ofstream test_output_file;
  test_output_file.open("testfile.s");
  test_output_file << testasm.GetASMString();
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
