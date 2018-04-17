#ifndef STATE_H_
#define STATE_H_

#include <map>
#include "scanner/token/Token.h"
#include "scanner/token/InvalidToken.h"

/*
  Every state must have a unique POSITIVE id.
  It can also have transitions to other states, referred to by id.

  "Error" states are denoted by negative ids.
  Creating a state without providing an id causes it to be an error state by default

  Provide a token in the constructor to create an Accepting State
*/

namespace cs160 {
namespace scanner {
namespace statemachine {

class State {
public:
  //Constructors for creating states, default value is -1
  //Otherwise initialize it with a Token
  explicit State(int id = -1);
  explicit State(int id, Token token);

  //Destructor for State object
  ~State(void);

  //Method for adding transition to a state, input is a character
  //and where the state should go
  void addTransition(char trigger, int nextStateId);
  int nextState(char input);

  //Basic getters
  int getId() const { return id_; }
  bool isAccepting() const { return accepting_; }
  Token getToken() const { return token_; }

private:
  int id_;
  bool accepting_;
  Token token_;
  std::map<char, int> transitions_;

};


} // namespace statemachine
} // namespace scanner
} // namespace cs160

#endif // STATE_H_
