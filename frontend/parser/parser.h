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
      while (match("-", "+")) {
        Token op = prev();
        Expression right = mult();
      }
      return e;
    }
    Expression mult() {
      Expression e;
      return e;
    }

    // helpers
    Token next() {
      if (current < tokens.size() - 1) current = current + 1;
      return prev();
    }
    Token prev() {
      return tokens[current - 1];
    }
    bool match(std::string left, std::string right) {
      return false;
    }
};

}  // namespace frontend
}  // namespace cs160

#endif
