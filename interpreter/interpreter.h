
#ifndef INTERPRETER_INTERPRETER_H_
#define INTERPRETER_INTERPRETER_H_

#include <sstream>
#include <string>

#include "abstract_syntax/abstract_syntax.h"

using cs160::abstract_syntax::version_1::IntegerExpr;
using cs160::abstract_syntax::version_1::BinaryOperatorExpr;
using cs160::abstract_syntax::version_1::AddExpr;
using cs160::abstract_syntax::version_1::SubtractExpr;
using cs160::abstract_syntax::version_1::MultiplyExpr;
using cs160::abstract_syntax::version_1::DivideExpr;
using cs160::abstract_syntax::version_1::AstVisitor;

namespace cs160 {
namespace interpreter {

class InterpretVisitor : public AstVisitor {
 public:
  InterpretVisitor() {}
  ~InterpretVisitor() {}

  const std::string GetOutput() const { return output_.str(); }

  void VisitIntegerExpr(const IntegerExpr& exp) { output_ << exp.value(); }

  void VisitBinaryOperatorExpr(const BinaryOperatorExpr& exp) {}

  void VisitAddExpr(const AddExpr& exp) {
    output_ << "(+ ";
    exp.lhs().Visit(const_cast<InterpretVisitor*>(this));
    output_ << " ";
    exp.rhs().Visit(const_cast<InterpretVisitor*>(this));
    output_ << ")";
  }

  void VisitSubtractExpr(const SubtractExpr& exp) {
    output_ << "(- ";
    exp.lhs().Visit(const_cast<InterpretVisitor*>(this));
    output_ << " ";
    exp.rhs().Visit(const_cast<InterpretVisitor*>(this));
    output_ << ")";
  }

  void VisitMultiplyExpr(const MultiplyExpr& exp) {
    output_ << "(* ";
    exp.lhs().Visit(const_cast<InterpretVisitor*>(this));
    output_ << " ";
    exp.rhs().Visit(const_cast<InterpretVisitor*>(this));
    output_ << ")";
  }

  void VisitDivideExpr(const DivideExpr& exp) {
    output_ << "(/ ";
    exp.lhs().Visit(const_cast<InterpretVisitor*>(this));
    output_ << " ";
    exp.rhs().Visit(const_cast<InterpretVisitor*>(this));
    output_ << ")";
  }

 private:
  std::stringstream output_;
};

}  // namespace interpreter
}  // namespace cs160
#endif  // INTERPRETER_INTERPRETER_H_
