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

using cs160::make_unique;

class PrinterTest : public ::testing::Test {
 protected:
  PrintVisitor printer_;
};

TEST_F(PrinterTest, IntegerExprIsVisited) {
  auto number = make_unique<const IntegerExpr>(7);
  number->Visit(&printer_);

  EXPECT_EQ(printer_.GetOutput(), "7");
}

TEST_F(PrinterTest, VariableExprIsVisited) {
  auto variable = make_unique<const VariableExpr>("var");
  variable->Visit(&printer_);

  EXPECT_EQ(printer_.GetOutput(), "var");
}

TEST_F(PrinterTest, AddExprIsVisited) {
  auto expr = make_unique<const AddExpr>((make_unique<const IntegerExpr>(7)),
                                         make_unique<const IntegerExpr>(5));
  expr->Visit(&printer_);

  EXPECT_EQ(printer_.GetOutput(), "(+ 7 5)");
}

TEST_F(PrinterTest, SubtractExprIsVisited) {
  auto expr = make_unique<const SubtractExpr>(
      make_unique<const IntegerExpr>(7), make_unique<const IntegerExpr>(5));

  expr->Visit(&printer_);

  EXPECT_EQ(printer_.GetOutput(), "(- 7 5)");
}

TEST_F(PrinterTest, MultiplyExprIsVisited) {
  auto expr = make_unique<const MultiplyExpr>(
      make_unique<const IntegerExpr>(7), make_unique<const IntegerExpr>(5));

  expr->Visit(&printer_);

  EXPECT_EQ(printer_.GetOutput(), "(* 7 5)");
}

TEST_F(PrinterTest, DivideExprIsVisited) {
  auto expr = make_unique<const DivideExpr>(make_unique<const IntegerExpr>(7),
                                            make_unique<const IntegerExpr>(5));

  expr->Visit(&printer_);

  EXPECT_EQ(printer_.GetOutput(), "(/ 7 5)");
}

TEST_F(PrinterTest, AssignmentIsVisited) {
  auto expr = make_unique<const Assignment>(make_unique<const VariableExpr>("var"),
                                              make_unique<const IntegerExpr>(7));
  expr->Visit(&printer_);

  EXPECT_EQ(printer_.GetOutput(), "var := 7");
}

TEST_F(PrinterTest, ProgramIsVisited) {
  std::vector<std::unique_ptr<const Assignment>> assignments {make_unique<const Assignment>(make_unique<const VariableExpr>("var7"),
                                                                                            make_unique<const IntegerExpr>(7)),
                                                              make_unique<const Assignment>(make_unique<const VariableExpr>("var21"),
                                                                                            make_unique<const IntegerExpr>(21))};
  auto arith_expr = make_unique<const AddExpr>(make_unique<const IntegerExpr>(12),
                                               make_unique<const IntegerExpr>(4));

  auto program = make_unique<const Program>(assignments, arith_expr);

  program->Visit(&printer_);

  EXPECT_EQ(printer_.GetOutput(), "var7 := 7var21 := 21(+ 12 4)");
}

TEST_F(PrinterTest, NestedVisitationsWorkProperly) {
  auto expr = make_unique<const DivideExpr>(
      make_unique<const AddExpr>(make_unique<const IntegerExpr>(7),
                                 make_unique<const IntegerExpr>(5)),
      make_unique<const SubtractExpr>(make_unique<const IntegerExpr>(2),
                                      make_unique<const IntegerExpr>(1)));

  expr->Visit(&printer_);

  EXPECT_EQ(printer_.GetOutput(), "(/ (+ 7 5) (- 2 1))");
}
