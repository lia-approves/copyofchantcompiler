// Copyright (c) 2018, Team-Chant

#ifndef FRONTEND_COMBINATOR_PARSER_H_
#define FRONTEND_COMBINATOR_PARSER_H_

#include <experimental/any>


namespace cs160 {
namespace frontend {

using Var = std::experimental::any;

class State {
 public:
  explicit State(std::string i) : input_(i), position_(0) {}
  void Advance() { position_++; }
  char ReadChar() const { return input_.at(position_); }
  bool AtEnd() const {
    try {
      input_.at(position_);
      return false;
    } catch (const std::out_of_range& oor) {
      return true;
    }
  }
  int Position() const { return position_; }
  void SetPosition(int p) { position_ = p; }
  bool Success() const { return success_; }
  bool Fail() const { return !success_; }
  void Success(bool s) { success_ = s; }
  void Value(Var v) { value_ = v; }
  Var Value() {
    return value_;
  }

 private:
  std::string input_;
  Var value_;
  int position_;
  bool success_;
};

// Represents a 'parse function': a function which takes a state and returns
// a result.  Just an alias for convenience; this type does not ever change.
// template<class T>
using Parser = std::function<State(State)>;
using CaptureMany = std::function< Var (std::vector<Var>) >;
using CaptureOne = std::function< Var (Var) >;

CaptureOne DefaultC1 = [](Var v) { return v; };
CaptureMany DefaultCM = [](std::vector<Var> v) { return v; };

Parser Lit(char c, CaptureOne Convert = DefaultC1) {
  return [c, Convert](State state) {
    if (state.AtEnd()) {
      state.Success(false);
      return state;
    }
    char next = state.ReadChar();

    if (next == c) {
      state.Advance();
      state.Success(true);
      state.Value(Convert(c));
      return state;
    } else {
      state.Success(false);
      return state;
    }
  };
}

}  // namespace frontend
}  // namespace cs160

#endif  // FRONTEND_COMBINATOR_PARSER_H_
