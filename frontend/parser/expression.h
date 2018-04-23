#ifndef FRONT_END_PARSER_EXPRESSION_H_
#define FRONT_END_PARSER_EXPRESSION_H_

#include "frontend/scanner/token/Token.h"

namespace cs160 {
namespace frontend {

class Expression {

};
class BinaryExpr : public Expression {
  public:
    explicit BinaryExpr(Expression left, cs160::frontend::Token op, Expression right)
      : left_(left), right_(right), op_(op)
    {}

  private:
    const Expression left_;
    const Expression right_;
    const cs160::frontend::Token op_;
};

class UnaryExpr : public Expression {
  public:
    explicit UnaryExpr(cs160::frontend::Token op, Expression right)
      : op_(op), right_(right) {}

  private:
    const cs160::frontend::Token op_;
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
    explicit Literal(cs160::frontend::Token lit) : lit_(lit) {}

  private:
    const cs160::frontend::Token lit_;
};
}  // namespace frontend
}  // namespace cs160

#endif
