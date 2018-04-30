cc_library(
	name = "intermediate_representation",
	copts = ["-Wall -g"],
	hdrs = ["assembly_generator_v1.h", "intermediate_representation_v1.h", "ir_generator_ast_visitor_v1.h"],
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
