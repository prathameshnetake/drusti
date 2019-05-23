load("@drusti//:build_config.bzl", "opencv_srcs", "opencv_linkopts", "opencv_hdrs")

cc_library(
    name = "opencv",
    srcs = opencv_srcs(exclude = []),
    hdrs = opencv_hdrs(),
    linkopts = opencv_linkopts(),
    includes = ["include"],
    visibility = ["//visibility:public"], 
    linkstatic = 1,
)