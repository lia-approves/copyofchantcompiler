// Copyright (c) 2018, Team-Chant

#ifndef FRONTEND_COMBINATOR_PARSER_H_
#define FRONTEND_COMBINATOR_PARSER_H_

#include <array>
#include <vector>
#include <string>
#include <iostream>
#include "frontend/combinator/result.h"
#include "frontend/combinator/state.h"
#include "utility/memory.h"

namespace cs160 {
namespace frontend {

// Represents a 'parse function': a function which takes a state and returns
// a result.  Just an alias for convenience; this type does not ever change.
template<class T>
using Parser = std::function<Result<T>(State)>;

using Node = std::unique_ptr<abstract_syntax::frontend::AstNode>;

template<class T>
using NodeMaker = std::function<Node(T)>;

//  Returns a function which:
//  runs the parser, then runs f on the result, then returns the final result
// template<class I, class O>
// Parser<O> Apply(Parser<I> parse, std::function<O(I)> f) {
//   return [parse, f](State state) {
//     auto result = parse(state);
//     if (!result.success()) {
//       return Result<O>(state, false, "failed to parse");
//     }
//     return Result<O>(state, f(result.value()));
//   };
// }

template<class T>
Parser<Node> Capture(Parser<T> Parse, NodeMaker<T> MakeNode) {
  return [Parse, MakeNode](State state) {
    auto result = Parse(state);
    Result<Node> ret(result.state(), MakeNode(result.value()));
    return ret;
  };
}

// Return a function which parses a single literal
Parser<std::string> Literal(char c) {
  return [c](State state) {
    if (state.atEnd()) {
      return Result<std::string>(state, false, "end of file");
    }
    char next = state.readChar();

    if (next == c) {
      state.advance();
      return Result<std::string>(state, std::string(1, c));
    } else {
      std::string err = "no match for character: ";
      err += c;
      return Result<std::string>(state, false, err);
    }
  };
}

// Returns a function which checks if a character is within
// a range of two characters
Parser<std::string> Range(std::string c) {
    return [c](State state) {
      if (state.atEnd()) {
        return Result<std::string>(state, false, "end of file");
      }
      char a = c.at(0);
      char b = c.at(1);

      if (a - 'a' >= b - 'a') {
        return Result<std::string>(state, false, "improper range");
      }

      char next = state.readChar();
      if (next - 'a' >= a - 'a' && next - 'a' <= b - 'a') {
        state.advance();
        return Result<std::string>(state, std::string(1, next));
      } else {
        std::string err = "not in range for character: ";
        err += next;
        return Result<std::string>(state, false, err);
      }
    };
  }

// Return a function which runs 1 parser, then the next.  That function returns
// the first successful result (or failure)
template<class T>
Parser<T> Or(Parser<T> parseA, Parser<T> parseB) {
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
    return Result<T>(state, false, "no match for A or B");
  };
}

//  Returns a function which runs 2 parsers, and returns an array of their
//  results.  If either fails, it returns failure
template<class A, class B>
Parser<std::tuple<A, B>> And(Parser<A> parseA, Parser<B> parseB) {
  return [parseA, parseB](State state) {
    // Save position so we can reset later.
    int oldPosition = state.position();
    auto resultA = parseA(state);
    if (!resultA.success()) {
      state.setPosition(oldPosition);
      return Result<std::tuple<A, B>>(state, false, "no match for A and B");
    }
    auto resultB = parseB(resultA.state());
    if (!resultB.success()) {
      state.setPosition(oldPosition);
      return Result<std::tuple<A, B>>(state, false, "no match for A and B");
    }
    std::tuple<A, B> res = std::make_tuple(resultA.value(), resultB.value());
    return Result<std::tuple<A, B>>(resultB.state(), res);
  };
}

// Returns a function which runs a parser 0 or more times, returning all results
// template<class T>
// Parser<std::vector<T>> Star(Parser<T> parse) {
//   return [parse](State state) {
//     std::vector<T> results;
//     auto currentResult = parse(state);  // Parse first element before the loop
//     while (currentResult.success()) {
//       results.push_back(currentResult.value());
//       currentResult = parse(currentResult.state());
//     }
//     // if (results.size() == 0) {
//     //   return Result<std::vector<T>>(state, false, "no matches at all");
//     // }
//     return Result<std::vector<T>>(state, results);
//   };
// }

// Returns a function which runs a parser 1 or more times, returning all results
template<class T>
Parser<std::vector<T>> OnePlus(Parser<T> parse) {
  return [parse](State state) {
    std::vector<T> results;
    auto currentResult = parse(state);  // Parse first element before the loop
    while (currentResult.success()) {
      results.push_back(currentResult.value());
      currentResult = parse(currentResult.state());
    }
    if (results.size() == 0) {  // Must have one or more match, unlike Star()
       return Result<std::vector<T>>(state, false, "no matches at all");
    }
    return Result<std::vector<T>>(state, results);
  };
}

// Returns a function which runs a parser, and returns a success if it fails
// and a failure if it succeeds
template<class T>
Parser<T> Not(Parser<T> parse) {
    return [parse](State state) {
      auto result = parse(state);
      if (result.success()) {
        return Result<T>(state, false, "no match for not");
      }
      return Result<std::string>(state, "!");;
    };
}

// Return a function which parses a string (whitespace sensitive)
Parser<std::string> ExactMatch(std::string str) {
  return [str](State state) {
    if (state.atEnd()) {
      return Result<std::string>(state, false, "end of file");
    }

    for (int i=0; i < str.size(); i++) {
        char next_p = state.readChar();
        char next_str = str.at(i);

        if (next_p != next_str) {
          return Result<std::string>(state, false, "no match for " + str);
        } else {
          state.advance();
        }

        if (state.atEnd() && i != str.size()-1) {
          // checks if it is at the end of the file
          // must have the second statement to avoid
          // returning on the last check
          return Result<std::string>(state, false, "end of file");
        }
    }

    // got to end of string with all characters matching
    // and not reaching end of file
    // therefore, return success
    return Result<std::string>(state, str);
  };
}

// Return a function which parses a string (whitespace insensitive)
// AKA this function ignores whitespace in either state or string
Parser<std::string> Match(std::string str) {
  return [str](State state) {
    if (state.atEnd()) {
      return Result<std::string>(state, false, "end of file");
    }

    int counter = 0;
    while (!state.atEnd() && counter < str.size()) {
      char next_p = state.readChar();
      char next_str = str.at(counter);
      counter++;

      while (next_p == ' ' && !state.atEnd()) {
        state.advance();
        next_p = state.readChar();
      }
      while (next_str == ' ' && counter < str.size()) {
        next_str = str.at(counter);
        counter++;
      }

      if ( (state.atEnd() || counter >= str.size())
        && (next_p == ' ' || next_str == ' ') ) {
          // for one of the strings, the last character is a whitespace
        break;
      }

      if (next_p != next_str) {
        return Result<std::string>(state, false, "no match for " + str);
      } else {
        state.advance();
      }
    }
    // got to end of string with all characters matching
    // and not reaching end of file
    // therefore, return success
    return Result<std::string>(state, str);
  };
}

template <class T>
Parser<T> Between(Parser<T> parseA, Parser<T> parseB, Parser<T> parseC) {
  return [parseA, parseB, parseC](State state) {
    // Save position so we can reset later.
    int oldPosition = state.position();
    auto resultA = parseA(state);
    if (!resultA.success()) {
      state.setPosition(oldPosition);
      return Result<T>(state, false, "C is not between A and B");
    }

    auto resultB = parseB(resultA.state());
    if (!resultB.success()) {
      state.setPosition(oldPosition);
      return Result<T>(state, false, "C is not between A and B");
    }

    auto resultC = parseC(resultB.state());
    if (!resultC.success()) {
      state.setPosition(oldPosition);
      return Result<T>(state, false, "C is not between A and B");
    }

    return Result<T>(resultB.state(), resultB.value());
  };
}

}  // namespace frontend
}  // namespace cs160

#endif  // FRONTEND_COMBINATOR_PARSER_H_
