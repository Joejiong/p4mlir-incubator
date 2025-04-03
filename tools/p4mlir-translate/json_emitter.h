#ifndef P4MLIR_TOOLS_P4MLIR_TRANSLATE_JSON_EMITTER_H
#define P4MLIR_TOOLS_P4MLIR_TRANSLATE_JSON_EMITTER_H

#include "llvm/Support/JSON.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/Operation.h"
#include "mlir/IR/Attributes.h"
#include "mlir/IR/Types.h"
#include "mlir/IR/Value.h"

namespace P4::P4MLIR {

class JsonEmitter {
public:
    llvm::json::Value emitModule(mlir::ModuleOp module);
    llvm::json::Value emitOperation(mlir::Operation *op);
    llvm::json::Value emitOperands(mlir::Operation *op);
    llvm::json::Value emitResults(mlir::Operation *op);
    llvm::json::Value emitAttributes(mlir::Operation *op);
    llvm::json::Value emitType(mlir::Type type);
    llvm::json::Value emitValue(mlir::Value value);
};

} // namespace P4::P4MLIR

#endif // P4MLIR_TOOLS_P4MLIR_TRANSLATE_JSON_EMITTER_H
