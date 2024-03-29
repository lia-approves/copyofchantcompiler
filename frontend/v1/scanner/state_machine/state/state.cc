/*
MIT License

Copyright (c) 2018, Team-Chant

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include <string>
#include <iostream>
#include "frontend/v1/scanner/state_machine/state/state.h"


namespace cs160 {
namespace frontend {

// Basic state object, contains the ID, a flag to see if it's
// accepting and the default token of invalid
State::State(int id) {
    this->id_ = id;
    this->accepting_ = false;
    this->token_ = InvalidToken();
}
    State::State(int id, Token token) {
    this->id_ = id;
    this->accepting_ = true;
    this->token_ = token;
}
State::~State(void) {}

void State::setTokenOutput
  (std::function<std::shared_ptr<Token>(std::string)> func) {
    createToken_ = func;
}

std::shared_ptr<Token> State::getToken(std::string str) {
    std::shared_ptr<Token> retval =  createToken_(str);
    return retval;
}

// Methods for getting next state of a given
// state and for adding transitions to a new state
void State::addTransition(char trigger, int nextStateId) {
  transitions_[trigger] = nextStateId;
}

    void State::makeAccepting() { accepting_ = true; }

void State::addTransition(char startChar, char endChar, int nextStateId) {
  int startASCII = static_cast<int> (startChar);
  int endASCII = static_cast<int> (endChar);

  for (int i = startASCII; i <= endASCII; i++) {
    this->addTransition(i, nextStateId);
  }
}

int State::nextState(char input) {
  return transitions_[input];
}
}  // namespace frontend
}  // namespace cs160
