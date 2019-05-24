def opencv_srcs(exclude = []):
  windows_srcs = ["lib/opencv_world410.lib", "lib/opencv_pvl410.lib"]
  linux_srcs = native.glob(["lib/*.so*"])
  return select({
    "@drusti//:windows" : windows_srcs,
    "@drusti//:linux_x86_64" : linux_srcs,
  })

def opencv_hdrs(exclude = []):
  windows_hdrs = native.glob(["include/**/*.hpp", "include/**/*.h"])
  linux_hdrs = native.glob(["include/**/*.hpp", "include/**/*.h"])
  return select({
    "@drusti//:windows" : windows_hdrs,
    "@drusti//:linux_x86_64" : linux_hdrs,
  })

def opencv_linkopts(exclude = []):
  windows_flags = []
  linux_flags = ["-ldl"]
  return select({
    "@drusti//:windows" : windows_flags,
    "@drusti//:linux_x86_64" : linux_flags,
  })

def ie_srcs():
  return select({
    "@drusti//:windows" : native.glob(["lib/*/Release/*.lib"]),
    "@drusti//:linux_x86_64" : native.glob(["lib/**/*.so"]),
  })