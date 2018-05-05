// Copyright (c) 2018, Team-Chant

#ifndef FRONTEND_COMBINATOR_RESULT_H
#define FRONTEND_COMBINATOR_RESULT_H

#include <string>

namespace cs160 {
namespace frontend {

template<typename T>
class Result {
 public:
  explicit Result(std::string errorMessage) : error_(errorMessage) {}

 private:
  T value_;
  std::string error_;
  bool success_;
};

}  // namespace frontend
}  // namespace cs160

#endif  // FRONTEND_COMBINATOR_RESULT_H
