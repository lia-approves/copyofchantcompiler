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
  bool operator== (const State &other) const {
    return (position_ == other.position() && input_ == other.getString());
  }
  int position() const { return position_; }
  void setPosition(int p) { position_ = p; }
  std::string getString() const {return input_; }

 private:
  std::string input_;
  int position_;
};


}  // namespace frontend
}  // namespace cs160

namespace std {

template <>
struct hash<cs160::frontend::State> {
  size_t operator() (const cs160::frontend::State& s) const {
    return (
      (hash<std::string>()(s.getString()) ^
      (hash<int>()(s.position()) << 1)) >> 1);
  }
};

}  // namespace std
#endif  // FRONTEND_COMBINATOR_STATE_H_
