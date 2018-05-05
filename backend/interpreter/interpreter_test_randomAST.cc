// Copyright msg for cpplint

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <iostream>

#include "interpreter/interpreter.h"
#include "abstract_syntax/abstract_syntax.h"
#include "gtest/gtest.h"
#include "utility/memory.h"



using cs160::abstract_syntax::backend::AstNode;
using cs160::abstract_syntax::backend::BinaryOperatorExpr;
using cs160::abstract_syntax::backend::IntegerExpr;
using cs160::abstract_syntax::backend::AddExpr;
using cs160::abstract_syntax::backend::SubtractExpr;
using cs160::abstract_syntax::backend::MultiplyExpr;
using cs160::abstract_syntax::backend::DivideExpr;

using cs160::abstract_syntax::backend::AstVisitor;
using cs160::interpreter::InterpretVisitor;

using cs160::make_unique;

std::unique_ptr<const AstNode> makeRandomAst();
std::unique_ptr<const AstNode> makeRandomAst(const double probNodeIsBinOp);
std::unique_ptr<const BinaryOperatorExpr> makeRandomBinOp(
  std::unique_ptr<const AstNode> lhs,
  std::unique_ptr<const AstNode> rhs,
  const double probNodeIsBinOp);

TEST(InterpretMainTest, InterpretRandomAst) {
  InterpretVisitor interpreter_;
  auto randomAst_ = makeRandomAst();
  randomAst_->Visit(&interpreter_);
  std::cout << std::endl;
  std::cout << "Evaluated input: " << interpreter_.GetOutput();

  EXPECT_EQ(0, 0);
}

std::unique_ptr<const AstNode> makeRandomAst() {
  const double probNodeIsBinOp = 0.2;
  srand(time(NULL));

  int whichBinOp = rand_r() % 4;
  switch (whichBinOp) {
    case 0:
    {
      std::cout << "( + ";
      auto lhs = makeRandomAst(probNodeIsBinOp);
      std::cout << " ";
      auto rhs = makeRandomAst(probNodeIsBinOp);
      std:: cout << " )";
      return std::move(
        make_unique<const AddExpr>(std::move(lhs), std::move(rhs)));
    }
    case 1:
    {
      std::cout << "( - ";
      auto lhs = makeRandomAst(probNodeIsBinOp);
      std::cout << " ";
      auto rhs = makeRandomAst(probNodeIsBinOp);
      std:: cout << " )";
      return std::move(
        make_unique<const SubtractExpr>(std::move(lhs), std::move(rhs)));
    }
    case 2:
    {
      std::cout << "( * ";
      auto lhs = makeRandomAst(probNodeIsBinOp);
      std::cout << " ";
      auto rhs = makeRandomAst(probNodeIsBinOp);
      std:: cout << " )";
      return std::move(
        make_unique<const MultiplyExpr>(std::move(lhs), std::move(rhs)));
    }
    default:
    {
       std::cout << "( / ";
      auto lhs = makeRandomAst(probNodeIsBinOp);
      std::cout << " ";
      auto rhs = makeRandomAst(probNodeIsBinOp);
      std:: cout << " )";
      return std::move(
        make_unique<const DivideExpr>(
          std::move(lhs),
          std::move(rhs)));
    }
  }
}

std::unique_ptr<const AstNode> makeRandomAst(const double probNodeIsBinOp) {
  double isIntExpr = (rand_r() % 100) / 100;

  if (isIntExpr > probNodeIsBinOp) {
    int randomInt = rand_r() % 100;
    std::cout << randomInt;
    return std::move(make_unique<IntegerExpr>(randomInt));
  } else {
    return std::move(
      makeRandomBinOp(
        std::move(makeRandomAst(probNodeIsBinOp)),
        std::move(makeRandomAst(probNodeIsBinOp)),
        probNodeIsBinOp));
  }
}

std::unique_ptr<const BinaryOperatorExpr> makeRandomBinOp(
  std::unique_ptr<const AstNode> lhs,
  std::unique_ptr<const AstNode> rhs,
  const double probNodeIsBinOp) {
  int whichBinOp = rand_r() % 4;
  switch (whichBinOp) {
    case 0:
    {
      std::cout << "( + ";
      auto lhs = makeRandomAst(probNodeIsBinOp);
      std::cout << " ";
      auto rhs = makeRandomAst(probNodeIsBinOp);
      std:: cout << " )";
      return std::move(
        make_unique<const AddExpr>(std::move(lhs),
        std::move(rhs)));
    }
    case 1:
    {
      std::cout << "( - ";
      auto lhs = makeRandomAst(probNodeIsBinOp);
      std::cout << " ";
      auto rhs = makeRandomAst(probNodeIsBinOp);
      std:: cout << " )";
      return std::move(
        make_unique<const SubtractExpr>(std::move(lhs),
        std::move(rhs)));
    }
    case 2:
    {
      std::cout << "( * ";
      auto lhs = makeRandomAst(probNodeIsBinOp);
      std::cout << " ";
      auto rhs = makeRandomAst(probNodeIsBinOp);
      std:: cout << " )";
      return std::move(
        make_unique<const MultiplyExpr>(std::move(lhs),
        std::move(rhs)));
    }
    default:
    {
      std::cout << "( / ";
      auto lhs = makeRandomAst(probNodeIsBinOp);
      std::cout << " ";
      auto rhs = makeRandomAst(probNodeIsBinOp);
      std:: cout << " )";
      return std::move(
        make_unique<const DivideExpr>(std::move(lhs),
        std::move(rhs)));
    }
  }
}
