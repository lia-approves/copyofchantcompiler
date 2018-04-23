#include "frontend.h"
#include "frontend/scanner/token/IntegerToken.h"
#include "frontend/scanner/token/ArithmeticExpressionToken.h"
#include "frontend/scanner/token/OpenParenthesisToken.h"
#include "frontend/scanner/token/ClosedParenthesisToken.h"

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

std::queue<Token> Frontend::tokenizeString(std::string input) {
  std::queue<Token> q;
  q.push(IntegerToken("2"));
  q.push(ArithmeticExpressionToken("*"));
  q.push(OpenParenthesisToken());
  q.push(IntegerToken("1"));
  q.push(ArithmeticExpressionToken("+"));
  q.push(IntegerToken("3"));
  q.push(ClosedParenthesisToken());
  return q;
}

std::unique_ptr<ast::AstNode> Frontend::makeParseTree(std::queue<Token> tokens) {
  auto two = cs160::make_unique<ast::IntegerExpr>(2);
  auto one = cs160::make_unique<ast::IntegerExpr>(1);
  auto three = cs160::make_unique<ast::IntegerExpr>(3);
  auto add = make_unique<ast::AddExpr>(std::move(one), std::move(three));
  auto root = make_unique<ast::MultiplyExpr>(std::move(two), std::move(add));
  return root;
}
}  // namespace frontend
}  // namespace cs160
