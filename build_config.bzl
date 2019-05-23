def opencv_srcs(exclude = []):
  windows_srcs = native.glob([
      "platform/default/*.cc",
      "platform/windows/*.cc",
      "platform/posix/error.cc",
  ], exclude = exclude)
  linux_srcs = native.glob(["lib/*.so*"])
  return select({
    "@drusti//:windows" : windows_srcs,
    "@drusti//:linux_x86_64" : linux_srcs,
  })

def clean_dep(dep):
  return str(Label(dep))

def if_windows(a):
  return select({
      clean_dep("@drusti//:windows"): a,
      "//conditions:default": "/opt/intel/openvino/opencv",
  })

def opencv_linkopts(exclude = []):
  windows_flags = []
  linux_flags = ["-ldl"]
  return select({
    "@drusti//:windows" : windows_flags,
    "@drusti//:linux_x86_64" : linux_flags,
  })

def opencv_local_path():
  return if_windows("/opt/intel/openvino/opencv")
  # return select({
  #   "@drusti//:windows" : "here goes windows path",
  #   "@drusti//:linux_x86_64" : "/opt/intel/openvino/opencv",
  # })

def _impl(repository_ctx):
  repository_ctx.path("/opt/intel/openvino/opencv")
  print(repository_ctx.attr)


local_opencv = repository_rule(
    implementation=_impl,
    local=True,
    new = True,
    attrs={"build_file": attr.label()})