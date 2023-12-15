cc_binary(
    name = "14",
    srcs = ["main.cc"],
    deps = [":lib"],
)

cc_library(
    name = "lib",
    srcs = [
        "14.cc",
    ],
    hdrs = ["14.h"],
    data = ["//inputs:14.txt"],
    deps = ["//shared"],
)

cc_test(
    name = "test",
    size = "small",
    srcs = ["14_test.cc"],
    data = [
        "//inputs:14.test.txt",
    ],
    defines = ["CATCH_CONFIG_MAIN"],
    deps = [
        ":lib",
        "@catch2",
    ],
)
