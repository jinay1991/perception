"""
Implementation of the cuda_toolchain
"""
CudaToolchainInfo = provider(
    doc = "Information about how to invoke the nvcc compiler.",
    fields = ["nvcc", "target_arch", "tools", "version"],
)

def _cuda_toolchain_impl(ctx):
    toolchain_info = platform_common.ToolchainInfo(
        nvcc_info = CudaToolchainInfo(
            nvcc = ctx.executable.nvcc,
            target_arch = ctx.attr.target_arch,
            tools = depset(direct = ctx.files.tools),
            version = ctx.attr.version,
        ),
    )
    return [toolchain_info]

cuda_toolchain = rule(
    implementation = _cuda_toolchain_impl,
    attrs = {
        "nvcc": attr.label(
            cfg = "host",
            doc = " nvcc. Main compiler for cuda files ",
            executable = True,
        ),
        "target_arch": attr.string(
            doc = " What the target arch is for this toolchain. i.e. x86_64, aarch64, etc. ",
            mandatory = True,
        ),
        "tools": attr.label_list(
            allow_files = True,
            doc = " A depset of the tools needed by this toolchain ",
        ),
        "version": attr.string(
            doc = " Which CUDA version is this toolchain wrapping. ",
            mandatory = True,
        ),
    },
    doc = "The information needed for the CUDA toolchain. Mostly unused right now. May become more important in the future.",
)
