cc_binary(
    name = "11",
    srcs = ["main.cc"],
    deps = [":lib"],
)

cc_library(
    name = "lib",
    srcs = [
        "11.cc",
    ],
    hdrs = ["11.h"],
    data = ["//inputs:11.txt"],
    deps = ["//shared"],
)

cc_test(
    name = "test",
    size = "small",
    srcs = ["11_test.cc"],
    data = [
        "//inputs:11.test.txt",
    ],
    defines = ["CATCH_CONFIG_MAIN"],
    deps = [
        ":lib",
        "@catch2",
    ],
)
