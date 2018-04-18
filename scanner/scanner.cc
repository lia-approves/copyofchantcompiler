#include <iostream>
#include "scanner/stateMachine/dfa.h"
#include "scanner/stateMachine/state.h"
#include "scanner/token/Token.h"
#include "scanner/token/IntegerToken.h"
#include "scanner/token/ArithmeticExpressionToken.h"
#include "scanner/token/OpenParenthesisToken.h"
#include "scanner/token/ClosedParenthesisToken.h"
#include <string>



int main() {
  cs160::scanner::statemachine::State error;

  cs160::scanner::statemachine::State start(0);
  cs160::scanner::statemachine::State intState(1);
  cs160::scanner::statemachine::State opState(2);
  cs160::scanner::statemachine::State openParenState(3);
  cs160::scanner::statemachine::State closeParenState(4);

  start.addTransition('0', 1);
  start.addTransition('1', 1);
  start.addTransition('2', 1);
  start.addTransition('3', 1);
  start.addTransition('4', 1);
  start.addTransition('5', 1);
  start.addTransition('6', 1);
  start.addTransition('7', 1);
  start.addTransition('8', 1);
  start.addTransition('9', 1);

  start.addTransition('+', 2);
  start.addTransition('-', 2);
  start.addTransition('/', 2);
  start.addTransition('*', 2);

  start.addTransition('(', 3);

  start.addTransition(')', 4);

    
    start.set_token_output([](std::string str)->cs160::scanner::token::Token {return cs160::scanner::token::InvalidToken(str);});
    
  intState.addTransition('0', 1);
  intState.addTransition('1', 1);
  intState.addTransition('2', 1);
  intState.addTransition('3', 1);
  intState.addTransition('4', 1);
  intState.addTransition('5', 1);
  intState.addTransition('6', 1);
  intState.addTransition('7', 1);
  intState.addTransition('8', 1);
  intState.addTransition('9', 1);
    
    intState.set_token_output([](std::string str)->cs160::scanner::token::Token {return cs160::scanner::token::IntegerToken(str);});
    opState.set_token_output([](std::string str)->cs160::scanner::token::Token {return cs160::scanner::token::ArithmeticExpressionToken(str);});
    openParenState.set_token_output([](std::string str)->cs160::scanner::token::Token {return cs160::scanner::token::OpenParenthesisToken(str);});
    closeParenState.set_token_output([](std::string str)->cs160::scanner::token::Token {return cs160::scanner::token::ClosedParenthesisToken(str);});

  cs160::scanner::statemachine::DFA arithmeticDFA(start);
  arithmeticDFA.addState(intState);
  arithmeticDFA.addState(opState);
  arithmeticDFA.addState(openParenState);
  arithmeticDFA.addState(closeParenState);

  arithmeticDFA.input('2');
  arithmeticDFA.input('+');
  arithmeticDFA.input('7');
    

  return 0;
}

