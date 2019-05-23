cc_library(
    name = "ie",
    srcs = glob(["lib/*/Release/*.lib"]),
    hdrs = glob(["include/**/*.hpp", "include/**/*.h", "include/*.h", "include/*.hpp"]),
    includes = ["include"],
    visibility = ["//visibility:public"], 
    linkstatic = 1,
)