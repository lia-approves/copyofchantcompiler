// Copyright (c) 2018, Team-Chant

#ifndef FRONTEND_COMBINATOR_PARSER_H_
#define FRONTEND_COMBINATOR_PARSER_H_

#include "frontend/combinator/result.h"
#include "frontend/combinator/state.h"

namespace cs160 {
namespace frontend {

std::function<Result<std::string>(State)> literal(char c) {
  return [c](State state) {
    if (state.atEnd()) {
      return Result<std::string>(false, "end of file");
    }
    char next = state.advance();

    if (next == c) {
      return Result<std::string>(std::string(1, c), state);
    } else {
      std::string err = "no match for character: ";
      err += c;
      return Result<std::string>(false, err);
    }
  };
}

// std::function<Result<R>(State)>
// or(std::function<A(State)> parseA, std::function<A(State)> parseB) {
//
// }


}  // namespace frontend
}  // namespace cs160

#endif  // FRONTEND_COMBINATOR_PARSER_H_
