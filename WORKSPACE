workspace(name = "drusti")

load(":build_config.bzl", "local_opencv")

new_local_repository(
    name = "opencv_windows",
    path = "C:/Program Files (x86)/IntelSWTools/openvino/opencv",
    build_file = "opencv.BUILD",
)

new_local_repository(
    name = "opencv_linux",
    path = "/opt/intel/openvino/opencv",
    build_file = "opencv.BUILD",
)

# new_local_repository(
#     name = "ie",
#     path = "C:/Program Files (x86)/IntelSWTools/openvino/inference_engine",
#     build_file = "ie.BUILD",
# )