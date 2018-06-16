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

TEST(v5, CanLoop) {
  Statement::Block statements;
  FunctionDef::Block function_defs;
  Statement::Block loop_body;

  // x = x + 1
  loop_body.push_back(std::move(make_unique<const AssignmentFromArithExp>(
    make_unique<const VariableExpr>("x"),
    make_unique<const AddExpr>(make_unique<const VariableExpr>("x"),
      make_unique<const IntegerExpr>(1)))));

  // y = y + x
  loop_body.push_back(std::move(make_unique<const AssignmentFromArithExp>(
    make_unique<const VariableExpr>("y"),
    make_unique<const AddExpr>(make_unique<const VariableExpr>("y"),
      make_unique<const VariableExpr>("x")))));

  // x = 1
  statements.push_back(std::move(make_unique<const AssignmentFromArithExp>(
    make_unique<const VariableExpr>("x"), make_unique<const IntegerExpr>(1))));
  // y = 2
  statements.push_back(std::move(make_unique<const AssignmentFromArithExp>(
    make_unique<const VariableExpr>("y"), make_unique<const IntegerExpr>(2))));

  // loop while (x < 100)
  //     x = x + 1
  //     y = y + x
  statements.push_back(std::move(make_unique<const Loop>(
    make_unique<const LessThanExpr>(make_unique<const VariableExpr>("x"),
    make_unique<const IntegerExpr>(100)),
    std::move(loop_body))));

  auto ae = make_unique<const VariableExpr>("x");
  auto ast = make_unique<const Program>(std::move(function_defs),
  std::move(statements), std::move(ae));

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

  // x should loop through, incrementing until it is 100
  EXPECT_EQ("100", output);
}
