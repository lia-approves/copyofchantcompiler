#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "interpreter/interpreter.h"
#include "abstract_syntax/abstract_syntax.h"

using cs160::abstract_syntax::version_1::IntegerExpr;
using cs160::abstract_syntax::version_1::AddExpr;
using cs160::abstract_syntax::version_1::SubtractExpr;
using cs160::abstract_syntax::version_1::MultiplyExpr;
using cs160::abstract_syntax::version_1::DivideExpr;
using cs160::interpreter::InterpretVisitor;

using cs160::make_unique;

namespace cs160 {
namespace interpreter {

int InterpreterMain() {
  InterpretVisitor interpreter_;
  auto randomAST = make_unique<;:>(7)
  number->Visit(&interpreter_);
  

  postOrderTraversal(&interpreter_);
  std::cout << std::endl;
  std::cout << "Output string: " << interpreter_.GetOutput();
}

void postOrderTraversal(const BinaryOperatorExpr& ast, AstVisitor* visitor){
  ast.lhs().Visit(visitor);
  ast.rhs().Visit(visitor);
  ast.Visit(visitor);
}

BinaryOperatorExpr* makeRandomAst(){
  const double probNodeIsBinOp = 0.7;
  srand(time(NULL));

  double whichBinOp = rand() % 4;
  switch(whichBinOp){
    case 0:
      return make_unique<AddExpr>(makeRandomAst(probNodeIsBinOp), makeRandomAst(probNodeIsBinOp));
    case 1:
      return make_unique<SubtractExpr>(makeRandomAst(probNodeIsBinOp), makeRandomAst(probNodeIsBinOp));
    case 2:
      return make_unique<MultiplyExpr>((makeRandomAst(probNodeIsBinOp), makeRandomAst(probNodeIsBinOp));
    case 3:
      return make_unique<DivideExpr>((makeRandomAst(probNodeIsBinOp), makeRandomAst(probNodeIsBinOp));
  }
}


BinaryOperatorExpr& makeRandomAST(const double probNodeIsBinOp){
  double isIntExpr = (rand() % 100) / 100;

  if(isIntExpr > probNodeIsBinOp){
    //auto numberLHS = make_unique<IntegerExpr>(rand() % 100);
    //auto numberRHS = make_unique<IntegerExpr>(rand() % 100);
    return IntegerExpr(rand() % 100);
  }else{
    return makeRandomBinOp(makeRandomAst(probNodeIsBinOp), makeRandomAst(probNodeIsBinOp));
  }
}

BinaryOperatorExpr& makeRandomBinOp(const AstNode& lhs, const AstNode& rhs){
  double whichBinOp = rand() % 4;
  switch(whichBinOp){
    case 0:
      return AddExpr(lhs, rhs);
    case 1:
      return SubtractExpr(lhs, rhs);
    case 2:
      return MultiplyExpr(lhs, rhs);
    case 3:
      return DivideExpr&(lhs, rhs);
  }
}

}  // namespace interpreter
}  // namespace cs160
