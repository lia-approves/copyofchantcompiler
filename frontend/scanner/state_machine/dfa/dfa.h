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

/*
  Deterministic Finite Automata class.

  Declare with a start state.  You can add states and transitions any time
  using the appropriately-named methods
*/

#ifndef FRONTEND_SCANNER_STATE_MACHINE_DFA_DFA_H_
#define FRONTEND_SCANNER_STATE_MACHINE_DFA_DFA_H_

#include <map>
#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include "frontend/scanner/state_machine/state/state.h"
#include "frontend/scanner/token/Token.h"


namespace cs160 {
namespace scanner {
namespace statemachine {

class DFA {
 public:
    explicit DFA(State start);
    ~DFA(void);



    void addState(State state);
    void reset() { currentState_ = startState_; }
    State getCurrentState() const { return states_.at(currentState_); }
    void input(char c);
    void input(std::string s);
    bool isAccepting() const { return states_.at(currentState_).isAccepting(); }

    // add a transition from state 'stateId' to
    // state 'destStateId' on character trigger
    // NOTE: you can refer to states that aren't
    // registerd!  The DFA will simply create them for you
    void addTransition(int stateId, char trigger, int destStateId);

    void print_queue();

 private:
    void rollback();
    void stack_empty();
    std::string lexeme_;
    int currentState_;
    int startState_;

    unsigned int position_ = 0;

    State getStateById_(int id);
    std::map<int, State> states_;
    std::stack<State> recently_visited_;    // used for rollback
    std::queue<token::Token> scanner_output_;
    // queue keeps track of all of the tokens found, gives this to the parser
};

}  // namespace statemachine
}  // namespace scanner
}  // namespace cs160

#endif  // FRONTEND_SCANNER_STATE_MACHINE_DFA_DFA_H_
