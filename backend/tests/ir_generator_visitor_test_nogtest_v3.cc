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

// g++ -I ../../ -std=c++11 ir_generator_visitor_test_nogtest_v3.cc
#include <sstream>
#include <string>
// #include "gtest/gtest.h"
#include "abstract_syntax/abstract_syntax_tree_v3.h"
#include "utility/memory.h"
#include "backend/lowerer_v3.h"
#include "backend/asm_generator_v3.h"


using cs160::backend::IrGenVisitor;
using cs160::make_unique;
using cs160::abstract_syntax::version_3::AstVisitor;
using cs160::abstract_syntax::version_3::AddExpr;
using cs160::abstract_syntax::version_3::SubtractExpr;
using cs160::abstract_syntax::version_3::MultiplyExpr;
using cs160::abstract_syntax::version_3::DivideExpr;
using cs160::abstract_syntax::version_3::IntegerExpr;
using cs160::abstract_syntax::version_3::VariableExpr;
using cs160::abstract_syntax::version_3::Assignment;
using cs160::abstract_syntax::version_3::Program;
using cs160::abstract_syntax::version_3::Statement;

using cs160::backend::AsmProgram;



int main() {
  /* made up test

  a=2
  if ((a<5) && (i<9)){
    b=3*2
    c=9+b*a
    y=1
  } else {
    b=4
    while ((b+c<50 && c<10) || (i<100) && (a+b>50) || (i == 9 && b <=10)){
     i=i-1
     a=b+5
    }
    c=2
  }
  a+b

  */

  Statement::Block statements;

  Statement::Block truebody;
  truebody.push_back(std::move(make_unique<const Assignment>(
    make_unique<const VariableExpr>("b"),
    make_unique<const MultiplyExpr>(make_unique<const IntegerExpr>(3),
      make_unique<const IntegerExpr>(2)))));
  truebody.push_back(std::move(make_unique<const Assignment>(
    make_unique<const VariableExpr>("c"),
    make_unique<const AddExpr>(make_unique<const IntegerExpr>(9),
      make_unique<const MultiplyExpr>(make_unique<const VariableExpr>("b"),
        make_unique<const VariableExpr>("a"))))));
  truebody.push_back(std::move(make_unique<const Assignment>(
    make_unique<const VariableExpr>("y"),
    make_unique<const IntegerExpr>(1))));
  Statement::Block falsebody;
  falsebody.push_back(std::move(make_unique<const Assignment>(
    make_unique<const VariableExpr>("b"),
    make_unique<const IntegerExpr>(4))));

  Statement::Block loopbody;
  loopbody.push_back(std::move(make_unique<const Assignment>(
    make_unique<const VariableExpr>("i"),
    make_unique<const SubtractExpr>(make_unique<const VariableExpr>("i"),
      make_unique<const IntegerExpr>(1)))));
  loopbody.push_back(std::move(make_unique<const Assignment>(
    make_unique<const VariableExpr>("a"),
    make_unique<const SubtractExpr>(make_unique<const VariableExpr>("b"),
      make_unique<const IntegerExpr>(5)))));
  falsebody.push_back(std::move(make_unique<const Loop>(
    make_unique<const LogicalOrExpr>(
      make_unique<const LogicalOrExpr>(
        make_unique<const LogicalAndExpr>(
          make_unique<const LessThanExpr>(
            make_unique<const AddExpr>(
              make_unique<const VariableExpr>("b"),
              make_unique<const VariableExpr>("c")),
            make_unique<const IntegerExpr>(50)),
          make_unique<const LessThanExpr>(
            make_unique<const VariableExpr>("c"),
            make_unique<const IntegerExpr>(10))),
        make_unique<const LogicalAndExpr>(
          make_unique<const LessThanExpr>(
            make_unique<const VariableExpr>("i"),
            make_unique<const IntegerExpr>(100)),
          make_unique<const GreaterThanExpr>(
            make_unique<const VariableExpr>("b"),
            make_unique<const IntegerExpr>(50)))),
      make_unique<const LogicalAndExpr>(
        make_unique<const EqualToExpr>(
          make_unique<const VariableExpr>("i"),
          make_unique<const IntegerExpr>(9)),
        make_unique<const LessThanEqualToExpr>(
          make_unique<const VariableExpr>("b"),
          make_unique<const IntegerExpr>(10)))),
    std::move(loopbody))));
  falsebody.push_back(std::move(make_unique<const Assignment>(
    make_unique<const VariableExpr>("c"),
    make_unique<const IntegerExpr>(2))));

  statements.push_back(std::move(make_unique<const Assignment>(
    make_unique<const VariableExpr>("a"),
    make_unique<const IntegerExpr>(2))));
  statements.push_back(std::move(make_unique<const Conditional>(
    make_unique<const LogicalAndExpr>(
      make_unique<const LessThanExpr>(
        make_unique<const VariableExpr>("a"),
        make_unique<const IntegerExpr>(5)),
      make_unique<const LessThanExpr>(
        make_unique<const VariableExpr>("i"),
        make_unique<const IntegerExpr>(9))),
    std::move(truebody), std::move(falsebody))));



  auto ae = make_unique<const AddExpr>(
    make_unique<const VariableExpr>("a"),
    make_unique<const VariableExpr>("b"));

  auto ast = make_unique<const Program>(std::move(statements), std::move(ae));


  /*
  bob = 42
  if ((bob<100 && bob>0) || (bob =<100 && bob =>0)) {

  } else {

  }
  while (bob!=0) {
    bob=bob-1
  }
  (((12/3)-4)+(3*2))
  */


  /* ast 3 test from prof
  Statement::Block statements;

  statements.push_back(std::move(
    make_unique<const Assignment>(make_unique<const VariableExpr>("bob"),
      make_unique<const IntegerExpr>(42))));

  statements.push_back(std::move(make_unique<const Conditional>(
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

  Statement::Block body;
  body.push_back(std::move(make_unique<const Assignment>(
    make_unique<const VariableExpr>("bob"),
    make_unique<const SubtractExpr>(make_unique<const VariableExpr>("bob"),
      make_unique<const IntegerExpr>(1)))));

  statements.push_back(std::move(make_unique<const Loop>(
    make_unique<const LogicalNotExpr>(
      make_unique<const EqualToExpr>(make_unique<const VariableExpr>("bob"),
        make_unique<const IntegerExpr>(0))),
    std::move(body))));

  auto ae = make_unique<const AddExpr>(
    make_unique<const SubtractExpr>(
      make_unique<const DivideExpr>(make_unique<const IntegerExpr>(12),
        make_unique<const IntegerExpr>(3)),
      make_unique<const IntegerExpr>(4)),
    make_unique<const MultiplyExpr>(make_unique<const IntegerExpr>(3),
      make_unique<const IntegerExpr>(2)));

  auto ast = make_unique<const Program>(std::move(statements), std::move(ae));
  */

  IrGenVisitor irGen;
  ast->Visit(&irGen);
  irGen.PrintIR();
  std::cout << endl;
  AsmProgram testasm;
  testasm.IrToAsm(irGen.GetIR());
  std::cout << testasm.GetASMString();


  return 0;
}
