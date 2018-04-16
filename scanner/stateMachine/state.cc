#include "state.h"

namespace cs160 {
namespace scanner {

State::State(int id) {
    this->id = id;
    this->accepting = false;
    this->token = Token();
}
State::State(int id, Token token) {
    this->id = id;
    this->accepting = true;
    this->token = token;
}
State::~State(void) {}

void State::addTransition(char trigger, int nextStateId) {
  transitions[trigger] = nextStateId;
}

int State::nextState(char input) {
  return transitions[input];
}

int State::getId() {
  return id;
}

bool State::isAccepting() {
  return this->accepting;
}

} // namespace scanner
} // namespace cs160