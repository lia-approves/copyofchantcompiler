#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <time.h>

#include "interpreter/interpreter.h"
#include "abstract_syntax/abstract_syntax.h"
#include "utility/memory.h"

using cs160::abstract_syntax::backend::AstNode;
using cs160::abstract_syntax::backend::BinaryOperatorExpr;
using cs160::abstract_syntax::backend::IntegerExpr;
using cs160::abstract_syntax::backend::AddExpr;
using cs160::abstract_syntax::backend::SubtractExpr;
using cs160::abstract_syntax::backend::MultiplyExpr;
using cs160::abstract_syntax::backend::DivideExpr;

using cs160::abstract_syntax::backend::AstVisitor;
using cs160::interpreter::InterpretVisitor;

using cs160::make_unique;

namespace cs160 {
namespace interpreter {

const int InterpretVisitor::GetOutput() const{
  return output_int;
}

void InterpretVisitor::VisitIntegerExpr(const IntegerExpr& exp){
  output_int = exp.value();
}

void InterpretVisitor::VisitAddExpr(const AddExpr& exp){
  exp.lhs().Visit(this);
  int lhs = output_int;
  exp.rhs().Visit(this);
  int rhs = output_int;
  output_int = lhs + rhs;
}

void InterpretVisitor::VisitSubtractExpr(const SubtractExpr& exp){
  exp.lhs().Visit(this);
  int lhs = output_int;
  exp.rhs().Visit(this);
  int rhs = output_int;
  output_int = lhs - rhs;
}

void InterpretVisitor::VisitMultiplyExpr(const MultiplyExpr& exp){
  exp.lhs().Visit(this);
  int lhs = output_int;
  exp.rhs().Visit(this);
  int rhs = output_int;
  output_int = lhs * rhs;
}

void InterpretVisitor::VisitDivideExpr(const DivideExpr & exp){
  exp.lhs().Visit(this);
  int lhs = output_int;
  exp.rhs().Visit(this);
  int rhs = output_int;
  if(rhs == 0){
    throw "ERROR: DIVISION BY ZERO";
  }
  output_int = lhs / rhs;
}

}  // namespace interpreter
}  // namespace cs160
