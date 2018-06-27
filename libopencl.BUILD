# Description: OpenCL driver Adreno 540 GPU & Mali T880 GPU
# https://github.com/supernovaremnant/Android-OpenCL-Driver

package(
    default_visibility = ["//visibility:public"],
)

filegroup(
    name = "qualcomm_adreno_540_32_bit_lib",
    srcs = [
        "Qualcomm-Adreno-540/libOpenCL_32.so",
    ],
)

filegroup(
    name = "qualcomm_adreno_540_64_bit_lib",
    srcs = [
        "Qualcomm-Adreno-540/libOpenCL_64.so",
    ],
)

filegroup(
    name = "qualcomm_adreno_530_32_bit_lib",
    srcs = [
        "Qualcomm-Adreno-530/libOpenCL_32.so",
    ],
)

filegroup(
    name = "qualcomm_adreno_530_64_bit_lib",
    srcs = [
        "Qualcomm-Adreno-530/libOpenCL_64.so",
    ],
)

filegroup(
    name = "arm_mali_t880_64_bit_lib",
    srcs = [
        "ARM-Mali-T880/libOpenCLIcd.so",
    ],
)

cc_library(
    name = "Adreno_540_64_bit_lib",
    hdrs = glob([
        "CL/**",
        "*.hpp",
    ]),
    srcs = [
        ":qualcomm_adreno_540_64_bit_lib",
    ],
    linkstatic = 1,
)

cc_library(
    name = "Adreno_530_64_bit_lib",
    hdrs = glob([
        "CL/**",
        "*.hpp",
    ]),
    srcs = [
        ":qualcomm_adreno_530_64_bit_lib",
    ],
    linkstatic = 1,
)

cc_library(
    name = "Mali_T880_64_bit_lib",
    hdrs = glob([
        "CL/**",
        "*.hpp",
    ]),
    srcs = [
        ":arm_mali_t880_64_bit_lib",
    ],
    linkstatic = 1,
)
