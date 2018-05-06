// Copyright (c) 2018, Team-Chant

#ifndef FRONTEND_COMBINATOR_PARSER_H_
#define FRONTEND_COMBINATOR_PARSER_H_

#include "frontend/combinator/result.h"
#include "frontend/combinator/state.h"
#include "utility/memory.h"

namespace cs160 {
namespace frontend {

// Represents a 'parse function': a function which takes a state and returns
// a result.  Just an alias for convenience; this type does not ever change.
template<class T>
using Parser = std::function<Result<T>(std::shared_ptr<State>)>;

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

template<class A, class B, class R>
Parser<R> Or(Parser<A> parseA, Parser<B> parseB) {
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
    return Result<R>(false, "no match for A or B");
  };
}

// template<class A, class B, class R>
// Parser<R> And(Parser<A> parseA, Parser<B> parseB) {
//   return [parseA, parseB](std::shared_ptr<State> state) {
//     // Save position so we can reset later.
//     int oldPosition = state->position();
//     auto resultA = parseA(state);
//     if (!resultA.success()) {
//       state->position(oldPosition);
//       return Result<R>
//     }
//     auto
//
//   }
// }


}  // namespace frontend
}  // namespace cs160

#endif  // FRONTEND_COMBINATOR_PARSER_H_
