// copyright msg for cpplint
#ifndef FRONTEND_FRONTEND_H_
#define FRONTEND_FRONTEND_H_

#include <string>
#include <queue>
#include "abstract_syntax/abstract_syntax.h"
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
  std::queue<Token>
    tokenizeString(std::string input);  // wrapper around the scanner

  std::unique_ptr<cs160::abstract_syntax::frontend::AstNode>
    // create parse tree from token sequence
    makeParseTree(std::queue<Token> tokens);
};
}  // namespace frontend
}  // namespace cs160

#endif  // FRONTEND_FRONTEND_H_
