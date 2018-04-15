#include "scanner/state.h"
#include <pair>

namespace cs160 {
namespace scanner {

template<typename Token>
State::State(int id) {
    this->id = id;
}
template<typename Token>
State::~State(void) {}

template<typename Token>
void State::addTransition(char trigger, int nextStateId) {
  transitions[trigger] = nextStateId;
}

template<typename Token>
int State::nextState(char input) {
  return transitions[input];
}

template<typename Token>
int State::getId() {
  return id;
}

template<typename Token>
virtual bool State::isAccepting() {
  return false;
}

template<typename Token>
virtual Token State::getToken() {
  return NULL;
}

}
}
