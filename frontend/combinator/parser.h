// Copyright (c) 2018, Team-Chant

#ifndef FRONTEND_COMBINATOR_PARSER_H_
#define FRONTEND_COMBINATOR_PARSER_H_

#include <array>
#include <vector>
#include <string>
#include <iostream>
#include <tuple>
#include "frontend/combinator/result.h"
#include "frontend/combinator/state.h"
#include "utility/memory.h"
#include "abstract_syntax/abstract_syntax.h"

namespace cs160 {
namespace frontend {

// Represents a 'parse function': a function which takes a state and returns
// a result.  Just an alias for convenience; this type does not ever change.
using Parser = std::function<Result(State)>;

using Node = std::unique_ptr<abstract_syntax::frontend::AstNode>;

template<class T>
using NodeMaker = std::function<Node(T)>;

template<class T>
using Converter = std::function<Value(T)>;

// class DummyVisitor

// template<class T>
// class DummyNode : public abstract_syntax::frontend::AstNode {
//  public:
//   explicit DummyNode(T value) {
//     value_ = value;
//   }
//   T value() {
//     return value_;
//   }
//   void Visit(abstract_syntax::frontend::AstVisitor* visitor) const { visitor->VisitDummy(*this); }
//  private:
//   T value_;
// };

// NodeMaker<T> ToDummyNode = [](T value) {
//   return std::unique_ptr<abstract_syntax::frontend::AstNode>(new DummyNode<T>(value));
// };

Value ToStringValue(std::string s) {
  return Value(s);
}

// Assumes both values are strings.  If one isn't, throws an exception
Value Concat(Value v1, Value v2) {
  if (v1.Type() != Value::type::string || v2.Type() != Value::type::string) {
    throw std::logic_error("Attempted to concatenate non-string values.");
  }
  return Value(v1.String() + v2.String());
}

//  Returns a function which:
//  runs the parser, then runs f on the result, then returns the final result
// template<class I, class O>
// Parser Apply(Parser parse, std::function<O(I)> f) {
//   return [parse, f](State state) {
//     auto result = parse(state);
//     if (!result.success()) {
//       return Result<O>(state, false, "failed to parse");
//     }
//     return Result<O>(state, f(result.value()));
//   };
// }

// Return a function which parses a single literal
Parser Literal(char c, Converter<std::string> ToValue = ToStringValue) {
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

// Returns a function which checks if a character is within
// a range of two characters
Parser Range(std::string c, Converter<std::string> ToValue = ToStringValue) {
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

// Return a function which runs 1 parser, then the next.  That function returns
// the first successful result (or failure)
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

//  Returns a function which runs 2 parsers, and returns an array of their
//  results.  If either fails, it returns failure
Parser And(Parser parseA, Parser parseB, std::function<Value(Value, Value)> ToValue = Concat) {
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
    return Result(resultB.state(), ToValue(resultA.value(), resultB.value()));
  };
}

// Returns a function which runs a parser 0 or more times, returning all results
// template<class T>
// Parser Star(Parser Parse, Converter<std::vector<Value>> ToNode) {
//   return [Parse, ToNode](State state) {
//     std::vector<Value> results;
//     auto currentResult = Parse(state);
//     // Parse first element before the loop
//     while (currentResult.success()) {
//       if (currentResult.value().Type() == Value::type::string) {
//         results.push_back(Value(currentResult.value().String()));
//       } else if (currentResult.value().Type() == Value::type::node) {
//         results.push_back( Value(Node()) );
//       }
//       currentResult = Parse(currentResult.state());
//     }
//     return currentResult;
//     // return Result(currentResult.state(), std::move(ToNode(std::move(results))));
//   };
// }


// // Returns a function which runs a parser 1 or more times, returning all results
// Parser> OnePlus(Parser parse) {
//   return [parse](State state) {
//     std::vector<T> results;
//     auto currentResult = parse(state);  // Parse first element before the loop
//     while (currentResult.success()) {
//       results.push_back(currentResult.value());
//       currentResult = parse(currentResult.state());
//     }
//     if (results.size() == 0) {  // Must have one or more match, unlike Star()
//        return Result<std::vector<T>>(state, false, "no matches at all");
//     }
//     return Result<std::vector<T>>(state, results);
//   };
// }

// Returns a function which runs a parser, and returns a success if it fails
// and a failure if it succeeds
 Parser Not(Parser parse, Converter<std::string> ToValue = ToStringValue) {
     return [parse, ToValue](State state) {
       auto result = parse(state);
       if (result.success()) {
         return Result(state, false, "no match for not");
       }
       char temp = state.readChar();
       return Result(state, ToValue(std::string(1, temp)));;
     };
 }
 /*
 Parser Literal(char c, Converter<std::string> ToValue = ToStringValue) {
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
 */
// Return a function which parses a string (whitespace sensitive)
Parser ExactMatch(std::string str, Converter<std::string> ToValue = ToStringValue) {
  return [str, ToValue](State state) {
    if (state.atEnd()) {
      return Result(state, false, "end of file");
    }

    std::string ret = "";

    for (int i = 0; i < str.size(); i++) {
        char next_p = state.readChar();
        char next_str = str.at(i);

        if (next_p != next_str) {
          return Result(state, false, "no match for " + str);
        } else {
          ret += state.readChar();
          state.advance();
        }

        if (state.atEnd() && i != str.size() - 1) {
          // checks if it is at the end of the file
          // must have the second statement to avoid
          // returning on the last check
          return Result(state, false, "end of file");
        }
    }
    // got to end of string with all characters matching
    // and not reaching end of file
    // therefore, return success
    return Result(state, ToValue(ret));
  };
}

// // Return a function which parses a string (whitespace insensitive)
// // AKA this function ignores whitespace in either state or string
// Parser Match(std::string str) {
//   return [str](State state) {
//     if (state.atEnd()) {
//       return Result<std::string>(state, false, "end of file");
//     }
//
//     int counter = 0;
//     while (!state.atEnd() && counter < str.size()) {
//       char next_p = state.readChar();
//       char next_str = str.at(counter);
//       counter++;
//
//       while (next_p == ' ' && !state.atEnd()) {
//         state.advance();
//         next_p = state.readChar();
//       }
//       while (next_str == ' ' && counter < str.size()) {
//         next_str = str.at(counter);
//         counter++;
//       }
//
//       if ( (state.atEnd() || counter >= str.size())
//         && (next_p == ' ' || next_str == ' ') ) {
//           // for one of the strings, the last character is a whitespace
//         break;
//       }
//
//       if (next_p != next_str) {
//         return Result<std::string>(state, false, "no match for " + str);
//       } else {
//         state.advance();
//       }
//     }
//     // got to end of string with all characters matching
//     // and not reaching end of file
//     // therefore, return success
//     return Result<std::string>(state, str);
//   };
// }
//
// Parser Between(Parser parseA, Parser parseB, Parser parseC) {
//   return [parseA, parseB, parseC](State state) {
//     // Save position so we can reset later.
//     int oldPosition = state.position();
//     auto resultA = parseA(state);
//     if (!resultA.success()) {
//       state.setPosition(oldPosition);
//       return Result<T>(state, false, "C is not between A and B");
//     }
//
//     auto resultB = parseB(resultA.state());
//     if (!resultB.success()) {
//       state.setPosition(oldPosition);
//       return Result<T>(state, false, "C is not between A and B");
//     }
//
//     auto resultC = parseC(resultB.state());
//     if (!resultC.success()) {
//       state.setPosition(oldPosition);
//       return Result<T>(state, false, "C is not between A and B");
//     }
//
//     return Result<T>(resultB.state(), resultB.value());
//   };
// }
//
// //  Returns a function which runs 2 parsers, and returns an array of their
// //  results.
// Parser Sequence (Parser parseA, Parser parseB, Parser parseC) {
//   return [parseA, parseB, parseC](State state) {
//     // Save position so we can reset later.
//     int oldPosition = state.position();
//     auto resultA = parseA(state);
//     if (!resultA.success()) {
//       state.setPosition(oldPosition);
//       return Result<std::tuple<A, B, C>>
//               (state, false, "no match for A, B, and C");
//     }
//     auto resultB = parseB(resultA.state());
//     if (!resultB.success()) {
//       state.setPosition(oldPosition);
//       return Result<std::tuple<A, B, C>>
//               (state, false, "no match for A, B, and C");
//     }
//
//     auto resultC = parseC(resultB.state());
//     if (!resultC.success()) {
//       state.setPosition(oldPosition);
//       return Result<std::tuple<A, B, C>>
//               (state, false, "no match for A, B, and C");
//     }
//
//     std::tuple<A, B, C> res = std::make_tuple
//             (resultA.value(), resultB.value(), resultC.value());
//     return Result<std::tuple<A, B, C>>(resultC.state(), res);
//   };
// }

}  // namespace frontend
}  // namespace cs160

#endif  // FRONTEND_COMBINATOR_PARSER_H_
