
cc_library(
  name = "token",
  copts = ["-Wall -g"],
  srcs = ["Token.cc", "IntegerToken.cc", "ArithmeticExpressionToken.cc", "OpenParenthesisToken.cc", "ClosedParenthesisToken.cc", "InvalidToken.cc"],
  hdrs = ["Token.h", "IntegerToken.h", "ArithmeticExpressionToken.h", "OpenParenthesisToken.h", "ClosedParenthesisToken.h", "InvalidToken.h"],
  visibility = ["//visibility:public"],
)

cc_test(
  name = "scanner_test",
  deps = ["@gtest//:main", ":scanner"],
  srcs = [
    "state.cc"
  ],
  timeout = "short",
  size = "small",
)
