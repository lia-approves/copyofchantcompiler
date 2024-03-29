// Copyright (c) 2018, Team-Chant
#include <vector>
#include <unordered_map>
#include "gtest/gtest.h"
#include "frontend/combinator/parser.h"
#include "abstract_syntax/print_visitor_v1.h"

namespace cs160 {
namespace frontend {
namespace Parse {

using std::string;
using abstract_syntax::version_1::IntegerExpr;
using abstract_syntax::version_1::AstNode;
using abstract_syntax::version_1::SubtractExpr;

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

TEST(StateTest, EqualityOperator) {
  State s1("hi");
  State s2("hi");
  ASSERT_TRUE(s1 == s2);
  s1.advance();
  ASSERT_FALSE(s1 == s2);
  s2.advance();
  ASSERT_TRUE(s1 == s2);
}

TEST(StateTest, Hash) {
  std::unordered_map<State, int> map;
  State s1("hi");
  State s2("there");
  map[s1] = 1;
  map[s2] = 2;
  ASSERT_EQ(map[s1], 1);
  ASSERT_EQ(map[s2], 2);
}

TEST(CombinatorTest, ParseLiteral) {
  State s("hi");
  auto parseH = Literal('h');
  auto parseI = Literal('i');
  auto resultI = parseI(s);  // this should fail, and rewind the state
  auto resultH = parseH(s);
  ASSERT_EQ(resultH.success(), true);
  ASSERT_EQ(resultI.success(), false);
  ASSERT_EQ(resultH.value().GetString(), "h");
  auto successfulResultI = parseI(resultH.state());
  ASSERT_EQ(successfulResultI.success(), true);
  ASSERT_EQ(successfulResultI.value().GetString(), "i");
}

TEST(CombinatorTest, ParseRange) {
  State s("hi");
  auto parseAZ = Range("az");
  auto resultAZ = parseAZ(s);
  auto resultAZ2 = parseAZ(resultAZ.state());

  ASSERT_EQ(resultAZ.success(), true);
  ASSERT_EQ(resultAZ.value().GetString(), "h");
  ASSERT_EQ(resultAZ2.success(), true);
  ASSERT_EQ(resultAZ2.value().GetString(), "i");
}

TEST(CombinatorTest, ParseRange2) {
  State s("hi");
  auto parseAG = Range("ag");
  auto resultAG = parseAG(s);

  ASSERT_EQ(resultAG.success(), false);
}

TEST(CombinatorTest, ParseRange3) {
  State s("hi");
  auto parseZA = Range("za");
  auto resultZA = parseZA(s);

  ASSERT_EQ(resultZA.success(), false);
}

TEST(CombinatorTest, ParseRange4) {
  State s("hi");
  auto parseAH = Range("ah");
  auto resultAH = parseAH(s);
  auto resultAH2 = parseAH(resultAH.state());

  ASSERT_EQ(resultAH.success(), true);
  ASSERT_EQ(resultAH.value().GetString(), "h");
  ASSERT_EQ(resultAH2.success(), false);
}

TEST(CombinatorTest, ParseOr) {
  State s("h");
  auto parser = Or(Literal('a'), Literal('h'));
  auto successResult = parser(s);
  ASSERT_EQ(successResult.success(), true);
  ASSERT_EQ(successResult.value().GetString(), "h");

  auto failResult = parser(successResult.state());
  ASSERT_EQ(failResult.success(), false);
}

TEST(CombinatorTest, ParseOrMult) {
  State s("d");
  std::vector<Parser> vec1;
  auto parser1 = Literal('e');
  auto parser2 = Literal('f');
  auto parser3 = Literal('g');
  auto parser4 = Literal('d');
  vec1.push_back(parser1);
  vec1.push_back(parser2);
  vec1.push_back(parser3);
  vec1.push_back(parser4);
  auto parser = Or(vec1);
  auto successResult = parser(s);
  ASSERT_EQ(successResult.success(), true);
  ASSERT_EQ(successResult.value().GetString(), "d");

  State s2("a");
  auto parserFail = Or(vec1);
  auto failResult = parserFail(s2);
  ASSERT_EQ(failResult.success(), false);
}

TEST(CombinatorTest, ParseAnd) {
  State s("hi");
  auto failParse = And(Literal('h'), Literal('a'));
  auto parse = And(Literal('h'), Literal('i'));
  auto fail = failParse(s);
  auto result = parse(s);
  ASSERT_EQ(fail.success(), false);
  ASSERT_EQ(result.success(), true);
  auto v = result.value();
  ASSERT_EQ(v.GetString(), "hi");
}


TEST(CombinatorTest, ParseAndMult) {
  State s1("hi");
  auto parser1 = Literal('h');
  auto parser2 = Literal('i');
  std::vector<Parser> p_vec;
  p_vec.push_back(parser1);
  p_vec.push_back(parser2);
  auto parse = And(p_vec);
  auto result = parse(s1);
  ASSERT_EQ(result.success(), true);
  auto v = result.value();
  ASSERT_EQ(v.GetString(), "hi");

  State s2("hello");
  auto parser3 = Literal('e');
  auto parser4 = Literal('l');
  auto parser5 = Literal('o');
  std::vector<Parser> p_vec2;
  p_vec2.push_back(parser1);
  p_vec2.push_back(parser3);
  p_vec2.push_back(parser4);
  p_vec2.push_back(parser4);
  p_vec2.push_back(parser5);
  auto parse2 =  And(p_vec2);
  auto result2 = parse2(s2);
  ASSERT_EQ(result2.success(), true);
  auto v2 = result2.value();
  ASSERT_EQ(v2.GetString(), "hello");
}

TEST(CombinatorTest, AndVecFail) {
  State s("heo");
  auto parser1 = Literal('h');
  auto parser2 = Literal('e');
  auto parser3 = Literal('y');
  std::vector<Parser> p_vec;
  p_vec.push_back(parser1);
  p_vec.push_back(parser2);
  p_vec.push_back(parser3);
  auto parseFail = And(p_vec);
  auto result = parseFail(s);
  ASSERT_EQ(result.success(), false);
}

TEST(CombinatorTest, NotTest) {
  State s("a");
  auto successParse = Not(Literal('b'));
  auto failParse = Not(Literal('a'));
  auto fail = failParse(s);
  auto success = successParse(s);
  ASSERT_EQ(fail.success(), false);
  ASSERT_EQ(success.success(), true);
  ASSERT_EQ(success.value().GetString(), "a");
}


TEST(CombinatorTest, ExactMatchTest) {
  // test without spaces
  State s1("hey");
  auto parse1 = ExactMatch("hey");
  auto success1 = parse1(s1);
  ASSERT_EQ(success1.success(), true);
  auto val = success1.value().GetString();
  ASSERT_EQ(val, "hey");

  // test with spaces
  State s2("hello world");
  auto parse2 = ExactMatch("hello world");
  auto success2 = parse2(s2);
  ASSERT_EQ(success2.success(), true);
  auto val2 = success2.value().GetString();
  ASSERT_EQ(val2, "hello world");

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
  ASSERT_EQ(success1.value().GetString(), "helloworld");

  State s2("hi");
  auto parse2 = Match("hi");
  auto success2 = parse2(s2);
  ASSERT_EQ(success2.success(), true);
  ASSERT_EQ(success2.value().GetString(), "hi");

  State s3("hey   ");
  auto parse3 = Match("hey");
  auto success3 = parse3(s3);
  ASSERT_EQ(success3.success(), true);
  ASSERT_EQ(success3.value().GetString(), "hey");

  State s4("  he");
  auto parse4 = Match(" he ");
  auto success4 = parse4(s4);
  ASSERT_EQ(success4.success(), true);
  ASSERT_EQ(success4.value().GetString(), " he ");

  State s5("test");
  auto parse5 = Match("lol");
  auto fail1 = parse5(s5);
  ASSERT_EQ(fail1.success(), false);
}

TEST(CombinatorTest, BetweenTest) {
  State s1("(h)");
  auto parse = Between(Literal('('), Literal('h'), Literal(')'));
  auto success = parse(s1);
  ASSERT_EQ(success.success(), true);
  ASSERT_EQ(success.value().GetString(), "h");

  State s2("heh");
  auto parseFail = Between(Literal('h'), Literal('a'), Literal('h'));
  auto fail = parseFail(s2);
  ASSERT_EQ(fail.success(), false);
}

// // // TEST(CombinatorTest, Apply) {
// // //   State s("1112");
// // //   std::function<int(std::string)> toInt = [](std::string in) {
// // //     return std::stoi(in);
// // //   };
// // //   auto parseInt = Apply<std::string, int>(Literal('1'), toInt);
// // //   auto result = parseInt(s);
// // //   ASSERT_EQ(result.value(), 1);
// // // }

TEST(CombinatorTest, CaptureIntNode) {
  State s("1");
  auto parseIntNode = Int();
  auto result = parseIntNode(s);
  auto v = result.value();
  ASSERT_EQ(v.GetType(), Value::node);
  abstract_syntax::version_1::PrintVisitor printer_;
  // These lines only work if you change ::version_1:: namespace to ::frontend::
  // Because the library expects a ::frontend::PrintVisitor
  // v.Visit(&printer_);
  // ASSERT_EQ(printer_.GetOutput(), "1");
}

TEST(CombinatorTest, CacheTest) {
  State s("a");
  auto parse = Literal('b');
  auto res1 = parse(s);
  auto res2 = parse(s);
}

TEST(CombinatorTest, Star) {
  State s("1112");
  auto parseOnes = Star(Literal('1'), ConcatVector);
  auto parseZeroes = Star(Literal('0'), ConcatVector);
  auto zr = parseZeroes(s);
  auto result = parseOnes(s);
  ASSERT_EQ(result.success(), true);
  ASSERT_EQ(zr.success(), true);
  auto val = result.value();
  ASSERT_EQ(val.GetString(), "111");
}

TEST(CombinatorTest, OnePlus) {
  State s("1112");
  auto parseOnes = OnePlus(Literal('1'), ConcatVector);
  auto parseZeroes = OnePlus(Literal('0'), ConcatVector);
  auto result = parseOnes(s);
  auto zr = parseZeroes(s);
  ASSERT_EQ(result.success(), true);  // multiple matches is OK
  ASSERT_EQ(zr.success(), false);  // no matches is not allowed, unlike Star
  auto val = result.value();
  ASSERT_EQ(val.GetString(), "111");
}



TEST(CombinatorTest, SequenceTest) {
  State s("hey");
  Converter<std::vector<Value>> concat = [](std::vector<Value> values) {
    std::string s;
    for (auto it = values.begin(); it != values.end(); ++it) {
      s += it->GetString();
    }
    return Value(s);
  };
  auto parse = Sequence(Literal('h'), Literal('e'), Literal('y'), concat);
  auto success = parse(s);
  std::string r = success.value().GetString();
  ASSERT_EQ(success.success(), true);
  ASSERT_EQ(r, "hey");

  auto parseFail = Sequence(Literal('l'), Literal('o'), Literal('l'), concat);
  auto fail = parseFail(s);
  ASSERT_EQ(fail.success(), false);
}

TEST(CombinatorTest, DebugTest) {
  State s("1");
  auto parse = Debug(Int(), "hi");
  auto res = parse(s);
}

}  // namespace Parse
}  // namespace frontend
}  // namespace cs160
