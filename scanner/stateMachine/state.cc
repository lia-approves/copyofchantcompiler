#include "state.h"

namespace cs160 {
namespace scanner {
namespace statemachine {

//Basic state object, contains the ID, a flag to see if it's
//accepting and the default token of invalid
State::State(int id) {
    this->id_ = id;
    this->accepting_ = false;
    this->token_ = InvalidToken();
}
State::State(int id, Token token) {
    this->id_ = id;
    this->accepting_ = true;
    this->token_ = token;
}
State::~State(void) {}

//Methods for getting next state of a given state and for adding transitions to a new state
void State::addTransition(char trigger, int nextStateId) {
  transitions_[trigger] = nextStateId;
}

int State::nextState(char input) {
  return transitions_[input];
}

} // namespace statemachine
} // namespace scanner
} // namespace cs160
