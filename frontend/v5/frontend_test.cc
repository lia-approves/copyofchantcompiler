// Copyright (c) 2018, Team-Chant

#include <string>
#include "gtest/gtest.h"
#include "frontend/v5/frontend.h"
#include "abstract_syntax/print_visitor_v5.h"

namespace cs160 {
namespace frontend {
namespace Parse {

class FrontendTest : public ::testing::Test {
 protected:
  bool test = false;
  abstract_syntax::version_5::PrintVisitor printer_;
};

TEST_F(FrontendTest, IntegerTest1) {
  // make a basic expression and parse
  auto ret = Frontend::stringToAst("1234");
  ret->Visit(&printer_);
  ASSERT_EQ(printer_.GetOutput(), "1234");
}



}  // namespace Parse
}  // namespace frontend
}  // namespace cs160
