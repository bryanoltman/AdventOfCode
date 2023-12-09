cc_binary(
    name = "09",
    srcs = ["main.cc"],
    deps = [":lib"],
)

cc_library(
    name = "lib",
    srcs = [
        "09.cc",
    ],
    hdrs = ["09.h"],
    data = ["//inputs:09.txt"],
    deps = ["//shared"],
)

cc_test(
    name = "test",
    size = "small",
    srcs = ["09_test.cc"],
    data = [
        "//inputs:09.test.txt",
    ],
    defines = ["CATCH_CONFIG_MAIN"],
    deps = [
        ":lib",
        "@catch2",
    ],
)
