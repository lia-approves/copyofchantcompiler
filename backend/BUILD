cc_library(
	name = "intermediate_representation",
	copts = ["-Wall -g"],
	hdrs = ["assembly_generator_v1.h", "intermediate_representation_v1.h"],
	deps = [
             "//abstract_syntax",
             "//utility"
        ],
	visibility = ["//visibility:public"],
)

cc_test(
	name = "assembly_test",
	srcs = ["assembly_generator_test.cc"],
	deps = [
             "@gtest//:main",
             ":intermediate_representation"
        ],
	timeout = "short",
	size = "small",
)

cc_test(
	name = "assembly_test_ORIGINAL",
	srcs = ["assembly_generator_test.cc"],
	deps = [
             "@gtest//:main",
             ":intermediate_representation"
        ],
	timeout = "short",
	size = "small",
)
cc_test(
	name = "ir_generator_visitor_test",
	srcs = ["ir_generator_visitor_test.cc"],
	deps = [
             "@gtest//:main",
             ":intermediate_representation"
        ],
	timeout = "short",
	size = "small",
)
