#!/bin/bash

TARGET=${PWD##*/}
REMOTE_ANDROID_DIR=/data/local/tmp

# Build for Android 64-bit device
bazel build :$TARGET \
  --crosstool_top=//external:android/crosstool \
  --host_crosstool_top=@bazel_tools//tools/cpp:toolchain \
  --cpu=arm64-v8a

adb push ../bazel-bin/$TARGET/$TARGET $REMOTE_ANDROID_DIR
