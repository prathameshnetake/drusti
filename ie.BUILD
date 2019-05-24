load("@drusti//:build_config.bzl", "ie_srcs")

cc_library(
    name = "ie",
    srcs = ie_srcs(),
    hdrs = glob(["include/**/*.hpp", "include/**/*.h", "include/*.h", "include/*.hpp"]),
    includes = ["include"],
    visibility = ["//visibility:public"], 
    linkstatic = 1,
)