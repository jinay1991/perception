package(default_visibility = ["//visibility:public"])

cc_library(
    name = "libuv",
    srcs = [
        "src/fs-poll.c",
        "src/idna.c",
        "src/inet.c",
        "src/random.c",
        "src/strscpy.c",
        "src/threadpool.c",
        "src/timer.c",
        "src/unix/async.c",
        "src/unix/core.c",
        "src/unix/dl.c",
        "src/unix/fs.c",
        "src/unix/getaddrinfo.c",
        "src/unix/getnameinfo.c",
        "src/unix/loop.c",
        "src/unix/loop-watcher.c",
        "src/unix/pipe.c",
        "src/unix/poll.c",
        "src/unix/process.c",
        "src/unix/proctitle.c",
        "src/unix/random-devurandom.c",
        "src/unix/signal.c",
        "src/unix/stream.c",
        "src/unix/tcp.c",
        "src/unix/thread.c",
        "src/unix/tty.c",
        "src/unix/udp.c",
        "src/uv-common.c",
        "src/uv-data-getter-setters.c",
        "src/version.c",
    ] + select({
        "@platforms/os:macos": [
            "src/unix/darwin-proctitle.c",
            "src/unix/darwin.c",
            "src/unix/fsevents.c",
        ],
        "@platforms/os:linux": [
            "src/unix/linux-core.c",
            "src/unix/linux-inotify.c",
            "src/unix/linux-syscalls.c",
            "src/unix/procfs-exepath.c",
            "src/unix/random-getrandom.c",
            "src/unix/random-sysctl-linux.c",
            "src/unix/sysinfo-loadavg.c",
        ],
        "//conditions:default": [],
    }),
    hdrs = glob([
        "include/**/*.h",
        "src/*.h",
        "src/unix/*.h",
    ]),
    defines =
        [
            "_FILE_OFFSET_BITS=64",
            "_LARGEFILE_SOURCE",
        ] + select({
            "@platforms/os:macos": [
                "_DARWIN_UNLIMITED_SELECT=1",
                "_DARWIN_USE_64_BIT_INODE=1",
            ],
            "//conditions:default": [
                "_GNU_SOURCE",
                "_POSIX_C_SOURCE=200112",
            ],
        }),
    includes = [
        "include",
        "src",
        "src/unix",
    ],
    linkopts = [
        "-lpthread",
    ] + select({
        "@platforms/os:linux": [
            "-ldl",
            "-lrt",
        ],
        "//conditions:default": [],
    }),
)
