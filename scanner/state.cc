#include "scanner/state.h"
#include <pair>

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

}
}
