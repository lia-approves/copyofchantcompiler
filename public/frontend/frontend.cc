#include "public/frontend/frontend.h"
#include "utility/memory.h"

namespace cs160 {
namespace frontend {

Frontend::~Frontend(void) {}

std::unique_ptr<cs160::abstract_syntax::frontend::AstNode> stringToAst(std::string input) {
  // return cs160::abstract_syntax::frontend::IntegerExpr node(2);
  auto tree = std::unique_ptr<cs160::abstract_syntax::frontend::AstNode>(new cs160::abstract_syntax::frontend::IntegerExpr(2));
  return tree;
}

std::queue<cs160::scanner::token::Token> tokenizeString(std::string input) {
  std::queue<cs160::scanner::token::Token> q;
  return q;
}



}  // namespace frontend
}  // namespace cs160

