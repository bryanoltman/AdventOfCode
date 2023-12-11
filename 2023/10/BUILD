cc_binary(
    name = "10",
    srcs = ["main.cc"],
    deps = [":lib"],
)

cc_library(
    name = "lib",
    srcs = [
        "10.cc",
    ],
    hdrs = ["10.h"],
    data = ["//inputs:10.txt"],
    deps = ["//shared"],
)

cc_test(
    name = "test",
    size = "small",
    srcs = ["10_test.cc"],
    data = [
        "//inputs:10.test.txt",
        "//inputs:10.test2.txt",
        "//inputs:10.test3.txt",
        "//inputs:10.test4.txt",
        "//inputs:10.test5.txt",
    ],
    defines = ["CATCH_CONFIG_MAIN"],
    deps = [
        ":lib",
        "@catch2",
    ],
)
