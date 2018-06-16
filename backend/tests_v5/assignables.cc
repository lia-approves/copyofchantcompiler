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


using cs160::abstract_syntax::version_5::ArithmeticExpr;
using cs160::abstract_syntax::version_5::AddExpr;
using cs160::abstract_syntax::version_5::SubtractExpr;
using cs160::abstract_syntax::version_5::MultiplyExpr;
using cs160::abstract_syntax::version_5::DivideExpr;
using cs160::abstract_syntax::version_5::IntegerExpr;
using cs160::abstract_syntax::version_5::VariableExpr;
using cs160::abstract_syntax::version_5::Dereference;
using cs160::abstract_syntax::version_5::Statement;
using cs160::abstract_syntax::version_5::AssignmentFromArithExp;
using cs160::abstract_syntax::version_5::AssignmentFromNewTuple;
using cs160::abstract_syntax::version_5::FunctionCall;
using cs160::abstract_syntax::version_5::FunctionDef;
using cs160::abstract_syntax::version_5::Program;

using cs160::backend::AsmProgram;
using cs160::backend::IrGenVisitor;
using cs160::backend::AsmProgram;
using cs160::backend::ControlFlowGraph;
using cs160::backend::SSA;

using cs160::make_unique;

TEST(Assignment, OfVariable) {
  FunctionDef::Block function_defs;
  Statement::Block statements;

  // a = 12
  statements.push_back(std::move(make_unique<const AssignmentFromArithExp>(
      make_unique<const VariableExpr>("a"),
      make_unique<const IntegerExpr>(12))));

  // 12 + 30
  auto ae = make_unique<const AddExpr>(
    make_unique<const IntegerExpr>(12),
    make_unique<const IntegerExpr>(30));

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

  // 12 + 30 = 42
  // output should be 42
  EXPECT_EQ("42", output);
}

TEST(Assignment, OfDereference) {
  FunctionDef::Block function_defs;
  Statement::Block statements;

  // a = 12
  statements.push_back(std::move(make_unique<const AssignmentFromArithExp>(
      make_unique<const VariableExpr>("a"),
      make_unique<const IntegerExpr>(12))));

  // b = tuple(3)
  statements.push_back(std::move(make_unique<const AssignmentFromNewTuple>(
    make_unique<const VariableExpr>("b"),
    make_unique<const IntegerExpr>(3))));

  // b[2] = 5
  statements.push_back(std::move(make_unique<const AssignmentFromArithExp>(
    std::move(make_unique<const Dereference>(
      make_unique<const VariableExpr>("b"),
      make_unique<const IntegerExpr>(2))),
    make_unique<const IntegerExpr>(5))));

  // a + 30
  auto ae = make_unique<const AddExpr>(
    make_unique<const VariableExpr>("a"),
    make_unique<const IntegerExpr>(30));

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

  // a + 30
  // 12 + 30 = 42
  // output should be 42
  EXPECT_EQ("42", output);
}

TEST(Access, OfDereference) {
  FunctionDef::Block function_defs;
  Statement::Block statements;

  // b = tuple(3)
  statements.push_back(std::move(make_unique<const AssignmentFromNewTuple>(
    make_unique<const VariableExpr>("b"),
    make_unique<const IntegerExpr>(3))));

  // b[2] = 30
  statements.push_back(std::move(make_unique<const AssignmentFromArithExp>(
    std::move(make_unique<const Dereference>(
      make_unique<const VariableExpr>("b"),
      make_unique<const IntegerExpr>(2))),
    make_unique<const IntegerExpr>(30))));

  // 12 + b[2]
  auto ae = make_unique<const AddExpr>(
    make_unique<const IntegerExpr>(12),
    make_unique<const Dereference>(
      make_unique<const VariableExpr>("b"),
      make_unique<const IntegerExpr>(2)));

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

  // 12 + b[2]
  // 12 + 30 = 42
  // output should be 42
  EXPECT_EQ("42", output);
}

TEST(Assignment, OfDereferenceToDereference) {
  FunctionDef::Block function_defs;
  Statement::Block statements;

  // a = 12
  statements.push_back(std::move(make_unique<const AssignmentFromArithExp>(
      make_unique<const VariableExpr>("a"),
      make_unique<const IntegerExpr>(12))));

  // b = tuple(3)
  statements.push_back(std::move(make_unique<const AssignmentFromNewTuple>(
    make_unique<const VariableExpr>("b"),
    make_unique<const IntegerExpr>(3))));

  // b[2] = b[3]
  statements.push_back(std::move(make_unique<const AssignmentFromArithExp>(
    std::move(make_unique<const Dereference>(
      make_unique<const VariableExpr>("b"),
      make_unique<const IntegerExpr>(2))),
    std::move(make_unique<const Dereference>(
      make_unique<const VariableExpr>("b"),
      make_unique<const IntegerExpr>(3))))));

  // a + 30
  auto ae = make_unique<const AddExpr>(
    make_unique<const VariableExpr>("a"),
    make_unique<const IntegerExpr>(30));

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

  // a + 30
  // 12 + 30 = 42
  // output should be 42
  EXPECT_EQ("42", output);
}

TEST(Assignment, OfNestedDereference) {
  FunctionDef::Block function_defs;
  Statement::Block statements;

  // a = 12
  statements.push_back(std::move(make_unique<const AssignmentFromArithExp>(
      make_unique<const VariableExpr>("a"),
      make_unique<const IntegerExpr>(12))));

  // b = tuple(3)
  statements.push_back(std::move(make_unique<const AssignmentFromNewTuple>(
    make_unique<const VariableExpr>("b"),
    make_unique<const IntegerExpr>(3))));

  // b[2] = 3
  statements.push_back(std::move(make_unique<const AssignmentFromArithExp>(
    std::move(make_unique<const Dereference>(
      make_unique<const VariableExpr>("b"),
      make_unique<const IntegerExpr>(2))),
    std::move(make_unique<const IntegerExpr>(3)))));

  // b[b[2]] = 5
  // b[3] = 5
  statements.push_back(std::move(make_unique<const AssignmentFromArithExp>(
    std::move(make_unique<const Dereference>(
      make_unique<const VariableExpr>("b"),
      make_unique<const Dereference>(
        make_unique<const VariableExpr>("b"),
        make_unique<const IntegerExpr>(2)))),
    std::move(make_unique<const IntegerExpr>(5)))));

  // a + 30
  auto ae = make_unique<const AddExpr>(
    make_unique<const VariableExpr>("a"),
    make_unique<const IntegerExpr>(30));

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

  // a + 30
  // 12 + 30 = 42
  // output should be 42
  EXPECT_EQ("42", output);
}

TEST(Assignment, OfNestedDereference2) {
  FunctionDef::Block function_defs;
  Statement::Block statements;

  // a = 2
  statements.push_back(std::move(make_unique<const AssignmentFromArithExp>(
      make_unique<const VariableExpr>("a"),
      make_unique<const IntegerExpr>(2))));

  // b = tuple(3)
  statements.push_back(std::move(make_unique<const AssignmentFromNewTuple>(
    make_unique<const VariableExpr>("b"),
    make_unique<const IntegerExpr>(3))));

  // b[2] = 3
  statements.push_back(std::move(make_unique<const AssignmentFromArithExp>(
    std::move(make_unique<const Dereference>(
      make_unique<const VariableExpr>("b"),
      make_unique<const IntegerExpr>(2))),
    std::move(make_unique<const IntegerExpr>(3)))));

  // b[b[a]] = 12
  // b[b[2]] = 12
  // b[3] = 12
  statements.push_back(std::move(make_unique<const AssignmentFromArithExp>(
    std::move(make_unique<const Dereference>(
      make_unique<const VariableExpr>("b"),
      make_unique<const Dereference>(
        make_unique<const VariableExpr>("b"),
        make_unique<const VariableExpr>("a")))),
    std::move(make_unique<const IntegerExpr>(12)))));

  // b[3] + 30
  auto ae = make_unique<const AddExpr>(
    make_unique<const Dereference>(
      make_unique<const VariableExpr>("b"),
      make_unique<const IntegerExpr>(3)),
    make_unique<const IntegerExpr>(30));

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

  // b[3] + 30
  // 12 + 30 = 42
  EXPECT_EQ("42", output);
}


TEST(Create, Function) {
  Statement::Block foo_statements;

  // local_b = param_a + 5
  foo_statements.push_back(std::move(make_unique<const AssignmentFromArithExp>(
    make_unique<const VariableExpr>("local_b"),
    make_unique<const AddExpr>(
      make_unique<const VariableExpr>("param_a"),
      make_unique<const IntegerExpr>(5)))));

  // local_b + 5
  auto foo_retval = make_unique<const AddExpr>(
    make_unique<const VariableExpr>("local_b"),
    make_unique<const IntegerExpr>(5));

  auto foo_params = std::vector<std::unique_ptr<const VariableExpr>>();
  foo_params.push_back(std::move(make_unique<const VariableExpr>("param_a")));

  // foo (param_a) {
  //    local_b = param_a + 5
  //    return local_b + 5
  // }
  auto foo_def = make_unique<const FunctionDef>(
    "foo", std::move(foo_params),
    std::move(foo_statements),
    std::move(foo_retval));

  FunctionDef::Block function_defs;
  function_defs.push_back(std::move(foo_def));

  Statement::Block statements;

  // a = 12
  statements.push_back(std::move(make_unique<const AssignmentFromArithExp>(
      make_unique<const VariableExpr>("a"),
      make_unique<const IntegerExpr>(12))));

  // a + 30
  auto ae = make_unique<const AddExpr>(
    make_unique<const  VariableExpr>("a"),
    make_unique<const IntegerExpr>(30));

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

  // a + 30
  // 12 + 30 = 42
  // output should be 42
  EXPECT_EQ("42", output);
}

TEST(Call, Function) {
  Statement::Block foo_statements;

  // local_b = param_a + 5
  foo_statements.push_back(std::move(make_unique<const AssignmentFromArithExp>(
    make_unique<const VariableExpr>("local_b"),
    make_unique<const AddExpr>(
      make_unique<const VariableExpr>("param_a"),
      make_unique<const IntegerExpr>(5)))));

  auto foo_retval = make_unique<const IntegerExpr>(22);

  auto foo_params = std::vector<std::unique_ptr<const VariableExpr>>();
  foo_params.push_back(std::move(make_unique<const VariableExpr>("param_a")));


  // foo (param_a) {
  //    local_b = param_a + 5
  //    return 22
  // }
  auto foo_def = make_unique<const FunctionDef>(
    "foo", std::move(foo_params),
    std::move(foo_statements),
    std::move(foo_retval));

  FunctionDef::Block function_defs;
  function_defs.push_back(std::move(foo_def));

  Statement::Block statements;
  statements.push_back(std::move(make_unique<const AssignmentFromArithExp>(
      make_unique<const VariableExpr>("a"),
      make_unique<const IntegerExpr>(12))));

  auto arguments = std::vector<std::unique_ptr<const ArithmeticExpr>>();
  arguments.push_back(std::move(make_unique<const IntegerExpr>(12)));

  statements.push_back(std::move(make_unique<const FunctionCall>(
    make_unique<const VariableExpr>("foo_retval"),
    "foo",
    std::move(arguments))));

  auto ae = make_unique<const AddExpr>(
    make_unique<const VariableExpr>("foo_retval"),
    make_unique<const IntegerExpr>(20));

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

  EXPECT_EQ("42", output);
}

TEST(Call, FunctionTwice) {
  Statement::Block foo_statements;
  foo_statements.push_back(std::move(make_unique<const AssignmentFromArithExp>(
    make_unique<const VariableExpr>("local_b"),
    make_unique<const AddExpr>(
      make_unique<const VariableExpr>("param_a"),
      make_unique<const IntegerExpr>(5)))));

  auto foo_retval = make_unique<const AddExpr>(
    make_unique<const VariableExpr>("local_b"),
    make_unique<const IntegerExpr>(5));

  auto foo_params = std::vector<std::unique_ptr<const VariableExpr>>();
  foo_params.push_back(std::move(make_unique<const VariableExpr>("param_a")));

  // foo (param_a) {
  //    local_b = param_a + 5
  //    return local_b + 5
  // }
  auto foo_def = make_unique<const FunctionDef>(
    "foo", std::move(foo_params),
    std::move(foo_statements),
    std::move(foo_retval));

  FunctionDef::Block function_defs;
  function_defs.push_back(std::move(foo_def));

  Statement::Block statements;
  statements.push_back(std::move(make_unique<const AssignmentFromArithExp>(
      make_unique<const VariableExpr>("a"),
      make_unique<const IntegerExpr>(12))));
  statements.push_back(std::move(make_unique<const AssignmentFromArithExp>(
      make_unique<const VariableExpr>("B"),
      make_unique<const IntegerExpr>(12))));

  auto arguments = std::vector<std::unique_ptr<const ArithmeticExpr>>();
  arguments.push_back(std::move(make_unique<const IntegerExpr>(12)));

  statements.push_back(std::move(make_unique<const FunctionCall>(
    make_unique<const VariableExpr>("foo_retval"),
    "foo",
    std::move(arguments))));

  auto arguments2 = std::vector<std::unique_ptr<const ArithmeticExpr>>();
  arguments2.push_back(std::move(make_unique<const IntegerExpr>(22)));

  // foo_retval = foo(22)
  // should return 32
  statements.push_back(std::move(make_unique<const FunctionCall>(
    make_unique<const VariableExpr>("foo_retval"),
    "foo",
    std::move(arguments2))));

  // foo_retval + 20
  // 32 + 20 = 52
  auto ae = make_unique<const AddExpr>(
    make_unique<const VariableExpr>("foo_retval"),
    make_unique<const IntegerExpr>(20));

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

  EXPECT_EQ("52", output);
}
