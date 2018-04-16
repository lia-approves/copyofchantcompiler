#include "dfa.h"
#include "state.h"
#include <map>

namespace cs160 {
namespace scanner {

DFA::DFA(int startState) {
  this->startState = this->currentState = startState;
  addState(State(startState));
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
  State nextState = states[nextStateId];
  return nextState.getToken();
}

}
}
