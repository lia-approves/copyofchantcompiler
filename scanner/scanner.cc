#include <iostream>
#include "scanner/stateMachine/dfa.h"
#include "scanner/stateMachine/state.h"

using namespace cs160::scanner;

int main() {
  State error;
  State test(1);
  DFA dfa(error);
  // dfa.addState(test);
  dfa.addTransition(error.getId(), 'a', test.getId());
  std::cout << "Starting state: " << dfa.getCurrentState().getId() << std::endl;
  dfa.input('a');
  std::cout << "Next state: " << dfa.getCurrentState().getId() << std::endl;

}
