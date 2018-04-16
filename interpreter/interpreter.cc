#include "interpreter/interpreter.h"

namespace cs160 {
namespace interpreter {

int InterpreterMain() { return 42; }

  void InterpretVisitor::VisitIntegerExpr(const IntegerExpr& exp) {
    output_ << exp.value();
    output_int = exp.value();
  }

  void InterpretVisitor::VisitAddExpr(const AddExpr& exp) {
    output_ << "(+ ";
    exp.lhs().Visit(const_cast<InterpretVisitor*>(this));
    output_ << " ";
    exp.rhs().Visit(const_cast<InterpretVisitor*>(this));
    output_ << ")";
  }

  void InterpretVisitor::VisitSubtractExpr(const SubtractExpr& exp) {
    output_ << "(- ";
    exp.lhs().Visit(const_cast<InterpretVisitor*>(this));
    output_ << " ";
    exp.rhs().Visit(const_cast<InterpretVisitor*>(this));
    output_ << ")";
  }

  void InterpretVisitor::VisitMultiplyExpr(const MultiplyExpr& exp) {
    output_ << "(* ";
    exp.lhs().Visit(const_cast<InterpretVisitor*>(this));
    output_ << " ";
    exp.rhs().Visit(const_cast<InterpretVisitor*>(this));
    output_ << ")";
  }

  void InterpretVisitor::VisitDivideExpr(const DivideExpr& exp) {
    output_ << "(/ ";
    exp.lhs().Visit(const_cast<InterpretVisitor*>(this));
    output_ << " ";
    exp.rhs().Visit(const_cast<InterpretVisitor*>(this));
    output_ << ")";
  }

    const int InterpretVisitor::GetOutput() const {
      return output_int;
    }

}  // namespace interpreter
}  // namespace cs160
