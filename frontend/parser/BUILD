cc_library(
  name = "parser",
  copts = ["-Wall -g"],
  srcs = ["parser.cc"],
  hdrs = ["parser.h", "expression.h"],
  deps = ["//frontend/scanner/token", "//utility"],
  visibility = ["//visibility:public"],
)

cc_test(
  name = "parser_test",
  copts = ["-Iexternal/gtest/googletest-release-1.8.0/googletest/include"],
  deps = ["@gtest//:main", ":parser"],
  srcs = ["parser_test.cc"],
  timeout = "short",
  size = "small",
)
