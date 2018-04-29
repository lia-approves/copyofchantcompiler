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
#include "frontend/v1/scanner/token/Token.h"
#include "frontend/v1/scanner/token/InvalidToken.h"
#include "frontend/v1/scanner/token/IntegerToken.h"
#include "frontend/v1/scanner/token/OpenParenthesisToken.h"
#include "frontend/v1/scanner/token/ClosedParenthesisToken.h"
#include "frontend/v1/scanner/token/ArithmeticExpressionToken.h"

namespace cs160 {
namespace frontend {
// Enum Tests
TEST(TokenTest, TokenBasicEnum) {
  Token t;
  ASSERT_EQ(token_, t.GetCurrType());
}

TEST(InvalidTokenTest, InvalidTokenEnum) {
  InvalidToken t;
  ASSERT_EQ(invalidToken, t.GetCurrType());
}

TEST(IntegerTokenTest, IntegerTokenEnum) {
  IntegerToken t(1);
  ASSERT_EQ(integerToken, t.GetCurrType());
}

TEST(OpenParenthesisTokenTest, OpenTokenEnum) {
  OpenParenthesisToken t;
  ASSERT_EQ(openParenthesisToken, t.GetCurrType());
}

TEST(ClosedParenthesisTest, IntegerTokenEnum) {
  ClosedParenthesisToken t;
  ASSERT_EQ(closedParenthesisToken, t.GetCurrType());
}

// Token Tests
TEST(EmptyTokenStringTest, TokenEmptyString) {
  Token t;
  ASSERT_EQ("", t.GetToken());
}

TEST(TokenStringTest, TokenString) {
  Token t("hello");
  ASSERT_EQ("hello", t.GetToken());
  t.SetTokenStr("hi");
  ASSERT_EQ("hi", t.GetToken());
}

// Invalid tests
TEST(InvalidStringTest, InvalidTokenString) {
  InvalidToken t1;
  ASSERT_EQ("Invalid Token", t1.GetToken());
  t1.SetToken("hello");
  ASSERT_EQ("Invalid Token", t1.GetToken());
  InvalidToken t2("hello");
  ASSERT_EQ("Invalid Token", t2.GetToken());
}

// Integer tests
TEST(IntgerTokenTest, IntegerTokenString) {
  IntegerToken t1("1");
  ASSERT_EQ("1", t1.GetToken());
  ASSERT_EQ(1, t1.GetTokenInt());
  IntegerToken t2(2);
  ASSERT_EQ(2, t2.GetTokenInt());
  ASSERT_EQ("2", t2.GetToken());
  // test if strings that are not numbers
  // are inputted
}

// OpenParenthesisToken tests
TEST(OpenParenthesisTest, OpenParen) {
    OpenParenthesisToken t1;
    ASSERT_EQ("(", t1.GetToken());
    t1.SetToken("hello");
    ASSERT_EQ("(", t1.GetToken());
    OpenParenthesisToken t2("hello");
    ASSERT_EQ("(", t2.GetToken());
}

// Closed Parenthesis Token Tests
TEST(ClosedParenthesisTest, ClosedParen) {
  ClosedParenthesisToken t1;
  ASSERT_EQ(")", t1.GetToken());
  t1.SetToken("hello");
  ASSERT_EQ(")", t1.GetToken());
  ClosedParenthesisToken t2("hello");
  ASSERT_EQ(")", t2.GetToken());
}

// Test that integer tokens have the correct type
TEST(TokenTypes, IntegerTokenType) {
  IntegerToken one("1");
  token_type_ integer = integerToken;
  ASSERT_EQ(one.GetCurrType(), integer);
}

TEST(TokenTypes, ArithmeticTokenTypes) {
  ArithmeticExpressionToken plus('+');
  ArithmeticExpressionToken minus('-');
  ArithmeticExpressionToken mult('*');
  ArithmeticExpressionToken divide("/");
  ASSERT_EQ(plus.GetCurrType(), plusToken);
  ASSERT_EQ(minus.GetCurrType(), minusToken);
  ASSERT_EQ(mult.GetCurrType(), multToken);
  ASSERT_EQ(divide.GetCurrType(), divideToken);
}

}  // namespace frontend
}  // namespace cs160
