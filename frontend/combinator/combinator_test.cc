// Copyright (c) 2018, Team-Chant
#include "gtest/gtest.h"
#include "frontend/combinator/parser.h"
#include "abstract_syntax/print_visitor_v1.h"

namespace cs160 {
namespace frontend {

using std::string;
using abstract_syntax::frontend::IntegerExpr;
using abstract_syntax::frontend::AstNode;

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

// TEST(CombinatorTest, ParseRange) {
//   State s("hi");
//   auto parseAZ = Range("az");
//   auto resultAZ = parseAZ(s);
//   auto resultAZ2 = parseAZ(s);
//
//   auto parseAG = Range("ag");
//   auto resultAG = parseAG(s);
//
//   auto parseZA = Range("za");
//   auto resultZA = parseZA(s);
//
//   auto parseAH = Range("ah");
//   auto resultAH = parseAH(s);
//   auto resultAH2 = parseAH(s);
//
//   ASSERT_EQ(resultAZ.success(), true);
//   ASSERT_EQ(resultAZ.value()[0], 'h');
//   ASSERT_EQ(resultAZ2.success(), true);
//   ASSERT_EQ(resultAZ2.value()[1], 'i');
//
//   ASSERT_EQ(resultAG.success(), false);
//   ASSERT_EQ(resultZA.success(), false);
//
//   ASSERT_EQ(resultAH.success(), true);
//   ASSERT_EQ(resultAH.value()[0], 'h');
//   ASSERT_EQ(resultAH2.success(), false);
// }

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
  auto val = result.value();
  ASSERT_EQ(val[0], "h");
  ASSERT_EQ(val[1], "i");
}

TEST(CombinatorTest, NotTest) {
  State s("a");
  auto successParse = Not(Literal('b'));
  auto failParse = Not(Literal('a'));
  auto fail = failParse(s);
  auto success = successParse(s);
  ASSERT_EQ(fail.success(), false);
  ASSERT_EQ(success.success(), true);
  ASSERT_EQ(success.value()[0], '!');
}

TEST(CombinatorTest, ExactMatchTest) {
  // test without spaces
  State s1("hey");
  auto parse1 = ExactMatch("hey");
  auto success1 = parse1(s1);
  ASSERT_EQ(success1.success(), true);
  auto val = success1.value();
  ASSERT_EQ(val[0], 'h');
  ASSERT_EQ(val[1], 'e');
  ASSERT_EQ(val[2], 'y');

  // test with spaces
  State s2("hello world");
  auto parse2 = ExactMatch("hello world");
  auto success2 = parse2(s2);
  ASSERT_EQ(success2.success(), true);
  auto val2 = success2.value();
  ASSERT_EQ(val2[0], 'h');
  ASSERT_EQ(val2[1], 'e');
  ASSERT_EQ(val2[2], 'l');
  ASSERT_EQ(val2[3], 'l');
  ASSERT_EQ(val2[4], 'o');
  ASSERT_EQ(val2[5], ' ');
  ASSERT_EQ(val2[6], 'w');
  ASSERT_EQ(val2[7], 'o');
  ASSERT_EQ(val2[8], 'r');
  ASSERT_EQ(val2[9], 'l');
  ASSERT_EQ(val2[10], 'd');

  State s3("nope");
  auto parseFail = ExactMatch("yes!");
  auto fail = parseFail(s3);
  ASSERT_EQ(fail.success(), false);
}

TEST(CombinatorTest, MatchTest) {
  State s1("hello world");
  auto parse1 = Match("helloworld");
  auto success1 = parse1(s1);
  ASSERT_EQ(success1.success(), true);

  State s2("hi");
  auto parse2 = Match("hi");
  auto success2 = parse2(s2);
  ASSERT_EQ(success2.success(), true);

  State s3("hey   ");
  auto parse3 = Match("hey");
  auto success3 = parse3(s3);
  ASSERT_EQ(success3.success(), true);

  State s4("  he");
  auto parse4 = Match(" he ");
  auto success4 = parse4(s4);
  ASSERT_EQ(success4.success(), true);
}

TEST(CombinatorTest, BetweenTest) {
  State s1("(h)");
  auto parse = Between(Literal('('), Literal('h'), Literal(')'));
  auto success = parse(s1);
  ASSERT_EQ(success.success(), true);
  ASSERT_EQ(success.value()[0], 'h');

  State s2("heh");
  auto parseFail = Between(Literal('h'), Literal('a'), Literal('h'));
  auto fail = parseFail(s2);
  ASSERT_EQ(fail.success(), false);
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

TEST(CombinatorTest, CaptureIntNode) {
  State s("1");
  auto parseIntNode = Capture<string>(Literal('1'), [](string s) {
    return std::unique_ptr<AstNode>(new IntegerExpr(std::stoi(s)));
  });
  auto result = parseIntNode(s);
  abstract_syntax::frontend::PrintVisitor printer_;
  result.value()->Visit(&printer_);
  ASSERT_EQ(printer_.GetOutput(), "1");
}

TEST(CombinatorTest, Star) {
  State s("1112");
  auto parseOnes = Star<std::string>(Literal('1'));
  auto parseZeroes = Star<std::string>(Literal('0'));
  auto zr = parseZeroes(s);
  auto result = parseOnes(s);
  ASSERT_EQ(result.success(), true);
  ASSERT_EQ(zr.success(), true);
  auto val = result.value();
  ASSERT_EQ(val.size(), 3);
  ASSERT_EQ(val[0], val[1]);
  ASSERT_EQ(val[2], val[1]);
  ASSERT_EQ(val[0], "1");
}

}  // namespace frontend
}  // namespace cs160
