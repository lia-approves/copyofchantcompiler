cc_library(
  name = "stateMachine",
  copts = ["-Wall -g"],
  srcs = ["state.cc", "dfa.cc", "AcceptingState.cc"],
  hdrs = ["dfa.h", "state.h", "AcceptingState.h"],
  deps = ["//scanner/token"],
  visibility = ["//visibility:public"],
)

cc_test(
  name = "stateMachine_test",
  copts = ["-Iexternal/gtest/googletest-release-1.8.0/googletest/include"],
  deps = ["@gtest//:main", ":stateMachine"],
  srcs = ["test/state_test.cc"],
  timeout = "short",
  size = "small",
)
