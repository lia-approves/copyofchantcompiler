cc_library(
  name = "state_machine",
  copts = ["-Wall -g"],
  srcs = ["state/state.cc", "dfa/dfa.cc"],
  hdrs = ["dfa/dfa.h", "state/state.h"],
  deps = ["//frontend/v1/scanner/token"],
  visibility = ["//visibility:public"],
)

cc_test(
  name = "state_machine_test",
  copts = ["-Iexternal/gtest/googletest-release-1.8.0/googletest/include"],
  deps = ["@gtest//:main", ":state_machine"],
  srcs = ["test/state_test.cc"],
  timeout = "short",
  size = "small",
)

cc_test(
  name = "dfa_test",
  copts = ["-Iexternal/gtest/googletest-release-1.8.0/googletest/include"],
  deps = ["@gtest//:main", ":state_machine"],
  srcs = ["dfa/Dfa_test.cc"],
  timeout = "short",
  size = "small",
)
