cc_library(
  name = "frontend",
  copts = ["-Wall -g"],
  srcs = ["frontend.cc"],
  hdrs = ["frontend.h"],
  deps = ["//frontend/combinator:combinator", "//abstract_syntax", "//utility", "//abstract_syntax:print_visitor_v5"],
  visibility = ["//visibility:public"],
)


cc_test(
  name = "frontend_test",
  copts = ["-Iexternal/gtest/googletest-release-1.8.0/googletest/include"],
  deps = ["@gtest//:main", ":frontend"],
  srcs = ["frontend_test.cc"],
  timeout = "short",
  size = "small",
)
