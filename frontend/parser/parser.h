#ifndef FRONT_END_PARSER_PARSER_H_
#define FRONT_END_PARSER_PARSER_H_

#include <vector>
#include <iostream>
#include "frontend/scanner/token/Token.h"
#include "frontend/parser/expression.h"
#include "utility/memory.h"

namespace cs160 {
namespace frontend {

class Parser {
  public:
    explicit Parser(std::vector<Token> tokens);
    ~Parser(void);
    std::shared_ptr<Expression> parse() {
      try {
        return expression();
      } catch (std::exception e) {
        std::cerr << e.what() << std::endl;
        return std::shared_ptr<Expression>(new Expression);
      }
    }

  private:
    std::vector<Token> tokens;
    int current = 0;

    // CFG methods
    std::shared_ptr<Expression> expression() { return add(); }
    std::shared_ptr<Expression> add() {
      //std::cout << "add" << std::endl;
      // equality → comparison ( ( "!=" | "==" ) comparison )* ;
      // add --> mult ( ("-" | "+") mult )*
      std::shared_ptr<Expression> e = mult();
      std::vector<std::string> tokenTypes = {"-", "+"};
      while (match(tokenTypes)) {
        cs160::frontend::Token op = prev();
        std::shared_ptr<Expression> right = mult();
        e = std::shared_ptr<Expression>(new BinaryExpr(e, op, right));
      }
      //std::cout << "add is done" << std::endl;
      return e;
    }
    std::shared_ptr<Expression> mult() {
      // comparison → addition ( ( ">" | ">=" | "<" | "<=" ) addition )* ;
      // mult --> unary ( ("/" | "*") unary )*
      //std::cout << "mult" << std::endl;
      std::shared_ptr<Expression> e = unary();
      std::vector<std::string> possibleTypes = {"/", "*"};
      while (match(possibleTypes)) {
        cs160::frontend::Token op = prev();
        std::shared_ptr<Expression> right = unary();
        e = std::shared_ptr<Expression>(new BinaryExpr(e, op, right));
      }
      //std::cout << "mult is done" << std::endl;
      return e;
    }
    std::shared_ptr<Expression> unary() {
      // unary --> primary | "-" unary
      //std::cout << "unary" << std::endl;
      std::vector<std::string> possibleTypes = {"-"};
      if (match(possibleTypes)) {
        cs160::frontend::Token op = prev();
        std::shared_ptr<Expression> right = unary();
        //std::cout << "unary is done" << std::endl;
        return std::shared_ptr<Expression>(new UnaryExpr(op, right));
      }
      //std::cout << "unary is done" << std::endl;
      return primary();
    }
    std::shared_ptr<Expression> primary() {
      // primary --> integer | (expression)
      //std::cout << "primary" << std::endl;
      std::vector<std::string> possibleLiterals = {"0","1","2","3","4","5","6","7","8"};
      if (match(possibleLiterals)) {
        //std::cout << "primary is done" << std::endl;
        return std::shared_ptr<Expression>(new Literal(prev()));
      }
      std::vector<std::string> leftParen = {"("};
      if (match(leftParen)) {
        std::shared_ptr<Expression> e = expression();
        consume(")", "Expected ')' after expression.");
        //std::cout << "primary is done" << std::endl;
        return std::shared_ptr<Expression>(new Group(e));
      }
      throw "primary production failed";
      //std::cout << "uh oh" << std::endl;
    }

    // helpers
    cs160::frontend::Token next() {
      if (!atEnd()) current = current + 1;
      return prev();
    }
    Token prev() {
      return tokens[current - 1];
    }
    bool atEnd() {
      return (current > tokens.size() - 1);
    }
    cs160::frontend::Token getCurrent() {
      return tokens[current];
    }
    bool match(std::vector<std::string> types) {
      for (auto const& type: types) {
        //std::cout << "Checking " << type;
        if (check(type)) {
          next();
          //std::cout << ": success" << std::endl;
          return true;
        }
        //std::cout << ": failed" << std::endl;
      }
      return false;
    }
    bool check(std::string type) {
      if (atEnd()) return false;
      //std::cout << "(against " << getCurrent().get_token() << ")";
      return getCurrent().get_token() == type;
    }
    cs160::frontend::Token consume(std::string until, std::string error) {
      if (check(until)) return next();
      throw error;
    }
};
}  // namespace frontend
}  // namespace cs160

#endif
