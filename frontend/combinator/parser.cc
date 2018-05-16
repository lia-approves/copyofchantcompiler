// Copyright (c) 2018, Team-Chant

#include <utility>
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

Parser Or(Parser parseA, Parser parseB) {
  // Note: we don't need to rewind the input here.  Since at most ONE parser
  // will successfully run, the input parsers will can rewind for us
  return [parseA, parseB](State state) {
    auto resultA = parseA(state);
    if (resultA.success()) {
      return resultA;
    }
    auto resultB = parseB(state);
    if (resultB.success()) {
      return resultB;
    }
    return Result(state, false, "no match for A or B");
  };
}

Parser And(Parser parseA, Parser parseB,
  std::function<Value(Value, Value)> ToValue) {
      return [parseA, parseB, ToValue](State state) {
        // Save position so we can reset later.
        int oldPosition = state.position();
        auto resultA = parseA(state);
        if (!resultA.success()) {
          state.setPosition(oldPosition);
          return Result(state, false, "no match for A and B");
        }
        auto resultB = parseB(resultA.state());
        if (!resultB.success()) {
          state.setPosition(oldPosition);
          return Result(state, false, "no match for A and B");
        }
        return Result(
          resultB.state(),
          ToValue(resultA.value(), resultB.value())
        );
      };
}

Parser Star(Parser Parse, Converter<std::vector<Value>> ToNode) {
  return [Parse, ToNode](State state) {
    std::vector<Value> results;
    auto currentResult = Parse(state);
    // Parse first element before the loop
    while (currentResult.success()) {
      Value v = currentResult.value();
      results.push_back( std::move(v) );
      currentResult = Parse(currentResult.state());
    }
    // return currentResult;
    return Result(currentResult.state(), ToNode(std::move(results)));
  };
}

Parser Not(Parser parse, Converter<std::string> ToValue) {
  return [parse, ToValue](State state) {
    auto result = parse(state);
    if (result.success()) {
      return Result(state, false, "no match for not");
    }
    char temp = state.readChar();
    return Result(state, ToValue(std::string(1, temp)));;
  };
}

}  // namespace Parse
}  // namespace frontend
}  // namespace cs160
