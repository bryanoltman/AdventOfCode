cc_binary(
    name = "25",
    srcs = ["main.cc"],
    deps = [":lib"],
)

cc_library(
    name = "lib",
    srcs = [
        "25.cc",
    ],
    hdrs = ["25.h"],
    data = ["//inputs:25.txt"],
    deps = ["//shared"],
)

cc_test(
    name = "test",
    size = "small",
    srcs = ["25_test.cc"],
    data = [
        "//inputs:25.test.txt",
    ],
    defines = ["CATCH_CONFIG_MAIN"],
    deps = [
        ":lib",
        "@catch2",
    ],
)
