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

private:
  int currentState;
  int startState;
  State getStateById(int id);
  std::map<int, State> states;

};

}
}

#endif // DFA_H_
