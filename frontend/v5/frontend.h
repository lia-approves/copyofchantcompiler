// Copyright (c) 2018, Team-Chant
#ifndef FRONTEND_V5_FRONTEND_H_
#define FRONTEND_V5_FRONTEND_H_

#include <vector>
#include <string>
#include <memory>
#include "abstract_syntax/abstract_syntax.h"
#include "frontend/combinator/parser.h"
#include "utility/memory.h"
#include "abstract_syntax/print_visitor_v5.h"


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
  using Printer = abstract_syntax::version_5::PrintVisitor;
  namespace ast = cs160::abstract_syntax::frontend;

namespace Frontend {

  Parser Lazy(std::function<Result(State)> &function);

    // Object containing Parsers for all of the rules in v2 Grammar
struct Grammar {
      Parser N;  // done
      Parser V;  // done
      Parser Fn;  // done
      Parser dref;
      Parser lhs;
      Parser primary;
      Parser unary;
      Parser multiply;
      Parser add;
      Parser ae;
      Parser rop;
      Parser re;
      Parser call;
      Parser loop;
      Parser cond;
      Parser assign;
      Parser stmt;
      Parser block;
      Parser fundef;
      Parser program;
};

// Function initializes all of the parsers in Grammar g
void InitializeParsers(Frontend::Grammar *g);

// Takes a string, outputs the root node for the resulting AST Tree
Node stringToAst(std::string s);

}  // namespace Frontend

}  // namespace Parse
}  // namespace frontend
}  // namespace cs160



#endif  // FRONTEND_V5_FRONTEND_H_
