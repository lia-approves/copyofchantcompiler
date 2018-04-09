
cc_library(
	name = "rcc",
	copts = ["-Wall -g"],
	srcs = ["rcc.cc"],
	hdrs = ["rcc.h"],
	visibility = ["//public:__pkg__"],
)

cc_test(
	name = "rcc_test",
	deps = ["@gtest//:main", ":rcc"],
	copts = ["-Iexternal/gtest/googletest-release-1.8.0/googletest/include"],
	srcs = ["rcc_test.cc"],
	timeout = "short",
	size = "small",
)
