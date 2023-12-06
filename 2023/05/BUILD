cc_binary(
    name = "05",
    srcs = ["main.cc"],
    deps = [":lib"],
)

cc_library(
    name = "lib",
    srcs = [
        "05.cc",
        "05.h",
    ],
    hdrs = ["05.h"],
    data = [
        "//inputs:05.test.txt",
        "//inputs:05.txt",
    ],
    deps = ["//shared"],
)

cc_test(
    name = "test",
    srcs = [
        "05_test.cc",
    ],
    data = [
        "//inputs:05.test.txt",
    ],
    defines = ["CATCH_CONFIG_MAIN"],
    deps = [
        ":lib",
        "@catch2",
    ],
)
