#ifndef FRONT_END_PARSER_PARSER_H_
#define FRONT_END_PARSER_PARSER_H_

#include <vector>
#include "frontend/scanner/token/Token.h"
#include "frontend/parser/expression.h"

namespace cs160 {
namespace frontend {

class Parser {
  public:
    explicit Parser(std::vector<Token> tokens);
    ~Parser(void);
    Expression parse();

  private:
    std::vector<Token> tokens;
    int current = 0;

    // CFG methods
    Expression expression() { return add(); }
    Expression add() {
      // equality → comparison ( ( "!=" | "==" ) comparison )* ;
      // add --> mult ( ("-" | "+") mult )*
      Expression e = mult();
      std::vector<std::string> tokenTypes = {"-", "+"};
      while (match(tokenTypes)) {
        cs160::frontend::Token op = prev();
        Expression right = mult();
        e = BinaryExpr(e, op, right);
      }
      return e;
    }
    Expression mult() {
      // comparison → addition ( ( ">" | ">=" | "<" | "<=" ) addition )* ;
      // mult --> unary ( ("/" | "*") unary )*
      Expression e = unary();
      std::vector<std::string> possibleTypes = {"/", "*"};
      while (match(possibleTypes)) {
        cs160::frontend::Token op = prev();
        Expression right = unary();
        e = BinaryExpr(e, op, right);
      }
      return e;
    }
    Expression unary() {
      // unary --> primary | "-" unary
      std::vector<std::string> possibleTypes = {"-"};
      if (match(possibleTypes)) {
        cs160::frontend::Token op = prev();
        Expression right = unary();
        UnaryExpr ue(op, right);
        return ue;
      }
      return primary();
    }
    Expression primary() {
      // primary --> integer | (expression)
      std::vector<std::string> possibleLiterals = {"0","1","2","3","4","5"};
      if (match(possibleLiterals)) {
        Literal e(prev());
        return e;
      }
      std::vector<std::string> leftParen = {"("};
      if (match(leftParen)) {
        Expression e;
        consume(")", "Expected ')' after expression.");
        Group g(e);
        return g;
      }
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
      return (current >= tokens.size() - 1);
    }
    cs160::frontend::Token getCurrent() {
      return tokens[current];
    }
    bool match(std::vector<std::string> types) {
      for (auto const& type: types) {
        if (check(type)) {
          next();
          return true;
        }
      }
      return false;
    }
    bool check(std::string type) {
      if (atEnd()) return false;
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
