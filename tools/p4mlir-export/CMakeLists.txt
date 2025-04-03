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

get_property(dialect_libs GLOBAL PROPERTY MLIR_DIALECT_LIBS)
get_property(conversion_libs GLOBAL PROPERTY MLIR_CONVERSION_LIBS)

set(LIBS
  ${dialect_libs}
  ${conversion_libs}
  
  P4MLIR_P4HIR
  
  MLIRFuncDialect
  MLIROptLib
)

set(P4MLIR_EXPORT_SRCS
  main.cpp
  options.cpp
  p4mlir-export.cpp
  json_emitter.cpp
)

add_llvm_executable(p4mlir-export ${P4MLIR_EXPORT_SRCS})

target_link_libraries(p4mlir-export PRIVATE ${P4C_LIBRARIES} ${P4C_LIB_DEPS})

llvm_update_compile_flags(p4mlir-export)

target_link_libraries(p4mlir-export PRIVATE ${LIBS})

mlir_check_all_link_libraries(p4mlir-export)

add_custom_target(linkp4mlir_export_out
  COMMAND ${CMAKE_COMMAND} -E create_symlink 
          ${P4MLIR_BINARY_DIR}/bin/p4mlir-export 
          ${P4C_BINARY_DIR}/p4mlir-export
  COMMAND ${CMAKE_COMMAND} -E create_symlink 
          ${P4C_BINARY_DIR}/p4include 
          ${CMAKE_CURRENT_BINARY_DIR}/p4include
)

add_dependencies(p4c_driver linkp4mlir_export_out)