/*
MIT License

Copyright (c) 2018, Team-Chant

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include <sstream>
#include <string>
//#include "gtest/gtest.h"
#include "abstract_syntax/abstract_syntax_tree_v5.h"
#include "utility/memory.h"
#include "backend/lowerer_v5.h"
#include "backend/asm_generator_v5.h"
#include "backend/SSA.h" 

using cs160::backend::IrGenVisitor;
using cs160::make_unique;
using cs160::abstract_syntax::version_5::AstVisitor;
using cs160::abstract_syntax::version_5::ArithmeticExpr;
using cs160::abstract_syntax::version_5::AddExpr;
using cs160::abstract_syntax::version_5::SubtractExpr;
using cs160::abstract_syntax::version_5::MultiplyExpr;
using cs160::abstract_syntax::version_5::DivideExpr;
using cs160::abstract_syntax::version_5::IntegerExpr;
using cs160::abstract_syntax::version_5::VariableExpr;
using cs160::abstract_syntax::version_5::LessThanExpr;
using cs160::abstract_syntax::version_5::LessThanEqualToExpr;
using cs160::abstract_syntax::version_5::GreaterThanExpr;
using cs160::abstract_syntax::version_5::GreaterThanEqualToExpr;
using cs160::abstract_syntax::version_5::EqualToExpr;
using cs160::abstract_syntax::version_5::LogicalAndExpr;
using cs160::abstract_syntax::version_5::LogicalOrExpr;
using cs160::abstract_syntax::version_5::LogicalNotExpr;
using cs160::abstract_syntax::version_5::Statement;
using cs160::abstract_syntax::version_5::Assignment;
using cs160::abstract_syntax::version_5::Conditional;
using cs160::abstract_syntax::version_5::Loop;
using cs160::abstract_syntax::version_5::FunctionCall;
using cs160::abstract_syntax::version_5::FunctionDef;
using cs160::abstract_syntax::version_5::Program;


using cs160::backend::AsmProgram;
using cs160::backend::ControlFlowGraph;
using cs160::backend::SSA;



int main() {
    Statement::Block foo_statements;
    FunctionDef::Block function_defs;

    Statement::Block true_branch;
    Statement::Block false_branch;
    true_branch.push_back(std::move(make_unique<const AssignmentFromArithExp>(make_unique<const VariableExpr>("a"), make_unique<const IntegerExpr>(4))));
    false_branch.push_back(std::move(make_unique<const AssignmentFromArithExp>(make_unique<const VariableExpr>("b"), make_unique<const IntegerExpr>(5))));
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
    int bob = 50;
    if (((bob < 100) && (bob > 100)) || ((bob <= 100) && (bob >= 0)));

    Statement::Block loop_body;
    loop_body.push_back(std::move(make_unique<const AssignmentFromArithExp>(
      make_unique<const VariableExpr>("bob"),
      make_unique<const SubtractExpr>(make_unique<const VariableExpr>("bob"),
        make_unique<const IntegerExpr>(1)))));

    foo_statements.push_back(std::move(make_unique<const Loop>(
      make_unique<const LogicalNotExpr>(
        make_unique<const EqualToExpr>(make_unique<const VariableExpr>("bob"),
          make_unique<const IntegerExpr>(0))),
      std::move(loop_body))));
    
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

    Statement::Block loop2;

    loop2.push_back(std::move(make_unique<const AssignmentFromArithExp>(
      make_unique<const VariableExpr>("x"),
      make_unique<const AddExpr>(make_unique<const VariableExpr>("x"),
        make_unique<const IntegerExpr>(1)))));
    loop2.push_back(std::move(make_unique<const AssignmentFromArithExp>(
      make_unique<const VariableExpr>("y"),
      make_unique<const AddExpr>(make_unique<const VariableExpr>("y"),
        make_unique<const VariableExpr>("x")))));

    loop2.push_back(std::move(make_unique<const AssignmentFromArithExp>(
      make_unique<const VariableExpr>("z"),
      make_unique<const AddExpr>(make_unique<const IntegerExpr>(1),
        make_unique<const IntegerExpr>(1)))));

    statements.push_back(std::move(make_unique<const AssignmentFromArithExp>(make_unique<const VariableExpr>("x"), make_unique<const IntegerExpr>(1))));
    statements.push_back(std::move(make_unique<const AssignmentFromArithExp>(make_unique<const VariableExpr>("y"), make_unique<const IntegerExpr>(1))));


    statements.push_back(std::move(make_unique<const Loop>(
      make_unique<const LessThanExpr>(make_unique<const VariableExpr>("x"), make_unique<const IntegerExpr>(100)),
      std::move(loop2))));

    statements.push_back(std::move(make_unique<const AssignmentFromNewTuple>(
      make_unique<const VariableExpr>("x"),
      make_unique<const IntegerExpr>(2))));

    statements.push_back(std::move(make_unique<const AssignmentFromArithExp>(
      make_unique<const Dereference>(make_unique<const VariableExpr>("x"),
        make_unique<const IntegerExpr>(1)),
      make_unique<const IntegerExpr>(13))));

    auto arguments = std::vector<std::unique_ptr<const ArithmeticExpr>>();
    arguments.push_back(std::move(
      make_unique<const Dereference>(make_unique<const VariableExpr>("x"),
        make_unique<const IntegerExpr>(1))));

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
    //x[x[11]-x[14]] = (x[x[0] * x[1]][x[x[8]] + x[5]]) / (x[9])


    auto ae =
      make_unique<const Dereference>(
        make_unique<const VariableExpr>("x"),
        make_unique<const IntegerExpr>(7));
  
    // return x[7]
    auto ast = make_unique<const Program>(std::move(function_defs),
      std::move(statements), std::move(ae));


    IrGenVisitor irGen;
    ast->Visit(&irGen);
    //irGen.PrintIR();
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
    std::cout << testasm.GetASMString();

  return 0;
}
