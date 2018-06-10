// Copyright (c) 2018, Team-Chant
#ifndef FRONTEND_V2_FRONTEND_H_
#define FRONTEND_V2_FRONTEND_H_

#include <vector>
#include <string>
#include <memory>
#include "abstract_syntax/abstract_syntax.h"
#include "frontend/combinator/parser.h"
#include "utility/memory.h"
#include "abstract_syntax/print_visitor_v2.h"


// Takes a pointer to AstNode Type T and outputs a pointer to AstNode Type R
template<class R, class T>
std::unique_ptr<R> unique_cast(std::unique_ptr<T> &&p) {
  T* ptr = p.release();
  return std::unique_ptr<R>(static_cast<R*>(ptr));
}

namespace cs160 {
namespace frontend {
namespace Parse {
  using Parser = std::function<Result(State)>;
  using ValueVec = std::vector<Value>;
  using Printer = abstract_syntax::version_2::PrintVisitor;
  namespace ast = cs160::abstract_syntax::frontend;

namespace Frontend {

// Used for parsing
  ValueVec mult_vec_;
  ValueVec add_vec_;
  std::vector<std::unique_ptr<const ast::Assignment>> assignments_;

  Parser Lazy(std::function<Result(State)> &function);

// Object containing Parsers for all of the rules in v2 Grammar
struct Grammar {
  Parser Program_;
  Parser Assign_;  // done
  Parser Expression_;  // done
  Parser Add_;  // done
  Parser Multiply_;  // done
  Parser Unary_;  // done
  Parser Primary_;  // done
  Parser Variable_;  // done
};

// Function initializes all of the parsers in Grammar g
void InitializeParsers(Frontend::Grammar *g);

// Takes a string, outputs the root node for the resulting AST Tree
Node stringToAst(std::string s);

}  // namespace Frontend

}  // namespace Parse
}  // namespace frontend
}  // namespace cs160



#endif  // FRONTEND_V2_FRONTEND_H_
