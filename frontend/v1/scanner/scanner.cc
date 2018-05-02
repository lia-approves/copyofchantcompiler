/*
 MIT License

 Copyright (c) 2018, Team-Chant
 */

#include <iostream>
#include <string>
#include "frontend/v1/parser/parser.h"
#include "frontend/v1/scanner/state_machine/dfa/dfa.h"
#include "frontend/v1/scanner/state_machine/state/state.h"
#include "frontend/v1/scanner/token/Token.h"
#include "frontend/v1/scanner/token/IntegerToken.h"
#include "frontend/v1/scanner/token/ArithmeticExpressionToken.h"
#include "frontend/v1/scanner/token/OpenParenthesisToken.h"
#include "frontend/v1/scanner/token/ClosedParenthesisToken.h"
#include "abstract_syntax/print_visitor_v1.h"



int main() {
  // declare all states with IDs = {1, 2, ..., n},
  // and make accepting if applicable
  // error state is always state 0
  cs160::abstract_syntax::frontend::PrintVisitor printer_;

  cs160::frontend::State start(1);
  cs160::frontend::State intState(2);
    intState.makeAccepting();
  cs160::frontend::State opState(3);
    opState.makeAccepting();
  cs160::frontend::State openParenState(4);
    openParenState.makeAccepting();
  cs160::frontend::State closeParenState(5);
    closeParenState.makeAccepting();

  // set token type that each state outputs
  start.setTokenOutput([](std::string str)->
  cs160::frontend::Token
  {return cs160::frontend::InvalidToken(str);});

  intState.setTokenOutput([](std::string str)->
  cs160::frontend::Token
  {return cs160::frontend::IntegerToken(str);});

  opState.setTokenOutput([](std::string str)->
  cs160::frontend::Token
  {return cs160::frontend::ArithmeticExpressionToken(str);});

  openParenState.setTokenOutput([](std::string str)->
  cs160::frontend::Token
  {return cs160::frontend::OpenParenthesisToken(str);});

  closeParenState.setTokenOutput([](std::string str)->
  cs160::frontend::Token
  {return cs160::frontend::ClosedParenthesisToken(str);});

  // add all transitions for each state (if any)
  start.addTransition('0', '9', 2);

  start.addTransition('+', 3);
  start.addTransition('-', 3);
  start.addTransition('/', 3);
  start.addTransition('*', 3);

  start.addTransition('(', 4);
  start.addTransition(')', 5);

  intState.addTransition('0', '9', 2);

  // finally, add all states to dfa
  cs160::frontend::DFA arithmeticDFA(start);
  arithmeticDFA.addState(intState);
  arithmeticDFA.addState(opState);
  arithmeticDFA.addState(openParenState);
  arithmeticDFA.addState(closeParenState);

  // then provide the input string and print the resulting queue of tokens
  arithmeticDFA.input("()");
  arithmeticDFA.printQueue();

  cs160::frontend::Parser p(arithmeticDFA.GetOutput());
  try {
    auto e = p.Parse();
    e->Visit(&printer_);
    std::cout << printer_.GetOutput() << std::endl;
  } catch(std::logic_error ex) {
    std::cout << ex.what() << std::endl;
  }


  return 0;
}
