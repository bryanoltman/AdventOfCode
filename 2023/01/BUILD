cc_binary(
    name = "01",
    srcs = ["main.cc"],
    data = [
        "//inputs:01.txt",
    ],
    deps = [
        ":lib",
        "//shared",
    ],
)

cc_library(
    name = "lib",
    srcs = ["01.cc"],
    hdrs = ["01.h"],
    data = [
        "//inputs:01.txt",
    ],
)

cc_test(
    name = "test",
    size = "small",
    srcs = ["01_test.cc"],
    data = [
        "//inputs:01.test.txt",
        "//inputs:01.test2.txt",
    ],
    defines = ["CATCH_CONFIG_MAIN"],
    deps = [
        ":lib",
        "//shared",
        "@catch2",
    ],
)
