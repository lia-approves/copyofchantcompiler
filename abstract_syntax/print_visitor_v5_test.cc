// Copyright (c) 2018, Team-Chant
#include <sstream>
#include <string>
#include "gtest/gtest.h"
#include "abstract_syntax/abstract_syntax_tree_v5.h"
#include "abstract_syntax/print_visitor_v5.h"
#include "utility/memory.h"

using cs160::abstract_syntax::version_5::IntegerExpr;
using cs160::abstract_syntax::version_5::VariableExpr;
using cs160::abstract_syntax::version_5::Dereference;
using cs160::abstract_syntax::version_5::AddExpr;
using cs160::abstract_syntax::version_5::SubtractExpr;
using cs160::abstract_syntax::version_5::MultiplyExpr;
using cs160::abstract_syntax::version_5::DivideExpr;
using cs160::abstract_syntax::version_5::LessThanExpr;
using cs160::abstract_syntax::version_5::LessThanEqualToExpr;
using cs160::abstract_syntax::version_5::GreaterThanExpr;
using cs160::abstract_syntax::version_5::GreaterThanEqualToExpr;
using cs160::abstract_syntax::version_5::EqualToExpr;
using cs160::abstract_syntax::version_5::LogicalAndExpr;
using cs160::abstract_syntax::version_5::LogicalOrExpr;
using cs160::abstract_syntax::version_5::AssignmentFromArithExp;
using cs160::abstract_syntax::version_5::AssignmentFromNewTuple;
using cs160::abstract_syntax::version_5::Conditional;
using cs160::abstract_syntax::version_5::Loop;
using cs160::abstract_syntax::version_5::FunctionCall;
using cs160::abstract_syntax::version_5::FunctionDef;
using cs160::abstract_syntax::version_5::Program;
using cs160::abstract_syntax::version_5::PrintVisitor;

namespace ast = cs160::abstract_syntax::version_5;


class PrinterTest : public ::testing::Test {
 protected:
  PrintVisitor printer_;
};

TEST_F(PrinterTest, IntegerExprIsVisited) {
  // auto number = make_unique<const IntegerExpr>(7);
  std::unique_ptr<const IntegerExpr> number( new IntegerExpr(7));
  number->Visit(&printer_);

  EXPECT_EQ(printer_.GetOutput(), "7");
}

TEST_F(PrinterTest, VariableExprIsVisited) {
  // auto variable = make_unique<const VariableExpr>("var");
  std::unique_ptr<const VariableExpr> variable(new VariableExpr("var"));

  variable->Visit(&printer_);

  EXPECT_EQ(printer_.GetOutput(), "var");
}

TEST_F(PrinterTest, DereferenceIsVisited) {
  std::unique_ptr<const Dereference> deref(new Dereference(
    std::unique_ptr<const VariableExpr> (new VariableExpr("var_123")),
    std::unique_ptr<const AddExpr> (new AddExpr(
      std::unique_ptr<const IntegerExpr> (new IntegerExpr(7)),
      std::unique_ptr<const IntegerExpr> (new IntegerExpr(5))))));

  deref->Visit(&printer_);

  EXPECT_EQ(printer_.GetOutput(), "var_123->(+ 7 5)");
}

TEST_F(PrinterTest, AddExprIsVisited) {
std::unique_ptr<const AddExpr> expr(new AddExpr
        (std::unique_ptr<const IntegerExpr> (new IntegerExpr(7)),
          std::unique_ptr<const IntegerExpr> (new IntegerExpr(5))));
  expr->Visit(&printer_);

  EXPECT_EQ(printer_.GetOutput(), "(+ 7 5)");
}

TEST_F(PrinterTest, SubtractExprIsVisited) {
  // auto expr = make_unique<const SubtractExpr>(
  //     make_unique<const IntegerExpr>(7), make_unique<const IntegerExpr>(5));
  std::unique_ptr<const SubtractExpr> expr(new SubtractExpr
          (std::unique_ptr<const IntegerExpr> (new IntegerExpr(7)),
            std::unique_ptr<const IntegerExpr> (new IntegerExpr(5))));

  expr->Visit(&printer_);

  EXPECT_EQ(printer_.GetOutput(), "(- 7 5)");
}

TEST_F(PrinterTest, MultiplyExprIsVisited) {
  auto expr = std::make_unique<const MultiplyExpr>(
      std::make_unique<const IntegerExpr>(7),
      std::make_unique<const IntegerExpr>(5));


  expr->Visit(&printer_);

  EXPECT_EQ(printer_.GetOutput(), "(* 7 5)");
}

TEST_F(PrinterTest, DivideExprIsVisited) {
  auto expr = std::make_unique<const DivideExpr>(
    std::make_unique<const IntegerExpr>(7),
    std::make_unique<const IntegerExpr>(5));

  expr->Visit(&printer_);

  EXPECT_EQ(printer_.GetOutput(), "(/ 7 5)");
}

TEST_F(PrinterTest, LessThanExprIsVisited) {
  auto expr = std::make_unique<const LessThanExpr>(
    std::make_unique<const DivideExpr>(
      std::make_unique<const IntegerExpr>(3),
      std::make_unique<const IntegerExpr>(19)),
    std::make_unique<const MultiplyExpr>(
      std::make_unique<const IntegerExpr>(27),
      std::make_unique<const IntegerExpr>(5)));

    expr->Visit(&printer_);

    EXPECT_EQ(printer_.GetOutput(), "(< (/ 3 19) (* 27 5))");
}

TEST_F(PrinterTest, LessThanEqualToExprIsVisited) {
  auto expr = std::make_unique<const LessThanEqualToExpr>(
  std::make_unique<const AddExpr>(
    std::make_unique<const IntegerExpr>(123),
    std::make_unique<const IntegerExpr>(42)),
  std::make_unique<const VariableExpr>("var_123"));

  expr->Visit(&printer_);

  EXPECT_EQ(printer_.GetOutput(), "(<= (+ 123 42) var_123)");
}

TEST_F(PrinterTest, GreaterThanExprIsVisited) {
  auto expr = std::make_unique<const GreaterThanExpr>(
    std::make_unique<const SubtractExpr>(
      std::make_unique<const IntegerExpr>(44),
      std::make_unique<const IntegerExpr>(12)),
    std::make_unique<const IntegerExpr>(7));

  expr->Visit(&printer_);

  EXPECT_EQ(printer_.GetOutput(), "(> (- 44 12) 7)");
}

TEST_F(PrinterTest, GreaterThanEqualToExprIsVisited) {
  auto expr = std::make_unique<const GreaterThanEqualToExpr>(
    std::make_unique<const IntegerExpr>(3),
    std::make_unique<const MultiplyExpr>(
      std::make_unique<const IntegerExpr>(27),
      std::make_unique<const IntegerExpr>(5)));

  expr->Visit(&printer_);

  EXPECT_EQ(printer_.GetOutput(), "(>= 3 (* 27 5))");
}

TEST_F(PrinterTest, EqualToExprIsVisited) {
  auto expr = std::make_unique<const EqualToExpr>(
    std::make_unique<const VariableExpr>("var_123"),
    std::make_unique<const SubtractExpr>(
      std::make_unique<const IntegerExpr>(27),
      std::make_unique<const IntegerExpr>(5)));

  expr->Visit(&printer_);

  EXPECT_EQ(printer_GetOutput(), "(= var_123 (- 27 5))");
}

TEST_F(PrinterTest, LogicalAndExprIsVisited) {
  auto expr = std::make_unique<const LogicalAndExpr>(
    std::make_unique<const EqualToExpr>(
      std::make_unique<const VariableExpr>("var_123"),
      std::make_unique<const SubtractExpr>(
        std::make_unique<const IntegerExpr>(27),
        std::make_unique<const IntegerExpr>(5))),
    std::make_unique<const GreaterThanEqualToExpr>(
      std::make_unique<const IntegerExpr>(3),
      std::make_unique<const MultiplyExpr>(
        std::make_unique<const IntegerExpr>(27),
        std::make_unique<const IntegerExpr>(5))));

  expr->Visit(&printer_);

  EXPECT_EQ(printer_GetOutput(), "(&& (= var_123 (- 27 5)) (>= 3 (* 27 5)))");
}

TEST_F(PrinterTest, LogicalOrExprIsVisited) {
  auto expr = std::make_unique<const LogicalOrExpr>(
    std::make_unique<const VariableExpr>("var_123"),
    std::make_unique<const GreaterThanEqualToExpr>(
      std::make_unique<const IntegerExpr>(3),
      std::make_unique<const MultiplyExpr>(
        std::make_unique<const IntegerExpr>(27),
        std::make_unique<const IntegerExpr>(5))));

  expr->Visit(&printer_);

  EXPECT_EQ(printer_GetOutput(), "(|| var_123 (>= 3 (* 27 5)))");
}

TEST_F(PrinterTest, LogicalNotExprIsVisited) {
  auto expr = std::make_unique<const LogicalNotExpr>(
    std::make_unique<const GreaterThanEqualToExpr>(
      std::make_unique<const IntegerExpr>(11),
      std::make_unique<const DivideExpr>(
        std::make_unique<const IntegerExpr>(90),
        std::make_unique<const IntegerExpr>(9))));

  expr->Visit(&printer_);

  EXPECT_EQ(printer_GetOutput(), "!(>= 11 (/ 90 9))");

}

TEST_F(PrinterTest, AssignmentFromArithExpIsVisited) {

}

TEST_F(PrinterTest, AssignmentFromNewTupleIsVisited) {

}

// TEST_F(PrinterTest, ProgramIsVisited) {
//   auto a = std::make_unique<const ast::AssignmentFromArithExp>(
//       std::make_unique<const VariableExpr>("var7"),
//       std::make_unique<const IntegerExpr>(7));
//     auto b = std::make_unique<const ast::AssignmentFromArithExp>(
//           std::make_unique<const VariableExpr>("var21"),
//           std::make_unique<const IntegerExpr>(21));
//
//   std::vector<std::unique_ptr<const ast::Assignment>> assignments;
//   assignments.push_back(std::move(a));
//   assignments.push_back(std::move(b));
//
//   auto arith_expr = std::make_unique<const AddExpr>(
//     std::make_unique<const IntegerExpr>(12),
//     std::make_unique<const IntegerExpr>(4));
//
//   auto program = std::make_unique<const Program>
//   (std::move(assignments), std::move(arith_expr));
//
//   program->Visit(&printer_);
//
//   EXPECT_EQ(printer_.GetOutput(), "var7 := 7var21 := 21(+ 12 4)");
// }

TEST_F(PrinterTest, NestedVisitationsWorkProperly) {
  auto expr = std::make_unique<const DivideExpr>(
      std::make_unique<const AddExpr>(std::make_unique<const IntegerExpr>(7),
                                 std::make_unique<const IntegerExpr>(5)),
      std::make_unique<const SubtractExpr>
      (std::make_unique<const IntegerExpr>(2),
                                      std::make_unique<const IntegerExpr>(1)));

  expr->Visit(&printer_);

  EXPECT_EQ(printer_.GetOutput(), "(/ (+ 7 5) (- 2 1))");
}
