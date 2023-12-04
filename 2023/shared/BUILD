cc_library(
    name = "shared",
    srcs = [
        "shared.cc",
        "shared.h",
    ],
    hdrs = ["shared.h"],
    visibility = ["//visibility:public"],
)

cc_test(
    name = "shared_test",
    size = "small",
    srcs = ["shared_test.cc"],
    deps = [
        ":shared",
        "@com_google_googletest//:gtest_main",
    ],
)
