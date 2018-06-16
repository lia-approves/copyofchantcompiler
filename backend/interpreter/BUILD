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
	srcs = ["interpreter_test.cc"],
	deps = [
             "@gtest//:main",
             ":interpreter"
        ],
	timeout = "short",
	size = "small",
)

cc_test(
	name = "interpreter_test_randomAst",
	srcs = ["interpreter_test_randomAst.cc"],
	deps = [
             "@gtest//:main",
             ":interpreter"
        ],
	timeout = "short",
	size = "small",
)
