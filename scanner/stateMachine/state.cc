#include "state.h"

namespace cs160 {
namespace scanner {

State::State(int id) {
    this->id_ = id;
    this->accepting_ = false;
    this->token_ = Token();
}
State::State(int id, Token token) {
    this->id_ = id;
    this->accepting_ = true;
    this->token_ = token;
}
State::~State(void) {}

void State::addTransition(char trigger, int nextStateId) {
  transitions_[trigger] = nextStateId;
}

int State::nextState(char input) {
  return transitions_[input];
}

} // namespace scanner
} // namespace cs160