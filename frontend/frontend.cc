/*
 MIT License

 Copyright (c) 2018, Team-Chant
 */
#include <string>
#include "frontend/frontend.h"
#include "frontend/v1/parser/parser.h"
#include "frontend/v1/scanner/state_machine/dfa/dfa.h"

namespace cs160 {
namespace frontend {

namespace ast = cs160::abstract_syntax::frontend;

Frontend::~Frontend(void) {}

// stub: 2 * (1 + 3)

std::unique_ptr<ast::AstNode> Frontend::stringToAst(std::string input) {
  // return cs160::abstract_syntax::frontend::IntegerExpr node(2);
  auto tokenQueue = Frontend::tokenizeString(input);
  return Frontend::makeParseTree(tokenQueue);
}


std::vector<std::shared_ptr<Token>>
  Frontend::tokenizeString(std::string input) {
  DFA dfa = makeDFA();
  dfa.input(input);
  return dfa.GetOutput();
}

std::unique_ptr<ast::AstNode> Frontend::makeParseTree
(std::vector<std::shared_ptr<Token>> tokens) {
  /*auto two = cs160::make_unique<ast::IntegerExpr>(2);
  auto one = cs160::make_unique<ast::IntegerExpr>(1);
  auto three = cs160::make_unique<ast::IntegerExpr>(3);
  auto add = make_unique<ast::AddExpr>(std::move(one), std::move(three));
  auto root = make_unique<ast::MultiplyExpr>(std::move(two), std::move(add));
  */
  // call parser
  Parser par(tokens);
  auto root = par.Parse();
  return root;
}


DFA Frontend::makeDFA() {
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

}  // namespace frontend
}  // namespace cs160
