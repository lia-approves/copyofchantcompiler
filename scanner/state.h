#ifndef STATE_H_
#define STATE_H_

#include <map>

namespace cs160 {
namespace scanner {

template<typename Token>

class State {
public:
  explicit State(int id);
  explicit State(int id, Token result);
  ~State(void);

  void addTransition(char trigger, int nextStateId);
  int nextState(char input);
  int getId();
  virtual bool isAccepting();
  virtual Token getToken();

private:
  int id;
  std::map<char, int> transitions;

};


}
}

#endif // STATE_H_
