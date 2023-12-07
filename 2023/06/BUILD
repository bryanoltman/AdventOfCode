cc_binary(
    name = "06",
    srcs = ["main.cc"],
    deps = [":lib"],
)

cc_library(
    name = "lib",
    srcs = [
        "06.cc",
    ],
    hdrs = ["06.h"],
    deps = ["//shared"],
)

cc_test(
    name = "test",
    size = "small",
    srcs = ["06_test.cc"],
    defines = ["CATCH_CONFIG_MAIN"],
    deps = [
        ":lib",
        "@catch2",
    ],
)
