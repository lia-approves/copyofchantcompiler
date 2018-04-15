#include "scanner/acceptingState.h"

namespace cs160 {
namespace scanner {

template<typename Token>
AcceptingState::AcceptingState(int id, Token result) : State(id) {
  token = result;
}

template<typename Token>
virtual bool AcceptingState::isAccepting() {
  return true;
}

template<typename Token>
virtual Token State::getToken() {
    return token;
}

}
}
