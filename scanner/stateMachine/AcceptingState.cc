#include "state.h"
#include "AcceptingState.h"

namespace cs160 {
namespace scanner {

AcceptingState::AcceptingState(int id, Token result) : State(id) {
  token = result;
}

bool AcceptingState::isAccepting() {
  return true;
}

Token State::getToken() {
    return this->token;
}

}
}
