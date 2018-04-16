#ifndef STATE_H_
#define STATE_H_

#include <map>
#include "scanner/token/Token.h"

/*
  Every state must have a unique POSITIVE id.
  It can also have transitions to other states, referred to by id.

  "Error" states are denoted by negative ids.
  Creating a state without providing an id causes it to be an error state by default

  Provide a token in the constructor to create an Accepting State
*/

namespace cs160 {
namespace scanner {

class State {
public:
  explicit State(int id = -1); // default id is -1, the error state
  explicit State(int id, Token token); // for creating an accepting state
  ~State(void);

  void addTransition(char trigger, int nextStateId);
  int nextState(char input);
  int getId();
  bool isAccepting();
  Token getToken();

private:
  int id;
  bool accepting;
  Token token; // defaults to Invalid Token
  std::map<char, int> transitions;

};


} // namespace scanner
} // namespace cs160

#endif // STATE_H_
