// Copyright (c) 2018, Team-Chant

#ifndef FRONTEND_COMBINATOR_RESULT_H
#define FRONTEND_COMBINATOR_RESULT_H

#include <string>
#include <stdexcept>
#include "frontend/combinator/state.h"
#include "abstract_syntax/abstract_syntax.h"

namespace cs160 {
namespace frontend {

// Container for return value of a parser
// Can either be a string or a unique pointer to an AstNode
class Value {
 public:
  enum type { node, string };
  explicit Value() {}
  explicit Value(std::unique_ptr<abstract_syntax::frontend::AstNode> value) :
    type_(type::node), node_(std::move(value)) {}
  explicit Value(std::string value) :
    type_(type::string), string_(value) {}
  Value(Value&& other) : type_(other.type_), node_(std::move(other.node_)), string_(other.string_) {}
  Value& operator=(Value&& other) {
    if (this != &other) {
      type_ = other.type_;
      string_ = other.string_;
      node_ = std::move(other.node_);
    }
    return *this;
  }
  std::unique_ptr<abstract_syntax::frontend::AstNode> Node() {
    return std::move(node_);
  }
  std::string String() const {
    return string_;
  }
  type Type() const {
    return type_;
  }

 private:
  type type_;
  std::unique_ptr<abstract_syntax::frontend::AstNode> node_;
  std::string string_;
};

class Result {
 public:
  explicit Result(State state, bool success, std::string errorMessage)
  : state_(state), error_(errorMessage), success_(false) {
    if (success) {
      throw std::logic_error("fail constructor should not be used for success");
    }
  }
  explicit Result(State state, Value value)
  : state_(state), value_(std::move(value)), error_("no error"), success_(true) {}

  const Value value() {
    if (!success_) {
      throw std::logic_error("can't access value of failed result");
    }
    return std::move(value_);
  }
  const bool success() { return success_; }
  const std::string error() { return error_; }
  const State state() { return state_; }

 private:
  State state_;
  Value value_;
  std::string error_;
  bool success_;
};

}  // namespace frontend
}  // namespace cs160

#endif  // FRONTEND_COMBINATOR_RESULT_H
