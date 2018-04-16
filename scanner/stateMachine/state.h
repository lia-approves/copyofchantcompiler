#ifndef STATE_H_
#define STATE_H_

#include <map>
#include "scanner/token/Token.h"

/*
  Every state must have a unique POSITIVE id.
  It can also have transitions to other states, referred to by id.

  "Error" states are denoted by negative ids.
  Creating a state without providing an id causes it to be an error state by default
*/

namespace cs160 {
namespace scanner {

class State {
public:
  explicit State(int id = -1); // default id is -1, the error state
  ~State(void);

  void addTransition(char trigger, int nextStateId);
  int nextState(char input);
  int getId();
  virtual bool isAccepting();
  virtual Token getToken();

private:
  int id;
  Token token; // ignore this unless you're dealing with an Accepting State
  std::map<char, int> transitions;

};


}
}

#endif // STATE_H_
