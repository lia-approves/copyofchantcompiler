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
#include <map>
#include <iostream>
#include "frontend/scanner/state_machine/dfa/dfa.h"

namespace cs160 {
namespace frontend {

// Start DFA off with initial state
// Intialize the intial state
DFA::DFA(State start) {
    State error(0);
    error.setTokenOutput([](std::string str)->
                           cs160::frontend::Token
    {return cs160::frontend::InvalidToken(str);});

    addState(error);
  this->startState_ = this->currentState_ = start.getId();
  addState(start);
}

DFA::~DFA(void) {}


void DFA::addState(State state) {
  states_[state.getId()] = state;
}

// Core function for DFA, lets us pass in the next
    // input char to be processed and assign necessary
    // states and transitions based on input
void DFA::input(char c) {
  lexeme_ = lexeme_ + c;


    int nextStateId = states_[currentState_].nextState(c);
    currentState_ = nextStateId;
    recently_visited_.push(states_[currentState_]);


  if (states_[currentState_].isAccepting()) {
      // double check that this works later
      stack_empty();
      recently_visited_.push(states_[currentState_]);
  }

    if (currentState_ == 0) {  // error state
        // call rollback here when its finished
      // return after rollback
      std::cout << "rollback " << lexeme_ << std::endl;
      rollback();
      return;
  }
}

void DFA::rollback() {
    // pop from stack until we find accepting state
    State s;
    int init_pos = position_;

    while (!s.isAccepting() && !recently_visited_.empty()) {
        // ends when stack is empty OR top state is accepting
        s = recently_visited_.top();
        recently_visited_.pop();

        if (!s.isAccepting()) {
            lexeme_ = lexeme_.substr(0, lexeme_.size()-1);
            position_--;
        }
    }

    if (s.isAccepting()) {
        Token t = s.getToken(lexeme_);
        scanner_output_.push(t);
    } else {
        // stack empty
        InvalidToken t;
        scanner_output_.push(t);
        position_ = init_pos;
    }

    // clear stack
    stack_empty();
    lexeme_ = "";

    currentState_ = startState_;
}

    void DFA::stack_empty() {
        while (!recently_visited_.empty()) {
            recently_visited_.pop();
        }
    }

void DFA::input(std::string s) {
  lexeme_ = "";  // fresh lexeme
  stack_empty();  // fresh stack

    recently_visited_.push(states_[currentState_]);
  for (; position_ < s.length(); position_++) {
      // pass chars one by one to input(char c)
    this->input(s.at(position_));
  }

    if (!recently_visited_.empty()) {
        State st = recently_visited_.top();
        Token t = st.getToken(lexeme_);
        scanner_output_.push(t);
    } else {
        InvalidToken t;
        scanner_output_.push(t);
    }
}

    void DFA::printQueue() {
        std::cout << "printing queue: " << std::endl;
        while (!scanner_output_.empty()) {
            std::cout << scanner_output_.front().Print() << std::endl;
            scanner_output_.pop();
        }
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
}  // namespace frontend
}  // namespace cs160
