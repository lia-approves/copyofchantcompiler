// Copyright (c) 2018, Team-Chant

#include <utility>
#include <iostream>
#include <unordered_map>
#include "frontend/combinator/parser.h"

namespace cs160 {
namespace frontend {
namespace Parse {

bool done_with_star = false;

std::function<CopyVisitor*()> MakeCopyVisitor;

bool copyVisitorIsSet = false;
void SetCopyVisitor(std::function<CopyVisitor*()> copier) {
  copyVisitorIsSet = true;
  MakeCopyVisitor = copier;
}

Result CacheNodeResult(
  Result res,
  // Use raw pointer to because a smart ptr could delete cache.
  std::unordered_map<State, std::unique_ptr<Value>>* cache) {

  if (!copyVisitorIsSet) return res;
  // Probably need to use two copiers, since GetCopy() will move the copy.
  auto copier1 = MakeCopyVisitor();
  auto copier2 = MakeCopyVisitor();
  auto value = res.value();
  value.GetNodeUnique()->Visit(copier1);
  value.GetNodeUnique()->Visit(copier2);
  auto copy1 = copier1->GetCopy();
  auto copy2 = copier2->GetCopy();
  (*cache)[res.state()] = std::make_unique<Value>(Value(std::move(copy1)));
  return Result(res.state(), Value(std::move(copy2)));
}

Parser Literal(char c, Converter<std::string> ToValue) {
  static std::unordered_map<State, std::unique_ptr<Value>> cache;
  return [c, ToValue](State state) {
    // Check cache first before calculating
    if (copyVisitorIsSet && (cache.find(state) != cache.end())) {
      // Check if value is empty:
      if (cache[state]->GetType() == Value::empty) {
        return Result(state, false, "cached empty value");
      }
      // Check if value is a string:
      if (cache[state]->GetType() == Value::string) {
        return Result(state, ToValue(cache[state]->GetString()));
      }
      // Retrieve the node from cached value.
      // At this point, the cached value is empty.
      auto node = cache[state]->GetNodeUnique();
      auto copier
        = MakeCopyVisitor();
      node->Visit(copier);
      auto nodeCopy = copier->GetCopy();
      // Since restore the cached value.
      cache[state] = std::make_unique<Value>(Value(std::move(node)));
      // Return a new result, using the copy of the node we made.
      return Result(state, Value(std::move(nodeCopy)));
    }

    if (state.atEnd()) {
      if (copyVisitorIsSet) {
        cache[state] = std::make_unique<Value>(Value());
      }
      return Result(state, false, "end of file");
    }
    char next = state.readChar();

    if (next == c) {
      state.advance();
      if (copyVisitorIsSet) {
        cache[state] = std::make_unique<Value>(ToValue(std::string(1, c)));
      }
      return Result(state, ToValue(std::string(1, c)));
    } else {
      std::string err = "no match for character: ";
      err += c;
      std::cout << "caching...\n";
      if (copyVisitorIsSet) {
        cache[state] = std::make_unique<Value>(Value());
      }
      return Result(state, false, err);
    }
  };
}

Parser Range(std::string c, Converter<std::string> ToValue) {
  static std::unordered_map<State, std::unique_ptr<Value>> cache;
  return [c, ToValue](State state) {
    // Check cache first before calculating
    if (copyVisitorIsSet && (cache.find(state) != cache.end())) {
      // Check if value is empty:
      if (cache[state]->GetType() == Value::empty) {
        return Result(state, false, "cached empty value");
      }
      // Check if value is a string:
      if (cache[state]->GetType() == Value::string) {
        return Result(state, ToValue(cache[state]->GetString()));
      }
      // Retrieve the node from cached value.
      // At this point, the cached value is empty.
      auto node = cache[state]->GetNodeUnique();
      auto copier
        = MakeCopyVisitor();
      node->Visit(copier);
      auto nodeCopy = copier->GetCopy();
      // Since restore the cached value.
      cache[state] = std::make_unique<Value>(Value(std::move(node)));
      // Return a new result, using the copy of the node we made.
      return Result(state, Value(std::move(nodeCopy)));
    }

    if (state.atEnd()) {
      if (copyVisitorIsSet) {
        cache[state] = std::make_unique<Value>(Value());
      }
      return Result(state, false, "end of file");
    }
    char a = c.at(0);
    char b = c.at(1);

    if (a - 'a' >= b - 'a') {
      if (copyVisitorIsSet) {
        cache[state] = std::make_unique<Value>(Value());
      }
      return Result(state, false, "improper range");
    }

    char next = state.readChar();

    if (next - 'a' >= a - 'a' && next - 'a' <= b - 'a') {
      state.advance();
      if (copyVisitorIsSet) {
        cache[state] = std::make_unique<Value>(ToValue(std::string(1, next)));
      }
      return Result(state, ToValue(std::string(1, next)));
    } else {
      std::string err = "not in range for character: ";
      err += next;
      if (copyVisitorIsSet) {
        cache[state] = std::make_unique<Value>(Value());
      }
      return Result(state, false, err);
    }
  };
}

Parser Or(Parser parseA, Parser parseB) {
  // Note: we don't need to rewind the input here.  Since at most ONE parser
  // will successfully run, the input parsers will can rewind for us
  static std::unordered_map<State, std::unique_ptr<Value>> cache;
  return [parseA, parseB](State state) {
    // Check cache first before calculating
    if (copyVisitorIsSet && (cache.find(state) != cache.end())) {
      // Check if value is empty:
      if (cache[state]->GetType() == Value::empty) {
        return Result(state, false, "cached empty value");
      }
      // Check if value is a string:
      if (cache[state]->GetType() == Value::string) {
        return Result(state, Value(cache[state]->GetString()));
      }
      // Retrieve the node from cached value.
      // At this point, the cached value is empty.
      auto node = cache[state]->GetNodeUnique();
      auto copier
        = MakeCopyVisitor();
      node->Visit(copier);
      auto nodeCopy = copier->GetCopy();
      // Since restore the cached value.
      cache[state] = std::make_unique<Value>(Value(std::move(node)));
      // Return a new result, using the copy of the node we made.
      return Result(state, Value(std::move(nodeCopy)));
    }

    auto resultA = parseA(state);
    if (resultA.success()) {
      return CacheNodeResult(std::move(resultA), &cache);
    }
    auto resultB = parseB(state);
    if (resultB.success()) {
      return CacheNodeResult(std::move(resultB), &cache);
    }
    if (copyVisitorIsSet) {
      cache[state] = std::make_unique<Value>(Value());
    }
    return Result(state, false, "no match for A or B");
  };
}

Parser Or(std::vector<Parser> p_vec) {
  static std::unordered_map<State, std::unique_ptr<Value>> cache;
  return [p_vec](State state) {
    // Check cache first before calculating
    if (copyVisitorIsSet && (cache.find(state) != cache.end())) {
      // Check if value is empty:
      if (cache[state]->GetType() == Value::empty) {
        return Result(state, false, "cached empty value");
      }
      // Check if value is a string:
      if (cache[state]->GetType() == Value::string) {
        return Result(state, Value(cache[state]->GetString()));
      }
      // Retrieve the node from cached value.
      // At this point, the cached value is empty.
      auto node = cache[state]->GetNodeUnique();
      auto copier
        = MakeCopyVisitor();
      node->Visit(copier);
      auto nodeCopy = copier->GetCopy();
      // Since restore the cached value.
      cache[state] = std::make_unique<Value>(Value(std::move(node)));
      // Return a new result, using the copy of the node we made.
      return Result(state, Value(std::move(nodeCopy)));
    }

    int size = p_vec.size();
    for (int i=0; i < size; i++) {
      auto curr_parser = p_vec.at(i);
      auto curr_result = curr_parser(state);
      if (curr_result.success()) {
        return CacheNodeResult(std::move(curr_result), &cache);
      }
    }

    return Result(state, false, "no match for vector of parsers");
  };
}

Parser And(Parser parseA, Parser parseB,
  std::function<Value(Value, Value)> ToValue) {
      static std::unordered_map<State, std::unique_ptr<Value>> cache;
      return [parseA, parseB, ToValue](State state) {
        // Check cache first before calculating
        if (copyVisitorIsSet && (cache.find(state) != cache.end())) {
          // Check if value is empty:
          if (cache[state]->GetType() == Value::empty) {
            return Result(state, false, "cached empty value");
          }
          // Check if value is a string:
          if (cache[state]->GetType() == Value::string) {
            return Result(state, Value(cache[state]->GetString()));
          }
          // Retrieve the node from cached value.
          // At this point, the cached value is empty.
          auto node = cache[state]->GetNodeUnique();
          auto copier
          = MakeCopyVisitor();
          node->Visit(copier);
          auto nodeCopy = copier->GetCopy();
          // Since restore the cached value.
          cache[state] = std::make_unique<Value>(Value(std::move(node)));
          // Return a new result, using the copy of the node we made.
          return Result(state, Value(std::move(nodeCopy)));
        }
        // Save position so we can reset later.
        std::string curr_s = state.getString();
        //  int pos = state.position();

        int oldPosition = state.position();
        auto resultA = parseA(state);
        if (!resultA.success()) {
          state.setPosition(oldPosition);
          if (copyVisitorIsSet) {
            cache[state] = std::make_unique<Value>(Value());
          }
          return Result(state, false, "no match for A and B");
        }
        auto resultB = parseB(resultA.state());
        if (!resultB.success()) {
          state.setPosition(oldPosition);
          if (copyVisitorIsSet) {
            cache[state] = std::make_unique<Value>(Value());
          }
          return Result(state, false, "no match for A and B");
        }
        Result res(
          resultB.state(),
          ToValue(resultA.value(), resultB.value()));
        return CacheNodeResult(std::move(res), &cache);
      };
}

Parser And(std::vector<Parser> p_vec,
    std::function<Value(Value, Value)> ToValue) {
  static std::unordered_map<State, std::unique_ptr<Value>> cache;
  return[p_vec, ToValue](State state) {
    // Check cache first before calculating
    if (copyVisitorIsSet && (cache.find(state) != cache.end())) {
      // Check if value is empty:
      if (cache[state]->GetType() == Value::empty) {
        return Result(state, false, "cached empty value");
      }
      // Check if value is a string:
      if (cache[state]->GetType() == Value::string) {
        return Result(state, Value(cache[state]->GetString()));
      }
      // Retrieve the node from cached value.
      // At this point, the cached value is empty.
      auto node = cache[state]->GetNodeUnique();
      auto copier
        = MakeCopyVisitor();
      node->Visit(copier);
      auto nodeCopy = copier->GetCopy();
      // Since restore the cached value.
      cache[state] = std::make_unique<Value>(Value(std::move(node)));
      // Return a new result, using the copy of the node we made.
      return Result(state, Value(std::move(nodeCopy)));
    }

    int size = p_vec.size();
    int oldPosition = state.position();
    auto curr_parser = p_vec.at(0);
    auto curr_result = curr_parser(state);
    if (!curr_result.success()) {
      state.setPosition(oldPosition);
      if (copyVisitorIsSet) {
        cache[state] = std::make_unique<Value>(Value());
      }
      return Result(state, false, "No result for vector of parsers");
    }

    auto curr_value = curr_result.value();
    for (int i=1; i < size; i++) {
      curr_parser = p_vec.at(i);
      curr_result = curr_parser(curr_result.state());
      if (!curr_result.success()) {
        state.setPosition(oldPosition);
        if (copyVisitorIsSet) {
          cache[state] = std::make_unique<Value>(Value());
        }
        return Result(state, false, "No result for vector of parsers");
      }
      curr_value = ToValue(std::move(curr_value), curr_result.value());
    }
    // if it does not return in the for loop, then
    // all of the parsers achieve success
    // therefore, return a success

    Result res(curr_result.state(), std::move(curr_value));
    return CacheNodeResult(std::move(res), &cache);
  };
}

Parser Star(Parser Parse, Converter<std::vector<Value>> ToNode) {
  static std::unordered_map<State, std::unique_ptr<Value>> cache;
  return [Parse, ToNode](State state) {
    // Check cache first before calculating
    if (copyVisitorIsSet && (cache.find(state) != cache.end())) {
      // Check if value is empty:
      if (cache[state]->GetType() == Value::empty) {
        return Result(state, false, "cached empty value");
      }
      // Check if value is a string:
      if (cache[state]->GetType() == Value::string) {
        return Result(state, Value(cache[state]->GetString()));
      }
      // Retrieve the node from cached value.
      // At this point, the cached value is empty.
      auto node = cache[state]->GetNodeUnique();
      auto copier
      = MakeCopyVisitor();
      node->Visit(copier);
      auto nodeCopy = copier->GetCopy();
      // Since restore the cached value.
      cache[state] = std::make_unique<Value>(Value(std::move(node)));
      // Return a new result, using the copy of the node we made.
      return Result(state, Value(std::move(nodeCopy)));
    }

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
    Result res(currentResult.state(), ToNode(std::move(results)));
    return CacheNodeResult(std::move(res), &cache);
  };
}

Parser Not(Parser parse, Converter<std::string> ToValue) {
  static std::unordered_map<State, std::unique_ptr<Value>> cache;
  return [parse, ToValue](State state) {
    // Check cache first before calculating
    if (copyVisitorIsSet && (cache.find(state) != cache.end())) {
      // Check if value is empty:
      if (cache[state]->GetType() == Value::empty) {
        return Result(state, false, "cached empty value");
      }
      // Check if value is a string:
      if (cache[state]->GetType() == Value::string) {
        return Result(state, Value(cache[state]->GetString()));
      }
      // Retrieve the node from cached value.
      // At this point, the cached value is empty.
      auto node = cache[state]->GetNodeUnique();
      auto copier
        = MakeCopyVisitor();
      node->Visit(copier);
      auto nodeCopy = copier->GetCopy();
      // Since restore the cached value.
      cache[state] = std::make_unique<Value>(Value(std::move(node)));
      // Return a new result, using the copy of the node we made.
      return Result(state, Value(std::move(nodeCopy)));
    }

    auto result = parse(state);
    if (result.success()) {
      if (copyVisitorIsSet) {
        cache[state] = std::make_unique<Value>(Value());
      }
      return Result(state, false, "no match for not");
    }
    char temp = state.readChar();
    Result res(state, ToValue(std::string(1, temp)));;
    return CacheNodeResult(std::move(res), &cache);
  };
}

// Returns a function which runs a parser 1 or more times, returning all results
Parser OnePlus(Parser parse, Converter<std::vector<Value>> ToNode) {
  static std::unordered_map<State, std::unique_ptr<Value>> cache;
  return [parse, ToNode](State state) {
    // Check cache first before calculating
    if (copyVisitorIsSet && (cache.find(state) != cache.end())) {
      // Check if value is empty:
      if (cache[state]->GetType() == Value::empty) {
        return Result(state, false, "cached empty value");
      }
      // Check if value is a string:
      if (cache[state]->GetType() == Value::string) {
        return Result(state, Value(cache[state]->GetString()));
      }
      // Retrieve the node from cached value.
      // At this point, the cached value is empty.
      auto node = cache[state]->GetNodeUnique();
      auto copier
        = MakeCopyVisitor();
      node->Visit(copier);
      auto nodeCopy = copier->GetCopy();
      // Since restore the cached value.
      cache[state] = std::make_unique<Value>(Value(std::move(node)));
      // Return a new result, using the copy of the node we made.
      return Result(state, Value(std::move(nodeCopy)));
    }

    std::vector<Value> results;
    auto currentResult = parse(state);
          // Parse first element before the loop
    while (currentResult.success()) {
      Value v = currentResult.value();
      results.push_back(std::move(v) );
      currentResult = parse(currentResult.state());
    }
    if (results.size() == 0) {  // Must have one or more match, unlike Star()
      if (copyVisitorIsSet) {
        cache[state] = std::make_unique<Value>(Value());
      }
      return Result(state, false, "no matches at all");
    }
    Result res(currentResult.state(), ToNode(std::move(results)));
    return CacheNodeResult(std::move(res), &cache);
  };
}

// Return a function which parses a string (whitespace sensitive)
Parser ExactMatch(std::string str,
    Converter<std::string> ToValue) {
  static std::unordered_map<State, std::unique_ptr<Value>> cache;
  return [str, ToValue](State state) {
    // Check cache first before calculating
    if (copyVisitorIsSet && (cache.find(state) != cache.end())) {
      // Check if value is empty:
      if (cache[state]->GetType() == Value::empty) {
        return Result(state, false, "cached empty value");
      }
      // Check if value is a string:
      if (cache[state]->GetType() == Value::string) {
        return Result(state, Value(cache[state]->GetString()));
      }
      // Retrieve the node from cached value.
      // At this point, the cached value is empty.
      auto node = cache[state]->GetNodeUnique();
      auto copier
        = MakeCopyVisitor();
      node->Visit(copier);
      auto nodeCopy = copier->GetCopy();
      // Since restore the cached value.
      cache[state] = std::make_unique<Value>(Value(std::move(node)));
      // Return a new result, using the copy of the node we made.
      return Result(state, Value(std::move(nodeCopy)));
    }

    if (state.atEnd()) {
      if (copyVisitorIsSet) {
        cache[state] = std::make_unique<Value>(Value());
      }
      return Result(state, false, "end of file");
    }

    std::string ret = "";

    for (int i = 0; i < str.size(); i++) {
        char next_p = state.readChar();
        char next_str = str.at(i);

        if (next_p != next_str) {
          if (copyVisitorIsSet) {
            cache[state] = std::make_unique<Value>(Value());
          }
          return Result(state, false, "no match for " + str);
        } else {
          ret += state.readChar();
          state.advance();
        }

        if (state.atEnd() && i != str.size() - 1) {
          // checks if it is at the end of the file
          // must have the second statement to avoid
          // returning on the last check
          if (copyVisitorIsSet) {
            cache[state] = std::make_unique<Value>(Value());
          }
          return Result(state, false, "end of file");
        }
    }
    // got to end of string with all characters matching
    // and not reaching end of file
    // therefore, return success
    Result res(state, ToValue(ret));
    return CacheNodeResult(std::move(res), &cache);
  };
}


// Return a function which parses a string (whitespace insensitive)
// AKA this function ignores whitespace in either state or string
Parser Match(std::string str, Converter<std::string> ToValue) {
  static std::unordered_map<State, std::unique_ptr<Value>> cache;
  return [str, ToValue](State state) {
    // Check cache first before calculating
    if (copyVisitorIsSet && (cache.find(state) != cache.end())) {
      // Check if value is empty:
      if (cache[state]->GetType() == Value::empty) {
        return Result(state, false, "cached empty value");
      }
      // Check if value is a string:
      if (cache[state]->GetType() == Value::string) {
        return Result(state, Value(cache[state]->GetString()));
      }
      // Retrieve the node from cached value.
      // At this point, the cached value is empty.
      auto node = cache[state]->GetNodeUnique();
      auto copier
        = MakeCopyVisitor();
      node->Visit(copier);
      auto nodeCopy = copier->GetCopy();
      // Since restore the cached value.
      cache[state] = std::make_unique<Value>(Value(std::move(node)));
      // Return a new result, using the copy of the node we made.
      return Result(state, Value(std::move(nodeCopy)));
    }

    if (state.atEnd()) {
      if (copyVisitorIsSet) {
        cache[state] = std::make_unique<Value>(Value());
      }
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
        if (copyVisitorIsSet) {
          cache[state] = std::make_unique<Value>(Value());
        }
        return Result(state, false, "no match for " + str);
      } else {
        state.advance();
      }
    }
    // got to end of string with all characters matching
    // and not reaching end of file
    // therefore, return success
    Result res(state, ToValue(str));
    return CacheNodeResult(std::move(res), &cache);
  };
}


Parser Between(Parser parseA, Parser parseB,
    Parser parseC, Converter<std::string> ToValue) {
  static std::unordered_map<State, std::unique_ptr<Value>> cache;
  return [parseA, parseB, parseC, ToValue](State state) {
    // Check cache first before calculating
    if (copyVisitorIsSet && (cache.find(state) != cache.end())) {
      // Check if value is empty:
      if (cache[state]->GetType() == Value::empty) {
        return Result(state, false, "cached empty value");
      }
      // Check if value is a string:
      if (cache[state]->GetType() == Value::string) {
        return Result(state, Value(cache[state]->GetString()));
      }
      // Retrieve the node from cached value.
      // At this point, the cached value is empty.
      auto node = cache[state]->GetNodeUnique();
      auto copier
      = MakeCopyVisitor();
      node->Visit(copier);
      auto nodeCopy = copier->GetCopy();
      // Since restore the cached value.
      cache[state] = std::make_unique<Value>(Value(std::move(node)));
      // Return a new result, using the copy of the node we made.
      return Result(state, Value(std::move(nodeCopy)));
    }

    // Save position so we can reset later.
    int oldPosition = state.position();
    auto resultA = parseA(state);
    if (!resultA.success()) {
      state.setPosition(oldPosition);
      if (copyVisitorIsSet) {
        cache[state] = std::make_unique<Value>(Value());
      }
      return Result(state, false, "C is not between A and B");
    }

    auto resultB = parseB(resultA.state());
    if (!resultB.success()) {
      state.setPosition(oldPosition);
      if (copyVisitorIsSet) {
        cache[state] = std::make_unique<Value>(Value());
      }
      return Result(state, false, "C is not between A and B");
    }

    auto resultC = parseC(resultB.state());
    if (!resultC.success()) {
      state.setPosition(oldPosition);
      if (copyVisitorIsSet) {
        cache[state] = std::make_unique<Value>(Value());
      }
      return Result(state, false, "C is not between A and B");
    }

    Result res(resultB.state(), resultB.value());
    return CacheNodeResult(std::move(res), &cache);
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
