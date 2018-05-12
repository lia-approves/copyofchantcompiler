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
using cs160::backend::StatementNode;
using cs160::backend::AsmProgram;
using cs160::backend::IrGenVisitor;

using cs160::make_unique;

using cs160::abstract_syntax::version_3::AstVisitor;
using cs160::abstract_syntax::version_3::VariableExpr;
using cs160::abstract_syntax::version_3::Assignment;
using cs160::abstract_syntax::version_3::Program;
using cs160::abstract_syntax::version_3::Statement;

using cs160::backend::AsmProgram;


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


TEST(ExecuteASM, Divide) {
  auto expr = make_unique<DivideExpr>(
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

  EXPECT_EQ("5", output);
}

TEST(ExecuteASM, AndNotOr) {
  Statement::Block statements;
  Statement::Block truebody;
  Statement::Block falsebody;
  truebody.push_back(std::move(
    make_unique<const Assignment>(
      make_unique<const VariableExpr>("a"),
      make_unique<const IntegerExpr>(1))));
  falsebody.push_back(std::move(
    make_unique<const Assignment>(
      make_unique<const VariableExpr>("a"),
      make_unique<const IntegerExpr>(0))));
  statements.push_back(std::move(
    make_unique<const Assignment>(
      make_unique<const VariableExpr>("a"),
      make_unique<const IntegerExpr>(1))));
  statements.push_back(std::move(
    make_unique<const Assignment>(
      make_unique<const VariableExpr>("b"),
      make_unique<const IntegerExpr>(2))));
  statements.push_back(std::move(
    make_unique<const Conditional>(
      make_unique<const LogicalAndExpr>(
        make_unique<const LogicalNotExpr>(
          make_unique<const EqualToExpr>(
            make_unique<const VariableExpr>("a"),
            make_unique<const IntegerExpr>(0))),
        make_unique<const LogicalOrExpr>(
          make_unique<const EqualToExpr>(
            make_unique<const VariableExpr>("b"),
            make_unique<const IntegerExpr>(1)),
          make_unique<const GreaterThanExpr>(
            make_unique<const VariableExpr>("b"),
            make_unique<const IntegerExpr>(-1)))),
      std::move(truebody), std::move(falsebody))));

  auto ae = make_unique<const AddExpr>(
              make_unique<VariableExpr>("a"),
              make_unique<IntegerExpr>(0));
  auto ast = make_unique<const Program>(std::move(statements), std::move(ae));

  IrGenVisitor irGen;
  ast->Visit(&irGen);

  AsmProgram testasm;
  irGen.PrintIR();  // see IR
  testasm.IrToAsm(irGen.GetIR());

  std::ofstream test_output_file;
  test_output_file.open("testfile.s");
  test_output_file << testasm.GetASMString();
  // std::cout << testasm.GetASMString(); //see assembly
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
