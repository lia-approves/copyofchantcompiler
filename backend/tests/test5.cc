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




int main() {
  Statement::Block statements;
  FunctionDef::Block function_defs;
  statements.push_back(std::move(make_unique<const AssignmentFromArithExp>(make_unique<const VariableExpr>("a"), make_unique<const IntegerExpr>(4))));
  statements.push_back(std::move(make_unique<const AssignmentFromArithExp>(make_unique<const VariableExpr>("b"), make_unique<const IntegerExpr>(5))));
  Statement::Block true_branch;
  true_branch.push_back(std::move(make_unique<const AssignmentFromArithExp>(make_unique<const VariableExpr>("a"), make_unique<const IntegerExpr>(6))));
  Statement::Block false_branch;
  false_branch.push_back(std::move(make_unique<const AssignmentFromArithExp>(make_unique<const VariableExpr>("a"), make_unique<const IntegerExpr>(7))));
  statements.push_back(std::move(make_unique<const AssignmentFromArithExp>(make_unique<const VariableExpr>("bob"), make_unique<const IntegerExpr>(50))));
  statements.push_back(std::move(make_unique<const Conditional>(
      make_unique<const LessThanExpr>(
        make_unique<const VariableExpr>("bob"),
        make_unique<const IntegerExpr>(100)),
    std::move(true_branch), std::move(false_branch))));
  auto ae = make_unique<const VariableExpr>("a");
  auto ast = make_unique<const Program>(std::move(function_defs), std::move(statements), std::move(ae));

  // a = 4
  // b = 5
  // if (4<3) a = 6
  // else     a = 7
  // print a

  IrGenVisitor irGen;
  ast->Visit(&irGen);
  ControlFlowGraph cfg = ControlFlowGraph(irGen.GetIR());
  cfg.CreateCFG();
  cfg.PrintGraph();
  //irGen.PrintIR();
  //std::cout << endl;
  //AsmProgram testasm;
  //testasm.IrToAsm(&irGen);
  //std::cout << testasm.GetASMString();
  return 0;
}
