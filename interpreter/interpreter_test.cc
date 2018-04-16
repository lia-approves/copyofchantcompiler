// Copyright msg for cpplint
#include "interpreter/interpreter.h"
#include "abstract_syntax/abstract_syntax.h"
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

TEST(IntegerTest, Interpret7) {
  InterpretVisitor interpreter_;
  auto number = make_unique<IntegerExpr>(7);
  number->Visit(&interpreter_);

  EXPECT_EQ(interpreter_.GetOutput(), 7);
}

TEST(IntegerTest, Interpret0) {
  InterpretVisitor interpreter_;
  auto number = make_unique<IntegerExpr>(0);
  number->Visit(&interpreter_);

  EXPECT_EQ(interpreter_.GetOutput(), 0);
}

TEST(AddTest, Add_1_2) {
  InterpretVisitor interpreter_;
  auto expr = make_unique<AddExpr>((make_unique<IntegerExpr>(1)),
                                   make_unique<IntegerExpr>(2));

  expr->Visit(&interpreter_);

  EXPECT_EQ(interpreter_.GetOutput(), 3);
}

TEST(AddTest, Add_n44_0) {
  InterpretVisitor interpreter_;
  auto expr = make_unique<AddExpr>((make_unique<IntegerExpr>(-44)),
                                   make_unique<IntegerExpr>(0));

  expr->Visit(&interpreter_);

  EXPECT_EQ(interpreter_.GetOutput(), -44);
}

TEST(MultiplyTest, pos_pos) {
  InterpretVisitor interpreter_;
  auto expr = make_unique<MultiplyExpr>((make_unique<IntegerExpr>(2)),
                                   make_unique<IntegerExpr>(3));

  expr->Visit(&interpreter_);

  EXPECT_EQ(interpreter_.GetOutput(), 6);
}

TEST(MultiplyTest, pos_neg) {
  InterpretVisitor interpreter_;
  auto expr = make_unique<MultiplyExpr>((make_unique<IntegerExpr>(4)),
                                   make_unique<IntegerExpr>(-9));

  expr->Visit(&interpreter_);

  EXPECT_EQ(interpreter_.GetOutput(), -36);
}

TEST(MultiplyTest, neg_pos) {
  InterpretVisitor interpreter_;
  auto expr = make_unique<MultiplyExpr>((make_unique<IntegerExpr>(-34)),
                                   make_unique<IntegerExpr>(2));

  expr->Visit(&interpreter_);

  EXPECT_EQ(interpreter_.GetOutput(), -68);
}

TEST(MultiplyTest, neg_neg) {
  InterpretVisitor interpreter_;
  auto expr = make_unique<MultiplyExpr>((make_unique<IntegerExpr>(-4)),
                                   make_unique<IntegerExpr>(-2));

  expr->Visit(&interpreter_);

  EXPECT_EQ(interpreter_.GetOutput(), 8);
}

// Add divide
TEST(DivideTest, pos_pos) {
  InterpretVisitor interpreter_;
  auto expr = make_unique<DivideExpr>((make_unique<IntegerExpr>(4)),
                                   make_unique<IntegerExpr>(2));

  expr->Visit(&interpreter_);

  EXPECT_EQ(interpreter_.GetOutput(), 2);
}

TEST(DivideTest, pos_pos_fraction) {
  InterpretVisitor interpreter_;
  auto expr = make_unique<DivideExpr>((make_unique<IntegerExpr>(70)),
                                   make_unique<IntegerExpr>(22));

  expr->Visit(&interpreter_);

  EXPECT_EQ(interpreter_.GetOutput(), 3);
}

// Add subtract tests
TEST(SubtractTest, Subtract_422_90) {
  InterpretVisitor interpreter_;
  auto expr = make_unique<SubtractExpr>((make_unique<IntegerExpr>(422)),
                                   make_unique<IntegerExpr>(90));

  expr->Visit(&interpreter_);

  EXPECT_EQ(interpreter_.GetOutput(), 332);
}
TEST(SubtractTest, Subtract_n23_9) {
  InterpretVisitor interpreter_;
  auto expr = make_unique<SubtractExpr>((make_unique<IntegerExpr>(-23)),
                                   make_unique<IntegerExpr>(9));

  expr->Visit(&interpreter_);

  EXPECT_EQ(interpreter_.GetOutput(), -32);
}
