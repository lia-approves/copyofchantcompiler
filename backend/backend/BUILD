cc_library(
	name = "intermediate_representation",
	copts = ["-Wall -g"],
	hdrs = ["asm_generator_v5.h", "ir_v5.h", "lowerer_v5.h", "SSA.h"],
	srcs = ["lowerer_v5.cc", "SSA.cc"],
	deps = [
             "//abstract_syntax",
             "//utility"
        ],
	visibility = ["//visibility:public"],
)

cc_test(
	name = "v5_loop",
	srcs = ["tests_v5/loop.cc"],
	deps = [
             "@gtest//:main",
             ":intermediate_representation"
        ],
	timeout = "short",
	size = "small",
)

cc_test(
	name = "v5_arithmetic",
	srcs = ["tests_v5/arithmetic.cc"],
	deps = [
             "@gtest//:main",
             ":intermediate_representation"
        ],
	timeout = "short",
	size = "small",
)

cc_test(
	name = "v5_assignables",
	srcs = ["tests_v5/assignables.cc"],
	deps = [
             "@gtest//:main",
             ":intermediate_representation"
        ],
	timeout = "short",
	size = "small",
)

cc_test(
	name = "v5_logicals",
	srcs = ["tests_v5/logicals.cc"],
	deps = [
             "@gtest//:main",
             ":intermediate_representation"
        ],
	timeout = "short",
	size = "small",
)

cc_test(
	name = "v5_integration",
	srcs = ["tests_v5/integration.cc"],
	deps = [
             "@gtest//:main",
             ":intermediate_representation"
        ],
	timeout = "short",
	size = "small",
)

cc_test(
	name = "cfg_loop",
	srcs = ["tests_control_flow_graph/loop.cc"],
	deps = [
             "@gtest//:main",
             ":intermediate_representation"
        ],
	timeout = "short",
	size = "small",
)

cc_test(
	name = "cfg_arithmetic",
	srcs = ["tests_control_flow_graph/arithmetic.cc"],
	deps = [
             "@gtest//:main",
             ":intermediate_representation"
        ],
	timeout = "short",
	size = "small",
)

cc_test(
	name = "cfg_assignables",
	srcs = ["tests_control_flow_graph/assignables.cc"],
	deps = [
             "@gtest//:main",
             ":intermediate_representation"
        ],
	timeout = "short",
	size = "small",
)

cc_test(
	name = "cfg_logicals",
	srcs = ["tests_control_flow_graph/logicals.cc"],
	deps = [
             "@gtest//:main",
             ":intermediate_representation"
        ],
	timeout = "short",
	size = "small",
)

cc_test(
	name = "cfg_integration",
	srcs = ["tests_control_flow_graph/integration.cc"],
	deps = [
             "@gtest//:main",
             ":intermediate_representation"
        ],
	timeout = "short",
	size = "small",
)

cc_test(
	name = "ssa_loop",
	srcs = ["tests_ssa/loop.cc"],
	deps = [
             "@gtest//:main",
             ":intermediate_representation"
        ],
	timeout = "short",
	size = "small",
)

cc_test(
	name = "ssa_arithmetic",
	srcs = ["tests_ssa/arithmetic.cc"],
	deps = [
             "@gtest//:main",
             ":intermediate_representation"
        ],
	timeout = "short",
	size = "small",
)

cc_test(
	name = "ssa_assignables",
	srcs = ["tests_ssa/assignables.cc"],
	deps = [
             "@gtest//:main",
             ":intermediate_representation"
        ],
	timeout = "short",
	size = "small",
)

cc_test(
	name = "ssa_logicals",
	srcs = ["tests_ssa/logicals.cc"],
	deps = [
             "@gtest//:main",
             ":intermediate_representation"
        ],
	timeout = "short",
	size = "small",
)

cc_test(
	name = "ssa_integration",
	srcs = ["tests_ssa/integration.cc"],
	deps = [
             "@gtest//:main",
             ":intermediate_representation"
        ],
	timeout = "short",
	size = "small",
)

