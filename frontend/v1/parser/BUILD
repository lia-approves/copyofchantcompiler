cc_library(
  name = "parser",
  copts = ["-Wall -g"],
  srcs = ["parser.cc"],
  hdrs = ["parser.h"],
  deps = ["//frontend/v1/scanner/token", "//utility", "//abstract_syntax"],
  visibility = ["//visibility:public"],
)

cc_test(
  name = "parser_test",
  copts = ["-Iexternal/gtest/googletest-release-1.8.0/googletest/include"],
  deps = ["@gtest//:main", ":parser", "//abstract_syntax:print_visitor_v1"],
  srcs = ["parser_test.cc"],
  timeout = "short",
  size = "small",
)
