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
#ifndef ABSTRACT_SYNTAX_ABSTRACT_SYNTAX_TREE_V1_H_
#define ABSTRACT_SYNTAX_ABSTRACT_SYNTAX_TREE_V1_H_

#include "utility/memory.h"

namespace cs160 {
namespace abstract_syntax {
namespace version_1 {
// This version of the abstract syntax consists of a single arithmetic
// expression. The grammar for the abstract syntax is:
//
// n ∈ Integer
//
// ae ∈ ArithmeticExp ⟵ n | ae1 op ae2
// op ∈ BinaryOperator ⟵ + | - | ⨯ | ÷
//
// prog ∈ Program ⟵ ae
//
// I.e., a program is an arithmetic expression.

// Forward declarations of abstract syntax tree node types for use in the
// abstract syntax tree visitor.
class IntegerExpr;
class AddExpr;
class SubtractExpr;
class MultiplyExpr;
class DivideExpr;

// The visitor abstract base class for visiting abstract syntax trees.
class AstVisitor {
 public:
  virtual ~AstVisitor() {}

  // These should be able to change members of the visitor, thus not const
  virtual void VisitIntegerExpr(const IntegerExpr& exp) = 0;
  virtual void VisitAddExpr(const AddExpr& exp) = 0;
  virtual void VisitSubtractExpr(const SubtractExpr& exp) = 0;
  virtual void VisitMultiplyExpr(const MultiplyExpr& exp) = 0;
  virtual void VisitDivideExpr(const DivideExpr& exp) = 0;
};

// The definition of the abstract syntax tree abstract base class.
class AstNode {
 public:
  virtual ~AstNode() {}

  virtual void Visit(AstVisitor* visitor) const = 0;
};

// An integer constant expression.
class IntegerExpr : public AstNode {
 public:
  explicit IntegerExpr(int value) : value_(value) {}

  void Visit(AstVisitor* visitor) const { visitor->VisitIntegerExpr(*this); }

  int value() const { return value_; }

 private:
  // The value of the integer constant.
  int value_;
};

// An abstract binary operator node.
class BinaryOperatorExpr : public AstNode {
 public:
  BinaryOperatorExpr(std::unique_ptr<const AstNode> lhs,
                     std::unique_ptr<const AstNode> rhs)
      : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

  const AstNode& lhs() const { return *lhs_; }
  const AstNode& rhs() const { return *rhs_; }

 protected:
  // The left-hand side and right-hand side of the expression.
  const std::unique_ptr<const AstNode> lhs_;
  const std::unique_ptr<const AstNode> rhs_;
};

// An addition expression.
class AddExpr : public BinaryOperatorExpr {
 public:
  AddExpr(std::unique_ptr<const AstNode> lhs,
          std::unique_ptr<const AstNode> rhs)
      : BinaryOperatorExpr(std::move(lhs), std::move(rhs)) {}

  void Visit(AstVisitor* visitor) const { visitor->VisitAddExpr(*this); }
};

// A subtraction expression.
class SubtractExpr : public BinaryOperatorExpr {
 public:
  SubtractExpr(std::unique_ptr<const AstNode> lhs,
               std::unique_ptr<const AstNode> rhs)
      : BinaryOperatorExpr(std::move(lhs), std::move(rhs)) {}

  void Visit(AstVisitor* visitor) const { visitor->VisitSubtractExpr(*this); }
};

// A multiplication expression.
class MultiplyExpr : public BinaryOperatorExpr {
 public:
  MultiplyExpr(std::unique_ptr<const AstNode> lhs,
               std::unique_ptr<const AstNode> rhs)
      : BinaryOperatorExpr(std::move(lhs), std::move(rhs)) {}

  void Visit(AstVisitor* visitor) const { visitor->VisitMultiplyExpr(*this); }
};

// A division expression.
class DivideExpr : public BinaryOperatorExpr {
 public:
  DivideExpr(std::unique_ptr<const AstNode> lhs,
             std::unique_ptr<const AstNode> rhs)
      : BinaryOperatorExpr(std::move(lhs), std::move(rhs)) {}

  void Visit(AstVisitor* visitor) const { visitor->VisitDivideExpr(*this); }
};

}  // namespace version_1
}  // namespace abstract_syntax
}  // namespace cs160

#endif  // ABSTRACT_SYNTAX_ABSTRACT_SYNTAX_TREE_V1_H_
