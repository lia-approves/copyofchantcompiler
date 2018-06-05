// Copyright (c) 2018, Team-Chant
#ifndef FRONTEND_V2_FRONTEND_H_
#define FRONTEND_V2_FRONTEND_H_

#include <vector>
#include <string>
#include <memory>
#include "abstract_syntax/abstract_syntax.h"
#include "frontend/combinator/parser.h"
#include "utility/memory.h"

namespace cs160 {
namespace frontend {
namespace Parse {

class Frontend {
 public:
  ~Frontend(void);
  Node stringToAst(std::string input);

 private:
  Parser Program();
  Parser Assign();
  Parser Expression();
  Parser Add();
  Parser Multiply();
  Parser Unary();
  Parser Primary();
  Parser Test_Function();
  Parser Lazy(Parser (Frontend::*function)());
  Parser Test2();
};

}  // namespace Parse
}  // namespace frontend
}  // namespace cs160

template<class R, class T>
std::unique_ptr<R> unique_cast(std::unique_ptr<T> &&p) {
  T* ptr = p.release();
  return std::unique_ptr<R>(static_cast<R*>(ptr));
}

#endif  // FRONTEND_V2_FRONTEND_H_
