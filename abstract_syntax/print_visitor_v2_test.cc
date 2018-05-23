// Copyright (c) 2018, Team-Chant
#include <sstream>
#include <string>

#include "gtest/gtest.h"

#include "abstract_syntax/abstract_syntax_tree_v2.h"
#include "abstract_syntax/print_visitor_v2.h"
#include "utility/memory.h"

using cs160::abstract_syntax::version_2::IntegerExpr;
using cs160::abstract_syntax::version_2::VariableExpr;
using cs160::abstract_syntax::version_2::AddExpr;
using cs160::abstract_syntax::version_2::SubtractExpr;
using cs160::abstract_syntax::version_2::MultiplyExpr;
using cs160::abstract_syntax::version_2::DivideExpr;
using cs160::abstract_syntax::version_2::Assignment;
using cs160::abstract_syntax::version_2::Program;
using cs160::abstract_syntax::version_2::PrintVisitor;


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

TEST_F(PrinterTest, AssignmentIsVisited) {
  auto expr = std::make_unique<const Assignment>(
    std::make_unique<const VariableExpr>("var"),
    std::make_unique<const IntegerExpr>(7));
  expr->Visit(&printer_);

  EXPECT_EQ(printer_.GetOutput(), "var := 7");
}

TEST_F(PrinterTest, ProgramIsVisited) {
  // std::vector<std::unique_ptr<const Assignment>> assignments {
  //   std::make_unique<const Assignment>(
  //     std::make_unique<const VariableExpr>("var7"),
  //     std::make_unique<const IntegerExpr>(7)),
  //   std::make_unique<const Assignment>(
  //     std::make_unique<const VariableExpr>("var21"),
  //     std::make_unique<const IntegerExpr>(21))
  //     };

  auto a = std::make_unique<const Assignment>(
      std::make_unique<const VariableExpr>("var7"),
      std::make_unique<const IntegerExpr>(7));
    auto b = std::make_unique<const Assignment>(
          std::make_unique<const VariableExpr>("var21"),
          std::make_unique<const IntegerExpr>(21));

  std::vector<std::unique_ptr<const Assignment>> assignments;
  assignments.push_back(std::move(a));
  assignments.push_back(std::move(b));

  auto arith_expr = std::make_unique<const AddExpr>(
    std::make_unique<const IntegerExpr>(12),
    std::make_unique<const IntegerExpr>(4));

  auto program = std::make_unique<const Program>
  (std::move(assignments), std::move(arith_expr));

  program->Visit(&printer_);

  EXPECT_EQ(printer_.GetOutput(), "var7 := 7var21 := 21(+ 12 4)");
}

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
