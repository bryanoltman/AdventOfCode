cc_binary(
    name = "13",
    srcs = ["main.cc"],
    deps = [":lib"],
)

cc_library(
    name = "lib",
    srcs = [
        "13.cc",
    ],
    hdrs = ["13.h"],
    data = ["//inputs:13.txt"],
    deps = ["//shared"],
)

cc_test(
    name = "test",
    size = "small",
    srcs = ["13_test.cc"],
    data = [
        "//inputs:13.test.txt",
        "//inputs:13.test2.txt",
    ],
    defines = ["CATCH_CONFIG_MAIN"],
    deps = [
        ":lib",
        "@catch2",
    ],
)
