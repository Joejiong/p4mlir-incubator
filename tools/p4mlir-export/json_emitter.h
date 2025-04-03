/*
Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
    http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#ifndef P4MLIR_JSON_EMITTER_H
#define P4MLIR_JSON_EMITTER_H

#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/OperationSupport.h"
#include "llvm/Support/JSON.h"

namespace P4::P4MLIR {

class JsonEmitter {
public:
  JsonEmitter() = default;
  llvm::json::Value emitModule(mlir::ModuleOp module);

private:
  llvm::json::Value emitOperation(mlir::Operation *op);
  llvm::json::Value emitAttribute(mlir::Attribute attr);
  llvm::json::Value emitType(mlir::Type type);
  llvm::json::Value emitRegion(mlir::Region &region);
  llvm::json::Value emitBlock(mlir::Block &block);
};

} // namespace P4::P4MLIR

#endif // P4MLIR_JSON_EMITTER_H