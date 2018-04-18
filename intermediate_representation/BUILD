cc_library(
	name = "intermediate_representation",
	copts = ["-Wall -g"],
	hdrs = ["intermediate_representation.h"],
	deps = ["//utility"],
	visibility = ["//visibility:public"],
)

cc_test(
	name = "intermediate_representation_test",
	srcs = ["intermediate_representation_test.cc"],
	deps = [
             "@gtest//:main",
             ":intermediate_representation"
        ],
	timeout = "short",
	size = "small",
)
