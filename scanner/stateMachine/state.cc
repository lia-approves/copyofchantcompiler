#include "state.h"

namespace cs160 {
namespace scanner {

template<typename Token>
State<Token>::State(int id) {
    this->id = id;
}
template<typename Token>
State<Token>::~State(void) {}

template<typename Token>
void State<Token>::addTransition(char trigger, int nextStateId) {
  transitions[trigger] = nextStateId;
}

template<typename Token>
int State<Token>::nextState(char input) {
  return transitions[input];
}

template<typename Token>
int State<Token>::getId() {
  return id;
}

template<typename Token>
bool State<Token>::isAccepting() {
  return false;
}

template<typename Token>
Token State<Token>::getToken() {
  return NULL;
}

}
}
