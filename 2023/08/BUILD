cc_binary(
    name = "010",
    srcs = ["main.cc"],
    deps = [":lib"],
)

cc_library(
    name = "lib",
    srcs = [
        "08.cc",
    ],
    hdrs = ["08.h"],
    data = ["//inputs:08.txt"],
    deps = ["//shared"],
)

cc_test(
    name = "test",
    size = "small",
    srcs = ["08_test.cc"],
    data = ["//inputs:08.test.txt"],
    defines = ["CATCH_CONFIG_MAIN"],
    deps = [
        ":lib",
        "@catch2",
    ],
)
