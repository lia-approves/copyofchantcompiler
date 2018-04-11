#include "gtest/gtest.h"
#include "./interpreter.h"

TEST(InterpreterMainTest, GetInterpreterMainTest) {
  EXPECT_EQ(cs160::rcc::InterpreterMain(), 42);
}
