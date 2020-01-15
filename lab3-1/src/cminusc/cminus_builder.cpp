#include "cminus_builder.hpp"
#include <iostream>

// You can define global variables here
// to store state
using namespace llvm;
LLVMContext context;
//IRBuilder<> builder(context);

#define CONST(num) \
  ConstantInt::get(context, APInt(32, num))

Type *TYPE32 = Type::getInt32Ty(context);

//Value *Additive_expression_value;//加法表达式的数值
//Value *Simple_expression_value;//简单表达式的数值
//Value *Expression_value;//表达式的值
//Value *Term_value;//项的数值
Value *Factor_value;//因数的数值
//Value *Var_address;//变量或数组元素的地址
Value *Result;
Value *Return_value;
int number;//num node's value
Value *ret;//num node's value type 
Function *mainFun;
Value * Array_address;

void CminusBuilder::visit(syntax_program &node) {//program结点
    //std::cout<<"*******enter_program"<<std::endl;
    //scope.enter();//一个全局作用域
    for(int i=0;i<node.declarations.size();i++){
        node.declarations[i]->accept(*this);
    }
    //scope.exit();
    //std::cout<<"*******exit_program"<<std::endl;
}


void CminusBuilder::visit(syntax_num &node) {
    //std::cout<<"*******enter_num"<<std::endl;
    ret = CONST(node.value);
    ////std::cout<<"here8"<<std::endl;
    number = node.value;
    //Expression_value=CONST(node.value);
    ////std::cout<<"here9"<<std::endl;
    Result=CONST(node.value);
    //Factor_value=CONST(node.value);
    //std::cout<<"factor_is_num"<<std::endl;
    //std::cout<<"*******exit_num"<<std::endl;
}

void CminusBuilder::visit(syntax_var_declaration &node) {
    //std::cout<<"*******enter_var_declaration"<<std::endl;
    Type *TYPE32 = Type::getInt32Ty(context);
    std::string varname = node.id;
    llvm::Value *val;
    //is global variable
    if(scope.in_global()){
        if(node.num == nullptr){
            val = new GlobalVariable(*module.get(),
                                    TYPE32,
                                    false,
                                    GlobalVariable::LinkageTypes::ExternalLinkage,
                                    ConstantAggregateZero::get(TYPE32),
                                    varname);
            scope.push(varname,val);
        }
        else{
            node.num->accept(*this);
            val = new GlobalVariable(*module.get(),
                                    ArrayType::get(TYPE32,number),
                                    false,
                                    GlobalVariable::LinkageTypes::ExternalLinkage,
                                    ConstantAggregateZero::get(ArrayType::get(TYPE32,number)),
                                    varname);
            scope.push(varname,val);
        }
    }
    //not global variable definition
    else{
        if(node.num == nullptr){//only one number,int a
            val = builder.CreateAlloca(TYPE32,nullptr,node.id);
            scope.push(varname,val);
        }
        else{//array int a[20]
            node.num->accept(*this);
            val = builder.CreateAlloca(ArrayType::get(TYPE32,number),nullptr,node.id);
            scope.push(varname,val);
        }
    }
    //std::cout<<"*******exit_var_declaration"<<std::endl;
}

void CminusBuilder::visit(syntax_fun_declaration &node) {
    //first push the funname and it's return type-alloc space
    //std::cout<<"*******enter_fun_declaration"<<std::endl;
    Type *ARRAYTYPE = Type::getInt32PtrTy(context);
    std::string funname = node.id;
    //args type is puzzling
    std::vector<Type *> types;
    //pushing params types
    //std::cout<<"*******here_fun1"<<std::endl;
    for (auto param: node.params){
        if(param->isarray){
            types.push_back(ARRAYTYPE);//what is array type
        }
        else{
            types.push_back(TYPE32);
        }
    }
    //std::cout<<"*******here_fun2"<<std::endl;
    Type *RetType;
    //judge return type
    if(node.type == TYPE_VOID){
        RetType = Type::getVoidTy(context);
    }
    else if(node.type == TYPE_INT){
        RetType = TYPE32;
    }
    //std::cout<<"*******here_fun3"<<std::endl;
    auto Fun = Function::Create(FunctionType::get(RetType,types,false),
                                GlobalValue::LinkageTypes::ExternalLinkage,
                                funname,module.get());
    mainFun = Fun;
    //std::cout<<"here_fun4"<<std::endl;
    //push function to the memory
    
    //std::cout<<"here_fun5"<<std::endl;
    auto bb = BasicBlock::Create(context,"entry",Fun);
    builder.SetInsertPoint(bb);

    if(node.type == TYPE_INT){
        //std::cout<<"here_fun_int"<<std::endl;
        auto ReturnInt = builder.CreateAlloca(TYPE32,nullptr,"returnint");
        Return_value=ReturnInt;
        //std::cout<<"here_fun8"<<std::endl;
        scope.push(funname,Fun);
        //std::cout<<"here_fun9"<<std::endl;
    }
    else if(node.type == TYPE_VOID){
        //void function
        llvm::Value *ReturnVoid = nullptr;
        scope.push(funname,Fun); 
    }

    scope.enter();
    //std::cout<<"here_fun6"<<std::endl;
    //std::cout<<"here_fun7"<<std::endl;
    std::vector<Value*> args;
    for(auto arg = Fun->arg_begin();arg != Fun->arg_end();arg++){
        args.push_back(arg);
    }
    Value *paramval;
    int i;
    for (i = 0; i < node.params.size();i++){
        if(node.params[i]->isarray){
            paramval = builder.CreateAlloca(ARRAYTYPE);
        }
        else{
            paramval = builder.CreateAlloca(TYPE32);
        }
        builder.CreateStore(args[i],paramval);
        scope.push(node.params[i]->id,paramval);
    }
    node.compound_stmt->accept(*this);
    scope.exit();
    //std::cout<<"*******exit_fun_declaration"<<std::endl;
}

void CminusBuilder::visit(syntax_param &node) {
    //push params into the scope
    /*
    //std::cout<<"*******enter_param"<<std::endl;
    Type *TYPE32 = Type::getInt32Ty(context);
    Value *paramval;
    std::string param = node.id;
    if(node.isarray){
        //array type,need to alloca pointer memory
        paramval = builder.CreateAlloca(PointerType::get(scope.find(param)->getType(),0));
        scope.push(param,paramval);
    }
    else{
        paramval = builder.CreateAlloca(TYPE32);
        scope.push(param,paramval);
    }
    //builder.CreateStore(scope.find(param),paramval);*/
}

void CminusBuilder::visit(syntax_compound_stmt &node) {
    //std::cout<<"*******enter_compound_stmt"<<std::endl;
    scope.enter();
    for (auto localdecls:node.local_declarations){
        localdecls->accept(*this);
    }
    for(auto statelists:node.statement_list){
        statelists->accept(*this);
    }
    scope.exit();
    //std::cout<<"*******exit_compound_stmt"<<std::endl;
}

//expression-stmt→expression ; ∣ ; 我们通常使用表达式语句中的表达式计算时产生的副作用，所以这种语句用于赋值和函数调用
void CminusBuilder::visit(syntax_expresion_stmt &node) {
    //std::cout<<"*******enter_expression_stmt"<<std::endl;
  if (node.expression!=nullptr)
  {
    node.expression->accept(*this);
  }
    //std::cout<<"*******exit_expression_stmt"<<std::endl;
}
//表达式语句由一个可选的表达式（即可以没有表达式）和一个分号组成,我们通常使用表达式语句中的表达式计算时产生的副作用，所以这种语句用于赋值和函数调用
//selection-stmt→ ​if ( expression ) statement∣ if ( expression ) statement else statement
void CminusBuilder::visit(syntax_selection_stmt &node) {
    //std::cout<<"*******enter_selection_stmt"<<std::endl;
  auto trueBB = BasicBlock::Create(context, "trueBB",mainFun);  // true分支
  auto elseBB = BasicBlock::Create(context, "elseBB", mainFun);
  auto endBB = BasicBlock::Create(context, "endBB", mainFun);
  const Instruction* branch;
  node.expression->accept(*this);
  llvm::Value* expression_value_first=Result;
  //Value* expression_value = builder.CreateIntCast(expression_value_first,Type::getInt1Ty(context),true);
  //Value* expression_value = builder.CreateTruncOrBitCast(expression_value_first,Type::getInt1Ty(context));
  Value* expression_value = builder.CreateICmpNE(expression_value_first,CONST(0));
  if (node.else_statement != nullptr){
    auto br = builder.CreateCondBr(expression_value, trueBB, elseBB);  // 条件BR
  }
  else{
      auto br = builder.CreateCondBr(expression_value,trueBB,endBB);
  }
  
  builder.SetInsertPoint(trueBB);
  //std::cout<<"*******enter_selection_stmt_here"<<std::endl;
  node.if_statement->accept(*this);
  trueBB = builder.GetInsertBlock();
  branch = trueBB->getTerminator();
  if(branch == nullptr){
  //std::cout<<"*******enter_selection_stmt_here2"<<std::endl;
      auto br = builder.CreateBr(endBB);  //无条件BR
  }

  if (node.else_statement != nullptr){
    builder.SetInsertPoint(elseBB);  // falseBB开始
    node.else_statement->accept(*this);
    elseBB = builder.GetInsertBlock();
    branch = elseBB->getTerminator();
    if(branch == nullptr){
       auto br = builder.CreateBr(endBB);  //无条件BR
    }
   }

  builder.SetInsertPoint(endBB);
  //std::cout<<"*******exit_expression_stmt"<<std::endl;
}
//while语句是C-中唯一的迭代语句。它执行时，会不断对表达式进行求值，并且在对表达式的求值结果为0前，循环执行执下面的语句
void CminusBuilder::visit(syntax_iteration_stmt &node) {
    //std::cout<<"*******enter_iteration_stmt"<<std::endl;
  auto condBB = BasicBlock::Create(context, "condBB", mainFun);  // condition分支
  auto while_bodyBB = BasicBlock::Create(context, "while_bodyBB", mainFun);    // true分支
  auto endloopBB = BasicBlock::Create(context, "endloopBB", mainFun);  // false分支
  const Instruction* branch;
  auto br = builder.CreateBr(condBB);

  builder.SetInsertPoint(condBB);  // condBB的开始
  node.expression->accept(*this);
  llvm::Value* expression_value_first=Result;
  Value* expression_value = builder.CreateICmpNE(expression_value_first,CONST(0));
  br = builder.CreateCondBr(expression_value, while_bodyBB, endloopBB);  // 条件BR

  //if(expression_value!=CONST(0)){
  //  br = builder.CreateBr(while_bodyBB);  
  //}
  //else {
  //  br = builder.CreateBr(endloopBB);
  //}
  
 //if(expression_value!=CONST(0)){
  builder.SetInsertPoint(while_bodyBB);  // while_bodyBB的开始
  node.statement->accept(*this);
  while_bodyBB = builder.GetInsertBlock();
  branch = while_bodyBB->getTerminator();
  if(branch == nullptr){
      auto br = builder.CreateBr(condBB);  //无条件BR
  }
 //}

  //if(!expression_value){
    builder.SetInsertPoint(endloopBB); 
  //} // endloopBB的开始
  //std::cout<<"*******exit_iteration_stmt"<<std::endl;
}
//return-stmt→return ; ∣ return expression ;
//return语句可以返回值，也可以不返回值。
//未声明为void\textbf{void}void类型的函数必须返回整型值。
//return会将程序的控制转移给当前函数的调用者，而main\textbf{main}main函数的return会使得程序终止
void CminusBuilder::visit(syntax_return_stmt &node) {
    //std::cout<<"*******enter_return_stmt"<<std::endl;
  if (node.expression!=nullptr)
  {
    node.expression->accept(*this);
    llvm::Value* expression_value=Result;
    builder.CreateRet(expression_value);
  }
  else {
    builder.CreateRetVoid();
  }
  //std::cout<<"*******exit_return_stmt"<<std::endl;
}





//var→ID ∣ ID [ expression]
//var可以是一个整型变量，或者一个取了下标的数组变量。
//一个负的下标会导致程序终止，但是对于上界并不做检查。
void CminusBuilder::visit(syntax_var &node) {//变量结点
    //std::cout<<"*******enter_var"<<std::endl;
    //Value *var_address;
    //std::cout<<"================var_id:"<<node.id<<std::endl;
    Value* var_address=scope.find(node.id);
    Result=var_address;
    if(node.expression!=nullptr){//是数组
        //std::cout<<"================var_id_isarray:"<<node.id<<std::endl;
        node.expression->accept(*this);//获得index
        Value * index=Result;
        Value * temp;
        Value * element_ptr;

        auto indexnextBB = BasicBlock::Create(context,"indexnextBB",mainFun);
        auto errorBB = BasicBlock::Create(context,"errorBB",mainFun);

        auto index1 = builder.CreateIntCast(index,Type::getInt32Ty(context),1);

        auto icmp=builder.CreateICmpSLT(index1,CONST(0));
        //std::cout<<"after_create_BB"<<std::endl;
        auto br=builder.CreateCondBr(icmp,errorBB,indexnextBB);
        builder.SetInsertPoint(errorBB);
        //std::cout<<"insert errorBB"<<std::endl;
        llvm::Value * error=scope.find("neg_idx_except");
        builder.CreateCall(error,{});
        builder.CreateRetVoid();
        builder.SetInsertPoint(indexnextBB);
        
        if(var_address->getType()->getPointerElementType()->isArrayTy()){
            element_ptr = builder.CreateInBoundsGEP(var_address,{CONST(0),index});
        }
        else{
            temp=builder.CreateLoad(var_address);
            //temp = builder.CreateIntCast(temp1,Type::getInt32Ty(context),1);
            element_ptr = builder.CreateInBoundsGEP(temp,index);
        }
        
        Result=element_ptr;
        element_ptr=nullptr;
    }
    //std::cout<<"*******exit_var"<<std::endl;
}



void CminusBuilder::visit(syntax_assign_expression &node) {//赋值语句
    //std::cout<<"*******enter_assign_expression"<<std::endl;
    Value *var_address;
    node.var->accept(*this);
    var_address=Result;
    node.expression->accept(*this);//对表达式求值，表达式结果放在全局变量Result中
    Value* expression_value=Result;//记录右值
    expression_value=Result;
    builder.CreateStore(expression_value,var_address);//将表达式的值存入var，即存入变量
    //Factor_value=Result;
    //std::cout<<"*******exit_assign_expression"<<std::endl;
}



void CminusBuilder::visit(syntax_simple_expression &node) {//简单表达式
    //std::cout<<"*******enter_simple_expression"<<std::endl;
    node.additive_expression_l->accept(*this);//计算表达式左值的数值，结果存在Result中
    ////std::cout<<"here13"<<std::endl;
    if(node.additive_expression_r==nullptr){//没有表达式右值，简单表达式就是加法表达式
        //Simple_expression_value=Additive_expression_value;//简单表达式的值就是加法表达式的值
        ////std::cout<<"here4"<<std::endl;
        //std::cout<<"r_empty"<<std::endl;
        ;
    }
    else{//简单表达式是一个关系运算
        //记录左值
        Value * left=Result;
        node.additive_expression_r->accept(*this);//计算表达式右值，结果存在全局变量Result
        Value * right=Result;//记录右值


        auto left_value = builder.CreateIntCast(left,Type::getInt32Ty(context),1);
        auto right_value = builder.CreateIntCast(right,Type::getInt32Ty(context),1);
        Value *icmp;
        if(node.op == OP_LE){//<=
            icmp=builder.CreateICmpSLE(left_value,right_value);//如何填写？比较的双方
            //Result=icmp;
        }
        else if(node.op==OP_LT){//<
            icmp=builder.CreateICmpSLT(left_value,right_value);
            //Result=icmp;
        }
        else if(node.op==OP_GT){//>
            icmp=builder.CreateICmpSGT(left_value,right_value);
            //Result=icmp;
        }
        else if(node.op==OP_GE){//>=
            //std::cout<<"Bigger than%%%%%%%%%%%%%%%%"<<std::endl;
                if(left_value->getType()->isIntegerTy()){
                //std::cout<<"left_value is integer"<<std::endl;
            }
            else{
                //std::cout<<"left_error+++++++++++"<<std::endl;
            }
            if(right_value->getType()->isIntegerTy()){
                //std::cout<<"right_value is integer"<<std::endl;
            }
            else{
                //std::cout<<"right_error+++++++++++"<<std::endl;
            }
            
            ////std::cout<<TYPE<<left_value->getType()<<left_value->getValueName()<<std::endl;
            ////std::cout<<"SECOND TYPE"<<right_value->getType()<<right_value->getValueName()<<std::endl;
            icmp=builder.CreateICmpSGE(left,right);
            //Result=icmp;
        }
        else if(node.op==OP_EQ){//==
            //std::cout<<"equal%%%%%%%%%%%%%%%%"<<std::endl;
            icmp=builder.CreateICmpEQ(left_value,right_value);
            //Result=icmp;
        }
        else if(node.op==OP_NEQ){//!=
            icmp=builder.CreateICmpNE(left_value,right_value);
            //Result=icmp;
        }
        Result = builder.CreateIntCast(icmp,Type::getInt32Ty(context),false);
    }
    //Factor_value=Result;
    //std::cout<<"*******exit_simple_expression"<<std::endl;
}

void CminusBuilder::visit(syntax_additive_expression &node) {//加法表达式
    //std::cout<<"*******enter_additive_expression"<<std::endl;
    if(node.additive_expression==nullptr){//加法表达式就是term
        //std::cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@is_term"<<std::endl;
        node.term->accept(*this);
    }
    else{
        node.additive_expression->accept(*this);//计算加法表达式的数值，结果放在Result
        Value * additive_value=Result;//记录加法表达式的数值
        node.term->accept(*this);//计算项的值
        Value * term_value=Result;//记录项的值
        Value *add;
        Value *sub;
        if(node.op==OP_PLUS){
            add=builder.CreateNSWAdd(additive_value,term_value);
            Result=add;
        }
        else if(node.op==OP_MINUS){
            sub=builder.CreateNSWSub(additive_value,term_value);//
            Result=sub;
        }
    }
    //std::cout<<"*******exit_additive_expression"<<std::endl;
}

void CminusBuilder::visit(syntax_term &node) {//项
    //std::cout<<"*******enter_term"<<std::endl;
    Value * factor_value;
    Value * factor_address;
    if(node.term==nullptr){//term只有factor
        node.factor->accept(*this);
        factor_value=Result;
        //factor_value=Factor_value;
        if(factor_value->getType()->isPointerTy()){//factor是var
            //std::cout<<"is_pointer*******************"<<std::endl;
            factor_address=factor_value;
            Array_address=factor_address;
            factor_value=builder.CreateLoad(factor_address);
        }
        Result=factor_value;
    }
    else{//term->term mulop factor
        node.term->accept(*this);//计算term的数值
        Value* term_value=Result;//记录term的数值
        node.factor->accept(*this);
        factor_value=Result;
        //factor_value=Factor_value;
        if(factor_value->getType()->isPointerTy()){//factor是var
            factor_address=factor_value;
            Array_address=factor_address;
            factor_value=builder.CreateLoad(factor_address);
        }
        //int test = term_value->getValue();
        if(node.op == OP_MUL){
            auto mul=builder.CreateNSWMul(term_value,factor_value);//
            //builder.CreateMul
            Result=mul;
        }
        else if(node.op==OP_DIV){
            auto div=builder.CreateSDiv(term_value,factor_value);
            Result=div;
        }
    }
    //std::cout<<"*******exit_term"<<std::endl;
}

void CminusBuilder::visit(syntax_call &node) {//函数调用
    //std::cout<<"*******enter_call"<<std::endl;
    llvm::Value *val=scope.find(node.id);//在符号表中查找函数
    //std::cout<<"here_call_id:"<<node.id<<std::endl;
    //std::vector <llvm::Value*> real_arg(node.args.size());
    std::vector <Value*> real_arg;
    Value * temp;
    Value * element_ptr;
        for(int i=0;i<node.args.size();i++){//计算每个实参
        //std::cout<<"here_i="<<i<<std::endl;
        node.args[i]->accept(*this);
        //std::cout<<"here_i_after_*"<<i<<std::endl;
        //real_arg[i]=Expression_value;
        temp=Result;
        
       if(temp->getType()->isArrayTy()){
            //element_ptr=builder.CreateLoad(temp);
            //std::cout<<"is array&&&&&&&&&&&&&&&&&&&&&&&&"<<std::endl;
            element_ptr=builder.CreateInBoundsGEP(Array_address,{CONST(0),CONST(0)});
            temp=element_ptr;
       }
        real_arg.push_back(temp);
        ////std::cout<<"expression_value="<<Expression_value->getValueID()<<std::endl;
        //std::cout<<"here_i_after"<<i<<std::endl;
        }
        auto call=builder.CreateCall(val,real_arg);//调用函数
        Result=call;
    //}
    //Factor_value=call;
    //std::cout<<"*******exit_call"<<std::endl;
    //如果函数参数是数组怎么传？arg里只有expression类型的表达式向量，expression作为factor的子类，都只有accept函数
    //错误处理：如果函数找不到怎么办？
    //2019.11.24 16:17
}
