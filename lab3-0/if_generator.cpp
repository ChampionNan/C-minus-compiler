#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Verifier.h>

#include <iostream>
#include <memory>

#ifdef DEBUG  // 用于调试信息,大家可以在编译过程中通过" -DDEBUG"来开启这一选项
#define DEBUG_OUTPUT std::cout << __LINE__ << std::endl;  // 输出行号的简单示例
#else
#define DEBUG_OUTPUT
#endif

using namespace llvm;  // 指明命名空间为llvm
#define CONST(num) \
  ConstantInt::get(context, APInt(32, num))  //得到常数值的表示,方便后面多次用到

int main() {
  LLVMContext context;
  Type *TYPE32 = Type::getInt32Ty(context);
  IRBuilder<> builder(context);
  auto module = new Module("if", context);  // module name是什么无关紧要

  // 函数参数类型的vector
  std::vector<Type *> Ints(2, TYPE32);
  // main函数
  auto mainFun = Function::Create(FunctionType::get(TYPE32, false),
                                  GlobalValue::LinkageTypes::ExternalLinkage,
                                  "main", module);
  auto bb = BasicBlock::Create(context, "entry", mainFun);
  builder.SetInsertPoint(bb);

  
  auto temp1 = builder.CreateAlloca(TYPE32);
  auto temp2 = builder.CreateAlloca(TYPE32);
  auto retAlloca = builder.CreateAlloca(TYPE32);
  builder.CreateStore(CONST(2), temp1);
  builder.CreateStore(CONST(1), temp2);

  auto temp1Load = builder.CreateLoad(temp1);
  auto temp2Load = builder.CreateLoad(temp2);
  auto icmp = builder.CreateICmpSGT(temp1Load, temp2Load);

  auto truesgt = BasicBlock::Create(context, "truesgt", mainFun);
  auto falsesgt = BasicBlock::Create(context, "falsesgt", mainFun);
  auto retBB = BasicBlock::Create(context, "retBB", mainFun);
  builder.CreateCondBr(icmp, truesgt, falsesgt);

  builder.SetInsertPoint(truesgt);
  builder.CreateStore(CONST(1), retAlloca);
  builder.CreateBr(retBB);

  builder.SetInsertPoint(falsesgt);
  builder.CreateStore(CONST(0), retAlloca);
  builder.CreateBr(retBB);

  builder.SetInsertPoint(retBB);
  auto retLoad = builder.CreateLoad(retAlloca);
  builder.CreateRet(retLoad);


  builder.ClearInsertionPoint();
  module->print(outs(), nullptr);
  delete module;
  return 0;
}
