// Copyright msg for cpplint
#ifndef BACKEND_INTERPRETER_INTERPRETER_H_
#define BACKEND_INTERPRETER_INTERPRETER_H_

#include <sstream>
#include <string>

#include "abstract_syntax/abstract_syntax.h"

using cs160::abstract_syntax::backend::IntegerExpr;
using cs160::abstract_syntax::backend::BinaryOperatorExpr;
using cs160::abstract_syntax::backend::AddExpr;
using cs160::abstract_syntax::backend::SubtractExpr;
using cs160::abstract_syntax::backend::MultiplyExpr;
using cs160::abstract_syntax::backend::DivideExpr;
using cs160::abstract_syntax::backend::AstVisitor;

namespace cs160 {
namespace interpreter {

class InterpretVisitor : public AstVisitor {
 public:
  InterpretVisitor() {}
  ~InterpretVisitor() {}

  const int GetOutputInt() const;

  const std::string GetOutputString() const;

  void VisitIntegerExpr(const IntegerExpr& exp);

  void VisitBinaryOperatorExpr(const BinaryOperatorExpr& exp) {}

  void VisitAddExpr(const AddExpr& exp);

  void VisitSubtractExpr(const SubtractExpr& exp);

  void VisitMultiplyExpr(const MultiplyExpr& exp);

  void VisitDivideExpr(const DivideExpr& exp);

 private:
  int output_int;
  std::stringstream output_string;
};

}  // namespace interpreter
}  // namespace cs160
#endif  // BACKEND_INTERPRETER_INTERPRETER_H_
