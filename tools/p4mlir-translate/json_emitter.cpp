#include "json_emitter.h"
#include "p4mlir/Dialect/P4HIR/P4HIR_Attrs.h"
#include "p4mlir/Dialect/P4HIR/P4HIR_Dialect.h"
#include "p4mlir/Dialect/P4HIR/P4HIR_Ops.h"
#include "p4mlir/Dialect/P4HIR/P4HIR_OpsEnums.h"
#include "p4mlir/Dialect/P4HIR/P4HIR_Types.h"
#include "llvm/Support/JSON.h"
#include <sstream>

namespace P4::P4MLIR {

llvm::json::Value JsonEmitter::emitModule(mlir::ModuleOp moduleOp) {
    llvm::json::Object moduleObj;

    llvm::errs() << "JsonEmitter: Module has " << std::distance(moduleOp.getBody()->begin(), moduleOp.getBody()->end()) 
                 << " operations\n";
    
    llvm::json::Array operations;
    for (auto &op : moduleOp.getBody()->getOperations()) {
        // print each operation
        llvm::errs() << "JsonEmitter: Processing operation: " << op.getName() << "\n";
        operations.push_back(emitOperation(&op));
    }
    moduleObj["operations"] = llvm::json::Value(std::move(operations));
    
    return llvm::json::Value(std::move(moduleObj));
}

llvm::json::Value JsonEmitter::emitOperation(mlir::Operation* op) {
    llvm::json::Object j;
    j["name"] = llvm::json::Value(op->getName().getStringRef().str());
    
    llvm::errs() << "JsonEmitter: Emitting operation " << op->getName() << "\n";
    
    j["operands"] = emitOperands(op);
    j["results"] = emitResults(op);
    j["attributes"] = emitAttributes(op);
    
    return llvm::json::Value(std::move(j));
}

llvm::json::Value JsonEmitter::emitOperands(mlir::Operation* op) {
    llvm::json::Array j;
    llvm::errs() << "JsonEmitter: Emitting " << op->getNumOperands() << " operands\n";
    
    for (auto operand : op->getOperands()) {
        j.push_back(emitValue(operand));
    }
    return llvm::json::Value(std::move(j));
}

llvm::json::Value JsonEmitter::emitResults(mlir::Operation* op) {
    llvm::json::Array j;
    llvm::errs() << "JsonEmitter: Emitting " << op->getNumResults() << " results\n";
    
    for (auto result : op->getResults()) {
        j.push_back(emitValue(result));
    }
    return llvm::json::Value(std::move(j));
}

llvm::json::Value JsonEmitter::emitAttributes(mlir::Operation* op) {
    llvm::json::Object j;    
    llvm::errs() << "JsonEmitter: Processing " << op->getAttrs().size() << " attributes for: " << op->getName() << "\n";
    for (auto attr : op->getAttrs()) {
        llvm::errs() << "  Attribute: " << attr.getName() << "\n";
            if (attr.getName() == "value" && op->getName().getStringRef() == "p4hir.const") {

            if (auto boolAttr = attr.getValue().dyn_cast<P4::P4MLIR::P4HIR::BoolAttr>()) {
                llvm::errs() << "    Found BoolAttr with value: " << (boolAttr.getValue() ? "true" : "false") << "\n";

                if (boolAttr.getValue()) {
                    j[attr.getName().str()] = llvm::json::Value("#true");
                } else {
                    j[attr.getName().str()] = llvm::json::Value("#p4hir.bool<false>");
                }
                continue;
            } else {
                llvm::errs() << "    Attribute kind: ";
                attr.getValue().dump();
                llvm::errs() << "\n";
            
                std::string attrStr;
                llvm::raw_string_ostream attrOS(attrStr);
                attr.getValue().print(attrOS);
                
                llvm::errs() << "    String representation: " << attrOS.str() << "\n";
                
                // hardcode textual for now
                j[attr.getName().str()] = llvm::json::Value(attrOS.str());
                continue;
            }
        }
        
        // normal attribute handling 
        if (auto intAttr = attr.getValue().dyn_cast<mlir::IntegerAttr>()) {
            j[attr.getName().str()] = llvm::json::Value(intAttr.getInt());
        } else if (auto strAttr = attr.getValue().dyn_cast<mlir::StringAttr>()) {
            j[attr.getName().str()] = llvm::json::Value(strAttr.getValue().str());
        } else if (auto typeAttr = attr.getValue().dyn_cast<mlir::TypeAttr>()) {
            j[attr.getName().str()] = emitType(typeAttr.getValue());
        } else if (auto arrayAttr = attr.getValue().dyn_cast<mlir::ArrayAttr>()) {
            llvm::json::Array arrayJson;
            for (auto elem : arrayAttr) {
                if (auto elemInt = elem.dyn_cast<mlir::IntegerAttr>()) {
                    arrayJson.push_back(llvm::json::Value(elemInt.getInt()));
                } else if (auto elemStrAttr = elem.dyn_cast<mlir::StringAttr>()) {
                    arrayJson.push_back(llvm::json::Value(elemStrAttr.getValue().str()));
                } else {
                    // other attribute types to string representation
                    std::string elemPrintStr;
                    llvm::raw_string_ostream elemOS(elemPrintStr);
                    elem.print(elemOS);
                    arrayJson.push_back(llvm::json::Value(elemOS.str()));
                }
            }
            j[attr.getName().str()] = llvm::json::Value(std::move(arrayJson));
        } else {
            // Fallback for other attribute types
            std::string attrStr;
            llvm::raw_string_ostream attrOS(attrStr);
            attr.getValue().print(attrOS);
            j[attr.getName().str()] = llvm::json::Value(attrOS.str());
        }
    }
    
    return llvm::json::Value(std::move(j));
}

llvm::json::Value JsonEmitter::emitType(mlir::Type type) {

    llvm::errs() << "JsonEmitter: Processing type: " << type << "\n";
    
    // hardcoded p4hir boolean type
    if (auto boolType = type.dyn_cast<P4::P4MLIR::P4HIR::BoolType>()) {
        llvm::errs() << "  Found BoolType\n";
        return llvm::json::Value("!p4hir.bool");
    }
    
    // for other p4hir types, use string representation
    std::string typeStr;
    llvm::raw_string_ostream typeOS(typeStr);
    type.print(typeOS);
    return llvm::json::Value(typeOS.str());
}

llvm::json::Value JsonEmitter::emitValue(mlir::Value value) {
    if (!value) {
        return llvm::json::Value(nullptr);
    }
    
    llvm::json::Object j;
    if (auto blockArg = value.dyn_cast<mlir::BlockArgument>()) {
        j["type"] = llvm::json::Value("block_argument");
        j["arg_number"] = llvm::json::Value(static_cast<int64_t>(blockArg.getArgNumber()));
        j["value_type"] = emitType(value.getType());
    } else if (auto opResult = value.dyn_cast<mlir::OpResult>()) {
        j["type"] = llvm::json::Value("op_result");
        j["result_number"] = llvm::json::Value(static_cast<int64_t>(opResult.getResultNumber()));
        j["value_type"] = emitType(value.getType());
    } else {
        return emitType(value.getType());
    }
    
    return llvm::json::Value(std::move(j));
}

} // namespace P4::P4MLIR
