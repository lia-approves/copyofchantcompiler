#include "dfa.h"
#include <map>

namespace cs160 {
namespace scanner {
namespace statemachine {

//Start DFA off with initial state
//Intialize the intial state
DFA::DFA(State start) {
  this->startState_ = this->currentState_ = start.getId();
  addState(start);
}

DFA::~DFA(void) {}

void DFA::addState(State state) {
  states_[state.getId()] = state;
}

//Core function for DFA, lets us pass in the next input char to be processed and assign necessary states and transitions based on input
Token DFA::input(char c) {
  int nextStateId = states_[currentState_].nextState(c);
  this->currentState_ = nextStateId;
  State nextState = states_[nextStateId];
  return nextState.getToken();
}

//Transition function for DFA
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

} // namespace statemachine
} // namespace scanner
} // namespace cs160
