#include "gtest/gtest.h"
#include "frontend/combinator/result.h"

namespace cs160 {
namespace frontend {

TEST(CombinatorTest, InstantiateResult) {
  Result<int> fail(false, "sample error");
  Result<int> success(1);
  ASSERT_EQ(success.value(), 1);
  ASSERT_THROW(fail.value(), std::logic_error);
  ASSERT_THROW(new Result<int>(true, "hi"), std::logic_error);
}

}  // namespace frontend
}  // namespace cs160

