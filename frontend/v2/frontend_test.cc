// Copyright (c) 2018, Team-Chant

#include <string>
#include "gtest/gtest.h"
#include "frontend/v2/frontend.h"
#include "abstract_syntax/print_visitor_v2.h"

namespace cs160 {
namespace frontend {
namespace Parse {

class FrontendTest : public ::testing::Test {
 protected:
  bool test = false;
  abstract_syntax::frontend::PrintVisitor printer_;
};

TEST_F(FrontendTest, BasicTest) {
  // make a basic expression and parse
  Frontend f;
  auto ret = f.stringToAst("a");
  // ret->Visit(&printer_);
  // ASSERT_EQ(printer_.GetOutput(), "1");
}

TEST_F(FrontendTest, BasicAdditionTest) {
  // make a basic expression and parse
  Frontend f;
  auto ret = f.stringToAst("1+2");
  ret->Visit(&printer_);
  ASSERT_EQ(printer_.GetOutput(), "(+ 1 2)");
}

// TEST_F(FrontendTest, BasicParenthesisTest) {
//   Frontend f;
//   auto ret = f.stringToAst("(1+2)");
//   ret->Visit(&printer_);
//   ASSERT_EQ(printer_.GetOutput(), "(+ 1 2)");
// }

}  // namespace Parse
}  // namespace frontend
}  // namespace cs160
