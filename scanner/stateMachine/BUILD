cc_library(
  name = "stateMachine",
  copts = ["-Wall -g"],
  srcs = ["state.cc", "dfa.cc", "AcceptingState.cc"],
  hdrs = ["dfa.h", "state.h", "AcceptingState.h"],
  visibility = ["//visibility:public"],
)

cc_test(
  name = "stateMachine_test",
  deps = ["@gtest//:main", ":scanner"],
  srcs = [],
  timeout = "short",
  size = "small",
)
