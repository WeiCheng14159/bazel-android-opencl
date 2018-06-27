# Description:
#   OpenCL info program for android

ANDROID_C_OPTS = [
  "-ffunction-sections",
  "-fdata-sections",
  "-fPIE",
  "-pie",
  "-fexceptions",
]

ANDROID_LINK_OPTS = [
  "-fPIE",
  "-pie",
  "-landroid",
  "-latomic",
  "-ldl",
  "-llog",
  "-lm",
  "-z defs",
  "-s",
  "-Wl,--gc-sections",
  "-fuse-ld=gold",
]

cc_binary(
    name = "opencl-info",
    srcs = [
        "opencl-info.cc",
    ],
    copts = ANDROID_C_OPTS,
    linkopts = ANDROID_LINK_OPTS,
    deps = [
        "@libopencl_archive//:Adreno_540_64_bit_lib",
    ],
)
