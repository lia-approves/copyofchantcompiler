// Copyright (c) 2018, Team-Chant

#ifndef FRONTEND_COMBINATOR_RESULT_H
#define FRONTEND_COMBINATOR_RESULT_H

#include <string>
#include <stdexcept>
#include "frontend/combinator/state.h"
#include "abstract_syntax/abstract_syntax.h"

namespace cs160 {
namespace frontend {

template<typename T>
class Result {
 public:
  explicit Result(State state, bool success, std::string errorMessage)
  : state_(state), error_(errorMessage), success_(false) {
    if (success) {
      throw std::logic_error("fail constructor should not be used for success");
    }
  }
  explicit Result(State state, T value)
  : state_(state), value_(value), error_("no error"), success_(true) {}

  const T value() {
    if (!success_) {
      throw std::logic_error("can't access value of failed result");
    }
    return value_;
  }
  const bool success() { return success_; }
  const std::string error() { return error_; }
  const std::unique_ptr<abstract_syntax::frontend::AstNode> lastNode() {
    return lastNode_;
  }
  void lastNode(std::unique_ptr<abstract_syntax::frontend::AstNode> node) {
    lastNode_ = std::move(node);
  }
  const State state() { return state_; }

 private:
  State state_;
  T value_;
  std::string error_;
  bool success_;
  std::unique_ptr<abstract_syntax::frontend::AstNode> lastNode_;
};

}  // namespace frontend
}  // namespace cs160

#endif  // FRONTEND_COMBINATOR_RESULT_H
