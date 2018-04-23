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

}  // namespace parser
}  // namespace cs160

#endif