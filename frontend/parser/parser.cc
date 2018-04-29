// Copyright (c) 2018, Team-Chant

#include "frontend/parser/parser.h"

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

Parser::Parser(std::vector<std::shared_ptr<Token>> tokens) {
  this->tokens_ = tokens;
}
Parser::~Parser() {}

std::unique_ptr<AstNode> Parser::AddRule() {
    // std::cout << "AddRule" << std::endl;
    // equality → comparison ( ( "!=" | "==" ) comparison )* ;
    // AddRule --> MultRule ( ("-" | "+") MultRule )*
   unique_ptr<AstNode> e =
    Parser::MultRule();
   std::vector<token_type_> possibleTypes = {plusToken, minusToken};
   while (Parser::Match(possibleTypes)) {
      std::shared_ptr<Token> op = Parser::Prev();
      std::unique_ptr<AstNode> right =
        Parser::MultRule();
      if (op->GetCurrType() == plusToken) {
        e = std::unique_ptr<AstNode>
          (new AddExpr(std::move(e), std::move(right)));
      } else if (op->GetCurrType() == minusToken) {
        e = std::unique_ptr<AstNode>
          (new SubtractExpr(std::move(e), std::move(right)));
      } else {
        throw "wtf";  // This should never happen.
      }
   }
   // std::cout << "MultRule is done" << std::endl;
   return e;
}

std::unique_ptr<AstNode> Parser::MultRule() {
   // MultRule --> UnaryRule ( ("/" | "*") UnaryRule )*
   // std::cout << "MultRule" << std::endl;
   std::unique_ptr<AstNode> e =
    Parser::UnaryRule();
   std::vector<token_type_> possibleTypes = {divideToken, multToken};
   while (Parser::Match(possibleTypes)) {
      std::shared_ptr<Token> op = Parser::Prev();
      std::unique_ptr<abstract_syntax::frontend::AstNode> right =
        UnaryRule();
      if (op->GetCurrType() == multToken) {
        e = std::unique_ptr<abstract_syntax::frontend::AstNode>
          (new abstract_syntax::frontend::MultiplyExpr
            (std::move(e), std::move(right))
          );
      } else if (op->GetCurrType() == divideToken) {
        e = std::unique_ptr<abstract_syntax::frontend::AstNode>
          (new abstract_syntax::frontend::DivideExpr
            (std::move(e), std::move(right))
          );
      } else {
        throw "wtf";  // This should never happen.
      }
   }
   // std::cout << "MultRule is done" << std::endl;
   return e;
}

unique_ptr<AstNode> Parser::UnaryRule() {
   // UnaryRule --> PrimaryRule | "-" UnaryRule
   // std::cout << "UnaryRule" << std::endl;
   std::vector<token_type_> possibleTypes = {minusToken};
   if (Match(possibleTypes)) {
      std::shared_ptr<Token> op = Prev();
      std::unique_ptr<abstract_syntax::frontend::AstNode> right
        = UnaryRule();
      std::unique_ptr<abstract_syntax::frontend::AstNode>
        zero(new abstract_syntax::frontend::IntegerExpr(0));
      // std::cout << "UnaryRule is done" << std::endl;
      return std::unique_ptr<abstract_syntax::frontend::AstNode>(
        new abstract_syntax::frontend::SubtractExpr(std::move(zero), std::move(right)));
   }
   // std::cout << "UnaryRule is done" << std::endl;
   return PrimaryRule();
}

std::unique_ptr<AstNode> Parser::PrimaryRule() {
   // PrimaryRule --> integer | (ExpressionRule)
   // std::cout << "PrimaryRule" << std::endl;
   std::vector<token_type_> possibleTypes = {integerToken};
   if (Match(possibleTypes)) {
      // std::cout << "PrimaryRule is done" << std::endl;
      return std::unique_ptr<abstract_syntax::frontend::AstNode>(
        new abstract_syntax::frontend::IntegerExpr(Prev()->GetTokenInt()));
   }
   std::vector<token_type_> leftParen = {openParenthesisToken};
   if (Match(leftParen)) {
      std::unique_ptr<abstract_syntax::frontend::AstNode> e = ExpressionRule();
      Consume(closedParenthesisToken, "Expected ')' after ExpressionRule.");
      // std::cout << "PrimaryRule is done" << std::endl;
      return e;
   }
   throw "PrimaryRule production failed";
   // std::cout << "uh oh" << std::endl;
}


}  // namespace frontend
}  // namespace cs160
