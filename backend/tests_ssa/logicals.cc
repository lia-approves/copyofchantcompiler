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
using cs160::backend::ControlFlowGraph;
using cs160::backend::SSA;

TEST(AE, CanAnd) {
  FunctionDef::Block function_defs;
  Statement::Block statements;

  // a + 0
  auto ae = make_unique<const AddExpr>(
    make_unique<VariableExpr>("a"),
    make_unique<const IntegerExpr>(0));

  Statement::Block trueStatements;
  Statement::Block falseStatements;

  // a = 3
  trueStatements.push_back(std::move(make_unique<const AssignmentFromArithExp>(
    make_unique<const VariableExpr>("a"),
    make_unique<const IntegerExpr>(3))));

  // a = 4
  falseStatements.push_back(std::move(make_unique<const AssignmentFromArithExp>(
    make_unique<const VariableExpr>("a"),
    make_unique<const IntegerExpr>(4))));

  // if ( (0 < 20) and (9 >= 8) )
  //     trueStatements
  // else
  //     falseStatements
  statements.push_back(std::move(make_unique<const Conditional>(
          make_unique<const LogicalAndExpr>(
            make_unique<const LessThanExpr>(
              make_unique<const IntegerExpr>(0),
              make_unique<const IntegerExpr>(20)),
            make_unique<const GreaterThanEqualToExpr>(
              make_unique<const IntegerExpr>(9),
              make_unique<const IntegerExpr>(8))),
      std::move(trueStatements), std::move(falseStatements))));


  auto ast = make_unique<const Program>(std::move(function_defs),
  std::move(statements), std::move(ae));

  // generate intermediate representation
  IrGenVisitor irGen;
  ast->Visit(&irGen);
  ControlFlowGraph cfg = ControlFlowGraph(irGen.GetIR());
  cfg.CreateCFG();
  cfg.PrintGraph();
  SSA ssatest = SSA(irGen.GetIR(), cfg.CFG());
  ssatest.GenerateDomination();
  ssatest.PrintDominators();
  ssatest.DetermineVariableLiveness();
  ssatest.InsertSSAFunctions();
  ssatest.PrintSSA();
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

  // conditional should be true,
  // so output should be 3
  EXPECT_EQ("3", output);
}

TEST(AE, CanOr) {
  FunctionDef::Block function_defs;
  Statement::Block statements;

  // a + 0
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

  // if ( (0 < 20) or (9 >= 8))
  statements.push_back(std::move(make_unique<const Conditional>(
          make_unique<const LogicalOrExpr>(
            make_unique<const LessThanExpr>(
              make_unique<const IntegerExpr>(0),
              make_unique<const IntegerExpr>(20)),
            make_unique<const GreaterThanEqualToExpr>(
              make_unique<const IntegerExpr>(9),
              make_unique<const IntegerExpr>(8))),
      std::move(trueStatements), std::move(falseStatements))));


  auto ast = make_unique<const Program>(std::move(function_defs),
  std::move(statements), std::move(ae));
  // generate intermediate representation
  IrGenVisitor irGen;
  ast->Visit(&irGen);
  ControlFlowGraph cfg = ControlFlowGraph(irGen.GetIR());
  cfg.CreateCFG();
  cfg.PrintGraph();
  SSA ssatest = SSA(irGen.GetIR(), cfg.CFG());
  ssatest.GenerateDomination();
  ssatest.PrintDominators();
  ssatest.DetermineVariableLiveness();
  ssatest.InsertSSAFunctions();
  ssatest.PrintSSA();
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

  // conditional should be true,
  // so output should be 3
  EXPECT_EQ("3", output);
}

TEST(AE, CanNot) {
  FunctionDef::Block function_defs;
  Statement::Block statements;

  auto ae = make_unique<const AddExpr>(
    make_unique<VariableExpr>("a"),
    make_unique<const IntegerExpr>(0));

  Statement::Block trueStatements;
  Statement::Block falseStatements;

  trueStatements.push_back(std::move(make_unique<const AssignmentFromArithExp>(
    make_unique<const VariableExpr>("a"),
    make_unique<const AddExpr>(
      make_unique<const IntegerExpr>(1),
      make_unique<const IntegerExpr>(2)))));

  falseStatements.push_back(std::move(make_unique<const AssignmentFromArithExp>(
    make_unique<const VariableExpr>("a"),
    make_unique<const IntegerExpr>(4))));

  // if ( !(20 < 0) )
  statements.push_back(std::move(make_unique<const Conditional>(
    make_unique<const LogicalNotExpr>(
            make_unique<const LessThanExpr>(
              make_unique<const IntegerExpr>(20),
              make_unique<const IntegerExpr>(0))),
      std::move(trueStatements), std::move(falseStatements))));


  auto ast = make_unique<const Program>(std::move(function_defs),
  std::move(statements), std::move(ae));

  // generate intermediate representation
IrGenVisitor irGen;
  ast->Visit(&irGen);
  ControlFlowGraph cfg = ControlFlowGraph(irGen.GetIR());
  cfg.CreateCFG();
  cfg.PrintGraph();
  SSA ssatest = SSA(irGen.GetIR(), cfg.CFG());
  ssatest.GenerateDomination();
  ssatest.PrintDominators();
  ssatest.DetermineVariableLiveness();
  ssatest.InsertSSAFunctions();
  ssatest.PrintSSA();
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

TEST(AE, CanAndNested) {
  FunctionDef::Block function_defs;
  Statement::Block statements;

  auto ae = make_unique<const AddExpr>(
    make_unique<VariableExpr>("a"),
    make_unique<const IntegerExpr>(0));

  Statement::Block trueStatements;
  Statement::Block falseStatements;

  trueStatements.push_back(std::move(make_unique<const AssignmentFromArithExp>(
    make_unique<const VariableExpr>("a"),
    make_unique<const AddExpr>(
      make_unique<const IntegerExpr>(1),
      make_unique<const IntegerExpr>(2)))));

  falseStatements.push_back(std::move(make_unique<const AssignmentFromArithExp>(
    make_unique<const VariableExpr>("a"),
    make_unique<const IntegerExpr>(4))));

  // ( ((0<20) and (9>=8)) and ((0<20) and (9>=8)) )
  statements.push_back(std::move(make_unique<const Conditional>(
    make_unique<const LogicalAndExpr>(
          make_unique<const LogicalAndExpr>(
            make_unique<const LessThanExpr>(
              make_unique<const IntegerExpr>(0),
              make_unique<const IntegerExpr>(20)),
            make_unique<const GreaterThanEqualToExpr>(
              make_unique<const IntegerExpr>(9),
              make_unique<const IntegerExpr>(8))),
          make_unique<const LogicalAndExpr>(
            make_unique<const LessThanExpr>(
              make_unique<const IntegerExpr>(0),
              make_unique<const IntegerExpr>(20)),
            make_unique<const GreaterThanEqualToExpr>(
              make_unique<const IntegerExpr>(9),
              make_unique<const IntegerExpr>(8)))),
      std::move(trueStatements), std::move(falseStatements))));


  auto ast = make_unique<const Program>(std::move(function_defs),
  std::move(statements), std::move(ae));

  // generate intermediate representation
IrGenVisitor irGen;
  ast->Visit(&irGen);
  ControlFlowGraph cfg = ControlFlowGraph(irGen.GetIR());
  cfg.CreateCFG();
  cfg.PrintGraph();
  SSA ssatest = SSA(irGen.GetIR(), cfg.CFG());
  ssatest.GenerateDomination();
  ssatest.PrintDominators();
  ssatest.DetermineVariableLiveness();
  ssatest.InsertSSAFunctions();
  ssatest.PrintSSA();
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

TEST(AE, CanMixLogicals1) {
  FunctionDef::Block function_defs;
  Statement::Block statements;

  auto ae = make_unique<const AddExpr>(
    make_unique<VariableExpr>("a"),
    make_unique<const IntegerExpr>(0));

  Statement::Block trueStatements;
  Statement::Block falseStatements;

  trueStatements.push_back(std::move(make_unique<const AssignmentFromArithExp>(
    make_unique<const VariableExpr>("a"),
    make_unique<const AddExpr>(
      make_unique<const IntegerExpr>(1),
      make_unique<const IntegerExpr>(2)))));

  falseStatements.push_back(std::move(make_unique<const AssignmentFromArithExp>(
    make_unique<const VariableExpr>("a"),
    make_unique<const IntegerExpr>(4))));

  // (if (2 < 4 && 2 < 0) || 9 >= 9) ---> should be true
  //    a = 3
  // else
  //    a = 4
  statements.push_back(std::move(make_unique<const Conditional>(
    make_unique<const LogicalOrExpr>(
      make_unique<const LogicalAndExpr>(
        make_unique<const LessThanExpr>(
          make_unique<const IntegerExpr>(2),
          make_unique<const IntegerExpr>(4)),
        make_unique<const LessThanExpr>(
          make_unique<const IntegerExpr>(2),
          make_unique<const IntegerExpr>(0))),
      make_unique<const GreaterThanEqualToExpr>(
        make_unique<const IntegerExpr>(9),
        make_unique<const IntegerExpr>(9))),
      std::move(trueStatements), std::move(falseStatements))));


  auto ast = make_unique<const Program>(std::move(function_defs),
  std::move(statements), std::move(ae));

  // generate intermediate representation
IrGenVisitor irGen;
  ast->Visit(&irGen);
  ControlFlowGraph cfg = ControlFlowGraph(irGen.GetIR());
  cfg.CreateCFG();
  cfg.PrintGraph();
  SSA ssatest = SSA(irGen.GetIR(), cfg.CFG());
  ssatest.GenerateDomination();
  ssatest.PrintDominators();
  ssatest.DetermineVariableLiveness();
  ssatest.InsertSSAFunctions();
  ssatest.PrintSSA();
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

TEST(AE, CanMixLogicals2) {
  FunctionDef::Block function_defs;
  Statement::Block statements;

  auto ae = make_unique<const AddExpr>(
    make_unique<VariableExpr>("a"),
    make_unique<const IntegerExpr>(0));

  Statement::Block trueStatements;
  Statement::Block falseStatements;

  trueStatements.push_back(std::move(make_unique<const AssignmentFromArithExp>(
    make_unique<const VariableExpr>("a"),
    make_unique<const AddExpr>(
      make_unique<const IntegerExpr>(1),
      make_unique<const IntegerExpr>(2)))));

  falseStatements.push_back(std::move(make_unique<const AssignmentFromArithExp>(
    make_unique<const VariableExpr>("a"),
    make_unique<const IntegerExpr>(4))));

  // (if (2 < 4 && 2 > 0) || 9 >= 9) ---> should be true
  //    a = 1 + 2
  // else
  //    a = 4
  statements.push_back(std::move(make_unique<const Conditional>(
    make_unique<const LogicalOrExpr>(
      make_unique<const LogicalAndExpr>(
        make_unique<const LessThanExpr>(
          make_unique<const IntegerExpr>(2),
          make_unique<const IntegerExpr>(4)),
        make_unique<const GreaterThanExpr>(
          make_unique<const IntegerExpr>(2),
          make_unique<const IntegerExpr>(0))),
      make_unique<const GreaterThanEqualToExpr>(
        make_unique<const IntegerExpr>(9),
        make_unique<const IntegerExpr>(9))),
      std::move(trueStatements), std::move(falseStatements))));


  auto ast = make_unique<const Program>(std::move(function_defs),
  std::move(statements), std::move(ae));

  // generate intermediate representation
  IrGenVisitor irGen;
  ast->Visit(&irGen);
  ControlFlowGraph cfg = ControlFlowGraph(irGen.GetIR());
  cfg.CreateCFG();
  cfg.PrintGraph();
  SSA ssatest = SSA(irGen.GetIR(), cfg.CFG());
  ssatest.GenerateDomination();
  ssatest.PrintDominators();
  ssatest.DetermineVariableLiveness();
  ssatest.InsertSSAFunctions();
  ssatest.PrintSSA();
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

TEST(AE, CanMixLogicals3) {
  FunctionDef::Block function_defs;
  Statement::Block statements;

  auto ae = make_unique<const AddExpr>(
    make_unique<VariableExpr>("a"),
    make_unique<const IntegerExpr>(0));

  Statement::Block trueStatements;
  Statement::Block falseStatements;

  trueStatements.push_back(std::move(make_unique<const AssignmentFromArithExp>(
    make_unique<const VariableExpr>("a"),
    make_unique<const AddExpr>(
      make_unique<const IntegerExpr>(1),
      make_unique<const IntegerExpr>(2)))));

  falseStatements.push_back(std::move(make_unique<const AssignmentFromArithExp>(
    make_unique<const VariableExpr>("a"),
    make_unique<const AddExpr>(
      make_unique<const IntegerExpr>(2),
      make_unique<const IntegerExpr>(2)))));

  // (if (2 < 4 && 2 > 0) || 9 >= 9) ---> should be true
  //    a = 1 + 2
  // else
  //    a = 4
  statements.push_back(std::move(make_unique<const Conditional>(
    make_unique<const LogicalOrExpr>(
      make_unique<const LogicalAndExpr>(
        make_unique<const LessThanExpr>(
          make_unique<const IntegerExpr>(2),
          make_unique<const IntegerExpr>(4)),
        make_unique<const GreaterThanExpr>(
          make_unique<const IntegerExpr>(2),
          make_unique<const IntegerExpr>(0))),
      make_unique<const GreaterThanEqualToExpr>(
        make_unique<const IntegerExpr>(9),
        make_unique<const IntegerExpr>(9))),
      std::move(trueStatements), std::move(falseStatements))));


  auto ast = make_unique<const Program>(std::move(function_defs),
  std::move(statements), std::move(ae));

  // generate intermediate representation
IrGenVisitor irGen;
  ast->Visit(&irGen);
  ControlFlowGraph cfg = ControlFlowGraph(irGen.GetIR());
  cfg.CreateCFG();
  cfg.PrintGraph();
  SSA ssatest = SSA(irGen.GetIR(), cfg.CFG());
  ssatest.GenerateDomination();
  ssatest.PrintDominators();
  ssatest.DetermineVariableLiveness();
  ssatest.InsertSSAFunctions();
  ssatest.PrintSSA();
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

TEST(AE, RootDominates) {
  FunctionDef::Block function_defs;
  Statement::Block statements;

  auto ae = make_unique<const AddExpr>(
    make_unique<VariableExpr>("a"),
    make_unique<const IntegerExpr>(0));

  Statement::Block trueStatements;
  Statement::Block falseStatements;

  trueStatements.push_back(std::move(make_unique<const AssignmentFromArithExp>(
    make_unique<const VariableExpr>("a"),
    make_unique<const AddExpr>(
      make_unique<const IntegerExpr>(1),
      make_unique<const IntegerExpr>(2)))));

  falseStatements.push_back(std::move(make_unique<const AssignmentFromArithExp>(
    make_unique<const VariableExpr>("a"),
    make_unique<const AddExpr>(
      make_unique<const IntegerExpr>(2),
      make_unique<const IntegerExpr>(2)))));

  // (if (2 < 4 && 2 > 0) || 9 >= 9) ---> should be true
  //    a = 1 + 2
  // else
  //    a = 4
  statements.push_back(std::move(make_unique<const Conditional>(
    make_unique<const LogicalOrExpr>(
      make_unique<const LogicalAndExpr>(
        make_unique<const LessThanExpr>(
          make_unique<const IntegerExpr>(2),
          make_unique<const IntegerExpr>(4)),
        make_unique<const GreaterThanExpr>(
          make_unique<const IntegerExpr>(2),
          make_unique<const IntegerExpr>(0))),
      make_unique<const GreaterThanEqualToExpr>(
        make_unique<const IntegerExpr>(9),
        make_unique<const IntegerExpr>(9))),
      std::move(trueStatements), std::move(falseStatements))));


  auto ast = make_unique<const Program>(std::move(function_defs),
  std::move(statements), std::move(ae));

  // generate intermediate representation
IrGenVisitor irGen;
  ast->Visit(&irGen);
  ControlFlowGraph cfg = ControlFlowGraph(irGen.GetIR());
  cfg.CreateCFG();
  cfg.PrintGraph();
  SSA ssatest = SSA(irGen.GetIR(), cfg.CFG());
  ssatest.GenerateDomination();
  ssatest.PrintDominators();
  ssatest.DetermineVariableLiveness();
  ssatest.InsertSSAFunctions();
  ssatest.PrintSSA();
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

  // see that root dominates all other nodes
  std::vector<int> dominates0 = ((ssatest.GetDominators()[0]).GetDominated())[0];
  std::vector<int> dominatesans = {0, 4, 5, 8, 11, 12, 13, 14, 19, 23};
  EXPECT_EQ(dominates0.size(), dominatesans.size());
  for (int i = 0; i < dominatesans.size(); i++) {
    auto it = std::find(dominates0.begin(), dominates0.end(), dominatesans[i]);
    EXPECT_EQ(*it, dominatesans[i]);
  }
}

TEST(AE, DominatesCheck) {
  FunctionDef::Block function_defs;
  Statement::Block statements;

  auto ae = make_unique<const AddExpr>(
    make_unique<VariableExpr>("b"),
    make_unique<const IntegerExpr>(4));

  Statement::Block trueStatements;
  Statement::Block falseStatements;

  trueStatements.push_back(std::move(make_unique<const AssignmentFromArithExp>(
    make_unique<const VariableExpr>("c"),
    make_unique<const AddExpr>(
      make_unique<const IntegerExpr>(17),
      make_unique<const IntegerExpr>(0)))));

  falseStatements.push_back(std::move(make_unique<const AssignmentFromArithExp>(
    make_unique<const VariableExpr>("d"),
    make_unique<const AddExpr>(
      make_unique<const IntegerExpr>(6),
      make_unique<const IntegerExpr>(-1)))));

  statements.push_back(std::move(make_unique<const Conditional>(
    make_unique<const LogicalAndExpr>(
      make_unique<const LogicalOrExpr>(
        make_unique<const LessThanExpr>(
          make_unique<const IntegerExpr>(4),
          make_unique<const IntegerExpr>(5)),
        make_unique<const GreaterThanExpr>(
          make_unique<const IntegerExpr>(7),
          make_unique<const IntegerExpr>(-9))),
      make_unique<const LessThanEqualToExpr>(
        make_unique<const IntegerExpr>(8),
        make_unique<const IntegerExpr>(3))),
      std::move(trueStatements), std::move(falseStatements))));


  auto ast = make_unique<const Program>(std::move(function_defs),
  std::move(statements), std::move(ae));

  // generate intermediate representation
  IrGenVisitor irGen;
  ast->Visit(&irGen);

  // create control flow graph
  ControlFlowGraph cfg = ControlFlowGraph(irGen.GetIR());
  cfg.CreateCFG();
  SSA ssatest = SSA(irGen.GetIR(), cfg.CFG());
  ssatest.GenerateDomination();
  ssatest.PrintDominators();

  // print SSA for test
  ssatest.PrintSSA();

  // generate assembly code
  AsmProgram testasm;
  testasm.IrToAsm(&irGen);

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

  // see that basic block 8 dominates blocks 8, 10, and 14
  std::vector<int> dominates =
    ssatest.GetDominators()[0].GetBlockNums();
  int index8 = std::distance(dominates.begin(), 
    std::find(dominates.begin(), dominates.end(), 8));
  std::vector<int> dominates8 = 
    ((ssatest.GetDominators()[0]).GetDominated())[index8];
  std::vector<int> dominatesans = {8, 10, 14};
  for (int i = 0; i < dominatesans.size(); i++) {
    auto it = std::find(dominates8.begin(), dominates8.end(), dominatesans[i]);
    EXPECT_EQ(*it, dominatesans[i]);
  }
}
