#ifndef FRONTEND_H_
#define FRONTEND_H_

#include "abstract_syntax/abstract_syntax.h"
#include <queue>
#include "frontend/scanner/token/Token.h"
#include "utility/memory.h"

namespace cs160 {
namespace frontend {

class Frontend {
  public:
    ~Frontend(void);

    std::unique_ptr<cs160::abstract_syntax::frontend::AstNode>
      stringToAst(std::string input);

  private:
    std::queue<cs160::scanner::token::Token>
      tokenizeString(std::string input);  // wrapper around the scanner

    std::unique_ptr<cs160::abstract_syntax::frontend::AstNode>
      makeParseTree(std::queue<cs160::scanner::token::Token> tokens); // create parse tree from token sequence

};

}
}

#endif // FRONTEND_H_
