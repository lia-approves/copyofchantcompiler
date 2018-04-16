#include "gtest/gtest.h"
#include "scanner/stateMachine/state.h"

using namespace cs160::scanner;

TEST(StateTests, DefaultState) {
  State s;
  ASSERT_EQ(s.getId(), -1);
}
