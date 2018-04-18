#include "public/frontend/frontend.h"

#include "scanner/token/IntegerToken.h"
#include "scanner/token/ArithmeticExpressionToken.h"
#include "scanner/token/OpenParenthesisToken.h"
#include "scanner/token/ClosedParenthesisToken.h"

namespace cs160 {
namespace frontend {

namespace ast = cs160::abstract_syntax::frontend;
namespace scan = cs160::scanner;

Frontend::~Frontend(void) {}

// stub: 2 * (1 + 3)

std::unique_ptr<ast::AstNode> Frontend::stringToAst(std::string input) {
  // return cs160::abstract_syntax::frontend::IntegerExpr node(2);
  auto tree = std::unique_ptr<ast::AstNode>(new ast::IntegerExpr(2));
  return tree;
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

std::unique_ptr<ast::AstNode> Frontend::makeParseTree(std::queue<scan::token::Token> tokens) {
  auto tree = std::unique_ptr<ast::AstNode>(new ast::IntegerExpr(2));
  return tree;
}



}  // namespace frontend
}  // namespace cs160

