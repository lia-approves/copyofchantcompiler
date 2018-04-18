#include "public/frontend/frontend.h"

namespace cs160 {
namespace frontend {

namespace ast = cs160::abstract_syntax::frontend;
namespace scan = cs160::scanner;

Frontend::~Frontend(void) {}

std::unique_ptr<ast::AstNode> Frontend::stringToAst(std::string input) {
  // return cs160::abstract_syntax::frontend::IntegerExpr node(2);
  auto tree = std::unique_ptr<ast::AstNode>(new ast::IntegerExpr(2));
  return tree;
}

std::queue<scan::token::Token> Frontend::tokenizeString(std::string input) {
  std::queue<scan::token::Token> q;
  return q;
}

std::unique_ptr<ast::AstNode> Frontend::makeParseTree(std::queue<scan::token::Token> tokens) {
  auto tree = std::unique_ptr<ast::AstNode>(new ast::IntegerExpr(2));
  return tree;
}



}  // namespace frontend
}  // namespace cs160

