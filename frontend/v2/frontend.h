// Copyright (c) 2018, Team-Chant
#ifndef FRONTEND_FRONTEND_H_
#define FRONTEND_FRONTEND_H_

#include <vector>
#include <string>
#include <memory>
#include "abstract_syntax/abstract_syntax.h"
#include "frontend/combinator/parser.h"
#include "utility/memory.h"

namespace cs160 {
namespace frontend {
namespace Parse {

class Frontend {
 public:
  ~Frontend(void);
  Node stringToAst(std::string input);

 private:
  Parser Program();
  Parser Assign();
  Parser Id();
  Parser Expression();
  Parser Add();
  Parser Multiply();
  Parser Unary();
  Parser Primary();
};

}  // namespace Parse
}  // namespace frontend
}  // namespace cs160

#endif  // FRONTEND_FRONTEND_H_
