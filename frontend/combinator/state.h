// Copyright (c) 2018, Team-Chant

#ifndef FRONTEND_COMBINATOR_STATE_H_
#define FRONTEND_COMBINATOR_STATE_H_

#include <string>
#include <stdexcept>

namespace cs160 {
namespace frontend {

class State {
 public:
  explicit State(std::string input) : input_(input), position_(0) {}
  void advance() {
    position_++;
  }
  char readChar() const {
    return input_.at(position_);
  }
  bool atEnd() const {
    try {
      input_.at(position_);
      return false;
    } catch (const std::out_of_range& oor) {
      return true;
    }
  }
  int position() const { return position_; }
  void setPosition(int p) { position_ = p; }
  std::string getString() {return input_; }
 private:
  std::string input_;
  int position_;
};

}  // namespace frontend
}  // namespace cs160
#endif  // FRONTEND_COMBINATOR_STATE_H_