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

using cs160::backend::AsmProgram;
using cs160::backend::IrGenVisitor;
using cs160::backend::AsmProgram;
using cs160::backend::ControlFlowGraph;
using cs160::backend::SSA;

using cs160::make_unique;

TEST(AE, NestedTuples) {
  Statement::Block foo_statements;
  FunctionDef::Block function_defs;

  Statement::Block true_branch;
  Statement::Block false_branch;

  // a = 4
  true_branch.push_back(std::move(make_unique<const AssignmentFromArithExp>(
    make_unique<const VariableExpr>("a"), make_unique<const IntegerExpr>(4))));

  // b = 5
  false_branch.push_back(std::move(make_unique<const AssignmentFromArithExp>(
    make_unique<const VariableExpr>("b"), make_unique<const IntegerExpr>(5))));

  // if ( (bob < 100 and bob > 0) or (bob <= 100 and bob >= 0) )
  //     true_branch
  // else
  //     false_branch
  foo_statements.push_back(std::move(make_unique<const Conditional>(
    make_unique<const LogicalOrExpr>(
      make_unique<const LogicalAndExpr>(
        make_unique<const LessThanExpr>(
          make_unique<const VariableExpr>("bob"),
          make_unique<const IntegerExpr>(100)),
        make_unique<const GreaterThanExpr>(
          make_unique<const VariableExpr>("bob"),
          make_unique<const IntegerExpr>(0))),
      make_unique<const LogicalAndExpr>(
        make_unique<const LessThanEqualToExpr>(
          make_unique<const VariableExpr>("bob"),
          make_unique<const IntegerExpr>(100)),
        make_unique<const GreaterThanEqualToExpr>(
          make_unique<const VariableExpr>("bob"),
          make_unique<const IntegerExpr>(0)))),
    std::move(true_branch), std::move(false_branch))));

  Statement::Block loop_body;

  // bob = bob - 1
  loop_body.push_back(std::move(make_unique<const AssignmentFromArithExp>(
    make_unique<const VariableExpr>("bob"),
    make_unique<const SubtractExpr>(make_unique<const VariableExpr>("bob"),
      make_unique<const IntegerExpr>(1)))));

  // loop while !(bob == 0)
  //     bob = bob - 1
  foo_statements.push_back(std::move(make_unique<const Loop>(
    make_unique<const LogicalNotExpr>(
      make_unique<const EqualToExpr>(make_unique<const VariableExpr>("bob"),
        make_unique<const IntegerExpr>(0))),
    std::move(loop_body))));

  // ( 12/3 - 4 ) + ( 3 * 2 )
  // 0 + 6 = 6
  auto foo_retval = make_unique<const AddExpr>(
    make_unique<const SubtractExpr>(
      make_unique<const DivideExpr>(make_unique<const IntegerExpr>(12),
        make_unique<const IntegerExpr>(3)),
      make_unique<const IntegerExpr>(4)),
    make_unique<const MultiplyExpr>(make_unique<const IntegerExpr>(3),
      make_unique<const IntegerExpr>(2)));

  auto foo_params = std::vector<std::unique_ptr<const VariableExpr>>();
  foo_params.push_back(std::move(make_unique<const VariableExpr>("bob")));

  auto foo_def = make_unique<const FunctionDef>("foo", std::move(foo_params),
    std::move(foo_statements),
    std::move(foo_retval));

  function_defs.push_back(std::move(foo_def));

  Statement::Block statements;

  // x = tuple(2)
  statements.push_back(std::move(make_unique<const AssignmentFromNewTuple>(
    make_unique<const VariableExpr>("x"),
    make_unique<const IntegerExpr>(2))));

  // x[1] = 13
  statements.push_back(std::move(make_unique<const AssignmentFromArithExp>(
    make_unique<const Dereference>(make_unique<const VariableExpr>("x"),
      make_unique<const IntegerExpr>(1)),
    make_unique<const IntegerExpr>(13))));

  auto arguments = std::vector<std::unique_ptr<const ArithmeticExpr>>();
  arguments.push_back(std::move(
    make_unique<const Dereference>(make_unique<const VariableExpr>("x"),
      make_unique<const IntegerExpr>(1))));

  // foo_retval = foo(x[1])
  // foo_retval = foo(13)
  // foo_retval = 6
  statements.push_back(std::move(make_unique<const FunctionCall>(
    make_unique<const VariableExpr>("foo_retval"), "foo",
    std::move(arguments))));

  // tuples testing begin
  statements.push_back(std::move(
    make_unique<const AssignmentFromNewTuple>(
      make_unique<const VariableExpr>("x"),
      make_unique<const IntegerExpr>(20))));
  // x = newTuple[20]
  statements.push_back(std::move(
    make_unique<const AssignmentFromArithExp>(
      make_unique<const Dereference>(
        make_unique<const VariableExpr>("x"),
        make_unique<const IntegerExpr>(0)),
      make_unique<const IntegerExpr>(2))));
  // x[0] = 2
  statements.push_back(std::move(
    make_unique<const AssignmentFromArithExp>(
      make_unique<const Dereference>(
        make_unique<const VariableExpr>("x"),
        make_unique<const IntegerExpr>(1)),
      make_unique<const IntegerExpr>(3))));
  // x[1] = 3
  statements.push_back(std::move(
    make_unique<const AssignmentFromArithExp>(
      make_unique<const Dereference>(
        make_unique<const VariableExpr>("x"),
        make_unique<const IntegerExpr>(4)),
      make_unique<const IntegerExpr>(3))));
  // x[4] = 3
  statements.push_back(std::move(
    make_unique<const AssignmentFromArithExp>(
      make_unique<const Dereference>(
        make_unique<const VariableExpr>("x"),
        make_unique<const IntegerExpr>(5)),
      make_unique<const IntegerExpr>(1))));
  // x[5] = 1
  statements.push_back(std::move(
    make_unique<const AssignmentFromNewTuple>(
      make_unique<const Dereference>(
        make_unique<const VariableExpr>("x"),
        make_unique<const IntegerExpr>(6)),
      make_unique<const IntegerExpr>(5))));
  // x[6] = newTuple[5]
  statements.push_back(std::move(
    make_unique<const AssignmentFromArithExp>(
      make_unique<const Dereference>(
        make_unique<const Dereference>(
          make_unique<const VariableExpr>("x"),
          make_unique<const IntegerExpr>(6)),
        make_unique<const IntegerExpr>(4)),
      make_unique<const IntegerExpr>(14))));
  // x[6][4] = 14
  statements.push_back(std::move(
    make_unique<const AssignmentFromArithExp>(
      make_unique<const Dereference>(
        make_unique<const VariableExpr>("x"),
        make_unique<const IntegerExpr>(9)),
      make_unique<const IntegerExpr>(2))));
  // x[9] = 2
  statements.push_back(std::move(
    make_unique<const AssignmentFromArithExp>(
      make_unique<const Dereference>(
        make_unique<const VariableExpr>("x"),
        make_unique<const IntegerExpr>(8)),
      make_unique<const IntegerExpr>(4))));
  // x[8] = 4

  statements.push_back(std::move(
    make_unique<const AssignmentFromArithExp>(
      make_unique<const Dereference>(
        make_unique<const VariableExpr>("x"),
        make_unique<const IntegerExpr>(11)),
      make_unique<const IntegerExpr>(22))));
  // x[11]=22
  statements.push_back(std::move(
    make_unique<const AssignmentFromArithExp>(
      make_unique<const Dereference>(
        make_unique<const VariableExpr>("x"),
        make_unique<const IntegerExpr>(14)),
      make_unique<const IntegerExpr>(15))));
  // x[14]=15

  statements.push_back(std::move(
    make_unique<const AssignmentFromArithExp>(
      make_unique<const Dereference>(
        make_unique<const VariableExpr>("x"),
        make_unique<const SubtractExpr>(
          make_unique<const Dereference>(
            make_unique<const VariableExpr>("x"),
            make_unique<const IntegerExpr>(11)),
          make_unique<const Dereference>(
            make_unique<const VariableExpr>("x"),
            make_unique<const IntegerExpr>(14)))),
      make_unique<const DivideExpr>(
        make_unique<const Dereference>(
          make_unique<const Dereference>(
            make_unique<const VariableExpr>("x"),
            make_unique<const MultiplyExpr>(
              make_unique<const Dereference>(
                make_unique<const VariableExpr>("x"),
                make_unique<const IntegerExpr>(0)),
              make_unique<const Dereference>(
                make_unique<const VariableExpr>("x"),
                make_unique<const IntegerExpr>(1)))),
          make_unique<const AddExpr>(
            make_unique<const Dereference>(
              make_unique<const VariableExpr>("x"),
              make_unique<const Dereference>(
                make_unique<const VariableExpr>("x"),
                make_unique<const IntegerExpr>(8))),
            make_unique<const Dereference>(
              make_unique<const VariableExpr>("x"),
              make_unique<const IntegerExpr>(5)))),
        make_unique<const Dereference>(
          make_unique<const VariableExpr>("x"),
          make_unique<const IntegerExpr>(9))))));
  // x[x[11]-x[14]] = {(x[ x[0]*x[1] ])[x[x[8]] + x[5]]} / x[9]
  // x[7] = {(x[ 2 * 3 ])[ x[ 4 ] + 1 ]} / 2
  // x[7] = {(tuple(5))[ 3 + 1 ]} / 2
  // x[7] = {(tuple(5))[ 3 + 1 ]} / 2
  // x[7] = x[6][4] / 2
  // x[7] = 14 / 2
  // x[7] = 7
  auto ae =
    make_unique<const Dereference>(
      make_unique<const VariableExpr>("x"),
      make_unique<const IntegerExpr>(7));

  // return x[7]
  // should be 7
  auto ast = make_unique<const Program>(std::move(function_defs),
    std::move(statements), std::move(ae));

  // generate intermediate representation
  IrGenVisitor irGen;
  ast->Visit(&irGen);

  // create control flow graph
  ControlFlowGraph cfg = ControlFlowGraph(irGen.GetIR());
  cfg.CreateCFG();
  cfg.PrintGraph();
  SSA ssatest = SSA(irGen.GetIR(), cfg.CFG());
  ssatest.GenerateDomination();
  ssatest.PrintDominators();

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

  EXPECT_EQ("7", output);
}
