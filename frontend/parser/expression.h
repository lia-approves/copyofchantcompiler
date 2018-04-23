#ifndef FRONT_END_PARSER_EXPRESSION_H_
#define FRONT_END_PARSER_EXPRESSION_H_

#include "frontend/scanner/token/Token.h"

namespace cs160 {
namespace frontend {

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
<<<<<<< HEAD
    const Token op_;
=======
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
>>>>>>> 0e087d935a17686d6987a6643d7191c54dba0493

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

}  // namespace frontend
}  // namespace cs160

#endif
