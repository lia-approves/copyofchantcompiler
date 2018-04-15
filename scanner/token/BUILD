
cc_library(
  name = "token",
  copts = ["-Wall -g"],
  srcs = ["Token.cpp", "IntegerToken.cpp", "ArithmeticExpressionToken.cpp", "OpenParenthesisToken.cpp", "ClosedParenthesisToken.cpp"],
  hdrs = ["Token.h", "IntegerToken.h", "ArithmeticExpressionToken.h", "OpenParenthesisToken.h", "ClosedParenthesisToken.h"],
  visibility = ["//public:__pkg__"],
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