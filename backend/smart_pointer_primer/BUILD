cc_library(
	name = "simple_example",
	copts = ["-Wall -g"],
	hdrs = ["simple_example.h"],
        deps = ["//utility"],
	visibility = ["//public:__pkg__"],
)

cc_test(
	name = "simple_example_test",
	deps = ["@gtest//:main", "//utility", ":simple_example"],
	copts = ["-Iexternal/gtest/googletest-release-1.8.0/googletest/include"],
	srcs = ["simple_example_test.cc"],
	timeout = "short",
	size = "small",
)
