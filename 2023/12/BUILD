cc_binary(
    name = "12",
    srcs = ["main.cc"],
    deps = [":lib"],
)

cc_library(
    name = "lib",
    srcs = [
        "12.cc",
    ],
    hdrs = ["12.h"],
    data = ["//inputs:12.txt"],
    deps = ["//shared"],
)

cc_test(
    name = "test",
    size = "small",
    srcs = ["12_test.cc"],
    data = [
        "//inputs:12.test.txt",
    ],
    defines = ["CATCH_CONFIG_MAIN"],
    deps = [
        ":lib",
        "@catch2",
    ],
)
