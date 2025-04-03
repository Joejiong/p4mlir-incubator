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