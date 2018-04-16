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

TEST(InterpreterIntegerTest, Interpret7) {
  InterpretVisitor interpreter_;
  auto number = make_unique<IntegerExpr>(7);
  number->Visit(&interpreter_);

  EXPECT_EQ(interpreter_.GetOutput(), 7);
}

TEST(InterpreterIntegerTest, Interpret0) {
  InterpretVisitor interpreter_;
  auto number = make_unique<IntegerExpr>(0);
  number->Visit(&interpreter_);

  EXPECT_EQ(interpreter_.GetOutput(), 0);
}

TEST(InterpreterAddTest, Interpret_1_2) {
  InterpretVisitor interpreter_;
  auto expr = make_unique<AddExpr>((make_unique<IntegerExpr>(1)),
                                   make_unique<IntegerExpr>(2));

  expr->Visit(&interpreter_);

  EXPECT_EQ(interpreter_.GetOutput(), 3);
}

TEST(InterpreterAddTest, Interpret_neg44_0) {
  InterpretVisitor interpreter_;
  auto expr = make_unique<AddExpr>((make_unique<IntegerExpr>(-44)),
                                   make_unique<IntegerExpr>(0));

  expr->Visit(&interpreter_);

  EXPECT_EQ(interpreter_.GetOutput(), -44);
}

TEST(InterpreterMultiplyTest, Interpret_pos_pos) {
  InterpretVisitor interpreter_;
  auto expr = make_unique<MultiplyExpr>((make_unique<IntegerExpr>(2)),
                                   make_unique<IntegerExpr>(3));

  expr->Visit(&interpreter_);

  EXPECT_EQ(interpreter_.GetOutput(), 6);
}

TEST(InterpreterMultiplyTest, Interpret_pos_neg) {
  InterpretVisitor interpreter_;
  auto expr = make_unique<MultiplyExpr>((make_unique<IntegerExpr>(4)),
                                   make_unique<IntegerExpr>(-9));

  expr->Visit(&interpreter_);

  EXPECT_EQ(interpreter_.GetOutput(), -36);
}

TEST(InterpreterMultiplyTest, Interpret_neg_pos) {
  InterpretVisitor interpreter_;
  auto expr = make_unique<MultiplyExpr>((make_unique<IntegerExpr>(-34)),
                                   make_unique<IntegerExpr>(2));

  expr->Visit(&interpreter_);

  EXPECT_EQ(interpreter_.GetOutput(), -68);
}

TEST(InterpreterMultiplyTest, Interpret_neg_neg) {
  InterpretVisitor interpreter_;
  auto expr = make_unique<MultiplyExpr>((make_unique<IntegerExpr>(-4)),
                                   make_unique<IntegerExpr>(-2));

  expr->Visit(&interpreter_);

  EXPECT_EQ(interpreter_.GetOutput(), 8);
}
