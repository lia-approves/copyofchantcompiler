cc_library(
  name = "combinator",
  copts = ["-Wall -g"],
  srcs = [],
  hdrs = ["result.h"],
  deps = ["//frontend/v1/scanner/token", "//utility", "//abstract_syntax"],
  visibility = ["//visibility:public"],
)

cc_test(
  name = "combinator_test",
  copts = ["-Iexternal/gtest/googletest-release-1.8.0/googletest/include"],
  deps = ["@gtest//:main", ":combinator"],
  srcs = ["combinator_test.cc"],
  timeout = "short",
  size = "small",
)