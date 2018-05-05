// Copyright (c) 2018, Team-Chant

#ifndef FRONTEND_COMBINATOR_STATE_H
#define FRONTEND_COMBINATOR_STATE_H

#include <string>
#include <stdexcept>

namespace cs160 {
namespace frontend {

class State {
 public:
  State(std::string input) : input_(input), position_(0) {}
  const int position() { return position_; }
  char advance() {
    position_++;
    return input_.at(position_ - 1);
  }
  bool atEnd() {
    try {
      input_.at(position_);
      return false;
    } catch (const std::out_of_range& oor) {
      return true;
    }
  }

 private:
  std::string input_;
  int position_;
};

} // namespace frontend
} // namespace cs160
#endif  // FRONTEND_COMBINATOR_STATE_H
