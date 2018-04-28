// Copyright (c) 2018, Team-Chant

#ifndef FRONTEND_PARSER_PARSER_H_
#define FRONTEND_PARSER_PARSER_H_

#include <vector>
#include <iostream>
#include <string>
#include <memory>
#include "frontend/scanner/token/Token.h"
#include "frontend/parser/expression.h"
// #include "abstract_syntax/abstract_syntax.h"
#include "utility/memory.h"

namespace cs160 {
namespace frontend {

class Parser {
 public:
    explicit Parser(std::vector<Token> tokens);
    ~Parser(void);
    std::unique_ptr<Expression> Parse() {
       try {
          return ExpressionRule();
       } catch (std::exception e) {
          std::cerr << e.what() << std::endl;
          return std::unique_ptr<Expression>(new Expression);
       }
     }

 private:
    std::vector<Token> tokens;
    int current = 0;

    // CFG methods
    std::unique_ptr<Expression> ExpressionRule() { return AddRule(); }
    std::unique_ptr<Expression> AddRule() {
       // std::cout << "AddRule" << std::endl;
       // equality → comparison ( ( "!=" | "==" ) comparison )* ;
       // AddRule --> MultRule ( ("-" | "+") MultRule )*
       std::unique_ptr<Expression> e = MultRule();
       std::vector<token_type_> tokenTypes = {plusToken, minusToken};
       while (Match(tokenTypes)) {
          cs160::frontend::Token op = Prev();
          std::unique_ptr<Expression> right = MultRule();
          e = std::unique_ptr<Expression>(new BinaryExpr(std::move(e), op, std::move(right)));
       }
       // std::cout << "AddRule is done" << std::endl;
       return e;
    }
    std::unique_ptr<Expression> MultRule() {
       // MultRule --> UnaryRule ( ("/" | "*") UnaryRule )*
       // std::cout << "MultRule" << std::endl;
       std::unique_ptr<Expression> e = UnaryRule();
       std::vector<token_type_> possibleTypes = {divideToken, multToken};
       while (Match(possibleTypes)) {
          cs160::frontend::Token op = Prev();
          std::unique_ptr<Expression> right = UnaryRule();
          e = std::unique_ptr<Expression>(new BinaryExpr(std::move(e), op, std::move(right)));
       }
       // std::cout << "MultRule is done" << std::endl;
       return e;
    }
    std::unique_ptr<Expression> UnaryRule() {
       // UnaryRule --> PrimaryRule | "-" UnaryRule
       // std::cout << "UnaryRule" << std::endl;
       std::vector<token_type_> possibleTypes = {minusToken};
       if (Match(possibleTypes)) {
          cs160::frontend::Token op = Prev();
          std::unique_ptr<Expression> right = UnaryRule();
          // std::cout << "UnaryRule is done" << std::endl;
          return std::unique_ptr<Expression>(new UnaryExpr(op, std::move(right)));
       }
       // std::cout << "UnaryRule is done" << std::endl;
       return PrimaryRule();
    }
    std::unique_ptr<Expression> PrimaryRule() {
       // PrimaryRule --> integer | (ExpressionRule)
       // std::cout << "PrimaryRule" << std::endl;
       std::vector<token_type_> possibleTypes = {integerToken};
       if (Match(possibleTypes)) {
          // std::cout << "PrimaryRule is done" << std::endl;
          return std::unique_ptr<Expression>(new Literal(Prev()));
       }
       std::vector<token_type_> leftParen = {openParenthesisToken};
       if (Match(leftParen)) {
          std::unique_ptr<Expression> e = ExpressionRule();
          Consume(closedParenthesisToken, "Expected ')' after ExpressionRule.");
          // std::cout << "PrimaryRule is done" << std::endl;
          return std::unique_ptr<Expression>(new Group(std::move(e)));
       }
       throw "PrimaryRule production failed";
       // std::cout << "uh oh" << std::endl;
    }

    // helpers
    cs160::frontend::Token Next() {
       if (!AtEnd()) current = current + 1;
       return Prev();
    }
    Token Prev() {
       return tokens[current - 1];
    }
    bool AtEnd() {
       return (current > tokens.size() - 1);
    }
    cs160::frontend::Token GetCurrent() {
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
       return GetCurrent().GetCurrType() == type;
    }
    cs160::frontend::Token Consume(token_type_ until, std::string error) {
       if (Check(until)) return Next();
       throw error;
    }
};
}  // namespace frontend
}  // namespace cs160

#endif  // FRONTEND_PARSER_PARSER_H_
