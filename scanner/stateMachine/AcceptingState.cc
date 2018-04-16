#include "AcceptingState.h"

namespace cs160 {
namespace scanner {

AcceptingState::AcceptingState(int id, Token result) : State(id) {
  token = result;
}

bool AcceptingState::isAccepting() {
  return true;
}

Token AcceptingState::getToken() {
    return this->token;
}

}
}
