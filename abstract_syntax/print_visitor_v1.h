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
#ifndef ABSTRACT_SYNTAX_PRINT_VISITOR_V1_H_
#define ABSTRACT_SYNTAX_PRINT_VISITOR_V1_H_

#include "abstract_syntax/abstract_syntax_tree_v1.h"
#include <sstream>
#include <string>

namespace cs160 {
namespace abstract_syntax {
namespace version_1 {

class PrintVisitor : public AstVisitor {
 public:
  PrintVisitor() {}
  ~PrintVisitor() {}

  const std::string GetOutput() const { return output_.str(); }

  void VisitIntegerExpr(const IntegerExpr& exp) { output_ << exp.value(); }

  void VisitBinaryOperatorExpr(const BinaryOperatorExpr& exp) {}

  void VisitAddExpr(const AddExpr& exp) {
    output_ << "(+ ";
    exp.lhs().Visit(this);
    output_ << " ";
    exp.rhs().Visit(this);
    output_ << ")";
  }

  void VisitSubtractExpr(const SubtractExpr& exp) {
    output_ << "(- ";
    exp.lhs().Visit(this);
    output_ << " ";
    exp.rhs().Visit(this);
    output_ << ")";
  }

  void VisitMultiplyExpr(const MultiplyExpr& exp) {
    output_ << "(* ";
    exp.lhs().Visit(this);
    output_ << " ";
    exp.rhs().Visit(this);
    output_ << ")";
  }

  void VisitDivideExpr(const DivideExpr& exp) {
    output_ << "(/ ";
    exp.lhs().Visit(this);
    output_ << " ";
    exp.rhs().Visit(this);
    output_ << ")";
  }

 private:
  std::stringstream output_;
};

}  // namespace version_1
}  // namespace abstract_syntax
}  // namespace cs160

#endif  // ABSTRACT_SYNTAX_PRINT_VISITOR_V1_H_
