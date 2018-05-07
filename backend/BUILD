cc_library(
	name = "intermediate_representation",
	copts = ["-Wall -g"],
	hdrs = ["asm_generator_v3.h", "ir_v3.h", "lowerer_v3.h"],
	deps = [
             "//abstract_syntax",
             "//utility"
        ],
	visibility = ["//visibility:public"],
)

cc_test(
	name = "asm_generator_test",
	srcs = ["asm_generator_test.cc"],
	deps = [
             "@gtest//:main",
             ":intermediate_representation"
        ],
	timeout = "short",
	size = "small",
)


cc_test(
	name = "integration_test",
	srcs = ["integration_test.cc"],
	deps = [
             "@gtest//:main",
             ":intermediate_representation"
        ],
	timeout = "short",
	size = "small",
)
