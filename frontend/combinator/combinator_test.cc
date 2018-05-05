#include "gtest/gtest.h"
#include "frontend/combinator/result.h"

namespace cs160 {
namespace frontend {

TEST(CombinatorTest, InstantiateResult) {
  Result<int> r("sample error");
}

}  // namespace frontend
}  // namespace cs160

