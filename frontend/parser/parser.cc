cc_library(
  name = "parser",
  copts = ["-Wall -g"],
  srcs = ["parser.cc"],
  hdrs = ["parser.h"],
  deps = ["//scanner/token"],
  visibility = ["//visibility:public"],
)
