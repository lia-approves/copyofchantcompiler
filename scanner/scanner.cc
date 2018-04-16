#include <iostream>
#include "scanner/stateMachine/dfa.h"
#include "scanner/stateMachine/state.h"
#include "scanner/stateMachine/AcceptingState.h"
#include "scanner/token/IntegerToken.h"
#include <string>

// namespace cs160 {
// namespace scanner {

int main() {
  cs160::scanner::State error;
  cs160::scanner::State test(1);
  cs160::scanner::DFA dfa(error);
  // Token regulartoken("hi");
  // // dfa.addState(test);
  // dfa.addTransition(error.getId(), 'a', test.getId());
  // std::cout << "Starting state: " << dfa.getCurrentState().getId() << std::endl;
  // dfa.input('a');
  // std::cout << "Next state: " << dfa.getCurrentState().getId() << std::endl;
  // Token res = dfa.input('4');
  // std::cout << res.get_token() << std::endl;

  IntegerToken token("hi");
  cs160::scanner::AcceptingState as(7, token);
  std::cout << "Accepting state token: " + as.getToken().get_token() << std::endl;

  dfa.addState(as);
  dfa.addTransition(error.getId(), 'a', as.getId());
  dfa.input('a');

  std::cout << "current state id: " << dfa.getCurrentState().getId() << std::endl;
  std::cout << "current state accepting?: " << dfa.getCurrentState().isAccepting() << std::endl;

  return 0;
}

// }  // namespace scanner
// }  // namespace cs160
