// Copyright (c) 2018, Team-Chant
#ifndef FRONTEND_FRONTEND_H_
#define FRONTEND_FRONTEND_H_

#include <vector>
#include <string>
#include <memory>
#include "abstract_syntax/abstract_syntax.h"
#include "frontend/v1/scanner/token/Token.h"
#include "frontend/v1/scanner/token/IntegerToken.h"
#include "frontend/v1/scanner/token/ArithmeticExpressionToken.h"
#include "frontend/v1/scanner/token/OpenParenthesisToken.h"
#include "frontend/v1/scanner/token/ClosedParenthesisToken.h"
#include "frontend/v1/scanner/state_machine/dfa/dfa.h"
#include "frontend/v1/parser/parser.h"
#include "utility/memory.h"

namespace cs160 {
namespace frontend {

class Frontend {
 public:
    ~Frontend(void);

    std::unique_ptr<cs160::abstract_syntax::frontend::AstNode>
      stringToAst(std::string input);

 private:
    std::vector<std::shared_ptr<Token>>
      tokenizeString(std::string input);
      // wrapper around the scanner

    std::unique_ptr<cs160::abstract_syntax::frontend::AstNode>
      makeParseTree(std::vector<std::shared_ptr<Token>> tokens);
      // create parse tree from token sequence
      DFA makeDFA();
};
}  // namespace frontend
}  // namespace cs160

#endif  // FRONTEND_FRONTEND_H_
