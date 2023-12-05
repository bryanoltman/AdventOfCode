cc_library(
    name = "shared",
    srcs = [
        "shared.cc",
        "shared.h",
    ],
    hdrs = [
        "shared.h",
    ],
    visibility = ["//visibility:public"],
)

cc_test(
    name = "test",
    size = "small",
    srcs = glob(["tests/*.cc"]),
    defines = ["CATCH_CONFIG_MAIN"],
    deps = [
        ":shared",
        "@catch2",
    ],
)
