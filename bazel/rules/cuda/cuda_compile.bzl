"""
Implementation of the cuda_compile rule
"""

load("@bazel_skylib//lib:types.bzl", "types")
load("@bazel_tools//tools/cpp:toolchain_utils.bzl", "find_cpp_toolchain")

def _get_tools_depset(ctx):
    cc_toolchain = find_cpp_toolchain(ctx)
    nvcc_info = ctx.toolchains["//bazel/toolchains/cuda:toolchain_type"].nvcc_info

    return depset(transitive = [item.files for item in nvcc_info.tools if DefaultInfo in item] + [cc_toolchain.all_files])

def _get_nvcc_common_flags(ctx, compute_archs):
    cc_toolchain = find_cpp_toolchain(ctx)

    args = ctx.actions.args()
    args.add("--keep")  # create temporary files locally in the sandbox folder instead of /tmp
    args.add("-ccbin", cc_toolchain.compiler_executable)
    args.add("-Xcompiler", "-fPIC")
    for arch in compute_archs:
        args.add("-gencode", "arch=compute_{arch},code=\"sm_{arch},compute_{arch}\"".format(arch = arch))
    args.add_all(ctx.attr._compiler_opts)
    args.add_all(ctx.attr.copts)

    return args

def _get_nvcc_compile_flags(ctx, compute_archs):
    args = _get_nvcc_common_flags(ctx, compute_archs)
    args.add("-std", "c++14")
    args.add("-x", "cu")
    args.add("-dc")

    return args

def _get_nvcc_dlink_flags(ctx, compute_archs):
    args = _get_nvcc_common_flags(ctx, compute_archs)
    args.add("-Wno-deprecated-gpu-targets")
    args.add("-shared")
    args.add("-dlink")

    return args

def _get_compilation_context_for_labels(label_list):
    includes = depset(direct = [], transitive = [dep[CcInfo].compilation_context.includes for dep in label_list if CcInfo in dep])
    system_includes = depset(direct = [], transitive = [dep[CcInfo].compilation_context.system_includes for dep in label_list if CcInfo in dep])
    return cc_common.create_compilation_context(includes = includes, system_includes = system_includes)

def _join_compilation_contexts(compilation_contexts):
    return cc_common.create_compilation_context(
        defines = depset(transitive = [item.defines for item in compilation_contexts]),
        headers = depset(transitive = [item.headers for item in compilation_contexts]),
        includes = depset(transitive = [item.includes for item in compilation_contexts]),
        quote_includes = depset(transitive = [item.quote_includes for item in compilation_contexts]),
        system_includes = depset(transitive = [item.system_includes for item in compilation_contexts]),
    )

def _get_compilation_context(ctx):
    explicit_comp_ctxt = _get_compilation_context_for_labels(ctx.attr.deps)
    implicit_comp_ctxt = _get_compilation_context_for_labels(ctx.attr._implicit_deps)
    return _join_compilation_contexts([explicit_comp_ctxt, implicit_comp_ctxt])

def _as_list(libraries_to_link):
    if types.is_list(libraries_to_link):
        return libraries_to_link
    elif types.is_depset(libraries_to_link):
        return libraries_to_link.to_list()
    elif hasattr(libraries_to_link, "to_list"):
        return libraries_to_link.to_list()
    else:
        fail("Could not get libraries_to_link")

def _get_linking_context_for_labels(labels, user_linkopts = []):
    linker_inputs_transitive = []

    linking_contexts = [dep[CcInfo].linking_context for dep in labels if CcInfo in dep]
    for item in linking_contexts:
        linker_inputs_transitive.append(item.linker_inputs)

    linker_inputs = depset(direct = [], transitive = linker_inputs_transitive)

    return cc_common.create_linking_context(
        linker_inputs = linker_inputs,
    )

def _get_linking_context(ctx):
    return _get_linking_context_for_labels(ctx.attr._implicit_deps, ctx.attr.linkopts)

def _get_headers_from_attr(attrib):
    return depset(direct = [], transitive = [dep[CcInfo].compilation_context.headers for dep in attrib if CcInfo in dep])

def _get_library_folders(libraries_to_link):
    dynamic_lib_paths = [item.dynamic_library.dirname for item in _as_list(libraries_to_link) if item.dynamic_library]
    static_lib_paths = [item.static_library.dirname for item in _as_list(libraries_to_link) if item.static_library]
    return dynamic_lib_paths + static_lib_paths

def _get_libraries(libraries_to_link):
    dynamic_lib_paths = [item.dynamic_library.path for item in _as_list(libraries_to_link) if item.dynamic_library]
    static_lib_paths = [item.static_library.path for item in _as_list(libraries_to_link) if item.static_library]
    return dynamic_lib_paths + static_lib_paths

def _get_nvcc_build_environment():
    # TODO: make dependencies (such as 'as') in /usr/bin available through the toolchain.
    return {"PATH": "/usr/bin:"}

def _compile_cuda_kernels(ctx, compile_ctx):
    src_kernels = [f for f in ctx.files.srcs if f.extension == "cu"]
    src_headers = [f for f in ctx.files.srcs if f.extension in ["h", "hpp", "cuh"]]

    headers_from_deps = _get_headers_from_attr(ctx.attr.deps)
    headers_from_implicit_deps = _get_headers_from_attr(ctx.attr._implicit_deps)

    nvcc_info = ctx.toolchains["//bazel/toolchains/cuda:toolchain_type"].nvcc_info

    out_files = []
    compile_flags = _get_nvcc_compile_flags(ctx, ctx.attr.compute_archs)
    for f in src_kernels:
        out = ctx.actions.declare_file("_objs/{}/{}.o".format(ctx.label.name, f.basename))

        args = ctx.actions.args()
        args.add("-o", out)
        args.add(f.path)

        args.add("-I", ".")
        args.add("-I", f.dirname)
        args.add_all(compile_ctx.includes, before_each = "-I")
        args.add_all(compile_ctx.quote_includes, before_each = "-iquote")
        args.add_all(compile_ctx.system_includes, before_each = "-isystem")

        ctx.actions.run(
            executable = nvcc_info.nvcc,
            tools = _get_tools_depset(ctx),
            outputs = [out],
            arguments = [compile_flags, args],
            inputs = depset(direct = [f] + src_headers, transitive = [headers_from_deps, headers_from_implicit_deps]),
            env = _get_nvcc_build_environment(),
            progress_message = "Building CUDA object {}".format(out.basename),
        )
        out_files.append(out)

    return out_files

def _device_link_object_files(ctx, cu_object_files):
    predeclared_cu_object_files = [f for f in ctx.files.srcs if (f.basename.endswith("cu.o"))]

    nvcc_info = ctx.toolchains["//bazel/toolchains/cuda:toolchain_type"].nvcc_info

    compile_ctx_tool = _get_compilation_context_for_labels(nvcc_info.tools)

    headers_from_tool_deps = _get_headers_from_attr(nvcc_info.tools)

    dlink_out = ctx.actions.declare_file("_objs/{}/dlink.o".format(ctx.label.name))
    args = _get_nvcc_dlink_flags(ctx, ctx.attr.compute_archs)
    args.add("-o", dlink_out)

    # nvcc automatically links some libs when required, such as libcudart.
    # In case they are not in the default path, their locations have to be exposed with "-L <path>"

    args.add_all(cu_object_files)
    args.add_all(predeclared_cu_object_files)
    args.add_all(ctx.attr.linkopts)
    args.add_all(compile_ctx_tool.system_includes, before_each = "-isystem")

    ctx.actions.run(
        executable = nvcc_info.nvcc,
        tools = _get_tools_depset(ctx),
        outputs = [dlink_out],
        arguments = [args],
        inputs = depset(direct = cu_object_files + predeclared_cu_object_files, transitive = [headers_from_tool_deps]),
        env = _get_nvcc_build_environment(),
        progress_message = "Linking CUDA device code {}".format(dlink_out.basename),
    )

    return dlink_out

def _cuda_compile_impl(ctx):
    compile_ctx = _get_compilation_context(ctx)
    link_ctx = _get_linking_context(ctx)

    cu_object_files = _compile_cuda_kernels(ctx, compile_ctx)
    dlink_file = _device_link_object_files(ctx, cu_object_files)

    return [
        DefaultInfo(files = depset(cu_object_files + [dlink_file])),
        CcInfo(compilation_context = compile_ctx, linking_context = link_ctx),
    ]

cuda_compile = rule(
    attrs = {
        "srcs": attr.label_list(allow_files = [
            ".cu",
            ".h",
            ".hpp",
            ".cuh",
            ".o",
        ]),
        "deps": attr.label_list(
            allow_files = True,
            providers = [CcInfo],
        ),
        "_cc_toolchain": attr.label(
            default = Label("@bazel_tools//tools/cpp:current_cc_toolchain"),
        ),
        "_implicit_deps": attr.label_list(
            allow_files = True,
            providers = [CcInfo],
            default = [
                "@cuda//:cudart",
                "@cuda//:cudadevrt",
            ],
        ),
        "_compiler_opts": attr.string_list(default = [
            "-O2",
            "-g",
        ]),
        "linkopts": attr.string_list(),
        "copts": attr.string_list(),
        "compute_archs": attr.string_list(default = [
            "35",
            "52",
        ]),
    },
    provides = [CcInfo],
    toolchains = ["//bazel/toolchains/cuda:toolchain_type"],
    implementation = _cuda_compile_impl,
)
