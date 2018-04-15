#ifndef DFA_H_
#define DFA_H_

#include <map>

namespace cs160 {
namespace scanner {

template<typename Token>

class DFA {

public:
  explicit DFA(int startState);
  ~DFA(void);

  void addState(State state);
  bool isAccepting();
  void reset();
  State getCurrentState();
  Token input(char c);

private:
  int currentState;
  int startState;
  State getStateById(int id);
  map<int, State> states;

}

}
}
