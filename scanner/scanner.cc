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
  IntegerToken token;
  cs160::scanner::AcceptingState(7, token);
  // dfa.addState(test);
  dfa.addTransition(error.getId(), 'a', test.getId());
  std::cout << "Starting state: " << dfa.getCurrentState().getId() << std::endl;
  dfa.input('a');
  std::cout << "Next state: " << dfa.getCurrentState().getId() << std::endl;
  std::cout << token.get_token();

  return 0;
}

// }  // namespace scanner
// }  // namespace cs160
