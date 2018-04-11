
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
<<<<<<< HEAD
	copts = ["-Iexternal/gtest/googletest-release-1.8.0/googletest/include"],
	timeout = "short", 
=======
	timeout = "short",
>>>>>>> 347c86dba288f1a6747d9c48090b3c684cde5de8
	size = "small",
)
