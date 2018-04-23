#ifndef PARSER_H_
#define PARSER_H_

#include <queue>
#include "frontend/scanner/token/Token.h"

namespace cs160 {
namespace parser {

class Parser {
  public:
    explicit Parser(std::queue<scanner::token::Token> tokens);
    ~Parser(void);

  private:
    std::queue<scanner::token::Token> tokens;
};

}  // namespace cs160
}  // namespace parser

#endif