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
#include "dfa.h"
#include <map>
#include <iostream>

namespace cs160 {
namespace scanner {
namespace statemachine {

// Start DFA off with initial state
// Intialize the intial state
DFA::DFA(State start) {
  this->startState_ = this->currentState_ = start.getId();
  addState(start);
}

DFA::~DFA(void) {}

void DFA::addState(State state) {
  states_[state.getId()] = state;
}

// Core function for DFA, lets us pass in the next input char to be processed and assign necessary states and transitions based on input
void DFA::input(char c) {
  int nextStateId = states_[currentState_].nextState(c);
  this->currentState_ = nextStateId;
  std::cout << nextStateId;
}

// Transition function for DFA
void DFA::addTransition(int stateId, char trigger, int destStateId) {
  // check that both states are registered in the DFA
  if (states_.count(stateId) == 0) {
    states_[stateId] = State(stateId);
  }
  if (states_.count(destStateId) == 0) {
    states_[destStateId] = State(destStateId);
  }
  states_[stateId].addTransition(trigger, destStateId);
}

}  // namespace statemachine
}  // namespace scanner
}  // namespace cs160
