// Copyright (c) 2018, Team-Chant

#include "frontend/parser/parser.h"

using cs160::abstract_syntax::frontend::AstNode;
using cs160::abstract_syntax::frontend::IntegerExpr;
using cs160::abstract_syntax::frontend::MultiplyExpr;
using cs160::abstract_syntax::frontend::AddExpr;
using cs160::abstract_syntax::frontend::SubtractExpr;
using cs160::abstract_syntax::frontend::DivideExpr;
using unique_ptr;
using shared_ptr;
using move;

namespace cs160 {
namespace frontend {

Parser::Parser(std::vector<shared_ptr<Token>> tokens) {
  this->tokens_ = tokens;
}
Parser::~Parser() {}

unique_ptr<AstNode> Parser::AddRule() {
    // std::cout << "AddRule" << std::endl;
    // equality → comparison ( ( "!=" | "==" ) comparison )* ;
    // AddRule --> MultRule ( ("-" | "+") MultRule )*
   unique_ptr<AstNode> e = Parser::MultRule();
   std::vector<token_type_> possibleTypes = {plusToken, minusToken};
   while (Parser::Match(possibleTypes)) {
      shared_ptr<Token> op = Parser::Prev();
      unique_ptr<AstNode> right = Parser::MultRule();
      if (op->GetCurrType() == plusToken) {
        e = unique_ptr<AstNode>
          (new AddExpr(move(e), move(right)));
      } else if (op->GetCurrType() == minusToken) {
        e = unique_ptr<AstNode>
          (new SubtractExpr(move(e), move(right)));
      } else {
        throw "wtf";  // This should never happen.
      }
   }
   // std::cout << "MultRule is done" << std::endl;
   return e;
}

unique_ptr<AstNode> Parser::MultRule() {
   // MultRule --> UnaryRule ( ("/" | "*") UnaryRule )*
   // std::cout << "MultRule" << std::endl;
   unique_ptr<AstNode> e =
    Parser::UnaryRule();
   std::vector<token_type_> possibleTypes = {divideToken, multToken};
   while (Parser::Match(possibleTypes)) {
      shared_ptr<Token> op = Parser::Prev();
      unique_ptr<abstract_syntax::frontend::AstNode> right =
        UnaryRule();
      if (op->GetCurrType() == multToken) {
        e = unique_ptr<abstract_syntax::frontend::AstNode>
          (new abstract_syntax::frontend::MultiplyExpr
            (move(e), move(right))
          );
      } else if (op->GetCurrType() == divideToken) {
        e = unique_ptr<abstract_syntax::frontend::AstNode>
          (new abstract_syntax::frontend::DivideExpr
            (move(e), move(right))
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
      shared_ptr<Token> op = Prev();
      unique_ptr<abstract_syntax::frontend::AstNode> right
        = UnaryRule();
      unique_ptr<abstract_syntax::frontend::AstNode>
        zero(new abstract_syntax::frontend::IntegerExpr(0));
      // std::cout << "UnaryRule is done" << std::endl;
      return unique_ptr<abstract_syntax::frontend::AstNode>(
        new abstract_syntax::frontend::SubtractExpr(move(zero), move(right)));
   }
   // std::cout << "UnaryRule is done" << std::endl;
   return PrimaryRule();
}

unique_ptr<AstNode> Parser::PrimaryRule() {
   // PrimaryRule --> integer | (ExpressionRule)
   // std::cout << "PrimaryRule" << std::endl;
   std::vector<token_type_> possibleTypes = {integerToken};
   if (Match(possibleTypes)) {
      // std::cout << "PrimaryRule is done" << std::endl;
      return unique_ptr<abstract_syntax::frontend::AstNode>(
        new abstract_syntax::frontend::IntegerExpr(Prev()->GetTokenInt()));
   }
   std::vector<token_type_> leftParen = {openParenthesisToken};
   if (Match(leftParen)) {
      unique_ptr<abstract_syntax::frontend::AstNode> e = ExpressionRule();
      Consume(closedParenthesisToken, "Expected ')' after ExpressionRule.");
      // std::cout << "PrimaryRule is done" << std::endl;
      return e;
   }
   throw "PrimaryRule production failed";
   // std::cout << "uh oh" << std::endl;
}


}  // namespace frontend
}  // namespace cs160
