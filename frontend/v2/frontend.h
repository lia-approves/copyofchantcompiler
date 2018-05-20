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
  Result Program(State s);
  Result Assign(State s);
  Result Id(State s);
  Result Expression(State s);
  Result Add(State s);
  Result Multiply(State s);
  Result Unary(State s);
  Result Primary(State s);
};

}  // namespace Parse
}  // namespace frontend
}  // namespace cs160

#endif  // FRONTEND_FRONTEND_H_
