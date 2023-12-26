cc_binary(
    name = "20",
    srcs = ["main.cc"],
    deps = [":lib"],
)

cc_library(
    name = "lib",
    srcs = [
        "20.cc",
    ],
    hdrs = ["20.h"],
    data = ["//inputs:20.txt"],
    deps = ["//shared"],
)

cc_test(
    name = "test",
    size = "small",
    srcs = ["20_test.cc"],
    data = [
        "//inputs:20.test.txt",
        "//inputs:20.test2.txt",
    ],
    defines = ["CATCH_CONFIG_MAIN"],
    deps = [
        ":lib",
        "@catch2",
    ],
)
