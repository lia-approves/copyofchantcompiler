// Copyright (c) 2018, Team-Chant

#ifndef FRONTEND_PARSER_PARSER_H_
#define FRONTEND_PARSER_PARSER_H_

#include <vector>
#include <iostream>
#include <string>
#include <memory>
#include "frontend/scanner/token/Token.h"
#include "frontend/parser/expression.h"
#include "utility/memory.h"

namespace cs160 {
namespace frontend {

class Parser {
 public:
    explicit Parser(std::vector<Token> tokens);
    ~Parser(void);
    std::shared_ptr<Expression> Parse() {
       try {
          return ExpressionRule();
       } catch (std::exception e) {
          std::cerr << e.what() << std::endl;
          return std::shared_ptr<Expression>(new Expression);
       }
     }

 private:
    std::vector<Token> tokens;
    int current = 0;

    // CFG methods
    std::shared_ptr<Expression> ExpressionRule() { return AddRule(); }
    std::shared_ptr<Expression> AddRule() {
       // std::cout << "AddRule" << std::endl;
       // equality → comparison ( ( "!=" | "==" ) comparison )* ;
       // AddRule --> MultRule ( ("-" | "+") MultRule )*
       std::shared_ptr<Expression> e = MultRule();
       std::vector<std::string> tokenTypes = {"-", "+"};
       while (Match(tokenTypes)) {
          cs160::frontend::Token op = Prev();
          std::shared_ptr<Expression> right = MultRule();
          e = std::shared_ptr<Expression>(new BinaryExpr(e, op, right));
       }
       // std::cout << "AddRule is done" << std::endl;
       return e;
    }
    std::shared_ptr<Expression> MultRule() {
       // MultRule --> UnaryRule ( ("/" | "*") UnaryRule )*
       // std::cout << "MultRule" << std::endl;
       std::shared_ptr<Expression> e = UnaryRule();
       std::vector<std::string> possibleTypes = {"/", "*"};
       while (Match(possibleTypes)) {
          cs160::frontend::Token op = Prev();
          std::shared_ptr<Expression> right = UnaryRule();
          e = std::shared_ptr<Expression>(new BinaryExpr(e, op, right));
       }
       // std::cout << "MultRule is done" << std::endl;
       return e;
    }
    std::shared_ptr<Expression> UnaryRule() {
       // UnaryRule --> PrimaryRule | "-" UnaryRule
       // std::cout << "UnaryRule" << std::endl;
       std::vector<std::string> possibleTypes = {"-"};
       if (Match(possibleTypes)) {
          cs160::frontend::Token op = Prev();
          std::shared_ptr<Expression> right = UnaryRule();
          // std::cout << "UnaryRule is done" << std::endl;
          return std::shared_ptr<Expression>(new UnaryExpr(op, right));
       }
       // std::cout << "UnaryRule is done" << std::endl;
       return PrimaryRule();
    }
    std::shared_ptr<Expression> PrimaryRule() {
       // PrimaryRule --> integer | (ExpressionRule)
       // std::cout << "PrimaryRule" << std::endl;
       std::vector<std::string> possibleLiterals =
        {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
       if (Match(possibleLiterals)) {
          // std::cout << "PrimaryRule is done" << std::endl;
          return std::shared_ptr<Expression>(new Literal(Prev()));
       }
       std::vector<std::string> leftParen = {"("};
       if (Match(leftParen)) {
          std::shared_ptr<Expression> e = ExpressionRule();
          Consume(")", "Expected ')' after ExpressionRule.");
          // std::cout << "PrimaryRule is done" << std::endl;
          return std::shared_ptr<Expression>(new Group(e));
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
    bool Match(std::vector<std::string> types) {
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
    bool Check(std::string type) {
       if (AtEnd()) return false;
       // std::cout << "(against " << GetCurrent().GetToken() << ")";
       return GetCurrent().GetToken() == type;
    }
    cs160::frontend::Token Consume(std::string until, std::string error) {
       if (Check(until)) return Next();
       throw error;
    }
};
}  // namespace frontend
}  // namespace cs160

#endif  // FRONTEND_PARSER_PARSER_H_
