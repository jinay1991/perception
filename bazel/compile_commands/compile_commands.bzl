# Copyright 2017 GRAIL, Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

"""Compilation database generation Bazel rules.

compilation_database will generate a compile_commands.json file for the
given targets. This approach uses the aspects feature of bazel.

An alternative approach is the one used by the kythe project using
(experimental) action listeners.
https://github.com/google/kythe/blob/master/tools/cpp/generate_compilation_database.sh
"""

load("@bazel_tools//tools/cpp:toolchain_utils.bzl", "find_cpp_toolchain")
load(
    "@bazel_tools//tools/build_defs/cc:action_names.bzl",
    "CPP_COMPILE_ACTION_NAME",
    "C_COMPILE_ACTION_NAME",
)

CompilationAspectInfo = provider()

_cpp_extensions = [
    "cc",
    "cpp",
    "cxx",
    "cu",
]

_cc_rules = [
    "cc_library",
    "cc_binary",
    "cc_test",
    "cc_inc_library",
    "cc_proto_library",
    "cuda_compile",
]

_all_rules = _cc_rules

def _compilation_db_json(compilation_db):
    # Return a JSON string for the compilation db entries.

    entries = [entry.to_json() for entry in compilation_db]
    return ",\n ".join(entries)

def _is_cpp_target(srcs):
    return any([src.extension in _cpp_extensions for src in srcs])

def _sources(target, ctx):
    srcs = []
    if "srcs" in dir(ctx.rule.attr):
        srcs += [f for src in ctx.rule.attr.srcs for f in src.files.to_list()]
    if "hdrs" in dir(ctx.rule.attr):
        srcs += [f for src in ctx.rule.attr.hdrs for f in src.files.to_list()]

    if ctx.rule.kind == "cc_proto_library":
        srcs += [f for f in target.files.to_list() if f.extension in ["h", "cc"]]

    return srcs

# Function copied from https://gist.github.com/oquenchil/7e2c2bd761aa1341b458cc25608da50c
def _get_compile_flags(dep):
    options = []
    compilation_context = dep[CcInfo].compilation_context
    for define in compilation_context.defines.to_list():
        options.append("-D{}".format(define))

    for system_include in compilation_context.system_includes.to_list():
        if len(system_include) == 0:
            system_include = "."
        options.append("-isystem {}".format(system_include))

    for include in compilation_context.includes.to_list():
        if len(include) == 0:
            include = "."
        options.append("-I {}".format(include))

    for quote_include in compilation_context.quote_includes.to_list():
        if len(quote_include) == 0:
            quote_include = "."
        options.append("-I {}".format(quote_include))  # https://bugreports.qt.io/browse/QTCREATORBUG-22949

    return options

def _cc_compiler_info(ctx, target, srcs, feature_configuration, cc_toolchain):
    compile_variables = None
    compiler_options = None
    compiler = None
    compile_flags = None
    force_language_mode_option = ""

    # This is useful for compiling .h headers as C++ code.
    if _is_cpp_target(srcs) or ctx.attr._force_cpp == "yes":
        compile_variables = cc_common.create_compile_variables(
            feature_configuration = feature_configuration,
            cc_toolchain = cc_toolchain,
            user_compile_flags = ctx.fragments.cpp.cxxopts +
                                 ctx.fragments.cpp.copts,
            add_legacy_cxx_options = True,
        )
        compiler_options = cc_common.get_memory_inefficient_command_line(
            feature_configuration = feature_configuration,
            action_name = CPP_COMPILE_ACTION_NAME,
            variables = compile_variables,
        )
        force_language_mode_option = " -x c++"
    else:
        compile_variables = cc_common.create_compile_variables(
            feature_configuration = feature_configuration,
            cc_toolchain = cc_toolchain,
            user_compile_flags = ctx.fragments.cpp.copts,
        )
        compiler_options = cc_common.get_memory_inefficient_command_line(
            feature_configuration = feature_configuration,
            action_name = C_COMPILE_ACTION_NAME,
            variables = compile_variables,
        )

    compiler = str(
        cc_common.get_tool_for_action(
            feature_configuration = feature_configuration,
            action_name = C_COMPILE_ACTION_NAME,
        ),
    )

    compile_flags = (compiler_options +
                     _get_compile_flags(target) +
                     (ctx.rule.attr.copts if "copts" in dir(ctx.rule.attr) else []))

    return struct(
        compile_variables = compile_variables,
        compiler_options = compiler_options,
        compiler = compiler,
        compile_flags = compile_flags,
        force_language_mode_option = force_language_mode_option,
    )

def _compilation_database_aspect_impl(target, ctx):
    # Write the compile commands for this target to a file, and return
    # the commands for the transitive closure.

    # We support only these rule kinds.
    if ctx.rule.kind not in _all_rules:
        return []

    compilation_db = []

    cc_toolchain = find_cpp_toolchain(ctx)
    feature_configuration = cc_common.configure_features(
        ctx = ctx,
        cc_toolchain = cc_toolchain,
        requested_features = ctx.features,
        unsupported_features = ctx.disabled_features,
    )

    srcs = _sources(target, ctx)
    if not srcs:
        return []

    compiler_info = None

    if ctx.rule.kind in _cc_rules:
        compiler_info = _cc_compiler_info(ctx, target, srcs, feature_configuration, cc_toolchain)

    compile_flags = compiler_info.compile_flags
    compile_command = compiler_info.compiler + " " + " ".join(compile_flags) + compiler_info.force_language_mode_option

    for src in srcs:
        command_for_file = compile_command + " -c " + src.path

        exec_root_marker = "__EXEC_ROOT__"
        compilation_db.append(
            struct(command = command_for_file, directory = exec_root_marker, file = src.path),
        )

    # Write the commands for this target.
    compdb_file = ctx.actions.declare_file(ctx.label.name + ".compile_commands.json")
    ctx.actions.write(
        content = _compilation_db_json(compilation_db),
        output = compdb_file,
    )

    # Collect all transitive dependencies.
    transitive_compilation_db = []
    all_compdb_files = []
    for dep in ctx.rule.attr.deps:
        if CompilationAspectInfo not in dep:
            continue
        transitive_compilation_db.append(dep[CompilationAspectInfo].compilation_db)
        all_compdb_files.append(dep[OutputGroupInfo].compdb_files)

    compilation_db = depset(compilation_db, transitive = transitive_compilation_db)
    all_compdb_files = depset([compdb_file], transitive = all_compdb_files)

    return [
        CompilationAspectInfo(compilation_db = compilation_db),
        OutputGroupInfo(compdb_files = all_compdb_files),
    ]

compilation_database_aspect = aspect(
    attr_aspects = ["deps"],
    attrs = {
        "_cc_toolchain": attr.label(
            default = Label("@bazel_tools//tools/cpp:current_cc_toolchain"),
        ),
        "_force_cpp": attr.string(values = ["yes", "no"], default = "no"),
    },
    fragments = ["cpp"],
    required_aspect_providers = [CompilationAspectInfo],
    toolchains = ["@bazel_tools//tools/cpp:toolchain_type"],
    implementation = _compilation_database_aspect_impl,
)

compilation_database_aspect_force_cpp = aspect(
    attr_aspects = ["deps"],
    attrs = {
        "_cc_toolchain": attr.label(
            default = Label("@bazel_tools//tools/cpp:current_cc_toolchain"),
        ),
        "_force_cpp": attr.string(values = ["yes", "no"], default = "yes"),
    },
    fragments = ["cpp"],
    required_aspect_providers = [CompilationAspectInfo],
    toolchains = ["@bazel_tools//tools/cpp:toolchain_type"],
    implementation = _compilation_database_aspect_impl,
)

def _compilation_database_impl(ctx):
    # Generates a single compile_commands.json file with the
    # transitive depset of specified targets.

    if ctx.attr.disable:
        ctx.actions.write(output = ctx.outputs.filename, content = "[]\n")
        return

    # We make this rule a no-op on Windows because it is not supported.
    # We use the exposed host path separator as a hack to detect Windows.
    # The ideal solution here would be to use toolchains.
    # https://github.com/bazelbuild/bazel/issues/2045
    if ctx.configuration.host_path_separator != ":":
        print("Windows is not supported in compilation_database rule")
        ctx.actions.write(output = ctx.outputs.filename, content = "[]\n")
        return

    compilation_db = []
    for target in ctx.attr.targets:
        compilation_db.append(target[CompilationAspectInfo].compilation_db)

    compilation_db = depset(transitive = compilation_db)

    content = "[\n" + _compilation_db_json(compilation_db.to_list()) + "\n]\n"
    content = content.replace("__EXEC_ROOT__", ctx.attr.exec_root)
    ctx.actions.write(output = ctx.outputs.filename, content = content)

compilation_database = rule(
    attrs = {
        "targets": attr.label_list(
            aspects = [compilation_database_aspect],
            doc = "List of all cc targets which should be included.",
        ),
        "exec_root": attr.string(
            default = "__EXEC_ROOT__",
            doc = "Execution root of Bazel as returned by 'bazel info execution_root'.",
        ),
        "disable": attr.bool(
            default = False,
            doc = ("Makes this operation a no-op; useful in combination with a 'select' " +
                   "for platforms where the internals of this rule are not properly " +
                   "supported. For known unsupported platforms (e.g. Windows), the " +
                   "rule is always a no-op."),
        ),
    },
    outputs = {
        "filename": "compile_commands.json",
    },
    implementation = _compilation_database_impl,
)
