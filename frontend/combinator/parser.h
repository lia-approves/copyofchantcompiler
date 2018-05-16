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

namespace Parse {

// Represents a 'parse function': a function which takes a state and returns
// a result.  Just an alias for convenience; this type does not ever change.
using Parser = std::function<Result(State)>;

using Node = std::unique_ptr<abstract_syntax::frontend::AstNode>;

template<class T>
using NodeMaker = std::function<Node(T)>;

template<class T>
using Converter = std::function<Value(T)>;

Value ToStringValue(std::string s) {
  return Value(s);
}

// Assumes both values are strings.  If one isn't, throws an exception
Value Concat(Value v1, Value v2) {
  if (v1.GetType() != Value::type::string ||
      v2.GetType() != Value::type::string) {
    throw std::logic_error("Attempted to concatenate non-string values.");
  }
  return Value(v1.GetString() + v2.GetString());
}

// Return a function which parses a single literal
Parser Literal(char c, Converter<std::string> ToValue = ToStringValue);

// Returns a function which checks if a character is within
// a range of two characters
Parser Range(std::string c, Converter<std::string> ToValue = ToStringValue);

// Return a function which runs 1 parser, then the next.  That function returns
// the first successful result (or failure)
Parser Or(Parser parseA, Parser parseB);

//  Returns a function which runs 2 parsers, and returns an array of their
//  results.  If either fails, it returns failure
Parser And(
  Parser parseA,
  Parser parseB,
  std::function<Value(Value, Value)> ToValue = Concat
);

Parser Star(Parser Parse, Converter<std::vector<Value>> ToNode);

Parser OnePlus(Parser parse, Converter<std::vector<Value>> ToNode);

// Returns a function which runs a parser, and returns a success if it fails
// and a failure if it succeeds
Parser Not(Parser parse, Converter<std::string> ToValue = ToStringValue);

Parser ExactMatch(std::string str, Converter<std::string> ToValuee = ToStringValue);

Parser Match(std::string str, Converter<std::string> ToValue = ToStringValue);

Parser Between(Parser parseA, Parser parseB,
    Parser parseC, Converter<std::string> ToValue = ToStringValue);

Parser Int(Converter<std::string> ToNode = [](std::string s) {
  auto node = Node(new abstract_syntax::frontend::IntegerExpr(std::stoi(s)));
  return Value(std::move(node));
});

Parser Sequence(Parser parseA, Parser parseB, Parser parseC,
  Converter<std::vector<Value>> ToNode);

}  // namespace Parse
}  // namespace frontend
}  // namespace cs160

#endif  // FRONTEND_COMBINATOR_PARSER_H_
