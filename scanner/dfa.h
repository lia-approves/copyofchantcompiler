#ifndef DFA_H_
#define DFA_H_

#include "scanner/state.h"
#include <map>

namespace cs160 {
namespace scanner {

template<typename Token>

class DFA {

public:
  explicit DFA(int startState);
  ~DFA(void);

  void addState(State<Token> state);
  bool isAccepting();
  void reset();
  State<Token> getCurrentState();
  Token input(char c);

private:
  int currentState;
  int startState;
  State<Token> getStateById(int id);
  std::map<int, State<Token>> states;

};

}
}

#endif // DFA_H_
