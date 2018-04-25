#ifndef FRONT_END_PARSER_EXPRESSION_H_
#define FRONT_END_PARSER_EXPRESSION_H_

#include "frontend/scanner/token/Token.h"
#include "utility/memory.h"

namespace cs160 {
namespace frontend {

class Expression {
  public:
    virtual std::string toString() const {
      return "empty expression";
    }

};

class BinaryExpr : public Expression {
  public:
    explicit BinaryExpr(std::shared_ptr<Expression> left, cs160::frontend::Token op, std::shared_ptr<Expression> right)
      : left_(left), right_(right), op_(op) {}
    std::string toString() const {
      return "("+left_->toString()+op_.get_token()+right_->toString()+")";
    }

  private:
    const std::shared_ptr<Expression> left_;
    const std::shared_ptr<Expression> right_;
    const cs160::frontend::Token op_;
};

class UnaryExpr : public Expression {
  public:
    explicit UnaryExpr(cs160::frontend::Token op, std::shared_ptr<Expression> right)
      : op_(op), right_(right) {}
    std::string toString() const {
      return "("+op_.get_token()+right_->toString()+")";
    }

  private:
    const cs160::frontend::Token op_;
    const std::shared_ptr<Expression> right_;
};

class Group : public Expression {
  public:
    explicit Group(std::shared_ptr<Expression> enclosed) : enclosed_(enclosed) {}
  std::string toString() const {
    return "("+enclosed_->toString()+")";
  }

  private:
    const std::shared_ptr<Expression> enclosed_;
};

class Literal : public Expression {
  public:
    explicit Literal(cs160::frontend::Token lit) : lit_(lit) {}
  std::string toString() const {
    return lit_.get_token();
  }

  private:
    const cs160::frontend::Token lit_;
};
}  // namespace frontend
}  // namespace cs160

#endif
