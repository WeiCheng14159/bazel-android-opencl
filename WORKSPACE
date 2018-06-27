android_sdk_repository(
    name="androidsdk",
    path="/Users/chengwei/Library/Android/sdk", # Change to the one on your computer
    api_level=26,
)

android_ndk_repository(
    name="androidndk",
    path="/Users/chengwei/Library/Android/sdk/ndk-bundle", # Change to the one on your computer
    api_level=15,
)
#
new_http_archive(
    name = "libopencl_archive",
    urls = [
        "https://github.com/supernovaremnant/Android-OpenCL-Driver/archive/40ce4fa730a5369b1ecf171abd066c3453d27819.tar.gz",
    ],
    sha256 = "14485b3139bfd9ecbaffe3eb7d9f98904be50e2e046eff7d984b28512378514d",
    strip_prefix = "Android-OpenCL-Driver-40ce4fa730a5369b1ecf171abd066c3453d27819",
    build_file = "libopencl.BUILD",
)
