#include "gtest/gtest.h"
#include "frontend/combinator/parser.h"

namespace cs160 {
namespace frontend {

// TEST(CombinatorTest, InstantiateResult) {
//   Result<int> fail(false, "sample error");
//   State stub("stub");
//   Result<int> success(1);
//   ASSERT_EQ(success.value(), 1);
//   ASSERT_THROW(fail.value(), std::logic_error);
//   ASSERT_THROW(new Result<int>(true, "hi"), std::logic_error);
// }

TEST(CombinatorTest, InstantiateState) {
  State s("hi");
}

TEST(CombinatorTest, ParseLiteral) {
  State s("hi");
  auto parseH = Literal('h');
  auto parseI = Literal('i');
  auto resultI = parseI(s);  // this should fail, and rewind the state
  auto resultH = parseH(s);
  ASSERT_EQ(resultH.success(), true);
  ASSERT_EQ(resultI.success(), false);
  ASSERT_EQ(resultH.value(), "h");
  auto successfulResultI = parseI(resultH.state());
  ASSERT_EQ(successfulResultI.success(), true);
  ASSERT_EQ(successfulResultI.value(), "i");
}

TEST(CombinatorTest, ParseRange) {
  std::shared_ptr<State> s(new State("hi"));
  auto parseAZ = Range("az");
  auto resultAZ = parseAZ(s);
  auto resultAZ2 = parseAZ(s);

  auto parseAG = Range("ag");
  auto resultAG = parseAG(s);

  auto parseZA = Range("za");
  auto resultZA = parseZA(s);

  auto parseAH = Range("ah");
  auto resultAH = parseAH(s);
  auto resultAH2 = parseAH(s);

  ASSERT_EQ(resultAZ.success(), true);
  ASSERT_EQ(resultAZ.value(), 'h');
  ASSERT_EQ(resultAZ2.success(), true);
  ASSERT_EQ(resultAZ2.value(), 'i');

  ASSERT_EQ(resultAG.success(), false);
  ASSERT_EQ(resultZA.success(), false);

  ASSERT_EQ(resultAH.success(), true);
  ASSERT_EQ(resultAH.value(), 'h');
  ASSERT_EQ(resultAH2.success(), false);
}

TEST(CombinatorTest, ParseOr) {
  State s("hi");
  auto parser = Or<std::string>(Literal('a'), Literal('h'));
  auto successResult = parser(s);
  ASSERT_EQ(successResult.success(), true);
  ASSERT_EQ(successResult.value(), "h");

  auto failResult = parser(successResult.state());
  ASSERT_EQ(failResult.success(), false);
}

TEST(CombinatorTest, ParseAnd) {
  State s("hi");
  auto failParse = And<std::string>(Literal('h'), Literal('a'));
  auto parse = And<std::string>(Literal('h'), Literal('i'));
  auto fail = failParse(s);
  auto result = parse(s);
  ASSERT_EQ(fail.success(), false);
  ASSERT_EQ(result.success(), true);
  ASSERT_EQ(result.value()[0], "h");
  ASSERT_EQ(result.value()[1], "i");
}

// // TEST(CombinatorTest, Apply) {
// //   State s("1112");
// //   std::function<int(std::string)> toInt = [](std::string in) {
// //     return std::stoi(in);
// //   };
// //   auto parseInt = Apply<std::string, int>(Literal('1'), toInt);
// //   auto result = parseInt(s);
// //   ASSERT_EQ(result.value(), 1);
// // }

TEST(CombinatorTest, Star) {
  State s("1112");
  auto parseOnes = Star<std::string>(Literal('1'));
  auto parseZeroes = Star<std::string>(Literal('0'));
  auto zr = parseZeroes(s);
  auto result = parseOnes(s);
  ASSERT_EQ(result.success(), true);
  ASSERT_EQ(zr.success(), true);
  ASSERT_EQ(result.value().size(), 3);
  ASSERT_EQ(result.value()[0], result.value()[1]);
  ASSERT_EQ(result.value()[2], result.value()[1]);
  ASSERT_EQ(result.value()[0], "1");
}

}  // namespace frontend
}  // namespace cs160
