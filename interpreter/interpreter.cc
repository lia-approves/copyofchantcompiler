#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <time.h>

#include "interpreter/interpreter.h"
//#include "abstract_syntax/"
#include "abstract_syntax/abstract_syntax.h"
//#include "abstract_syntax/print_visitor_v1.h"

using cs160::abstract_syntax::backend::AstNode;
using cs160::abstract_syntax::backend::BinaryOperatorExpr;
using cs160::abstract_syntax::backend::IntegerExpr;
using cs160::abstract_syntax::backend::AddExpr;
using cs160::abstract_syntax::backend::SubtractExpr;
using cs160::abstract_syntax::backend::MultiplyExpr;
using cs160::abstract_syntax::backend::DivideExpr;

using cs160::abstract_syntax::backend::AstVisitor;
//using cs160::abstract_syntax::version_1::PrintVisitor;
using cs160::interpreter::InterpretVisitor;

using cs160::make_unique;

namespace cs160 {
namespace interpreter {

std::unique_ptr<const AstNode> makeRandomAst();
std::unique_ptr<const AstNode> makeRandomAst(const double probNodeIsBinOp);
std::unique_ptr<const BinaryOperatorExpr> makeRandomBinOp(std::unique_ptr<const AstNode> lhs, std::unique_ptr<const AstNode> rhs);

int InterpreterMain() {
  InterpretVisitor interpreter_;
  auto randomAst_ = makeRandomAst();
  randomAst_->Visit(&interpreter_);
  std::cout << std::endl;
  std::cout << "Evaluated input: " << interpreter_.GetOutput();

  return 0;
}

const int InterpretVisitor::GetOutput() const{
  return output_int;
}

void InterpretVisitor::VisitIntegerExpr(const IntegerExpr& exp){
  output_ << exp.value();
  output_int = exp.value();
}

void InterpretVisitor::VisitAddExpr(const AddExpr& exp){
  output_ << "(+ ";
  exp.lhs().Visit(this);
  int lhs = output_int;
  output_ << " ";
  exp.rhs().Visit(this);
  int rhs = output_int;
  output_ << ")";
  output_int = lhs + rhs;
}

void InterpretVisitor::VisitSubtractExpr(const SubtractExpr& exp){
  output_ << "(- ";
  exp.lhs().Visit(this);
  int lhs = output_int;
  output_ << " ";
  exp.rhs().Visit(this);
  int rhs = output_int;
  output_ << ")";
  output_int = lhs - rhs;
}

void InterpretVisitor::VisitMultiplyExpr(const MultiplyExpr& exp){
  output_ << "(* ";
  exp.lhs().Visit(this);
  int lhs = output_int;
  output_ << " ";
  exp.rhs().Visit(this);
  int rhs = output_int;
  output_ << ")";
  output_int = lhs * rhs;
}

void InterpretVisitor::VisitDivideExpr(const DivideExpr & exp){
  output_ << "(/ ";
  exp.lhs().Visit(this);
  int lhs = output_int;
  output_ << " ";
  exp.rhs().Visit(this);
  int rhs = output_int;
  output_ << ")";
  if(rhs == 0){
    throw "ERROR: DIVISION BY ZERO";
  }
  output_int = lhs / rhs;
}

std::unique_ptr<const AstNode> makeRandomAst(){
  const double probNodeIsBinOp = 0.7;
  srand(time(NULL));

  int whichBinOp = rand() % 4;
  switch(whichBinOp){
    case 0:
      return std::move(make_unique<const AddExpr>(makeRandomAst(probNodeIsBinOp), makeRandomAst(probNodeIsBinOp)));
    case 1:
      return std::move(make_unique<const SubtractExpr>(makeRandomAst(probNodeIsBinOp), makeRandomAst(probNodeIsBinOp)));
    case 2:
      return std::move(make_unique<const MultiplyExpr>(makeRandomAst(probNodeIsBinOp), makeRandomAst(probNodeIsBinOp)));
    case 3:
      return std::move(make_unique<const DivideExpr>(makeRandomAst(probNodeIsBinOp), makeRandomAst(probNodeIsBinOp)));
  }
}

std::unique_ptr<const AstNode> makeRandomAst(const double probNodeIsBinOp){
  double isIntExpr = (rand() % 100) / 100;

  if(isIntExpr > probNodeIsBinOp){
    return std::move(make_unique<IntegerExpr>(rand() % 100));
  }else{
    return std::move(makeRandomBinOp(makeRandomAst(probNodeIsBinOp), makeRandomAst(probNodeIsBinOp)));
  }
}

std::unique_ptr<const BinaryOperatorExpr> makeRandomBinOp(std::unique_ptr<const AstNode> lhs, std::unique_ptr<const AstNode> rhs){
  int whichBinOp = rand() % 4;
  switch(whichBinOp){
    case 0:
      return std::move(make_unique<const AddExpr>(lhs, rhs));
    case 1:
      return std::move(make_unique<const SubtractExpr>(lhs, rhs));
    case 2:
      return std::move(make_unique<const MultiplyExpr>(lhs, rhs));
    case 3:
      return std::move(make_unique<const DivideExpr>(lhs, rhs));
  }
}

}  // namespace interpreter
}  // namespace cs160
