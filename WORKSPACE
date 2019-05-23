workspace(name = "drusti")

load(":build_config.bzl", "local_opencv")

local_opencv(
    name = "opencv",
    build_file = str("@drusti//:opencv.BUILD")
)
# new_local_repository(
#     name = "ie",
#     path = "C:/Program Files (x86)/IntelSWTools/openvino/inference_engine",
#     build_file = "ie.BUILD",
# )