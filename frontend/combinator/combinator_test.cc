#include "gtest/gtest.h"
#include "frontend/combinator/parser.h"

namespace cs160 {
namespace frontend {

TEST(CombinatorTest, InstantiateResult) {
  Result<int> fail(false, "sample error");
  State stub("stub");
  Result<int> success(1);
  ASSERT_EQ(success.value(), 1);
  ASSERT_THROW(fail.value(), std::logic_error);
  ASSERT_THROW(new Result<int>(true, "hi"), std::logic_error);
}

TEST(CombinatorTest, InstantiateState) {
  State s("hi");
}

TEST(CombinatorTest, ParseLiteral) {
  std::shared_ptr<State> s(new State("hi"));
  auto parseH = Literal('h');
  auto parseI = Literal('i');
  auto resultI = parseI(s);  // this should fail, and rewind the state
  auto resultH = parseH(s);
  ASSERT_EQ(resultH.success(), true);
  ASSERT_EQ(resultI.success(), false);
  ASSERT_EQ(resultH.value(), "h");
  auto successfulResultI = parseI(s);
  ASSERT_EQ(successfulResultI.success(), true);
  ASSERT_EQ(successfulResultI.value(), "i");
}

TEST(CombinatorTest, ParseOr) {
  std::shared_ptr<State> s(new State("hi"));
  auto parser =
    Or<std::string>(Literal('a'), Literal('h'));
  auto successResult = parser(s);
  ASSERT_EQ(successResult.success(), true);
  ASSERT_EQ(successResult.value(), "h");

  auto failResult = parser(s);
  ASSERT_EQ(failResult.success(), false);
}

TEST(CombinatorTest, ParseAnd) {
  std::shared_ptr<State> s(new State("hi"));
  auto parser =
    And<std::string>(Literal('h'), Literal('i'));
}

}  // namespace frontend
}  // namespace cs160

