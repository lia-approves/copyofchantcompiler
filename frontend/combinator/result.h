// Copyright (c) 2018, Team-Chant

#ifndef FRONTEND_COMBINATOR_RESULT_H
#define FRONTEND_COMBINATOR_RESULT_H

#include <string>
#include <stdexcept>
#include "frontend/combinator/state.h"

namespace cs160 {
namespace frontend {

template<typename T>
class Result {
 public:
  explicit Result(bool success, std::string errorMessage)
  : error_(errorMessage), success_(false), state_(State("stub")) {
    if (success) {
      throw std::logic_error("fail constructor should not be used for success");
    }
  }
  explicit Result(T value, State state)
  : value_(value), error_("no error"), success_(true), state_(state) {}

  const T value() {
    if (!success_) {
      throw std::logic_error("can't access value of failed result");
    }
    return value_;
  }
  const bool success() { return success_; }
  const std::string error() { return error_; }
  const State state() {
    if (!success_) {
      throw std::logic_error("can't access state of failed result");
    }
    return state_;
  }

 private:
  T value_;
  std::string error_;
  bool success_;
  State state_;
};

}  // namespace frontend
}  // namespace cs160

#endif  // FRONTEND_COMBINATOR_RESULT_H
