#include "scanner/state.h"
#include "scanner/AcceptingState.h"

namespace cs160 {
namespace scanner {

template<typename Token>
AcceptingState<Token>::AcceptingState(int id, Token result) : State<Token>(id) {
  token = result;
}

template<typename Token>
bool AcceptingState<Token>::isAccepting() {
  return true;
}

template<typename Token>
Token State<Token>::getToken() {
    return this->token;
}

}
}
