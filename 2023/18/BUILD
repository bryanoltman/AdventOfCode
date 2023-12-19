cc_binary(
    name = "18",
    srcs = ["main.cc"],
    deps = [":lib"],
)

cc_library(
    name = "lib",
    srcs = [
        "18.cc",
    ],
    hdrs = ["18.h"],
    data = ["//inputs:18.txt"],
    deps = ["//shared"],
)

cc_test(
    name = "test",
    size = "small",
    srcs = ["18_test.cc"],
    data = [
        "//inputs:18.test.txt",
    ],
    defines = ["CATCH_CONFIG_MAIN"],
    deps = [
        ":lib",
        "@catch2",
    ],
)
