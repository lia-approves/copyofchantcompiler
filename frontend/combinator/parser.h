// Copyright (c) 2018, Team-Chant

#ifndef FRONTEND_COMBINATOR_PARSER_H_
#define FRONTEND_COMBINATOR_PARSER_H_

#include <vector>
#include <string>
#include <iostream>
#include <utility>
#include <memory>
#include "frontend/combinator/result.h"
#include "frontend/combinator/state.h"
#include "utility/memory.h"
#include "abstract_syntax/abstract_syntax.h"

namespace cs160 {
namespace frontend {

namespace Parse {

extern bool debug_next;

class CopyVisitor : public cs160::abstract_syntax::frontend::AstVisitor {
 public:
  virtual std::unique_ptr<cs160::abstract_syntax::frontend::AstNode> GetCopy();
};

// Represents a 'parse function': a function which takes a state and returns
// a result.  Just an alias for convenience; this type does not ever change.
using Parser = std::function<Result(State)>;

using Node = std::unique_ptr<abstract_syntax::frontend::AstNode>;

template<class T>
using NodeMaker = std::function<Node(T)>;

template<class T>
using Converter = std::function<Value(T)>;

//Helper function to return a value version of a string
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

//Helper to concatenate a vector of values properly
Value ConcatVector(std::vector<Value> values) {
  std::string s;
  for (auto it = values.begin(); it != values.end(); ++it) {
    s += it->GetString();
  }
  return Value(s);
}

// Return a function which parses a single literal
Parser Literal(char c, Converter<std::string> ToValue = ToStringValue);

// Returns a function which checks if a character is within
// a range of two characters
Parser Range(std::string c, Converter<std::string> ToValue = ToStringValue);

// Return a function which runs 1 parser, then the next.  That function returns
// the first successful result (or failure)
Parser Or(Parser parseA, Parser parseB);

Parser Or(std::vector<Parser> p_vec);

//  Returns a function which runs 2 parsers, and returns an array of their
//  results.  If either fails, it returns failure
Parser And(
  Parser parseA,
  Parser parseB,
  std::function<Value(Value, Value)> ToValue = Concat
);

Parser And(std::vector<Parser> p_vec,
    std::function<Value(Value, Value)> ToValue = Concat);

// Returns a function which runs a Parser and fulfills the duty of a star operator
Parser Star(Parser Parse, Converter<std::vector<Value>> ToNode);

Parser OnePlus(Parser parse, Converter<std::vector<Value>> ToNode);

// Returns a function which runs a parser, and returns a success if it fails
// and a failure if it succeeds
Parser Not(Parser parse, Converter<std::string> ToValue = ToStringValue);

// Returns a function which checks if a given string value is an exact match
Parser ExactMatch(std::string str, Converter<std::string>
  ToValue = ToStringValue);

// Returns a function which checks if a given string matches at all
Parser Match(std::string str, Converter<std::string> ToValue = ToStringValue);

// Returns a function which takes multiple parsers and checks if one is between the others
Parser Between(Parser parseA, Parser parseB,
    Parser parseC, Converter<std::string> ToValue = ToStringValue);

// Returns a IntegerExpr node
Parser Int(Converter<std::string> ToNode = [](std::string s) {
  auto node = Node(new abstract_syntax::frontend::IntegerExpr(std::stoi(s)));
  return Value(std::move(node));
});

// Returns a function to check if multiple parsers are in a sequence
Parser Sequence(Parser parseA, Parser parseB, Parser parseC,
  Converter<std::vector<Value>> ToNode);

// Helper function to help debug sequences of parsers
Parser Debug(Parser parser, std::string text);

}  // namespace Parse
}  // namespace frontend
}  // namespace cs160

#endif  // FRONTEND_COMBINATOR_PARSER_H_
