#ifndef FRONTEND_H_
#define FRONTEND_H_

#include "abstract_syntax/abstract_syntax.h"
#include <queue>
#include "scanner/token/Token.h"

namespace cs160 {
namespace frontend {

class Frontend {
  public:
    ~Frontend(void);

    cs160::abstract_syntax::frontend::AstNode stringToAst(std::string input);

  private:
    std::queue<cs160::scanner::token::Token> tokenizeString(std::string input);  // wrapper around the scanner



};

}
}

#endif // FRONTEND_H_