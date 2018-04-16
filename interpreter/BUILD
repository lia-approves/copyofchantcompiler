cc_library(
	name = "interpreter",
	copts = ["-Wall -g"],
	hdrs = ["interpreter.h"],
  srcs = ["interpreter.cc"],
	deps = [
             "//abstract_syntax",
             "//utility"
        ],
	visibility = ["//visibility:public"],
)

cc_test(
	name = "interpreter_test",
	srcs = ["interpreter_test_old.cc"],
	deps = [
             "@gtest//:main",
             ":interpreter"
        ],
	timeout = "short",
	size = "small",
)
