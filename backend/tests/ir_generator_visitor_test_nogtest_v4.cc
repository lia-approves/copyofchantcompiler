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
#include "abstract_syntax/abstract_syntax_tree_v4.h"
#include "utility/memory.h"
#include "backend/lowerer_v4.h"
#include "backend/asm_generator_v4.h"


using cs160::backend::IrGenVisitor;
using cs160::make_unique;
using cs160::abstract_syntax::version_4::AstVisitor;
using cs160::abstract_syntax::version_4::ArithmeticExpr;
using cs160::abstract_syntax::version_4::AddExpr;
using cs160::abstract_syntax::version_4::SubtractExpr;
using cs160::abstract_syntax::version_4::MultiplyExpr;
using cs160::abstract_syntax::version_4::DivideExpr;
using cs160::abstract_syntax::version_4::IntegerExpr;
using cs160::abstract_syntax::version_4::VariableExpr;
using cs160::abstract_syntax::version_4::LessThanExpr;
using cs160::abstract_syntax::version_4::LessThanEqualToExpr;
using cs160::abstract_syntax::version_4::GreaterThanExpr;
using cs160::abstract_syntax::version_4::GreaterThanEqualToExpr;
using cs160::abstract_syntax::version_4::EqualToExpr;
using cs160::abstract_syntax::version_4::LogicalAndExpr;
using cs160::abstract_syntax::version_4::LogicalOrExpr;
using cs160::abstract_syntax::version_4::LogicalNotExpr;
using cs160::abstract_syntax::version_4::Statement;
using cs160::abstract_syntax::version_4::Assignment;
using cs160::abstract_syntax::version_4::Conditional;
using cs160::abstract_syntax::version_4::Loop;
using cs160::abstract_syntax::version_4::FunctionCall;
using cs160::abstract_syntax::version_4::FunctionDef;
using cs160::abstract_syntax::version_4::Program;


using cs160::backend::AsmProgram;



int main() {
  /*
  Statement::Block foo_statements;

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
    Statement::Block(), Statement::Block())));

  Statement::Block loop_body;
  loop_body.push_back(std::move(make_unique<const Assignment>(
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

  FunctionDef::Block function_defs;
  function_defs.push_back(std::move(foo_def));

  auto arguments = std::vector<std::unique_ptr<const ArithmeticExpr>>();
  arguments.push_back(std::move(make_unique<const IntegerExpr>(42)));

  Statement::Block statements;

  statements.push_back(std::move(make_unique<const FunctionCall>(
    make_unique<const VariableExpr>("foo_retval"), "foo",
    std::move(arguments))));

  auto ae = make_unique<const VariableExpr>("foo_retval");

  auto ast = make_unique<const Program>(std::move(function_defs),
    std::move(statements), std::move(ae));
    

  /*

  
  Statement::Block foo_statements;

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
    Statement::Block(), Statement::Block())));

  Statement::Block loop_body;
  loop_body.push_back(std::move(make_unique<const Assignment>(
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

  FunctionDef::Block function_defs;
  function_defs.push_back(std::move(foo_def));

  auto arguments = std::vector<std::unique_ptr<const ArithmeticExpr>>();
  arguments.push_back(std::move(make_unique<const IntegerExpr>(42)));

  Statement::Block statements;

  statements.push_back(std::move(make_unique<const FunctionCall>(
    make_unique<const VariableExpr>("foo_retval"), "foo",
    std::move(arguments))));

  auto ae = make_unique<const VariableExpr>("foo_retval");

  auto ast = make_unique<const Program>(std::move(function_defs),
    std::move(statements), std::move(ae));*/

/*
Statement::Block statements;
statements.push_back(std::move(make_unique<const Assignment>(
  make_unique<const VariableExpr>("x"), make_unique<const IntegerExpr>(4))));
auto ae = make_unique<const AddExpr>(make_unique<const IntegerExpr>(3),
  make_unique<const VariableExpr>("x"));
FunctionDef::Block function_defs;

auto ast = make_unique<const Program>(std::move(function_defs),
  std::move(statements), std::move(ae));*/
Statement::Block foo_statements;

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
  Statement::Block(), Statement::Block())));

Statement::Block loop_body;
loop_body.push_back(std::move(make_unique<const Assignment>(
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

FunctionDef::Block function_defs;
function_defs.push_back(std::move(foo_def));

auto arguments = std::vector<std::unique_ptr<const ArithmeticExpr>>();
arguments.push_back(std::move(make_unique<const MultiplyExpr>(make_unique<const IntegerExpr>(3),

  make_unique<const IntegerExpr>(2))));
arguments.push_back(std::move(make_unique<const MultiplyExpr>(make_unique<const IntegerExpr>(3),

  make_unique<const IntegerExpr>(2))));

Statement::Block statements;

statements.push_back(std::move(make_unique<const FunctionCall>(
  make_unique<const VariableExpr>("foo_retval"), "foo",
  std::move(arguments))));

auto ae = make_unique<const VariableExpr>("foo_retval");

auto ast = make_unique<const Program>(std::move(function_defs),
  std::move(statements), std::move(ae));


/*    function definition:
def foo(bob,jim,mike) {
a=45
bob = bob + 8
h=45
j=45
mike=45
ab=45
return bob + h + jim*mike
}
//main function:
y=9
x=1
foo_retval=foo(17,17,17)
12+foo_retval
*/
  IrGenVisitor irGen;
  ast->Visit(&irGen);
  irGen.PrintIR();
  std::cout << endl;
  AsmProgram testasm;
  testasm.IrToAsm(&irGen);
  std::cout << testasm.GetASMString();
  return 0;
}