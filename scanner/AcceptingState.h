#ifndef ACCEPTING_STATE_H_
#define ACCEPTING_STATE_H_

#include "scanner/state.h"

namespace cs160 {
namespace scanner {

template<typename Token>
class AcceptingState : public State {
  public:
    AcceptingState(int id, Token result);

  private:
    Token token;
};

}
}

#endif // ACCEPTING_STATE_H_
