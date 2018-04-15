#ifndef STATE_H_
#define STATE_H_

#include <map>

namespace cs160 {
namespace scanner {

class State {
public:
  explicit State(int id);
  ~State(void);

  void addTransition(char trigger, int nextStateId);
  int nextState(char input);

private:
  map<char, int> transitions;
  
}


}
}
