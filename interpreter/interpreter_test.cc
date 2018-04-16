#include "interpreter.h"
#include "../abstract_syntax/abstract_syntax.h"
#include "gtest/gtest.h"
#include "utility/memory.h"

using cs160::abstract_syntax::version_1::IntegerExpr;
using cs160::abstract_syntax::version_1::AddExpr;
using cs160::abstract_syntax::version_1::SubtractExpr;
using cs160::abstract_syntax::version_1::MultiplyExpr;
using cs160::abstract_syntax::version_1::DivideExpr;
using cs160::interpreter::InterpretVisitor;

using cs160::make_unique;

// TEST(InterpreterMainTest, GetInterpreterMainTest) {
//   EXPECT_EQ(cs160::rcc::InterpreterMain(), 42);
// }

TEST(InterpreterMainTest, InterpretInteger7) {
  InterpretVisitor interpreter_;
  auto number = make_unique<IntegerExpr>(7);
  number->Visit(&interpreter_);

  EXPECT_EQ(interpreter_.GetOutput(), 7);
}

TEST(InterpreterMainTest, InterpretInteger0) {
  InterpretVisitor interpreter_;
  auto number = make_unique<IntegerExpr>(0);
  number->Visit(&interpreter_);

  EXPECT_EQ(interpreter_.GetOutput(), 0);
}
