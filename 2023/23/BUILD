cc_binary(
    name = "23",
    srcs = ["main.cc"],
    deps = [":lib"],
)

cc_library(
    name = "lib",
    srcs = [
        "23.cc",
    ],
    hdrs = ["23.h"],
    data = ["//inputs:23.txt"],
    deps = ["//shared"],
)

cc_test(
    name = "test",
    size = "small",
    srcs = ["23_test.cc"],
    data = [
        "//inputs:23.test.txt",
    ],
    defines = ["CATCH_CONFIG_MAIN"],
    deps = [
        ":lib",
        "@catch2",
    ],
)
