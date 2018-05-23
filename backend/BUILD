cc_library(
	name = "intermediate_representation",
	copts = ["-Wall -g"],
	hdrs = ["asm_generator_v5.h", "ir_v5.h", "lowerer_v5.h"],
	srcs = ["lowerer_v5.cc"],
	deps = [
             "//abstract_syntax",
             "//utility"
        ],
	visibility = ["//visibility:public"],
)

cc_test(
	name = "arithmetic_expr",
	srcs = ["v5testsArithmeticOps.cc"],
	deps = [
             "@gtest//:main",
             ":intermediate_representation"
        ],
	timeout = "short",
	size = "small",
)

cc_test(
	name = "assignment_ops",
	srcs = ["v5testsAssignmentOps.cc"],
	deps = [
             "@gtest//:main",
             ":intermediate_representation"
        ],
	timeout = "short",
	size = "small",
)
