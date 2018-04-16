#include "gtest/gtest.h"
#include "scanner/stateMachine/state.h"

namespace cs160 {
namespace scanner {

TEST(StateTests, DefaultState) {
  scanner::State s;
  ASSERT_EQ(s.getId(), -1);
}

} // namespace scanner
} // namespace cs160
