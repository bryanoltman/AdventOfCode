cc_binary(
    name = "15",
    srcs = ["main.cc"],
    deps = [":lib"],
)

cc_library(
    name = "lib",
    srcs = [
        "15.cc",
    ],
    hdrs = ["15.h"],
    data = ["//inputs:15.txt"],
    deps = ["//shared"],
)

cc_test(
    name = "test",
    size = "small",
    srcs = ["15_test.cc"],
    data = [
        "//inputs:15.test.txt",
    ],
    defines = ["CATCH_CONFIG_MAIN"],
    deps = [
        ":lib",
        "@catch2",
    ],
)
