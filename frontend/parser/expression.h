#ifndef EXPRESSION_H_
#define EXPRESSION_H_

#include "frontend/scanner/token/Token.h"

namespace cs160 {
namespace parser {

class Expression {

};

class BinaryExpr : public Expression {
  public:
    explicit BinaryExpr(Expression left, scanner::token::Token op, Expression right)
      : left_(left), right_(right), op_(op)
    {}

  private:
    const Expression left_;
    const Expression right_;
    const scanner::token::Token op_;
};

class UnaryExpr : public Expression {
  public:
    explicit UnaryExpr(scanner::token::Token op, Expression right)
      : op_(op), right_(right) {}

  private:
    const scanner::token::Token op_;
    const Expression right_;
};

class Group : public Expression {
  public:
    explicit Group(Expression enclosed) : enclosed_(enclosed) {}

  private:
    const Expression enclosed_;
};

class Literal : public Expression {
  public:
    explicit Literal(scanner::token::Token lit) : lit_(lit) {}

  private:
    const scanner::token::Token lit_;
};

}  // namespace parser
}  // namespace cs160

#endif