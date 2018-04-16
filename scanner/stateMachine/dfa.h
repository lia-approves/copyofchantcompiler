/*
  Deterministic Finite Automata class.

  Declare with a start state.  You can add states and transitions any time
  using the appropriately-named methods
*/

#ifndef DFA_H_
#define DFA_H_

#include "state.h"
#include "scanner/token/Token.h"
#include <map>

namespace cs160 {
namespace scanner {

class DFA {

public:
  explicit DFA(State start);
  ~DFA(void);

  void addState(State state);
  bool isAccepting();
  void reset();
  State getCurrentState();
  Token input(char c);

  // add a transition from state 'stateId' to state 'destStateId' on character trigger
  // NOTE: you can refer to states that aren't registerd!  The DFA will simply create them for you
  void addTransition(int stateId, char trigger, int destStateId);

private:
  int currentState;
  int startState;
  State getStateById(int id);
  std::map<int, State> states;

};

} // namespace scanner
} // namespace cs160

#endif // DFA_H_
