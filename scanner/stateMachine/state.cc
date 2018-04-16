#include "state.h"

namespace cs160 {
namespace scanner {

State::State(int id) {
    this->id = id;
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
  return false;
}

Token State::getToken() {
  return Token();
}

}
}
