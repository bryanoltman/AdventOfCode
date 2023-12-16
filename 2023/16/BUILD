cc_binary(
    name = "16",
    srcs = ["main.cc"],
    deps = [":lib"],
)

cc_library(
    name = "lib",
    srcs = [
        "16.cc",
    ],
    hdrs = ["16.h"],
    data = ["//inputs:16.txt"],
    deps = ["//shared"],
)

cc_test(
    name = "test",
    size = "small",
    srcs = ["16_test.cc"],
    data = [
        "//inputs:16.test.txt",
    ],
    defines = ["CATCH_CONFIG_MAIN"],
    deps = [
        ":lib",
        "@catch2",
    ],
)
