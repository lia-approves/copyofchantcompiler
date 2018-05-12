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

// NOTE: These tests implicitly test goto since it is used

TEST(IRv3, IfLessThanTrue) {
  // a = 2;
  // if (a < 10)
  // b = 3;
  // else
  // b = 4;
  // a + b;

  // expected output is 5

auto a_var = new Variable("a");
auto b_var = new Variable("b");

  StatementNode *expr7 = new StatementNode(
    new Label(7),
    new Register(3),
    new Operator(Operator::kAdd),
    a_var,
    b_var,
    nullptr);
  StatementNode *expr6 = new StatementNode(
    new Label(6),
    b_var,
    new Operator(Operator::kAssign),
    new Constant(4),
    nullptr,
    expr7);
  StatementNode *expr5 = new StatementNode(
    new Label(5),
    new Label(7),
    new Operator(Operator::kGoto),
    nullptr,
    nullptr,
    expr6);
  StatementNode *expr4 = new StatementNode(
    new Label(4),
    b_var,
    new Operator(Operator::kAssign),
    new Constant(3),
    nullptr,
    expr5);
  StatementNode *expr3 = new StatementNode(
    new Label(3),
    new Label(6),
    new Operator(Operator::kGoto),
    nullptr,
    nullptr,
    expr4);
  StatementNode *expr2 = new StatementNode(
    new Label(2),
    new Label(4),
    new Operator(Operator::kLessThan),
    a_var,
    new Constant(10),
    expr3);
  StatementNode *expr1 = new StatementNode(
    new Label(1),
    a_var,
    new Operator(Operator::kAssign),
    new Constant(2),
    nullptr,
    expr2);

  AsmProgram testasm;
  testasm.IrToAsm(expr1);

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

  EXPECT_EQ("5", output);
  // EXPECT_EQ(0,0);
}

TEST(IRv3, IfLessThanFalse) {
  // a = 20;
  // if (a < 10)
  // b = 3;
  // else
  // b = 4;
  // a + b;

  // expected output is 24

auto a_var = new Variable("a");
auto b_var = new Variable("b");

  StatementNode *expr7 = new StatementNode(
    new Label(7),
    new Register(3),
    new Operator(Operator::kAdd),
    a_var,
    b_var,
    nullptr);
  StatementNode *expr6 = new StatementNode(
    new Label(6),
    b_var,
    new Operator(Operator::kAssign),
    new Constant(4),
    nullptr,
    expr7);
  StatementNode *expr5 = new StatementNode(
    new Label(5),
    new Label(7),
    new Operator(Operator::kGoto),
    nullptr,
    nullptr,
    expr6);
  StatementNode *expr4 = new StatementNode(
    new Label(4),
    b_var,
    new Operator(Operator::kAssign),
    new Constant(3),
    nullptr,
    expr5);
  StatementNode *expr3 = new StatementNode(
    new Label(3),
    new Label(6),
    new Operator(Operator::kGoto),
    nullptr,
    nullptr,
    expr4);
  StatementNode *expr2 = new StatementNode(
    new Label(2),
    new Label(4),
    new Operator(Operator::kLessThan),
    a_var,
    new Constant(10),
    expr3);
  StatementNode *expr1 = new StatementNode(
    new Label(1),
    a_var,
    new Operator(Operator::kAssign),
    new Constant(20),
    nullptr,
    expr2);

  AsmProgram testasm;
  testasm.IrToAsm(expr1);

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

  EXPECT_EQ("24", output);
  // EXPECT_EQ(0,0);
}


TEST(IRv3, IfEqualToTrue) {
  // a = 20;
  // if (a == 20)
  // b = 3;
  // else
  // b = 4;
  // a + b;

  // expected output is 23

auto a_var = new Variable("a");
auto b_var = new Variable("b");

  StatementNode *expr7 = new StatementNode(
    new Label(7),
    new Register(3),
    new Operator(Operator::kAdd),
    a_var,
    b_var,
    nullptr);
  StatementNode *expr6 = new StatementNode(
    new Label(6),
    b_var,
    new Operator(Operator::kAssign),
    new Constant(4),
    nullptr,
    expr7);
  StatementNode *expr5 = new StatementNode(
    new Label(5),
    new Label(7),
    new Operator(Operator::kGoto),
    nullptr,
    nullptr,
    expr6);
  StatementNode *expr4 = new StatementNode(
    new Label(4),
    b_var,
    new Operator(Operator::kAssign),
    new Constant(3),
    nullptr,
    expr5);
  StatementNode *expr3 = new StatementNode(
    new Label(3),
    new Label(6),
    new Operator(Operator::kGoto),
    nullptr,
    nullptr,
    expr4);
  StatementNode *expr2 = new StatementNode(
    new Label(2),
    new Label(4),
    new Operator(Operator::kEqualTo),
    a_var,
    new Constant(20),
    expr3);
  StatementNode *expr1 = new StatementNode(
    new Label(1),
    a_var,
    new Operator(Operator::kAssign),
    new Constant(20),
    nullptr,
    expr2);

  AsmProgram testasm;
  testasm.IrToAsm(expr1);

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

  EXPECT_EQ("23", output);
  // EXPECT_EQ(0,0);
}

TEST(IRv3, IfEqualToFalse) {
  // a = 20;
  // if (a == 2)
  // b = 3;
  // else
  // b = 4;
  // a + b;

  // expected output is 24

auto a_var = new Variable("a");
auto b_var = new Variable("b");

  StatementNode *expr7 = new StatementNode(
    new Label(7),
    new Register(3),
    new Operator(Operator::kAdd),
    a_var,
    b_var,
    nullptr);
  StatementNode *expr6 = new StatementNode(
    new Label(6),
    b_var,
    new Operator(Operator::kAssign),
    new Constant(4),
    nullptr,
    expr7);
  StatementNode *expr5 = new StatementNode(
    new Label(5),
    new Label(7),
    new Operator(Operator::kGoto),
    nullptr,
    nullptr,
    expr6);
  StatementNode *expr4 = new StatementNode(
    new Label(4),
    b_var,
    new Operator(Operator::kAssign),
    new Constant(3),
    nullptr,
    expr5);
  StatementNode *expr3 = new StatementNode(
    new Label(3),
    new Label(6),
    new Operator(Operator::kGoto),
    nullptr,
    nullptr,
    expr4);
  StatementNode *expr2 = new StatementNode(
    new Label(2),
    new Label(4),
    new Operator(Operator::kEqualTo),
    a_var,
    new Constant(2),
    expr3);
  StatementNode *expr1 = new StatementNode(
    new Label(1),
    a_var,
    new Operator(Operator::kAssign),
    new Constant(20),
    nullptr,
    expr2);

  AsmProgram testasm;
  testasm.IrToAsm(expr1);

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

  EXPECT_EQ("24", output);
  // EXPECT_EQ(0,0);
}

TEST(IRv3, IfGreaterThanTrue) {
  // a = 2;
  // if (a > 1)
  // b = 3;
  // else
  // b = 4;
  // a + b;

  // expected output is 5

auto a_var = new Variable("a");
auto b_var = new Variable("b");

  StatementNode *expr7 = new StatementNode(
    new Label(7),
    new Register(3),
    new Operator(Operator::kAdd),
    a_var,
    b_var,
    nullptr);
  StatementNode *expr6 = new StatementNode(
    new Label(6),
    b_var,
    new Operator(Operator::kAssign),
    new Constant(4),
    nullptr,
    expr7);
  StatementNode *expr5 = new StatementNode(
    new Label(5),
    new Label(7),
    new Operator(Operator::kGoto),
    nullptr,
    nullptr,
    expr6);
  StatementNode *expr4 = new StatementNode(
    new Label(4),
    b_var,
    new Operator(Operator::kAssign),
    new Constant(3),
    nullptr,
    expr5);
  StatementNode *expr3 = new StatementNode(
    new Label(3),
    new Label(6),
    new Operator(Operator::kGoto),
    nullptr,
    nullptr,
    expr4);
  StatementNode *expr2 = new StatementNode(
    new Label(2),
    new Label(4),
    new Operator(Operator::kGreaterThan),
    a_var,
    new Constant(1),
    expr3);
  StatementNode *expr1 = new StatementNode(
    new Label(1),
    a_var,
    new Operator(Operator::kAssign),
    new Constant(2),
    nullptr,
    expr2);

  AsmProgram testasm;
  testasm.IrToAsm(expr1);

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

  EXPECT_EQ("5", output);
  // EXPECT_EQ(0,0);
}


TEST(IRv3, IfGreaterThanFalse) {
  // a = 2;
  // if (a > 2)
  // b = 3;
  // else
  // b = 4;
  // a + b;

  // expected output is 6

auto a_var = new Variable("a");
auto b_var = new Variable("b");

  StatementNode *expr7 = new StatementNode(
    new Label(7),
    new Register(3),
    new Operator(Operator::kAdd),
    a_var,
    b_var,
    nullptr);
  StatementNode *expr6 = new StatementNode(
    new Label(6),
    b_var,
    new Operator(Operator::kAssign),
    new Constant(4),
    nullptr,
    expr7);
  StatementNode *expr5 = new StatementNode(
    new Label(5),
    new Label(7),
    new Operator(Operator::kGoto),
    nullptr,
    nullptr,
    expr6);
  StatementNode *expr4 = new StatementNode(
    new Label(4),
    b_var,
    new Operator(Operator::kAssign),
    new Constant(3),
    nullptr,
    expr5);
  StatementNode *expr3 = new StatementNode(
    new Label(3),
    new Label(6),
    new Operator(Operator::kGoto),
    nullptr,
    nullptr,
    expr4);
  StatementNode *expr2 = new StatementNode(
    new Label(2),
    new Label(4),
    new Operator(Operator::kGreaterThan),
    a_var,
    new Constant(2),
    expr3);
  StatementNode *expr1 = new StatementNode(
    new Label(1),
    a_var,
    new Operator(Operator::kAssign),
    new Constant(2),
    nullptr,
    expr2);

  AsmProgram testasm;
  testasm.IrToAsm(expr1);

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

  EXPECT_EQ("6", output);
  // EXPECT_EQ(0,0);
}

TEST(IRv3, IfLessThanEqualToTrue) {
  // a = 2;
  // if (a <= 2)
  // b = 3;
  // else
  // b = 4;
  // a + b;

  // expected output is 5

auto a_var = new Variable("a");
auto b_var = new Variable("b");

  StatementNode *expr7 = new StatementNode(
    new Label(7),
    new Register(3),
    new Operator(Operator::kAdd),
    a_var,
    b_var,
    nullptr);
  StatementNode *expr6 = new StatementNode(
    new Label(6),
    b_var,
    new Operator(Operator::kAssign),
    new Constant(4),
    nullptr,
    expr7);
  StatementNode *expr5 = new StatementNode(
    new Label(5),
    new Label(7),
    new Operator(Operator::kGoto),
    nullptr,
    nullptr,
    expr6);
  StatementNode *expr4 = new StatementNode(
    new Label(4),
    b_var,
    new Operator(Operator::kAssign),
    new Constant(3),
    nullptr,
    expr5);
  StatementNode *expr3 = new StatementNode(
    new Label(3),
    new Label(6),
    new Operator(Operator::kGoto),
    nullptr,
    nullptr,
    expr4);
  StatementNode *expr2 = new StatementNode(
    new Label(2),
    new Label(4),
    new Operator(Operator::kLessThanEqualTo),
    a_var,
    new Constant(2),
    expr3);
  StatementNode *expr1 = new StatementNode(
    new Label(1),
    a_var,
    new Operator(Operator::kAssign),
    new Constant(2),
    nullptr,
    expr2);

  AsmProgram testasm;
  testasm.IrToAsm(expr1);

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

  EXPECT_EQ("5", output);
  // EXPECT_EQ(0,0);
}
TEST(IRv3, IfLessThanEqualToFalse) {
  // a = 2;
  // if (a <= 1)
  // b = 3;
  // else
  // b = 4;
  // a + b;

  // expected output is 6

auto a_var = new Variable("a");
auto b_var = new Variable("b");

  StatementNode *expr7 = new StatementNode(
    new Label(7),
    new Register(3),
    new Operator(Operator::kAdd),
    a_var,
    b_var,
    nullptr);
  StatementNode *expr6 = new StatementNode(
    new Label(6),
    b_var,
    new Operator(Operator::kAssign),
    new Constant(4),
    nullptr,
    expr7);
  StatementNode *expr5 = new StatementNode(
    new Label(5),
    new Label(7),
    new Operator(Operator::kGoto),
    nullptr,
    nullptr,
    expr6);
  StatementNode *expr4 = new StatementNode(
    new Label(4),
    b_var,
    new Operator(Operator::kAssign),
    new Constant(3),
    nullptr,
    expr5);
  StatementNode *expr3 = new StatementNode(
    new Label(3),
    new Label(6),
    new Operator(Operator::kGoto),
    nullptr,
    nullptr,
    expr4);
  StatementNode *expr2 = new StatementNode(
    new Label(2),
    new Label(4),
    new Operator(Operator::kLessThanEqualTo),
    a_var,
    new Constant(1),
    expr3);
  StatementNode *expr1 = new StatementNode(
    new Label(1),
    a_var,
    new Operator(Operator::kAssign),
    new Constant(2),
    nullptr,
    expr2);

  AsmProgram testasm;
  testasm.IrToAsm(expr1);

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

  EXPECT_EQ("6", output);
  // EXPECT_EQ(0,0);
}
TEST(IRv3, IfGreaterThanEqualToTrue) {
  // a = 2;
  // if (a >= 2)
  // b = 3;
  // else
  // b = 4;
  // a + b;

  // expected output is 5

auto a_var = new Variable("a");
auto b_var = new Variable("b");

  StatementNode *expr7 = new StatementNode(
    new Label(7),
    new Register(3),
    new Operator(Operator::kAdd),
    a_var,
    b_var,
    nullptr);
  StatementNode *expr6 = new StatementNode(
    new Label(6),
    b_var,
    new Operator(Operator::kAssign),
    new Constant(4),
    nullptr,
    expr7);
  StatementNode *expr5 = new StatementNode(
    new Label(5),
    new Label(7),
    new Operator(Operator::kGoto),
    nullptr,
    nullptr,
    expr6);
  StatementNode *expr4 = new StatementNode(
    new Label(4),
    b_var,
    new Operator(Operator::kAssign),
    new Constant(3),
    nullptr,
    expr5);
  StatementNode *expr3 = new StatementNode(
    new Label(3),
    new Label(6),
    new Operator(Operator::kGoto),
    nullptr,
    nullptr,
    expr4);
  StatementNode *expr2 = new StatementNode(
    new Label(2),
    new Label(4),
    new Operator(Operator::kGreaterThanEqualTo),
    a_var,
    new Constant(2),
    expr3);
  StatementNode *expr1 = new StatementNode(
    new Label(1),
    a_var,
    new Operator(Operator::kAssign),
    new Constant(2),
    nullptr,
    expr2);

  AsmProgram testasm;
  testasm.IrToAsm(expr1);

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

  EXPECT_EQ("5", output);
  // EXPECT_EQ(0,0);
}

TEST(IRv3, IfGreaterThanEqualToFalse) {
  // a = 2;
  // if (a >= 20)
  // b = 3;
  // else
  // b = 4;
  // a + b;

  // expected output is 6

auto a_var = new Variable("a");
auto b_var = new Variable("b");

  StatementNode *expr7 = new StatementNode(
    new Label(7),
    new Register(3),
    new Operator(Operator::kAdd),
    a_var,
    b_var,
    nullptr);
  StatementNode *expr6 = new StatementNode(
    new Label(6),
    b_var,
    new Operator(Operator::kAssign),
    new Constant(4),
    nullptr,
    expr7);
  StatementNode *expr5 = new StatementNode(
    new Label(5),
    new Label(7),
    new Operator(Operator::kGoto),
    nullptr,
    nullptr,
    expr6);
  StatementNode *expr4 = new StatementNode(
    new Label(4),
    b_var,
    new Operator(Operator::kAssign),
    new Constant(3),
    nullptr,
    expr5);
  StatementNode *expr3 = new StatementNode(
    new Label(3),
    new Label(6),
    new Operator(Operator::kGoto),
    nullptr,
    nullptr,
    expr4);
  StatementNode *expr2 = new StatementNode(
    new Label(2),
    new Label(4),
    new Operator(Operator::kGreaterThanEqualTo),
    a_var,
    new Constant(20),
    expr3);
  StatementNode *expr1 = new StatementNode(
    new Label(1),
    a_var,
    new Operator(Operator::kAssign),
    new Constant(2),
    nullptr,
    expr2);

  AsmProgram testasm;
  testasm.IrToAsm(expr1);

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

  EXPECT_EQ("6", output);
  // EXPECT_EQ(0,0);
}
