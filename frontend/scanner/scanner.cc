/*
 MIT License
 
 Copyright (c) 2018, Team-Chant
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */


#include <iostream>
#include <string>

#include "frontend/scanner/state_machine/dfa/dfa.h"
#include "frontend/scanner/state_machine/state/state.h"
#include "frontend/scanner/token/Token.h"
#include "frontend/scanner/token/IntegerToken.h"
#include "frontend/scanner/token/ArithmeticExpressionToken.h"
#include "frontend/scanner/token/OpenParenthesisToken.h"
#include "frontend/scanner/token/ClosedParenthesisToken.h"



int main() {
    // error state is always the 0th state

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


    start.set_token_output([](std::string str)->
                           cs160::scanner::token::Token
    {return cs160::scanner::token::InvalidToken(str);});

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

    intState.set_token_output([](std::string str)->
                              cs160::scanner::token::Token
    {return cs160::scanner::token::IntegerToken(str);});
    opState.set_token_output([](std::string str)->
                             cs160::scanner::token::Token
    {return cs160::scanner::token::ArithmeticExpressionToken(str);});
    openParenState.set_token_output([](std::string str)->
                                    cs160::scanner::token::Token
    {return cs160::scanner::token::OpenParenthesisToken(str);});
    closeParenState.set_token_output([](std::string str)->
                                     cs160::scanner::token::Token
    {return cs160::scanner::token::ClosedParenthesisToken(str);});

  cs160::scanner::statemachine::DFA arithmeticDFA(start);
  arithmeticDFA.addState(intState);
  arithmeticDFA.addState(opState);
  arithmeticDFA.addState(openParenState);
  arithmeticDFA.addState(closeParenState);

    arithmeticDFA.input("12(a))2");
    arithmeticDFA.print_queue();


  return 0;
}
