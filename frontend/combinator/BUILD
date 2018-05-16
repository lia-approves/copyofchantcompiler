cc_library(
  name = "combinator",
  copts = ["-Wall -g"],
  srcs = ["parser.cc"],
  hdrs = ["result.h", "parser.h", "state.h"],
  deps = ["//frontend/v1/scanner/token", "//utility", "//abstract_syntax"],
  visibility = ["//visibility:public"],
)

cc_test(
  name = "combinator_test",
  copts = ["-Iexternal/gtest/googletest-release-1.8.0/googletest/include"],
  deps = ["@gtest//:main", ":combinator", "//abstract_syntax:print_visitor_v1"],
  srcs = ["combinator_test.cc"],
  timeout = "short",
  size = "small",
)
