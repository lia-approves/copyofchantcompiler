#include <iostream>
#include "scanner/stateMachine/dfa.h"
#include "scanner/stateMachine/state.h"
#include "scanner/token/Token.h"
#include "scanner/token/IntegerToken.h"
#include <string>



int main() {

    std::string input = "1+2";

    cs160::scanner::statemachine::State error; // error state
    cs160::scanner::statemachine::State start(0); // s_0

  // ACCEPTING STATES
    cs160::scanner::statemachine::State integer(1,  cs160::scanner::token::IntegerToken("int")); // s_1
    cs160::scanner::statemachine::State op(2,  cs160::scanner::token::Token("stub operator token")); // s_2
    cs160::scanner::statemachine::State leftParen(3); // s_3
    cs160::scanner::statemachine::State rightParent(4); // s_4



  return 0;
}

