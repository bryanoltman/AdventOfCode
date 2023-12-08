cc_binary(
    name = "07",
    srcs = ["main.cc"],
    deps = [":lib"],
)

cc_library(
    name = "lib",
    srcs = [
        "07.cc",
    ],
    hdrs = ["07.h"],
    data = ["//inputs:07.txt"],
    deps = ["//shared"],
)

cc_test(
    name = "test",
    size = "small",
    srcs = ["07_test.cc"],
    data = ["//inputs:07.test.txt"],
    defines = ["CATCH_CONFIG_MAIN"],
    deps = [
        ":lib",
        "@catch2",
    ],
)
