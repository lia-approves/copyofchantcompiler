
cc_library(
	name = "rcc",
	copts = ["-Wall -g"],
	srcs = ["rcc.cc","interpreter.cc"],
	hdrs = ["rcc.h","interpreter.h"],
	visibility = ["//public:__pkg__"],
)

cc_test(
	name = "rcc_test",
	deps = ["@gtest//:main", ":rcc"],
	srcs = ["rcc_test.cc"],
	timeout = "short", 
	size = "small",
)

cc_test(
	name = "interpreter_test",
	deps = ["@gtest//:main", ":rcc"],
	srcs = ["interpreter_test.cc"],
	timeout = "short", 
	size = "small",
)
