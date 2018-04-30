/*
 MIT License

 Copyright (c) 2018, Team-Chant
 */
#include <vector>
#include "gtest/gtest.h"
#include "frontend/v1/scanner/token/Token.h"
#include "frontend/v1/scanner/token/InvalidToken.h"
#include "frontend/v1/scanner/token/IntegerToken.h"
#include "frontend/v1/scanner/token/OpenParenthesisToken.h"
#include "frontend/v1/scanner/token/ClosedParenthesisToken.h"
#include "frontend/v1/scanner/token/ArithmeticExpressionToken.h"
#include "frontend/v1/scanner/state_machine/state/state.h"
#include "frontend/v1/scanner/state_machine/dfa/dfa.h"

namespace cs160 {
namespace frontend {

DFA makeDFA() {
  cs160::frontend::State start(1);
  cs160::frontend::State intState(2);
    intState.makeAccepting();
  cs160::frontend::State opState(3);
    opState.makeAccepting();
  cs160::frontend::State openParenState(4);
    openParenState.makeAccepting();
  cs160::frontend::State closeParenState(5);
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

    start.setTokenOutput([](std::string str)->
    cs160::frontend::Token
    {return cs160::frontend::InvalidToken(str);});

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

  cs160::frontend::DFA arithmeticDFA(start);
  arithmeticDFA.addState(intState);
  arithmeticDFA.addState(opState);
  arithmeticDFA.addState(openParenState);
  arithmeticDFA.addState(closeParenState);

  return arithmeticDFA;
}

TEST(AdditionDFATest, BasicDFA) {
  DFA d = makeDFA();
  d.input("1+2");
  std::vector<Token> output = d.GetOutput();
  IntegerToken it1(1);
  ArithmeticExpressionToken at('+');
  IntegerToken it2(2);
  ASSERT_EQ(output.at(0).GetToken(), it1.GetToken());
  ASSERT_EQ(output.at(1).GetToken(), at.GetToken());
  ASSERT_EQ(output.at(2).GetToken(), it2.GetToken());
}

TEST(ParenthesisDFATest, BasicDFA) {
  DFA d = makeDFA();
  d.input("(())");
  std::vector<Token> output = d.GetOutput();
  OpenParenthesisToken opt;
  ClosedParenthesisToken cpt;
  ASSERT_EQ(output.at(0).GetToken(), opt.GetToken());
  ASSERT_EQ(output.at(1).GetToken(), opt.GetToken());
  ASSERT_EQ(output.at(2).GetToken(), cpt.GetToken());
  ASSERT_EQ(output.at(3).GetToken(), cpt.GetToken());
}

TEST(ArithmeticDFATest, BasicDFA) {
  DFA d = makeDFA();
  d.input("+-*/");
  std::vector<Token> output = d.GetOutput();
  ArithmeticExpressionToken at('+');
  ArithmeticExpressionToken st('-');
  ArithmeticExpressionToken mt('*');
  ArithmeticExpressionToken dt('/');
  ASSERT_EQ(output.at(0).GetToken(), at.GetToken());
  ASSERT_EQ(output.at(1).GetToken(), st.GetToken());
  ASSERT_EQ(output.at(2).GetToken(), mt.GetToken());
  ASSERT_EQ(output.at(3).GetToken(), dt.GetToken());
}

TEST(InvalidDFATest, BasicDFA) {
  DFA d = makeDFA();
  d.input("a");
  std::vector<Token> output = d.GetOutput();
  InvalidToken ivt;
  ASSERT_EQ(output.at(0).GetToken(), ivt.GetToken());
}

TEST(InvalidDFATest2, BasicDFA) {
  DFA d = makeDFA();
  d.input("+ 0");
  std::vector<Token> output = d.GetOutput();
  InvalidToken ivt;
  ArithmeticExpressionToken aet('+');
  IntegerToken it(0);
  ASSERT_EQ(output.at(0).GetToken(), aet.GetToken());
  ASSERT_EQ(output.at(1).GetToken(), ivt.GetToken());
  ASSERT_EQ(output.at(2).GetToken(), it.GetToken());
}

}  // namespace frontend
}  // namespace cs160
