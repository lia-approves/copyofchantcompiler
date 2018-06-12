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

  template<class T>
  using Converter = std::function<Value(T)>;

namespace Frontend {



  Parser Lazy(std::function<Result(State)> &function);

ValueVec mult_vec_;
ValueVec add_vec_;
ValueVec call_vec_;
std::vector<ValueVec> re_vec_;
std::vector<ValueVec> block_vec_;
ValueVec var_vec_;
ValueVec function_vec_;
    // Object containing Parsers for all of the rules in v2 Grammar
struct Grammar {
  // As a general note, a lot of the stmt functions work with N but not
  // with ae or any other parser

      Parser N;  // done, tested
      Parser V;  // done, tested
      Parser Fn;  // done, tested
      Parser dref;  // done, tested
      Parser lhs;  // done, tested
      Parser primary;  // done, tested
      Parser unary;  // done, tested
      Parser multiply;  // done, tested
      Parser add;  // done, tested
      Parser ae;  // needs fixing
      Parser rop;  // done, tested
      Parser re;  // done, tested
      Parser call;  // done, works with N but not with ae
      Parser loop;  // done, tested
      Parser cond;  // done, tested
      Parser assign;  // done, tested
      Parser stmt;  // done as a top level production
      Parser block;  // done, works with N
      Parser fundef;  // done, tested
      Parser program;
};

// Function initializes all of the parsers in Grammar g
void InitializeParsers(Frontend::Grammar *g);
void InitializeParsers2(Frontend::Grammar *g);

// Takes a string, outputs the root node for the resulting AST Tree
Node stringToAst(std::string s);

}  // namespace Frontend

}  // namespace Parse
}  // namespace frontend
}  // namespace cs160



#endif  // FRONTEND_V5_FRONTEND_H_
