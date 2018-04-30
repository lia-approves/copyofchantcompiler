/*
 MIT License

 Copyright (c) 2018, Team-Chant
 */
#include <vector>
#include <memory>
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
  std::vector<std::shared_ptr<Token>> output = d.GetOutput();
  IntegerToken it1(1);
  std::shared_ptr<Token> it1t = std::make_shared<Token>(it1);
  ArithmeticExpressionToken at('+');
  std::shared_ptr<Token> att = std::make_shared<Token>(at);
  IntegerToken it2(2);
  std::shared_ptr<Token> it2t = std::make_shared<Token>(it2);
  ASSERT_EQ(output.at(0)->GetToken(), it1t->GetToken());
  ASSERT_EQ(output.at(1)->GetToken(), att->GetToken());
  ASSERT_EQ(output.at(2)->GetToken(), it2t->GetToken());
}

TEST(ParenthesisDFATest, BasicDFA) {
  DFA d = makeDFA();
  d.input("(())");
  std::vector<std::shared_ptr<Token>> output = d.GetOutput();
  OpenParenthesisToken opt;
  std::shared_ptr<Token> optt = std::make_shared<Token>(opt);
  ClosedParenthesisToken cpt;
  std::shared_ptr<Token> cptt = std::make_shared<Token>(cpt);
  ASSERT_EQ(output.at(0)->GetToken(), optt->GetToken());
  ASSERT_EQ(output.at(1)->GetToken(), optt->GetToken());
  ASSERT_EQ(output.at(2)->GetToken(), cptt->GetToken());
  ASSERT_EQ(output.at(3)->GetToken(), cptt->GetToken());
}

TEST(ArithmeticDFATest, BasicDFA) {
  DFA d = makeDFA();
  d.input("+-*/");
  std::vector<std::shared_ptr<Token>> output = d.GetOutput();
  ArithmeticExpressionToken at('+');
  std::shared_ptr<Token> att = std::make_shared<Token>(at);
  ArithmeticExpressionToken st('-');
  std::shared_ptr<Token> stt = std::make_shared<Token>(st);
  ArithmeticExpressionToken mt('*');
  std::shared_ptr<Token> mtt = std::make_shared<Token>(mt);
  ArithmeticExpressionToken dt('/');
  std::shared_ptr<Token> dtt = std::make_shared<Token>(dt);
  ASSERT_EQ(output.at(0)->GetToken(), att->GetToken());
  ASSERT_EQ(output.at(1)->GetToken(), stt->GetToken());
  ASSERT_EQ(output.at(2)->GetToken(), mtt->GetToken());
  ASSERT_EQ(output.at(3)->GetToken(), dtt->GetToken());
}

TEST(InvalidDFATest, BasicDFA) {
  DFA d = makeDFA();
  d.input("a");
  std::vector<std::shared_ptr<Token>> output = d.GetOutput();
  InvalidToken ivt;
  std::shared_ptr<Token> ivtt = std::make_shared<Token>(ivt);
  ASSERT_EQ(output.at(0)->GetToken(), ivtt->GetToken());
}

TEST(InvalidDFATest2, BasicDFA) {
  DFA d = makeDFA();
  d.input("+ 0");
  std::vector<std::shared_ptr<Token>> output = d.GetOutput();
  InvalidToken ivt;
  std::shared_ptr<Token> ivtt = std::make_shared<Token>(ivt);
  ArithmeticExpressionToken aet('+');
  std::shared_ptr<Token> aett = std::make_shared<Token>(aet);
  IntegerToken it(0);
  std::shared_ptr<Token> itt = std::make_shared<Token>(it);
  ASSERT_EQ(output.at(0)->GetToken(), aett->GetToken());
  ASSERT_EQ(output.at(1)->GetToken(), ivtt->GetToken());
  ASSERT_EQ(output.at(2)->GetToken(), itt->GetToken());
}
}  // namespace frontend
}  // namespace cs160
