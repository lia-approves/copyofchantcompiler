#include "scanner/dfa.h"
#include "scanner/state.h"
#include <map>

namespace cs160 {
namespace scanner {

template<typename Token>
DFA<Token>::DFA(int startState) {
  this->startState = this->currentState = startState;
  addState(new State<Token>(startState));
}

template<typename Token>
DFA<Token>::~DFA(void) {}

template<typename Token>
void DFA<Token>::addState(State<Token> state) {
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
State<Token> DFA<Token>::getCurrentState() {
  return states[currentState];
}

template<typename Token>
Token DFA<Token>::input(char c) {
  int nextStateId = states[currentState].nextState(c);
  State<Token> nextState = states[nextStateId];
  return nextState.getToken();
}

}
}
