config_setting(
    name = "linux_x86_64",
    values = {"cpu": "k8"},
    visibility = ["//visibility:public"],
)

config_setting(
    name = "windows",
    values = {"cpu": "x64_windows"},
    visibility = ["//visibility:public"],
)

alias (
    name = "opencv",
    actual = select({
        "//:windows": "@opencv_windows//:opencv",
        "//:linux_x86_64": "@opencv_linux//:openv",
    }),
    visibility = ["//visibility:public"], 
)