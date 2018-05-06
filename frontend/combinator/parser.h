// Copyright (c) 2018, Team-Chant

#ifndef FRONTEND_COMBINATOR_PARSER_H_
#define FRONTEND_COMBINATOR_PARSER_H_

#include <array>
#include "frontend/combinator/result.h"
#include "frontend/combinator/state.h"
#include "utility/memory.h"

namespace cs160 {
namespace frontend {

// Represents a 'parse function': a function which takes a state and returns
// a result.  Just an alias for convenience; this type does not ever change.
template<class T>
using Parser = std::function<Result<T>(std::shared_ptr<State>)>;

template<class I, class O>
Parser<O> Apply(Parser<I> parse, std::function<O(I)> f) {
  return [parse, f](std::shared_ptr<State> state) {
    auto result = parse(state);
    if (!result.success()) {
      return Result<O>(false, "failed to parse");
    }
    return Result<O>(f(result.value()));
  };
}

Parser<std::string> Literal(char c) {
  return [c](std::shared_ptr<State> state) {
    if (state->atEnd()) {
      return Result<std::string>(false, "end of file");
    }
    char next = state->readChar();

    if (next == c) {
      state->advance();
      return Result<std::string>(std::string(1, c));
    } else {
      std::string err = "no match for character: ";
      err += c;
      return Result<std::string>(false, err);
    }
  };
}

template<class T>
Parser<T> Or(Parser<T> parseA, Parser<T> parseB) {
  // Note: we don't need to rewind the input here.  Since at most ONE parser
  // will successfully run, the input parsers will can rewind for us
  return [parseA, parseB](std::shared_ptr<State> state) {
    auto resultA = parseA(state);
    if (resultA.success()) {
      return resultA;
    }
    auto resultB = parseB(state);
    if (resultB.success()) {
      return resultB;
    }
    return Result<T>(false, "no match for A or B");
  };
}

template<class T>
Parser<std::array<T, 2>> And(Parser<T> parseA, Parser<T> parseB) {
  return [parseA, parseB](std::shared_ptr<State> state) {
    // Save position so we can reset later.
    int oldPosition = state->position();
    auto resultA = parseA(state);
    if (!resultA.success()) {
      state->setPosition(oldPosition);
      return Result<std::array<T, 2>>(false, "no match for A and B");
    }
    auto resultB = parseB(state);
    if (!resultB.success()) {
      state->setPosition(oldPosition);
      return Result<std::array<T, 2>>(false, "no match for A and B");
    }
    std::array<T, 2> res{{ resultA.value(), resultB.value() }};
    return Result<std::array<T, 2>>(res);

  };
}


}  // namespace frontend
}  // namespace cs160

#endif  // FRONTEND_COMBINATOR_PARSER_H_
