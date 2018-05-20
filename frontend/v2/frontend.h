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

class Frontend {
 public:
    ~Frontend(void);

  Parse::Node stringToAst(std::string input);

};
}  // namespace frontend
}  // namespace cs160

#endif  // FRONTEND_FRONTEND_H_
