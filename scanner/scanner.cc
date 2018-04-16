#include <iostream>
#include "scanner/stateMachine/dfa.h"
#include "scanner/stateMachine/state.h"

using namespace cs160::scanner;

int main() {
  State error;
  DFA dfa(error);
  std::cout << "hi";
}
