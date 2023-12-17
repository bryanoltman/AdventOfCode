cc_binary(
    name = "17",
    srcs = ["main.cc"],
    deps = [":lib"],
)

cc_library(
    name = "lib",
    srcs = [
        "17.cc",
    ],
    hdrs = ["17.h"],
    data = ["//inputs:17.txt"],
    deps = ["//shared"],
)

cc_test(
    name = "test",
    size = "small",
    srcs = ["17_test.cc"],
    data = [
        "//inputs:17.test.txt",
    ],
    defines = ["CATCH_CONFIG_MAIN"],
    deps = [
        ":lib",
        "@catch2",
    ],
)
