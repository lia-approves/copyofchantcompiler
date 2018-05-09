// Copyright (c) 2018, Team-Chant

#ifndef FRONTEND_COMBINATOR_PARSER_H_
#define FRONTEND_COMBINATOR_PARSER_H_

#include <array>
#include <vector>
#include "frontend/combinator/result.h"
#include "frontend/combinator/state.h"
#include "utility/memory.h"

namespace cs160 {
namespace frontend {

// Represents a 'parse function': a function which takes a state and returns
// a result.  Just an alias for convenience; this type does not ever change.
template<class T>
using Parser = std::function<Result<T>(std::shared_ptr<State>)>;

//  Returns a function which:
//  runs the parser, then runs f on the result, then returns the final result
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

// Return a function which parses a single literal
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

// Prototype range
/*
Parser<std::string> Range(string c) {
    return [c](std::shared_ptr<State> state) {
      if (state->atEnd()) {
        return Result<std::string>(false, "end of file");
      }
      char a = c.at(0);
      char b = c.at(1);
      if(a - 'a' > b - 'a'){
        return Result<std::string>(false, "improper range");
      }

      while(!state->atEnd()){
        char next = state->readChar();
        if(next - 'a' > b - 'a'){
          return Result<std::string>(false, "greater than range");
        }else if(next - 'a' < a - 'a'){
          return Result<std::string>(false, "less than range");
        }
      }

      state->advance();
      return Result<std::string>(std::string(1, c));
    };
  }
  */

// Return a function which runs 1 parser, then the next.  That function returns
// the first successful result (or failure)
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

//  Returns a function which runs 2 parsers, and returns an array of their
//  results.  If either fails, it returns failure
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

// Returns a function which runs a parser 0 or more times, returning all results
template<class T>
Parser<std::vector<T>> Star(Parser<T> parse) {
  return [parse](std::shared_ptr<State> state) {
    std::vector<T> results;
    auto currentResult = parse(state);  // Parse first element before the loop
    while (currentResult.success()) {
      results.push_back(currentResult.value());
      currentResult = parse(state);
    }
    if (results.size() == 0) {
      return Result<std::vector<T>>(false, "no matches at all");
    }
    return Result<std::vector<T>>(results);
  };
}

}  // namespace frontend
}  // namespace cs160

#endif  // FRONTEND_COMBINATOR_PARSER_H_
