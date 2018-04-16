#include "dfa.h"
#include <map>

namespace cs160 {
namespace scanner {

DFA::DFA(State start) {
  this->startState = this->currentState = start.getId();
  addState(start);
}

DFA::~DFA(void) {}

void DFA::addState(State state) {
  states[state.getId()] = state;
}

bool DFA::isAccepting() {
  return states[currentState].isAccepting();
}

void DFA::reset() {
  currentState = startState;
}

State DFA::getCurrentState() {
  return states[currentState];
}

Token DFA::input(char c) {
  int nextStateId = states[currentState].nextState(c);
  this->currentState = nextStateId;
  State nextState = states[nextStateId];
  return nextState.getToken();
}

void DFA::addTransition(int stateId, char trigger, int destStateId) {
  // check that both states are registered in the DFA
  if (states.count(stateId) == 0) {
    states[stateId] = State(stateId);
  }
  if (states.count(destStateId) == 0) {
    states[destStateId] = State(destStateId);
  }
  states[stateId].addTransition(trigger, destStateId);
}

} // namespace scanner
} // namespace cs160
