#include "scanner/dfa.h"
#include "scanner/state.h"
#include <map>

template<typename Token>
DFA<Token>::DFA(int startState) {
  this->startState = this->currentState = startState;
  addState(new State(startState));
}

template<typename Token>
DFA<Token>::~DFA(void) {}

template<typename Token>
void DFA<Token>::addState(State state) {
  states[state.getId()] = state;
}

template<typename Token>
bool DFA<Token>::isAccepting() {
  return states[currentState].isAccepting();
}

template<typename Token>
void DFA<Token>::reset() {
  currentState = startState;
}

template<typename Token>
State DFA<Token>::getCurrentState() {
  return states[currentState];
}

template<typename Token>
Token DFA<Token>::input(char c) {
  int nextStateId = states[currentState].nextState(c);
  State nextState = states[nextStateId];
  return nextState.getToken();
}
