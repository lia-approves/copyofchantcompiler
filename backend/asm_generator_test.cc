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
using cs160::backend::StatementNode;
using cs160::backend::AsmProgram;
using cs160::backend::IrGenVisitor;

using cs160::make_unique;

TEST(ExecuteASM, Add) {
  auto expr = make_unique<AddExpr>(
    make_unique<IntegerExpr>(10),
    make_unique<IntegerExpr>(2));
  IrGenVisitor irGen;
  expr->Visit(&irGen);

  AsmProgram testasm;
  testasm.IrToAsm(irGen.GetIR());

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

  EXPECT_EQ("12", output);
}

TEST(ExecuteASM, Subtract) {
  auto expr = make_unique<SubtractExpr>(
    make_unique<IntegerExpr>(10),
    make_unique<IntegerExpr>(2));
  IrGenVisitor irGen;
  expr->Visit(&irGen);

  AsmProgram testasm;
  testasm.IrToAsm(irGen.GetIR());

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

  EXPECT_EQ("8", output);
}

TEST(ExecuteASM, Multiply) {
  auto expr = make_unique<MultiplyExpr>(
    make_unique<IntegerExpr>(10),
    make_unique<IntegerExpr>(2));
  IrGenVisitor irGen;
  expr->Visit(&irGen);

  AsmProgram testasm;
  testasm.IrToAsm(irGen.GetIR());

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

  EXPECT_EQ("20", output);
}
