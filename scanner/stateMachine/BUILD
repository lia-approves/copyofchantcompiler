cc_library(
  name = "scanner",
  copts = ["-Wall -g"],
  srcs = ["state.cc", "dfa.cc", "AcceptingState.cc"],
  hdrs = ["dfa.h", "state.h", "AcceptingState.h"],
  visibility = ["//public:__pkg__"],
)

cc_test(
  name = "scanner_test",
  deps = ["@gtest//:main", ":scanner"],
  srcs = [
    "state.cc"
  ],
  timeout = "short",
  size = "small",
)
