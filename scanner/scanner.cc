#include <iostream>
#include "scanner/stateMachine/dfa.h"
#include "scanner/stateMachine/state.h"
#include "scanner/token/IntegerToken.h"
#include <string>

int main() {
  std::string input = "1+2";

  cs160::scanner::State error; // error state
  cs160::scanner::State start(0); // s_0

  // ACCEPTING STATES
  cs160::scanner::State integer(1, IntegerToken("int")); // s_1
  cs160::scanner::State op(2, Token("stub operator token")); // s_2
  cs160::scanner::State leftParen(3); // s_3
  cs160::scanner::State rightParent(4); // s_4



  return 0;
}
<<<<<<< HEAD
//test
=======

>>>>>>> d2f382767b42609c90bfe2609cd00b39331990b6
