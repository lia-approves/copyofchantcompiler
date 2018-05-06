// Copyright (c) 2018, Team-Chant

#ifndef FRONTEND_COMBINATOR_PARSER_H_
#define FRONTEND_COMBINATOR_PARSER_H_

#include "frontend/combinator/result.h"
#include "frontend/combinator/state.h"

namespace cs160 {
namespace frontend {

// Represents a 'parse function': a function which takes a state and returns
// a result.  Just an alias for convenience; this type does not ever change.
using Parser = std::function<Result<std::string>(State)>;

Parser Literal(char c) {
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

Parser Or(Parser parseA, Parser parseB) {
  return [parseA, parseB](State state) {
    auto resultA = parseA(state);
    if (resultA.success()) {
      return resultA;
    }
    auto resultB = parseB(state);
    if (resultB.success()) {
      return resultB;
    }
    return Result<std::string>(false, "no match for A or B");
  };
}


}  // namespace frontend
}  // namespace cs160

#endif  // FRONTEND_COMBINATOR_PARSER_H_
