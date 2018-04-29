// Copyright (c) 2018, Team-Chant

#ifndef FRONTEND_PARSER_PARSER_H_
#define FRONTEND_PARSER_PARSER_H_

#include <vector>
#include <iostream>
#include <string>
#include <memory>
#include "frontend/scanner/token/Token.h"
#include "abstract_syntax/abstract_syntax.h"
#include "utility/memory.h"

namespace cs160 {
namespace frontend {

class Parser {
 public:
    explicit Parser(std::vector<std::shared_ptr<Token>> tokens);
    ~Parser(void);
    std::unique_ptr<abstract_syntax::frontend::AstNode> Parse() {
       try {
          return ExpressionRule();
       } catch (std::exception e) {
          std::cerr << e.what() << std::endl;
       }
       throw "failed to parse";
     }

 private:
    std::vector<std::shared_ptr<Token>> tokens;
    int current = 0;

    // CFG methods
    std::unique_ptr<abstract_syntax::frontend::AstNode> ExpressionRule() { return AddRule(); }
    std::unique_ptr<abstract_syntax::frontend::AstNode> AddRule() {
        // std::cout << "AddRule" << std::endl;
        // equality → comparison ( ( "!=" | "==" ) comparison )* ;
        // AddRule --> MultRule ( ("-" | "+") MultRule )*
       std::unique_ptr<abstract_syntax::frontend::AstNode> e =
        MultRule();
       std::vector<token_type_> possibleTypes = {plusToken, minusToken};
       while (Match(possibleTypes)) {
          std::shared_ptr<Token> op = Prev();
          std::unique_ptr<abstract_syntax::frontend::AstNode> right =
            MultRule();
          if (op->GetCurrType() == plusToken) {
            e = std::unique_ptr<abstract_syntax::frontend::AstNode>
              (new abstract_syntax::frontend::AddExpr
                (std::move(e), std::move(right))
              );
          } else if (op->GetCurrType() == minusToken) {
            e = std::unique_ptr<abstract_syntax::frontend::AstNode>
              (new abstract_syntax::frontend::SubtractExpr
                (std::move(e), std::move(right))
              );
          } else {
            throw "wtf";  // This should never happen.
          }
       }
       // std::cout << "MultRule is done" << std::endl;
       return e;
    }
    std::unique_ptr<abstract_syntax::frontend::AstNode> MultRule() {
       // MultRule --> UnaryRule ( ("/" | "*") UnaryRule )*
       // std::cout << "MultRule" << std::endl;
       std::unique_ptr<abstract_syntax::frontend::AstNode> e =
        UnaryRule();
       std::vector<token_type_> possibleTypes = {divideToken, multToken};
       while (Match(possibleTypes)) {
          std::shared_ptr<Token> op = Prev();
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
    std::unique_ptr<abstract_syntax::frontend::AstNode> UnaryRule() {
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
    std::unique_ptr<abstract_syntax::frontend::AstNode> PrimaryRule() {
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

    // helpers
    std::shared_ptr<Token> Next() {
       if (!AtEnd()) current = current + 1;
       return Prev();
    }
    std::shared_ptr<Token> Prev() {
       return tokens[current - 1];
    }
    bool AtEnd() {
       return (current > tokens.size() - 1);
    }
    std::shared_ptr<Token> GetCurrent() {
       return tokens[current];
    }
    bool Match(std::vector<token_type_> types) {
       for (auto const& type : types) {
          // std::cout << "Checking " << type;
          if (Check(type)) {
             Next();
             // std::cout << ": success" << std::endl;
             return true;
          }
          // std::cout << ": failed" << std::endl;
       }
       return false;
    }
    bool Check(token_type_ type) {
       if (AtEnd()) return false;
       // std::cout << "(against " << GetCurrent().GetToken() << ")";
       return GetCurrent()->GetCurrType() == type;
    }
    std::shared_ptr<Token> Consume(token_type_ until, std::string error) {
       if (Check(until)) return Next();
       throw error;
    }
};
}  // namespace frontend
}  // namespace cs160

#endif  // FRONTEND_PARSER_PARSER_H_
