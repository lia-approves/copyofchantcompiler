#ifndef ACCEPTING_STATE_H_
#define ACCEPTING_STATE_H_

#include "state.h"

namespace cs160 {
namespace scanner {

class AcceptingState: public State {
  public:
    AcceptingState(int id, Token result);
    bool isAccepting();
    Token getToken();

  private:
    Token token;
};

}
}

#endif // ACCEPTING_STATE_H_
