// Copyright (c) 2018, Team-Chant

#ifndef FRONTEND_COMBINATOR_RESULT_H_
#define FRONTEND_COMBINATOR_RESULT_H_

#include <string>
#include <stdexcept>
#include <memory>
#include <utility>
#include "frontend/combinator/state.h"
#include "abstract_syntax/abstract_syntax.h"

namespace cs160 {
namespace frontend {

class Value {
 public:
  enum type { node, string, empty };
  Value(): type_(type::empty) {}
  explicit Value(std::unique_ptr<abstract_syntax::frontend::AstNode> i) :
    type_(type::node),
    node_(std::move(i)) {}
  explicit Value(std::string s) :
    type_(type::string),
    string_(s) {}
  Value(Value&& v) :
    type_(v.type_),
    node_(std::move(v.node_)),
    string_(v.string_) {}
  Value& operator=(Value&& v) {
    if (this != &v) {
      type_ = v.type_;
      string_ = v.string_;
      node_ = std::move(v.node_);
    }
    return *this;
  }
  void Visit(abstract_syntax::frontend::AstVisitor* visitor) {
    node_->Visit(visitor);
  }

  abstract_syntax::frontend::AstNode* GetNodePointer() const {
    return node_.get();
  }
  std::unique_ptr<abstract_syntax::frontend::AstNode> GetNodeUnique() {
    return std::move(node_);
  }
  std::string GetString() const { return string_; }
  void SetString(std::string s) { string_ = s; }
  type GetType() const { return type_; }

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
  explicit Result(State state, Value value) :
    state_(state),
    value_(std::move(value)),
    error_("no error"),
    success_(true) {}

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

#endif  // FRONTEND_COMBINATOR_RESULT_H_
