// Copyright (c) 2018, Team-Chant

#include <utility>
#include <stdexcept>
#include <iostream>
#include "frontend/v1/parser/parser.h"

using cs160::abstract_syntax::frontend::AstNode;
using cs160::abstract_syntax::frontend::IntegerExpr;
using cs160::abstract_syntax::frontend::MultiplyExpr;
using cs160::abstract_syntax::frontend::AddExpr;
using cs160::abstract_syntax::frontend::SubtractExpr;
using cs160::abstract_syntax::frontend::DivideExpr;
using std::unique_ptr;
using std::shared_ptr;
using std::move;

namespace cs160 {
namespace frontend {

Parser::Parser(std::vector<shared_ptr<Token>> tokens) {
  this->tokens_ = tokens;
}
Parser::~Parser() {}

// AddRule --> MultRule ( ("-" | "+") MultRule )*
unique_ptr<AstNode> Parser::AddRule() {
  std::cout << "in add rule" << std::endl;
  unique_ptr<AstNode> e = MultRule();  // Consume first expression
  std::vector<token_type_> possibleTypes = {plusToken, minusToken};
  while (Match(possibleTypes)) {
    shared_ptr<Token> op = Prev();  // Get token
    unique_ptr<AstNode> right = MultRule();  // Consume second expression

    // Based on op type, create new Add or Subtract expression
    if (op->GetCurrType() == plusToken) {
      e = unique_ptr<AstNode>(new AddExpr(move(e), move(right)));
    } else if (op->GetCurrType() == minusToken) {
      e = unique_ptr<AstNode>(new SubtractExpr(move(e), move(right)));
    } else {
      // This should never happen.
      std::cout << "THROWING 1\n";
      throw std::runtime_error("unexpected token: "+op->GetToken());
    }
  }
  return e;
}

// MultRule --> UnaryRule ( ("/" | "*") UnaryRule )*
// Same as AddRule() but with unaries
unique_ptr<AstNode> Parser::MultRule() {
  std::cout << "in mult rule" << std::endl;
  unique_ptr<AstNode> e = UnaryRule();
  std::vector<token_type_> possibleTypes = {divideToken, multToken};
  while (Match(possibleTypes)) {
    shared_ptr<Token> op = Prev();
    unique_ptr<abstract_syntax::frontend::AstNode> right = UnaryRule();
    if (op->GetCurrType() == multToken) {
      e = unique_ptr<AstNode>(new MultiplyExpr(move(e), move(right)));
    } else if (op->GetCurrType() == divideToken) {
      e = unique_ptr<AstNode>(new DivideExpr(move(e), move(right)));
    } else {
      // This should never happen.
      std::cout << "THROWING 2\n";
      throw std::runtime_error("unexpected token: "+op->GetToken());
    }
  }
  return e;
}

// UnaryRule --> PrimaryRule | "-" UnaryRule
unique_ptr<AstNode> Parser::UnaryRule() {
  std::cout << "in unary" << std::endl;
  std::vector<token_type_> possibleTypes = {minusToken};
  if (Match(possibleTypes)) {  // Try to consume a minus sign
    shared_ptr<Token> op = Prev();
    unique_ptr<AstNode> right = UnaryRule();  // Consume the next unary
    unique_ptr<AstNode> zero(new IntegerExpr(0));
    // Return 0 - NextUnary
    return unique_ptr<AstNode>(new SubtractExpr(move(zero), move(right)));
  }
  return PrimaryRule();
}

// PrimaryRule --> integer | (ExpressionRule)
unique_ptr<AstNode> Parser::PrimaryRule() {
  std::cout << "in primary" << std::endl;
  // Return literal, if possible
  std::vector<token_type_> possibleTypes = {integerToken};
  if (Match(possibleTypes)) {
    std::cout << "in first if statement" << std::endl;
    // std::cout << "int: " << Prev()->GetTokenIn() << std::endl;
    return unique_ptr<AstNode>(new IntegerExpr(Prev()->GetTokenInt()));
  }
  // Return parenthetical group, if possible
  std::vector<token_type_> leftParen = {openParenthesisToken};
  if (Match(leftParen)) {
    unique_ptr<AstNode> e = ExpressionRule();
    Consume(closedParenthesisToken, "Expected ')' after ExpressionRule.");
    return e;
  }

  std::cout << "THROWING 3\n";
  std::logic_error("primary rule failed");
}


}  // namespace frontend
}  // namespace cs160
