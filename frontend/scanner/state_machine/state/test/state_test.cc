/*
MIT License

Copyright (c) 2018, Team-Chant

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include "gtest/gtest.h"
#include "scanner/state_machine/state/state.h"

namespace cs160 {
namespace frontend {

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

}  // namespace frontend
}  // namespace cs160
