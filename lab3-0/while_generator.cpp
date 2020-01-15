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
  auto module = new Module("while", context);  // module name是什么无关紧要

  // 函数参数类型的vector
  std::vector<Type *> Ints(2, TYPE32);
  // main函数
  auto mainFun = Function::Create(FunctionType::get(TYPE32, false),
                                  GlobalValue::LinkageTypes::ExternalLinkage,
                                  "main", module);
  auto bb = BasicBlock::Create(context, "entry", mainFun);
  builder.SetInsertPoint(bb);


  auto aAlloc = builder.CreateAlloca(TYPE32);
  auto iAlloc = builder.CreateAlloca(TYPE32);
  builder.CreateStore(CONST(10), aAlloc);
  builder.CreateStore(CONST(0), iAlloc);

  auto whileBB = BasicBlock::Create(context, "whileBB", mainFun);
  auto returnBB = BasicBlock::Create(context, "returnBB", mainFun);
  auto compareBB = BasicBlock::Create(context, "compareBB", mainFun);
  builder.CreateBr(compareBB);

  builder.SetInsertPoint(compareBB);
  auto iLoad1 = builder.CreateLoad(iAlloc);
  auto icmp = builder.CreateICmpSLT(iLoad1, CONST(10));
  builder.CreateCondBr(icmp, whileBB, returnBB);

  builder.SetInsertPoint(whileBB);
  auto iLoad = builder.CreateLoad(iAlloc);
  auto addi = builder.CreateNSWAdd(iLoad, CONST(1));
  builder.CreateStore(addi, iAlloc);
  auto iLoad2 = builder.CreateLoad(iAlloc);
  auto aLoad = builder.CreateLoad(aAlloc);
  auto adda = builder.CreateAdd(iLoad2, aLoad);
  builder.CreateStore(adda, aAlloc);
  builder.CreateBr(compareBB);

  builder.SetInsertPoint(returnBB);
  auto returnLoad = builder.CreateLoad(aAlloc);
  builder.CreateRet(returnLoad);

  builder.ClearInsertionPoint();
  module->print(outs(), nullptr);
  delete module;
  return 0;
}
