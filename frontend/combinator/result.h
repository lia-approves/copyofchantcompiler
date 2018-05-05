// Copyright (c) 2018, Team-Chant

#ifndef FRONTEND_COMBINATOR_RESULT_H
#define FRONTEND_COMBINATOR_RESULT_H

#include <string>
#include <stdexcept>

namespace cs160 {
namespace frontend {

template<typename T>
class Result {
 public:
  explicit Result(bool success, std::string errorMessage)
  : error_(errorMessage), success_(false) {
    if (success) {
      throw std::logic_error("fail constructor should not be used for success");
    }
  }
  explicit Result(T value)
  : value_(value), error_("no error"), success_(true) {}

  const T value() {
    if (!success_) {
      throw std::logic_error("can't access value of failed result");
    }
    return value_;
  }
  const bool success() { return success_; }

 private:
  T value_;
  std::string error_;
  bool success_;
};

}  // namespace frontend
}  // namespace cs160

#endif  // FRONTEND_COMBINATOR_RESULT_H
