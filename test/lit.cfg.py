import os
import platform
import lit.formats
import lit.util
from lit.llvm import llvm_config
from lit.llvm.subst import ToolSubst
from lit.llvm.subst import FindTool

# Configuration file for the 'lit' test runner.

# name: The name of this test suite.
config.name = "P4MLIR"

# Check if use_lit_shell exists, fallback to True if not
use_lit_shell = getattr(llvm_config, "use_lit_shell", True)
config.test_format = lit.formats.ShTest(not use_lit_shell)

# suffixes: A list of file extensions to treat as test files.
config.suffixes = [".mlir", ".p4"]

# test_source_root: The root path where tests are located.
config.test_source_root = os.path.dirname(__file__)

# test_exec_root: The root path where tests should be run.
config.test_exec_root = os.path.join(config.p4mlir_obj_root, "test")

config.substitutions.append(("%PATH%", config.environment["PATH"]))
config.substitutions.append(("%shlibext", config.llvm_shlib_ext))

llvm_config.with_system_environment(["HOME", "INCLUDE", "LIB", "TMP", "TEMP"])

llvm_config.use_default_substitutions()

# excludes: A list of directories to exclude from the testsuite. The 'Inputs'
# subdirectories contain auxiliary inputs for various tests in their parent
# directories.
config.excludes = ["Inputs", "Examples", "CMakeLists.txt", "README.txt", "LICENSE.txt"]

# test_exec_root: The root path where tests should be run.
config.test_exec_root = os.path.join(config.p4mlir_obj_root, "test")
config.p4mlir_tools_dir = os.path.join(config.p4mlir_obj_root, "bin")
config.p4mlir_libs_dir = os.path.join(config.p4mlir_obj_root, "lib")

config.substitutions.append(("%p4mlir_libs", config.p4mlir_libs_dir))

# Tweak the PATH to include the tools dir.
llvm_config.with_environment("PATH", config.llvm_tools_dir, append_path=True)

tool_dirs = [config.p4mlir_tools_dir, config.llvm_tools_dir]
tools = [
    "mlir-opt",
    "p4mlir-opt",
    "p4mlir-translate",
    "p4mlir-export-bmv2"
]

llvm_config.add_tool_substitutions(tools, tool_dirs)

llvm_config.with_environment(
    "PYTHONPATH",
    [
        os.path.join(config.mlir_obj_dir, "python_packages", "p4mlir"),
    ],
    append_path=True,
)
