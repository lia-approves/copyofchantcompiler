// Copyright msg for cpplint

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <sstream>
#include <string>

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

const int InterpretVisitor::GetOutputInt() const {
  return output_int;
}

const std::string InterpretVisitor::GetOutputString() const {
  return output_string.str();
}

void InterpretVisitor::VisitIntegerExpr(const IntegerExpr& exp) {
  output_int = exp.value();
  output_string << output_int;
}

void InterpretVisitor::VisitAddExpr(const AddExpr& exp) {
  output_string << "( + ";
  exp.lhs().Visit(this);
  int lhs = output_int;
  output_string << " ";
  exp.rhs().Visit(this);
  int rhs = output_int;
  output_int = lhs + rhs;
  output_string << " )";
}

void InterpretVisitor::VisitSubtractExpr(const SubtractExpr& exp) {
  output_string << "( - ";
  exp.lhs().Visit(this);
  int lhs = output_int;
  output_string << " ";
  exp.rhs().Visit(this);
  int rhs = output_int;
  output_int = lhs - rhs;
  output_string << " )";
}

void InterpretVisitor::VisitMultiplyExpr(const MultiplyExpr& exp) {
  output_string << "( * ";
  exp.lhs().Visit(this);
  int lhs = output_int;
  output_string << " ";
  exp.rhs().Visit(this);
  int rhs = output_int;
  output_int = lhs * rhs;
  output_string << " )";
}

void InterpretVisitor::VisitDivideExpr(const DivideExpr & exp) {
  output_string << "( / ";
  exp.lhs().Visit(this);
  int lhs = output_int;
  output_string << " ";
  exp.rhs().Visit(this);
  int rhs = output_int;
  if (rhs == 0) {
    throw "ERROR: DIVISION BY ZERO";
    std::cerr << "ERROR: DIVISION BY ZERO" << std::endl;
  }
  output_int = lhs / rhs;
  output_string << " )";
}

}  // namespace interpreter
}  // namespace cs160
