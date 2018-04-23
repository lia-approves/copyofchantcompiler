#ifndef FRONT_END_PARSER_EXPRESSION_H_
#define FRONT_END_PARSER_EXPRESSION_H_

#include "frontend/scanner/token/Token.h"

namespace cs160 {
namespace frontend {

class Expression {

};

class BinaryExpr : public Expression {
  public:
    explicit BinaryExpr(Expression left, Token op, Expression right)
      : left_(left), right_(right), op_(op)
    {}

  private:
    const Expression left_;
    const Expression right_;
    const Token op_;

};

}  // namespace frontend
}  // namespace cs160

#endif
