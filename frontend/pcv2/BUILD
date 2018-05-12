cc_library(
  name = "combinator",
  copts = ["-Wall -g"],
  srcs = [],
  hdrs = ["parser.h"],
  deps = ["//utility"],
  visibility = ["//visibility:public"],
)

cc_test(
  name = "combinator_test",
  copts = ["-Iexternal/gtest/googletest-release-1.8.0/googletest/include", "-std=c++17"],
  deps = ["@gtest//:main", ":combinator", "//abstract_syntax", "//abstract_syntax:print_visitor_v1"],
  srcs = ["combinator_test.cc"],
  timeout = "short",
  size = "small",
)
