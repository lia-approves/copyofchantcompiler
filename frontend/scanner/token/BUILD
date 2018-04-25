
cc_library(
  name = "token",
  copts = ["-Wall -g"],
  srcs = ["Token.cc", "IntegerToken.cc", "ArithmeticExpressionToken.cc", "OpenParenthesisToken.cc", "ClosedParenthesisToken.cc", "InvalidToken.cc"],
  hdrs = ["Token.h", "IntegerToken.h", "ArithmeticExpressionToken.h", "OpenParenthesisToken.h", "ClosedParenthesisToken.h", "InvalidToken.h"],
  visibility = ["//visibility:public"],
)

cc_test(
  name = "token_test",
  copts = ["-Iexternal/gtest/googletest-release-1.8.0/googletest/include"],
  deps = ["@gtest//:main", ":token"],
  srcs = ["Token_test.cc"],
  timeout = "short",
  size = "small",
)
