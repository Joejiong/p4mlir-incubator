#include "json_emitter.h"
#include "p4mlir/Dialect/P4HIR/P4HIR_Dialect.h"
#include "llvm/Support/JSON.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm::json;

namespace P4::P4MLIR {

llvm::json::Value JsonEmitter::emitModule(mlir::ModuleOp module) {
  Object moduleObj;
  moduleObj["type"] = "module";
  moduleObj["name"] = module.getName() ? module.getName()->str() : "";
  
  Array operations;
  for (auto &op : module.getOps()) {
    operations.push_back(emitOperation(&op));
  }
  moduleObj["operations"] = std::move(operations);
  
  return moduleObj;
}

llvm::json::Value JsonEmitter::emitOperation(mlir::Operation *op) {
  Object opObj;
  opObj["name"] = op->getName().getStringRef().str();
  
  // 处理操作的属性
  Object attrs;
  for (auto namedAttr : op->getAttrs()) {
    attrs[namedAttr.getName().str()] = emitAttribute(namedAttr.getValue());
  }
  opObj["attributes"] = std::move(attrs);
  
  // 处理操作的类型
  Array resultTypes;
  for (auto type : op->getResultTypes()) {
    resultTypes.push_back(emitType(type));
  }
  opObj["result_types"] = std::move(resultTypes);
  
  // 处理操作的区域
  Array regions;
  for (auto &region : op->getRegions()) {
    regions.push_back(emitRegion(region));
  }
  opObj["regions"] = std::move(regions);
  
  return opObj;
}

llvm::json::Value JsonEmitter::emitAttribute(mlir::Attribute attr) {
  Object attrObj;
  
  // 根据属性类型处理不同类型的属性
  if (auto strAttr = attr.dyn_cast<mlir::StringAttr>()) {
    attrObj["value"] = strAttr.getValue().str();
    attrObj["type"] = "string";
  } else if (auto intAttr = attr.dyn_cast<mlir::IntegerAttr>()) {
    attrObj["value"] = std::to_string(intAttr.getInt());
    attrObj["type"] = "integer";
  } else {
    // 默认情况，尝试将属性转换为字符串
    std::string attrStr;
    llvm::raw_string_ostream os(attrStr);
    attr.print(os);
    attrObj["value"] = os.str();
    attrObj["type"] = "unknown";
  }
  
  return attrObj;
}

llvm::json::Value JsonEmitter::emitType(mlir::Type type) {
  Object typeObj;
  typeObj["dialect"] = type.getDialect().getNamespace().str();
  
  // 将类型转换为字符串表示
  std::string typeStr;
  llvm::raw_string_ostream os(typeStr);
  type.print(os);
  typeObj["value"] = os.str();
  
  return typeObj;
}

llvm::json::Value JsonEmitter::emitRegion(mlir::Region &region) {
  Object regionObj;
  
  Array blocks;
  for (auto &block : region) {
    blocks.push_back(emitBlock(block));
  }
  regionObj["blocks"] = std::move(blocks);
  
  return regionObj;
}

llvm::json::Value JsonEmitter::emitBlock(mlir::Block &block) {
  Object blockObj;
  
  Array arguments;
  for (auto &arg : block.getArguments()) {
    Object argObj;
    argObj["type"] = emitType(arg.getType());
    arguments.push_back(std::move(argObj));
  }
  blockObj["arguments"] = std::move(arguments);
  
  Array operations;
  for (auto &op : block.getOperations()) {
    operations.push_back(emitOperation(&op));
  }
  blockObj["operations"] = std::move(operations);
  
  return blockObj;
}

} // namespace P4::P4MLIR