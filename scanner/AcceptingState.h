#ifndef ACCEPTING_STATE_H_
#define ACCEPTING_STATE_H_

namespace cs160 {
namespace scanner {

template<typename Token>

class AcceptingState : public State {
  public:
    AcceptingState(int id, Token result) : State(id);

  private:
    Token token;
}

}
}
