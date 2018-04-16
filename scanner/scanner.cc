#include <iostream>
#include "scanner/stateMachine/dfa.h"
#include "scanner/stateMachine/state.h"

// namespace cs160 {
// namespace scanner {

int main() {
  cs160::scanner::State error;
  cs160::scanner::State test(1);
  cs160::scanner::DFA dfa(error);
  // dfa.addState(test);
  dfa.addTransition(error.getId(), 'a', test.getId());
  std::cout << "Starting state: " << dfa.getCurrentState().getId() << std::endl;
  dfa.input('a');
  std::cout << "Next state: " << dfa.getCurrentState().getId() << std::endl;

  return 0;
}

// }  // namespace scanner
// }  // namespace cs160
