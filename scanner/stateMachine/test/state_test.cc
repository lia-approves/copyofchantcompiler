#include "gtest/gtest.h"
#include "scanner/stateMachine/state.h"

namespace cs160 {
namespace scanner {

TEST(StateTests, DefaultState) {
  State s;
  ASSERT_EQ(s.getId(), -1);
  ASSERT_EQ(s.isAccepting(), false);
}

TEST(StateTests, CustomStateId) {
  State s(4);
  ASSERT_EQ(s.getId(), 4);
  ASSERT_EQ(s.isAccepting(), false);
}

TEST(StateTests, Transition) {
  State s(3);
  s.addTransition('a', 5);
  ASSERT_EQ(s.nextState('a'), 5);
}

TEST(StateTests, DefaultToken) {
  State s;
  Token t;
  ASSERT_EQ(s.getToken().get_token(), t.get_token());
}

} // namespace scanner
} // namespace cs160
