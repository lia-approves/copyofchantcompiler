// Copyright (c) 2018, Team-Chant

#include <utility>
#include <iostream>
#include <unordered_map>
#include "frontend/combinator/parser.h"

namespace cs160 {
namespace frontend {
namespace Parse {

bool done_with_star = false;

std::function<CopyVisitor()> Copier;

bool copyVisitorIsSet = false;
void SetCopyVisitor(std::function<CopyVisitor()> copier) {
  copyVisitorIsSet = true;
  Copier = copier;
}

Parser Literal(char c, Converter<std::string> ToValue) {
  static std::unordered_map<State, Result> cache;
  return [c, ToValue](State state) {
    if (copyVisitorIsSet && (cache.find(state) != cache.end())) {
      std::cout << "retrieving Literal from cache\n";

    }
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
    // std::cout <<__PRETTY_FUNCTION__ << "BADNESS 9000" << std::endl;
    // exit(0);

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

Parser Or(std::vector<Parser> p_vec) {
  return [p_vec](State state) {


    int size = p_vec.size();
    for (int i=0; i < size; i++) {
      auto curr_parser = p_vec.at(i);
      auto curr_result = curr_parser(state);
      if (curr_result.success()) {
        return curr_result;
      }
    }

    return Result(state, false, "no match for vector of parsers");
  };
}

Parser And(Parser parseA, Parser parseB,
  std::function<Value(Value, Value)> ToValue) {
      return [parseA, parseB, ToValue](State state) {
        // Save position so we can reset later.
        std::string curr_s = state.getString();
      //  int pos = state.position();

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
          ToValue(resultA.value(), resultB.value()));
      };
}

Parser And(std::vector<Parser> p_vec,
    std::function<Value(Value, Value)> ToValue) {
  return[p_vec, ToValue](State state) {
    // std::cout <<__PRETTY_FUNCTION__ << "BADNESS 9000" << std::endl;
    // exit(0);

    int size = p_vec.size();
    int oldPosition = state.position();
    auto curr_parser = p_vec.at(0);
    auto curr_result = curr_parser(state);
    if (!curr_result.success()) {
      state.setPosition(oldPosition);
      return Result(state, false, "No result for vector of parsers");
    }

    auto curr_value = curr_result.value();
    for (int i=1; i < size; i++) {
      curr_parser = p_vec.at(i);
      curr_result = curr_parser(curr_result.state());
      if (!curr_result.success()) {
        state.setPosition(oldPosition);
        return Result(state, false, "No result for vector of parsers");
      }
        curr_value = ToValue(std::move(curr_value), curr_result.value());
    }
    // if it does not return in the for loop, then
    // all of the parsers achieve success
    // therefore, return a success

    return Result(curr_result.state(), std::move(curr_value));
  };
}

Parser Star(Parser Parse, Converter<std::vector<Value>> ToNode) {
  return [Parse, ToNode](State state) {


    std::vector<Value> results;
    auto currentResult = Parse(state);
    // Parse first element before the loop
    while (currentResult.success()) {
      Value v = currentResult.value();
      results.push_back(std::move(v) );
      if (currentResult.state().atEnd()) {
        break;
      }
      currentResult = Parse(currentResult.state());
    }

    // return currentResult;
    return Result(currentResult.state(), ToNode(std::move(results)));
  };
}

Parser Not(Parser parse, Converter<std::string> ToValue) {
  return [parse, ToValue](State state) {
    // std::cout <<__PRETTY_FUNCTION__ << "BADNESS 9000" << std::endl;
    // exit(0);

    auto result = parse(state);
    if (result.success()) {
       return Result(state, false, "no match for not");
    }
    char temp = state.readChar();
    return Result(state, ToValue(std::string(1, temp)));;
  };
}

// Returns a function which runs a parser 1 or more times, returning all results
Parser OnePlus(Parser parse, Converter<std::vector<Value>> ToNode) {
  return [parse, ToNode](State state) {
    // std::cout <<__PRETTY_FUNCTION__ << "BADNESS 9000" << std::endl;
    // exit(0);

    std::vector<Value> results;
    auto currentResult = parse(state);
          // Parse first element before the loop
    while (currentResult.success()) {
      Value v = currentResult.value();
      results.push_back(std::move(v) );
      currentResult = parse(currentResult.state());
    }
    if (results.size() == 0) {  // Must have one or more match, unlike Star()
       return Result(state, false, "no matches at all");
    }
    return Result(currentResult.state(), ToNode(std::move(results)));
  };
}

// Return a function which parses a string (whitespace sensitive)
Parser ExactMatch(std::string str,
    Converter<std::string> ToValue) {
  return [str, ToValue](State state) {
    // std::cout <<__PRETTY_FUNCTION__ << "BADNESS 9000" << std::endl;
    // exit(0);

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


// Return a function which parses a string (whitespace insensitive)
// AKA this function ignores whitespace in either state or string
Parser Match(std::string str, Converter<std::string> ToValue) {
  return [str, ToValue](State state) {
    // std::cout <<__PRETTY_FUNCTION__ << "BADNESS 9000" << std::endl;
    // exit(0);

    if (state.atEnd()) {
      return Result(state, false, "end of file");
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
        return Result(state, false, "no match for " + str);
      } else {
        state.advance();
      }
    }
    // got to end of string with all characters matching
    // and not reaching end of file
    // therefore, return success
    return Result(state, ToValue(str));
  };
}


Parser Between(Parser parseA, Parser parseB,
    Parser parseC, Converter<std::string> ToValue) {
  return [parseA, parseB, parseC, ToValue](State state) {
    // std::cout <<__PRETTY_FUNCTION__ << "BADNESS 9000" << std::endl;
    // exit(0);

    // Save position so we can reset later.
    int oldPosition = state.position();
    auto resultA = parseA(state);
    if (!resultA.success()) {
      state.setPosition(oldPosition);
      return Result(state, false, "C is not between A and B");
    }

    auto resultB = parseB(resultA.state());
    if (!resultB.success()) {
      state.setPosition(oldPosition);
      return Result(state, false, "C is not between A and B");
    }

    auto resultC = parseC(resultB.state());
    if (!resultC.success()) {
      state.setPosition(oldPosition);
      return Result(state, false, "C is not between A and B");
    }

    return Result(resultB.state(), resultB.value());
  };
}

Parser Int(Converter<std::string> ToNode) {
  return [ToNode](State state) {

    auto parse = Range("09");
    auto res = parse(state);
    if (!res.success()) {
      return Result(state, false, "not an integer");
    }
    // auto result = Result(res.state(), ToNode(res.value().String()));
    auto v = ToNode(res.value().GetString());
    return Result(res.state(), std::move(v));
  };
}

//  Returns a function which runs 3 parsers, and returns an array of their
// results.

struct SequenceLambda {
  Parser parseA, parseB, parseC;
  Converter<std::vector<Value>> ToNode;

  Result operator()(State state) {
    // std::cout <<__PRETTY_FUNCTION__ << "BADNESS 9000" << std::endl;
    // exit(0);

    std::string curr_s = state.getString();
    int pos = state.position();
    if (curr_s.at(pos) == '}') {
      state.setPosition(pos);
      return Result(state, false, "no match for A, B, and C");
    }

    // Save position so we can reset later.
    int oldPosition = state.position();
    std::vector<Value> results;
    auto resultA = parseA(state);
    if (!resultA.success()) {
      state.setPosition(oldPosition);
      return Result(state, false, "no match for A, B, and C");
    }

    auto resultB = parseB(resultA.state());
    if (!resultB.success()) {
      state.setPosition(oldPosition);
      return Result(state, false, "no match for A, B, and C");
    }

    auto resultC = parseC(resultB.state());
    if (!resultC.success()) {
      state.setPosition(oldPosition);
      return Result(state, false, "no match for A, B, and C");
    }
    Value v1 = resultA.value();
    Value v2 = resultB.value();
    Value v3 = resultC.value();
    results.push_back(std::move(v1) );
    results.push_back(std::move(v2) );
    results.push_back(std::move(v3) );
    return Result(resultC.state(), ToNode(std::move(results)));
  }
};

Parser Sequence(Parser parseA, Parser parseB, Parser parseC,
    Converter<std::vector<Value>> ToNode) {

  return SequenceLambda {parseA, parseB, parseC, ToNode};
  // return [parseA, parseB, parseC, ToNode](State state) {

  // };
}

Parser Debug(Parser parser, std::string text) {
  return [parser, text](State state) {
      if (state.position() == state.getString().size()) {
        std::cout << text << "  ; at end\n";
      } else {
        std::cout << text << "  remaining state: " << state.getString().substr(state.position()) << std::endl;
      }
      return parser(state);
  };
}

}  // namespace Parse
}  // namespace frontend
}  // namespace cs160
