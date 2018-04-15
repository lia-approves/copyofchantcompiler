#ifndef STATE_H_
#define STATE_H_

#include <map>

namespace cs160 {
namespace scanner {

template<typename Token>

class State {
public:
  explicit State(int id);
  ~State(void);

  void addTransition(char trigger, int nextStateId);
  int nextState(char input);
  int getId();
  virtual bool isAccepting();
  virtual Token getToken();

private:
  int id;
  map<char, int> transitions;

}


}
}
