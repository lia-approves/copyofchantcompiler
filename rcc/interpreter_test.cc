#include "gtest/gtest.h"
#include "./interpreter.h"
#include "./abstract_syntax_tree.h"
#include "./memory.h"


using cs160::abstract_syntax::IntegerExpr;
using cs160::abstract_syntax::AddExpr;
using cs160::abstract_syntax::SubtractExpr;
using cs160::abstract_syntax::MultiplyExpr;
using cs160::abstract_syntax::DivideExpr;
using cs160::abstract_syntax::InterpretVisitor;

using cs160::make_unique;
// TEST(InterpreterMainTest, GetInterpreterMainTest) {
//   EXPECT_EQ(cs160::rcc::InterpreterMain(), 42);
// }

TEST(InterpreterMainTest, SimpleTest) {
  InterpretVisitor interpreter_;
  auto number = make_unique<IntegerExpr>(7);
  number->Visit(&interpreter_);

  EXPECT_EQ(interpreter_.GetOutput(), "7");
}
