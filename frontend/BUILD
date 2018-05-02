cc_library(
  name = "frontend",
  copts = ["-Wall -g"],
  srcs = ["frontend.cc"],
  hdrs = ["frontend.h"],
  deps = ["//frontend/v1/scanner/token", "//frontend/v1/scanner/state_machine",
  "//frontend/v1/parser", "//abstract_syntax", "//utility"],
  visibility = ["//visibility:public"],
)


cc_test(
  name = "frontend_test",
  copts = ["-Iexternal/gtest/googletest-release-1.8.0/googletest/include"],
  deps = ["@gtest//:main", ":frontend", "//abstract_syntax:print_visitor_v1"],
  srcs = ["frontend_test.cc"],
  timeout = "short",
  size = "small",
)
