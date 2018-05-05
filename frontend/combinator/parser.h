// Copyright (c) 2018, Team-Chant

#ifndef FRONTEND_COMBINATOR_PARSER_H_
#define FRONTEND_COMBINATOR_PARSER_H_

#include "frontend/combinator/result.h"

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
      input_.at(position_+1);
      return false;
    } catch (const std::out_of_range& oor) {
      return true;
    }
  }

 private:
  std::string input_;
  int position_;
};

std::function<Result<char>(State)> literal(char c) {
  return [c](State state) {
    if (state.atEnd()) {
      return Result<char>(false, "end of file");
    }
    char next = state.advance();

    if (next == c) {
      return Result<char>(c);
    } else {
      std::string err = "no match for character: ";
      err += c;
      return Result<char>(false, err);
    }
  };
}


}  // namespace frontend
}  // namespace cs160

#endif  // FRONTEND_COMBINATOR_PARSER_H_
