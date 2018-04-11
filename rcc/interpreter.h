
#ifndef RCC_INTERPRETER_H_
#define RCC_INTERPRETER_H_

#include <sstream>
#include <string>

#include "abstract_syntax_tree.h"

using cs160::abstract_syntax::IntegerExpr;
using cs160::abstract_syntax::BinaryOperatorExpr;
using cs160::abstract_syntax::AddExpr;
using cs160::abstract_syntax::SubtractExpr;
using cs160::abstract_syntax::MultiplyExpr;
using cs160::abstract_syntax::DivideExpr;
using cs160::abstract_syntax::AstVisitor;

namespace cs160 {
namespace abstract_syntax {

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

}  // namespace abstract_syntax
}  // namespace cs160

#endif  // ABSTRACT_SYNTAX_INTERPRET_VISITOR_H_
