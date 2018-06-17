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
#include "backend/SSA.h"


using cs160::abstract_syntax::version_5::AddExpr;
using cs160::abstract_syntax::version_5::SubtractExpr;
using cs160::abstract_syntax::version_5::MultiplyExpr;
using cs160::abstract_syntax::version_5::DivideExpr;
using cs160::abstract_syntax::version_5::IntegerExpr;
using cs160::abstract_syntax::version_5::VariableExpr;
using cs160::abstract_syntax::version_5::LessThanExpr;
using cs160::abstract_syntax::version_5::Statement;
using cs160::abstract_syntax::version_5::AssignmentFromArithExp;
using cs160::abstract_syntax::version_5::Conditional;
using cs160::abstract_syntax::version_5::FunctionDef;
using cs160::abstract_syntax::version_5::Program;

using cs160::backend::AsmProgram;
using cs160::backend::IrGenVisitor;
using cs160::backend::AsmProgram;
using cs160::backend::SSA;

using cs160::make_unique;

TEST(AE, CanAdd) {
  FunctionDef::Block function_defs;
  Statement::Block statements;

  // 12 + 30
  auto ae = make_unique<const AddExpr>(
    make_unique<const IntegerExpr>(12),
    make_unique<const IntegerExpr>(30));

  auto ast = make_unique<const Program>(std::move(function_defs),
  std::move(statements), std::move(ae));

  IrGenVisitor irGen;
  ast->Visit(&irGen);
  SSA ssatest = SSA(irGen.GetIR());
  ssatest.ComputeCFG();
  ssatest.GenerateDomination();
  ssatest.DetermineVariableLiveness();
  ssatest.InsertSSAFunctions();
  ssatest.RenameAllVariables();
  ssatest.PrintCFG();
  ssatest.PrintDominators();
  AsmProgram testasm;
  testasm.SSAIRToAsm(ssatest.GetSSAIR());
  
  

  // save & run assembly with gcc
  std::ofstream test_output_file;
  test_output_file.open("testfile.s");
  test_output_file << testasm.GetASMString();
  test_output_file.close();
  system("gcc testfile.s && ./a.out > test_output.txt");

  // get output of running assembly to compare it to the expected output
  std::ifstream output_file;
  output_file.open("test_output.txt");
  std::string output;
  output_file >> output;
  output_file.close();
  system("rm testfile.s test_output.txt");

  // 12 + 30 = 42
  // output should be 42
  EXPECT_EQ("42", output);
}

TEST(AE, CanSubtract) {
  FunctionDef::Block function_defs;
  Statement::Block statements;

  // 52 - 10
  auto ae = make_unique<const SubtractExpr>(
    make_unique<const IntegerExpr>(52),
    make_unique<const IntegerExpr>(10));

  auto ast = make_unique<const Program>(std::move(function_defs),
  std::move(statements), std::move(ae));

  IrGenVisitor irGen;
  ast->Visit(&irGen);
  SSA ssatest = SSA(irGen.GetIR());
  ssatest.ComputeCFG();
  ssatest.GenerateDomination();
  ssatest.DetermineVariableLiveness();
  ssatest.InsertSSAFunctions();
  ssatest.RenameAllVariables();
  ssatest.PrintCFG();
  ssatest.PrintDominators();
  AsmProgram testasm;
  testasm.SSAIRToAsm(ssatest.GetSSAIR());
  

  // save & run assembly with gcc
  std::ofstream test_output_file;
  test_output_file.open("testfile.s");
  test_output_file << testasm.GetASMString();
  test_output_file.close();
  system("gcc testfile.s && ./a.out > test_output.txt");

  // get output of running assembly to compare it to the expected output
  std::ifstream output_file;
  output_file.open("test_output.txt");
  std::string output;
  output_file >> output;
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

  // generate intermediate representation
  IrGenVisitor irGen;
  ast->Visit(&irGen);
  SSA ssatest = SSA(irGen.GetIR());
  ssatest.ComputeCFG();
  ssatest.GenerateDomination();
  ssatest.DetermineVariableLiveness();
  ssatest.InsertSSAFunctions();
  ssatest.RenameAllVariables();
  ssatest.PrintCFG();
  ssatest.PrintDominators();
  AsmProgram testasm;
  testasm.SSAIRToAsm(ssatest.GetSSAIR());
  

  // save & run assembly with gcc
  std::ofstream test_output_file;
  test_output_file.open("testfile.s");
  test_output_file << testasm.GetASMString();
  test_output_file.close();
  system("gcc testfile.s && ./a.out > test_output.txt");

  // get output of running assembly to compare it to the expected output
  std::ifstream output_file;
  output_file.open("test_output.txt");
  std::string output;
  output_file >> output;
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

  // generate intermediate representation
  IrGenVisitor irGen;
  ast->Visit(&irGen);
  SSA ssatest = SSA(irGen.GetIR());
  ssatest.ComputeCFG();
  ssatest.GenerateDomination();
  ssatest.DetermineVariableLiveness();
  ssatest.InsertSSAFunctions();
  ssatest.RenameAllVariables();
  ssatest.PrintCFG();
  ssatest.PrintDominators();
  AsmProgram testasm;
  testasm.SSAIRToAsm(ssatest.GetSSAIR());
  

  // save & run assembly with gcc
  std::ofstream test_output_file;
  test_output_file.open("testfile.s");
  test_output_file << testasm.GetASMString();
  test_output_file.close();
  system("gcc testfile.s && ./a.out > test_output.txt");

  // get output of running assembly to compare it to the expected output
  std::ifstream output_file;
  output_file.open("test_output.txt");
  std::string output;
  output_file >> output;
  output_file.close();
  system("rm testfile.s test_output.txt");

  EXPECT_EQ("42", output);
}


TEST(AE, CanConditionalTrue) {
  FunctionDef::Block function_defs;
  Statement::Block statements;

  auto ae = make_unique<const AddExpr>(
    make_unique<VariableExpr>("a"),
    make_unique<const IntegerExpr>(0));

  Statement::Block trueStatements;
  Statement::Block falseStatements;

  trueStatements.push_back(std::move(make_unique<const AssignmentFromArithExp>(
    make_unique<const VariableExpr>("a"),
    make_unique<const IntegerExpr>(3))));

  falseStatements.push_back(std::move(make_unique<const AssignmentFromArithExp>(
    make_unique<const VariableExpr>("a"),
    make_unique<const IntegerExpr>(4))));

  statements.push_back(std::move(make_unique<const Conditional>(
              make_unique<const GreaterThanExpr>(
                  make_unique<const IntegerExpr>(20),
                  make_unique<const IntegerExpr>(0)),
      std::move(trueStatements), std::move(falseStatements))));


  auto ast = make_unique<const Program>(std::move(function_defs),
  std::move(statements), std::move(ae));

  IrGenVisitor irGen;
  ast->Visit(&irGen);
  SSA ssatest = SSA(irGen.GetIR());
  ssatest.ComputeCFG();
  ssatest.GenerateDomination();
  ssatest.DetermineVariableLiveness();
  ssatest.InsertSSAFunctions();
  ssatest.RenameAllVariables();
  ssatest.PrintCFG();
  ssatest.PrintDominators();
  AsmProgram testasm;
  testasm.SSAIRToAsm(ssatest.GetSSAIR());
  

  // save & run assembly with gcc
  std::ofstream test_output_file;
  test_output_file.open("testfile.s");
  test_output_file << testasm.GetASMString();
  test_output_file.close();
  system("gcc testfile.s && ./a.out > test_output.txt");

  // get output of running assembly to compare it to the expected output
  std::ifstream output_file;
  output_file.open("test_output.txt");
  std::string output;
  output_file >> output;
  output_file.close();
  system("rm testfile.s test_output.txt");

  EXPECT_EQ("3", output);
}

TEST(AE, CanConditionalFalse) {
  FunctionDef::Block function_defs;
  Statement::Block statements;

  auto ae = make_unique<const AddExpr>(
    make_unique<VariableExpr>("a"),
    make_unique<const IntegerExpr>(0));

  Statement::Block trueStatements;
  Statement::Block falseStatements;

  trueStatements.push_back(std::move(make_unique<const AssignmentFromArithExp>(
    make_unique<const VariableExpr>("a"),
    make_unique<const IntegerExpr>(3))));

  falseStatements.push_back(std::move(make_unique<const AssignmentFromArithExp>(
    make_unique<const VariableExpr>("a"),
    make_unique<const IntegerExpr>(4))));

  statements.push_back(std::move(make_unique<const Conditional>(
              make_unique<const LessThanExpr>(
                  make_unique<const IntegerExpr>(20),
                  make_unique<const IntegerExpr>(0)),
      std::move(trueStatements), std::move(falseStatements))));


  auto ast = make_unique<const Program>(std::move(function_defs),
  std::move(statements), std::move(ae));

  IrGenVisitor irGen;
  ast->Visit(&irGen);
  SSA ssatest = SSA(irGen.GetIR());
  ssatest.ComputeCFG();
  ssatest.GenerateDomination();
  ssatest.DetermineVariableLiveness();
  ssatest.InsertSSAFunctions();
  ssatest.RenameAllVariables();
  ssatest.PrintCFG();
  ssatest.PrintDominators();
  AsmProgram testasm;
  testasm.SSAIRToAsm(ssatest.GetSSAIR());
  

  // save & run assembly with gcc
  std::ofstream test_output_file;
  test_output_file.open("testfile.s");
  test_output_file << testasm.GetASMString();
  test_output_file.close();
  system("gcc testfile.s && ./a.out > test_output.txt");

  // get output of running assembly to compare it to the expected output
  std::ifstream output_file;
  output_file.open("test_output.txt");
  std::string output;
  output_file >> output;
  output_file.close();
  system("rm testfile.s test_output.txt");

  EXPECT_EQ("4", output);
}

TEST(AE, DominatesItself) {
  FunctionDef::Block function_defs;
  Statement::Block statements;

  // ((-4 / 2) - 101) + (15 * 7) = 
   auto ae = make_unique<const AddExpr>(
    make_unique<const SubtractExpr>(
      make_unique<const DivideExpr>(make_unique<const IntegerExpr>(-4),
        make_unique<const IntegerExpr>(2)),
      make_unique<const IntegerExpr>(101)),
    make_unique<const MultiplyExpr>(make_unique<const IntegerExpr>(15),
      make_unique<const IntegerExpr>(7)));

   auto ast = make_unique<const Program>(std::move(function_defs),
  std::move(statements), std::move(ae));

  // generate intermediate representation
   IrGenVisitor irGen;
   ast->Visit(&irGen);
   SSA ssatest = SSA(irGen.GetIR());
   ssatest.ComputeCFG();
   ssatest.GenerateDomination();
   ssatest.DetermineVariableLiveness();
   ssatest.InsertSSAFunctions();
   ssatest.RenameAllVariables();
   ssatest.PrintCFG();
   ssatest.PrintDominators();
   AsmProgram testasm;
   testasm.SSAIRToAsm(ssatest.GetSSAIR());
   

  // see that the one basic block dominates itself
  int dominates = ((ssatest.GetDominators()[0]).GetDominated())[0][0];



  // save & run assembly with gcc
  std::ofstream test_output_file;
  test_output_file.open("testfile.s");
  test_output_file << testasm.GetASMString();
  test_output_file.close();
  system("gcc testfile.s && ./a.out > test_output.txt");

  // get output of running assembly to compare it to the expected output
  std::ifstream output_file;
  output_file.open("test_output.txt");
  std::string output;
  output_file >> output;
  output_file.close();
  system("rm testfile.s test_output.txt");

  EXPECT_EQ("2", output);
  EXPECT_EQ(0, dominates);
}

