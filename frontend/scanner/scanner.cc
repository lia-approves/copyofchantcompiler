#include <iostream>
#include "frontend/scanner/state_machine/dfa/dfa.h"
#include "frontend/scanner/state_machine/state/state.h"
#include "frontend/scanner/token/Token.h"
#include "frontend/scanner/token/IntegerToken.h"
#include "frontend/scanner/token/ArithmeticExpressionToken.h"
#include "frontend/scanner/token/OpenParenthesisToken.h"
#include "frontend/scanner/token/ClosedParenthesisToken.h"
#include <string>



int main() {
    //error state is always the 0th state

  cs160::scanner::statemachine::State start(1);
  cs160::scanner::statemachine::State intState(2);
    intState.makeAccepting();
  cs160::scanner::statemachine::State opState(3);
    opState.makeAccepting();
  cs160::scanner::statemachine::State openParenState(4);
    openParenState.makeAccepting();
  cs160::scanner::statemachine::State closeParenState(5);
    closeParenState.makeAccepting();

  start.addTransition('0', 2);
  start.addTransition('1', 2);
  start.addTransition('2', 2);
  start.addTransition('3', 2);
  start.addTransition('4', 2);
  start.addTransition('5', 2);
  start.addTransition('6', 2);
  start.addTransition('7', 2);
  start.addTransition('8', 2);
  start.addTransition('9', 2);

  start.addTransition('+', 3);
  start.addTransition('-', 3);
  start.addTransition('/', 3);
  start.addTransition('*', 3);

  start.addTransition('(', 4);

  start.addTransition(')', 5);


    start.set_token_output([](std::string str)->cs160::scanner::token::Token {return cs160::scanner::token::InvalidToken(str);});

  intState.addTransition('0', 2);
  intState.addTransition('1', 2);
  intState.addTransition('2', 2);
  intState.addTransition('3', 2);
  intState.addTransition('4', 2);
  intState.addTransition('5', 2);
  intState.addTransition('6', 2);
  intState.addTransition('7', 2);
  intState.addTransition('8', 2);
  intState.addTransition('9', 2);

    intState.set_token_output([](std::string str)->cs160::scanner::token::Token {return cs160::scanner::token::IntegerToken(str);});
    opState.set_token_output([](std::string str)->cs160::scanner::token::Token {return cs160::scanner::token::ArithmeticExpressionToken(str);});
    openParenState.set_token_output([](std::string str)->cs160::scanner::token::Token {return cs160::scanner::token::OpenParenthesisToken(str);});
    closeParenState.set_token_output([](std::string str)->cs160::scanner::token::Token {return cs160::scanner::token::ClosedParenthesisToken(str);});

  cs160::scanner::statemachine::DFA arithmeticDFA(start);
  arithmeticDFA.addState(intState);
  arithmeticDFA.addState(opState);
  arithmeticDFA.addState(openParenState);
  arithmeticDFA.addState(closeParenState);

  //arithmeticDFA.input('2');
  //arithmeticDFA.input('+');
  //arithmeticDFA.input('7');
    arithmeticDFA.input("12(a))2");
    arithmeticDFA.print_queue();


  return 0;
}
