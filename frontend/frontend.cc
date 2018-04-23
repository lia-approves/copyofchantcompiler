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


#include "frontend/frontend.h"
#include "frontend/scanner/token/IntegerToken.h"
#include "frontend/scanner/token/ArithmeticExpressionToken.h"
#include "frontend/scanner/token/OpenParenthesisToken.h"
#include "frontend/scanner/token/ClosedParenthesisToken.h"

namespace cs160 {
namespace frontend {

namespace ast = cs160::abstract_syntax::frontend;
namespace scan = cs160::scanner;

Frontend::~Frontend(void) {}

// stub: 2 * (1 + 3)

std::unique_ptr<ast::AstNode> Frontend::stringToAst(std::string input) {
  // return cs160::abstract_syntax::frontend::IntegerExpr node(2);
  auto tokenQueue = Frontend::tokenizeString(input);
  return Frontend::makeParseTree(tokenQueue);
}

std::queue<scan::token::Token> Frontend::tokenizeString(std::string input) {
  std::queue<scan::token::Token> q;
  q.push(scan::token::IntegerToken("2"));
  q.push(scan::token::ArithmeticExpressionToken("*"));
  q.push(scan::token::OpenParenthesisToken());
  q.push(scan::token::IntegerToken("1"));
  q.push(scan::token::ArithmeticExpressionToken("+"));
  q.push(scan::token::IntegerToken("3"));
  q.push(scan::token::ClosedParenthesisToken());
  return q;
}

std::unique_ptr<ast::AstNode>
    Frontend::makeParseTree(std::queue<scan::token::Token> tokens) {
  auto two = cs160::make_unique<ast::IntegerExpr>(2);
  auto one = cs160::make_unique<ast::IntegerExpr>(1);
  auto three = cs160::make_unique<ast::IntegerExpr>(3);
  auto add = make_unique<ast::AddExpr>(std::move(one), std::move(three));

  auto root = make_unique<ast::MultiplyExpr>(std::move(two), std::move(add));
  return root;
}
}  // namespace frontend
}  // namespace cs160
