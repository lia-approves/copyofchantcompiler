#ifndef PARSER_H_
#define PARSER_H_

#include <vector>
#include "frontend/scanner/token/Token.h"
#include "frontend/parser/expression.h"

namespace cs160 {
namespace parser {

class Parser {
  public:
    explicit Parser(std::vector<scanner::token::Token> tokens);
    ~Parser(void);
    Expression parse();

  private:
    std::vector<scanner::token::Token> tokens;
    int current = 0;

    // CFG methods
    Expression expression() { return add(); }
    Expression add() {
      // equality → comparison ( ( "!=" | "==" ) comparison )* ;
      // add --> mult ( ("-" | "+") mult )*
      Expression e = mult();
      while (match("-", "+")) {
        scanner::token::Token op = prev();
        Expression right = mult();
      }
      return e;
    }
    Expression mult() {
      Expression e;
      return e;
    }

    // helpers
    scanner::token::Token next() {
      if (current < tokens.size() - 1) current = current + 1;
      return prev();
    }
    scanner::token::Token prev() {
      return tokens[current - 1];
    }
    bool match(std::string left, std::string right) {
      return false;
    }
};

}  // namespace cs160
}  // namespace parser

#endif