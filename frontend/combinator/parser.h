// Copyright (c) 2018, Team-Chant

#ifndef FRONTEND_COMBINATOR_PARSER_H_
#define FRONTEND_COMBINATOR_PARSER_H_

#include "frontend/combinator/result.h"
#include "frontend/combinator/state.h"

namespace cs160 {
namespace frontend {

std::function<Result<char>(State)> literal(char c) {
  return [c](State state) {
    if (state.atEnd()) {
      return Result<char>(false, "end of file");
    }
    char next = state.advance();

    if (next == c) {
      return Result<char>(c, state);
    } else {
      std::string err = "no match for character: ";
      err += c;
      return Result<char>(false, err);
    }
  };
}


}  // namespace frontend
}  // namespace cs160

#endif  // FRONTEND_COMBINATOR_PARSER_H_
