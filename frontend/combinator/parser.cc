// Copyright (c) 2018, Team-Chant

#include "frontend/combinator/parser.h"

namespace cs160 {
namespace frontend {
namespace Parse {

Parser Literal(char c, Converter<std::string> ToValue) {
  return [c, ToValue](State state) {
    if (state.atEnd()) {
      return Result(state, false, "end of file");
    }
    char next = state.readChar();

    if (next == c) {
      state.advance();
      return Result(state, ToValue(std::string(1, c)));
    } else {
      std::string err = "no match for character: ";
      err += c;
      return Result(state, false, err);
    }
  };
}

Parser Range(std::string c, Converter<std::string> ToValue) {
  return [c, ToValue](State state) {
    if (state.atEnd()) {
      return Result(state, false, "end of file");
    }
    char a = c.at(0);
    char b = c.at(1);

    if (a - 'a' >= b - 'a') {
      return Result(state, false, "improper range");
    }

    char next = state.readChar();

    if (next - 'a' >= a - 'a' && next - 'a' <= b - 'a') {
      state.advance();
      return Result(state, ToValue(std::string(1, next)));
    } else {
      std::string err = "not in range for character: ";
      err += next;
      return Result(state, false, err);
    }
  };
}

}  // namespace Parse
}  // namespace frontend
}  // namespace cs160