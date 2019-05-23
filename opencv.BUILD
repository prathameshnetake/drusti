load("@drusti//:build_config.bzl", "opencv_srcs", "opencv_linkopts")

cc_library(
    name = "opencv",
    srcs = opencv_srcs(exclude = []),
    hdrs = glob(["include/**/*.hpp", "include/**/*.h"]),
    linkopts = opencv_linkopts(),
    includes = ["include"],
    visibility = ["//visibility:public"], 
    linkstatic = 1,
)