#include "gtest/gtest.h"
#include "frontend/combinator/parser.h"

namespace cs160 {
namespace frontend {

TEST(CombinatorTest, InstantiateResult) {
  Result<int> fail(false, "sample error");
  State stub("stub");
  Result<int> success(1, stub);
  ASSERT_EQ(success.value(), 1);
  ASSERT_THROW(fail.value(), std::logic_error);
  ASSERT_THROW(new Result<int>(true, "hi"), std::logic_error);
}

TEST(CombinatorTest, InstantiateState) {
  State s("hi");
}

TEST(CombinatorTest, ParseLiteral) {
  State s("hi");
  auto parseH = literal('h');
  auto parseI = literal('i');
  auto resultH = parseH(s);
  auto resultI = parseI(s);
  ASSERT_EQ(resultH.success(), true);
  ASSERT_EQ(resultI.success(), false);
  ASSERT_EQ(resultH.value(), 'h');
}

}  // namespace frontend
}  // namespace cs160

