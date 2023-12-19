cc_binary(
    name = "19",
    srcs = ["main.cc"],
    deps = [":lib"],
)

cc_library(
    name = "lib",
    srcs = [
        "19.cc",
    ],
    hdrs = ["19.h"],
    data = ["//inputs:19.txt"],
    deps = ["//shared"],
)

cc_test(
    name = "test",
    size = "small",
    srcs = ["19_test.cc"],
    data = [
        "//inputs:19.test.txt",
    ],
    defines = ["CATCH_CONFIG_MAIN"],
    deps = [
        ":lib",
        "@catch2",
    ],
)
