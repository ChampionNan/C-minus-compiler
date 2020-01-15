# lab3-1实验报告

###### 小组成员：

###### PB17111644全映菱（队长）

###### PB17111650陈炳楠 

###### PB17111637张陶竞

## 一、实验要求

1.通过遍历C++语法树各结点，生成LLVM IR。

2.填充访问C++语法树结点的src/cminusc/cminus_builder.cpp中的16个visit函数。

## 二、实验难点

##### 1.全局变量Value *Result的设计：

①在一般情况下，Result中记录的是表达式的值，在visit var中，Result记录的是var的地址。

②对于var的visit函数，我的设计是visit函数执行完毕后，全局变量Result中的值为var的地址；var这个非终结符最终会用于作为赋值语句的左边，这时需要的就是它的地址；也可能被归约成factor，这是需要的是它的值。

③factor作为term的一部分，即乘除运算的一部分或者单独归约成term，那么此时需要的是factor的值，但如果factor不是由var归约而成，那么visit factor之后，得到的就是factor的值；此处我的处理是`node.factor->accept(*this)`之后紧接着判断Result的值是否为指针类型，如果是，说明factor由var归约而成，得到的是var的地址，我需要CreateLoad以获取factor的值。

④对于var结点的设计，我原本的设计是visit var之后就可以获得var的值，这样每一次visit var，我都需要根据找到的var的地址把var的值Load出来；但有些时候我可能需要的只是var的地址，Load操作是多余的，这样产生的.ll代码里每次访问var都会出现很多冗余的Load语句；而在visit var中只获得var的地址，再根据全局变量值的类型判断是否需要Load，代码就比较干净。

##### 2.Simple_expression中出现比较双方类型不匹配的问题

(1)我们在进行某些测试样例的测试时，会出现报错信息说明我们使用CreateIcmp时比较的两边类型不匹配，我们用`getType()->isIntegerTy()`调试发现两边都是Integer类型，猜测可能是出现了i1与i32的比较。

(2)我们在比较之前将左右值进行类型转换，以保证比较双方等长：

```C
auto left_value = builder.CreateIntCast(left,Type::getInt32Ty(context),1);
auto right_value = builder.CreateIntCast(right,Type::getInt32Ty(context),1);
```

##### 3.var中对变量数组元素与形参数组元素的不同处理

(1)在某些测试样例中我们发现在访问数组元素时，如果这个数组是函数形参，就会出现错误。

(2)我们参考了机器生成的.ll代码，发现函数参数为数组时，传入函数的值为i32\*\*类型，访问数组元素时需要将其load出来，得到i32\*类型，再进行index偏移获取数组元素的地址。

(3)在var中，如果var为数组元素(node.expression不为空)，还要判断是否为形参数组，如果是就先Load出来，进行一维访问，否则进行二维访问：

```C
if(var_address->getType()->getPointerElementType()->isArrayTy()){
	element_ptr = builder.CreateInBoundsGEP(var_address,{CONST(0),index});
}
else{
	temp = builder.CreateLoad(var_address);
	//temp = builder.CreateIntCast(temp1,Type::getInt32Ty(context),1);
	element_ptr = builder.CreateInBoundsGEP(temp,index);
}
```

##### 4.var中判断数组index是否小于0时比较双方类型不匹配问题

(1)与simple_expression中出现的比较双方类型不匹配的bug一样，我们把index转换为i32类型即可：

```C
auto index1 = builder.CreateIntCast(index,Type::getInt32Ty(context),1);
auto icmp = builder.CreateICmpSLT(index1,CONST(0));
```

##### 5.selection_stmt中if(expression)中expression的处理

(1)我们通过查找资料发现if(expression)的expression应该为i1类型，我们将expression的结果转化为i1类型，此处expression_value_first为直接求出的expression的结果：

```C
Value* expression_value = builder.CreateIntCast(expression_value_first,Type::getInt1Ty(context),true);
```

(2)但我们的某个测试样例中出现这样的情况：

```C
if (a = 7){//此处.ll文件中为br i1 true
	……
}
if (a = 6){//此处.ll文件中br i1 false，是错误的结果
    ……
}
```

我们意识到使用CreateIntCast进行类型转换无法得到我们想要的结果，而实际上我们需要的只是这个expression_value_first是否为0这个结果，以此进行条件跳转；我们把它改成：

```C
Value* expression_value = builder.CreateICmpNE(expression_value_first,CONST(0));
```

即可得到正确的i1结果；在iteration_stmt中也做同样的修改。

##### 6.数组声明的问题

(1)在某个测试样例中，声明局部变量数组之后，我们会对它进行赋值等操作；在运行二进制文件时，发现在对数组操作结束(对数组进行赋值，以及对数组值的输出)之后，却会显示`Segmentation Fault`；但是通过输出我们都发现赋值操作是成功的，说明空间应该是成功分配了的，但显示了非法访问的问题。通过很久的调试以及询问发现是局部变量的数组定义部分是有问题的。

(2)之前的`nullptr`位置写时填入了`CONST(0)`

```C
`val = builder.CreateAlloca(ArrayType::get(TYPE32,number),nullptr,node.id);`
```

这是由于对每一个参数理解不到位导致的，这个问题没有及时发现，导致之后很难去调试。

## 三、实验设计

##### 全局变量的设计：

(1)Value *Result

由于助教提供的实验框架中所有visit函数返回值都是void类型，我们需要使用全局变量来传递在不同节点中生成的值，比如表达式的值；此处我的处理原本是为各表达式的值都定义一个全局变量进行不断赋值与传递，但实际上从程序运行的角度来说，我只需要一个全局变量来记录所有的值，因为使用`accept(*this)`来访问节点以后，当时我得到的就是我需要的值，这个全局变量Result为Value\*类型。

(2)Value *Array_address

Array_address记录的是访问factor之后、如果全局变量Result里的内容为指针（此时factor由var归约，调用了visit var函数，Result为var的地址）、就把这个指针赋值给Array_address；这是为了处理在实现call函数时，如果调用的函数参数为数组，需要传入的是数组的首地址（即数组里index为0的元素的地址），此时就以Array_address为数组地址、获取数组index为0的元素的地址，作为调用函数时的参数。

(3)int number

用来存储调用了num结点的visit后，num的值。

(4)Function *mainFun

用来记录创建的函数，为之后BasicBlock的创建提供方便。

##### 1.void CminusBuilder::visit(syntax_program &node)

开始时不太确定是否需要在新进入一个需要翻译的`scope`，所以暂定为需要进入，在调用完`node`的`declarations`的`visit`之后会退出当前作用域。但之后在测试全局变量的时候发现如果在这时进入了新的区域，`scope`的`in_global()`函数无法判断出它是全局变量部分的定义，所以确定是不需要进入的。

```c
void CminusBuilder::visit(syntax_program &node) {//program结点
    for(int i=0;i<node.declarations.size();i++){
        node.declarations[i]->accept(*this);
    }
}
```

##### 2.void CminusBuilder::visit(syntax_num &node)

在设计访问该结点时，开始时只是将`num`的值转换为llvm作用域中的常数型`(ConstantInt::get(context, APInt(32, num)))`,赋值给函数中需要重复迭代赋值的全局变量`Result`，但之后在变量声明部分，需要得知数组大小的分配，需要int型的数值，所以也定义了全局变量`number`，用来记录NUM的数值，为之后数组空间大小的分配提供方便。

```c
void CminusBuilder::visit(syntax_num &node) {
    ret = CONST(node.value);
    number = node.value;
    Result=CONST(node.value);
}
```

##### 3.void CminusBuilder::visit(syntax_var_declaration &node)

在变量声明部分，需要两种情况：全局变量的定义和局部变量的定义，它们需要相应地做不同的处理。<br>
(1)对于全局变量，需要使用`GlobalVariable`的方法来做内存分配，这里要求对全局变量做初始化，所以需要使用到初始化器`ConstantAggregateZero::get()`，它会将该部分空间的数值全部初始化为0。对于简单的变量，它的类型为`Type *TYPE32 = Type::getInt32Ty(context);`定义的`TYPE32`，所以在初始化器中传入的是该类型；对于数组的分配，首先需要对它的`num`做访问，来得到它的数组空间大小。之后在初始化时传入它的类型`ArrayType::get(TYPE32,number)`，来初始化。<br>
(2)对于局部变量，仅需要采用之前使用过的`builder.CreateAlloca`即可，普通变量和数组注意传入不同的参数。<br>
在变量声明结束之后，需要以<变量名，分配空间的操作的返回值(即地址)>的形式将定义好的变量压进符号表，以供之后的变量查找。

```c
void CminusBuilder::visit(syntax_var_declaration &node) {
    Type *TYPE32 = Type::getInt32Ty(context);
    std::string varname = node.id;
    llvm::Value *val;
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
}
```

##### 4.void CminusBuilder::visit(syntax_fun_declaration &node)

对于函数，我们首先需要通过结点获取每一个参数的类型，将它们存在`Type*`的`vector`中，之后也可以通过结点信息获取函数的返回值类型。之后会通过这些拿到的参数创建函数，并且将创建好函数的值赋给全局变量 `mainFun`，之后`BasicBlock`需要它的值来判断插入在哪一个函数中。在函数定义好之后，会在这里插入函数进入点标志的`BasicBlock::Create(context,"entry",Fun)`来进入函数，并且将函数以<函数名，函数建立的返回值>的形式压入scope。之后我会进入一个新`scope`,在这个scope中压入函数的参数并且调用对`compound_stmt`的访问。在这里需要将参数做空间分配，对于数组需要分配指针类型的空间，为`Type *ARRAYTYPE = Type::getInt32PtrTy(context);`，在空间分配完成之后会将函数的参数通过`builder.CreateStore(args[i],paramval);`指令存在该空间里。由于参数的处理我全部会在函数定义的部分来实现，所以我选择不写`syntax_param &node`的visit函数。

```c
void CminusBuilder::visit(syntax_fun_declaration &node) {
    Type *ARRAYTYPE = Type::getInt32PtrTy(context);
    std::string funname = node.id;
    std::vector<Type *> types;
    for (auto param: node.params){
        if(param->isarray){
            types.push_back(ARRAYTYPE);//what is array type
        }
        else{
            types.push_back(TYPE32);
        }
    }
    Type *RetType;
    if(node.type == TYPE_VOID){
        RetType = Type::getVoidTy(context);
    }
    else if(node.type == TYPE_INT){
        RetType = TYPE32;
    }
    auto Fun = Function::Create(FunctionType::get(RetType,types,false),
                                GlobalValue::LinkageTypes::ExternalLinkage,
                                funname,module.get());
    mainFun = Fun;
    auto bb = BasicBlock::Create(context,"entry",Fun);
    builder.SetInsertPoint(bb);

    if(node.type == TYPE_INT){
        auto ReturnInt = builder.CreateAlloca(TYPE32,nullptr,"returnint");
        Return_value=ReturnInt;
        scope.push(funname,Fun);
    }
    else if(node.type == TYPE_VOID){
        llvm::Value *ReturnVoid = nullptr;
        scope.push(funname,Fun); 
    }

    scope.enter();
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
}

```

##### 5.void CminusBuilder::visit(syntax_compound_stmt &node)

可以通过C-语法看出它会产生`local_declarations`的visit和`statement_list`的visit。需要注意的是这里需要进入新的`scope`，在调用结束后会退出当前的`scope`。

```c
void CminusBuilder::visit(syntax_compound_stmt &node) {
    scope.enter();
    for (auto localdecls:node.local_declarations){
        localdecls->accept(*this);
    }
    for(auto statelists:node.statement_list){
        statelists->accept(*this);
    }
    scope.exit();
}
```

##### 6.void CminusBuilder::visit(syntax_param &node)

留空，在4.void CminusBuilder::visit(syntax_fun_declaration &node)中已说明

##### 7.void CminusBuilder::visit(syntax_expresion_stmt &node) <br />

(1)visit的结点：expresion_stmt

结点包含的信息：

```C
struct syntax_expresion_stmt: syntax_statement {
	virtual void accept(syntax_tree_visitor&) override final;	
    std::shared_ptr<syntax_expression> expression;
 };
```

结点对应产生式：`expression-stmt→expression ; ∣ ;`

C-minus语义：表达式语句由一个可选的表达式（即可以没有表达式）和一个分号组成我们通常使用表达式语句中的表达式计算时产生的副作用，所以这种语句用于赋值和函数调用

(2)设计：判断是否有表达式，若node.expression!=nullptr,则存在表达式，就用accept() visit expression。

##### 8.void CminusBuilder::visit(syntax_selection_stmt &node) <br />

(1)visit的结点：selection_stmt

结点包含的信息：

```C
struct syntax_selection_stmt: syntax_statement {
	virtual void accept(syntax_tree_visitor&) override final;
    std::shared_ptr<syntax_expression> expression;
    std::shared_ptr<syntax_statement> if_statement;
// should be nullptr if no else structure exists  std::shared_ptr<syntax_statement> else_statement;
};
```

结点对应产生式：
`selection-stmt→ if ( expression ) statement ∣ if ( expression ) statement else statement`
​C-minus语义：if语句中的表达式将被求值，若结果为0，则第二个语句执行（如果存在的话），否则第一个语句会执行。

(2)设计：

①用accpt visit if语句中的expression,计算表达式的值，将值存在全局变量中。

②创建三个BasicBlock：trueBB(表达式为真时跳转的BB),elseBB(存在else时，表达式为假时跳转的BB），endBB（跳出selection-stmt）。

③根据表达式的值跳转：

先判断是否有else:若`node.else_statement != nullptr`则存在else,条件跳转到trueBB或elseBB;若不存在else,条件跳转至trueBB或endBB。

④插入BasicBlock,（elseBB只有在`node.else_statement != nullptr`时插入），在trueBB或elseBB里visit statement,BB最后无条件跳转至endBB

⑤若trueBB和elseBB里有return,可能会有如下情况：

```C
if(expression){
	statement-list
	return-stmt
	}
return-stmt
```

```C
if(expression){
	statement-list
	return-stmt
}
else{
	statement-list
	return-stmt
}
```

```c
if(expression){
	statement-list
}
else{
	statement-list
	return-stmt
}
	return-stmt
```

```c
if(expression){
	statement-list
	return-stmt
}
else{
	statement-list
}
return-stmt
```

则上述实现在return之后仍会跳转至endBB，显然是不对的。

解决方法：判断当前的trueBB和falseBB里是否有return，只有没有return时才无条件跳转到endBB。使用`BasicBlock::getTerminator（）`，若返回值为nullptr则说明当前BB没有Terminator,就跳转到endBB,否则不跳转。由于trueBB/elseBB里return-stmt前的statement-list可能改变当前的BB，所以在getTerminator（）前用`builder.GetInsertBlock()`来获得当前插入的BB。

##### 9.void CminusBuilder::visit(syntax_iteration_stmt &node)<br />

(1)visit的结点：iteration_stmt

结点包含的信息：

```C
struct syntax_iteration_stmt: syntax_statement {
	virtual void accept(syntax_tree_visitor&) override final;
    std::shared_ptr<syntax_expression> expression;
    std::shared_ptr<syntax_statement> statement;
};
```

结点对应产生式：`iteration-stmt→while ( expression ) statement`

C-minus语义：while语句是C-中唯一的迭代语句。它执行时，会不断对表达式进行求值，并且在对表达式的求值结果为0前，循环执行下面的语句。

(2)设计：

创建三个BB，condBB（表达式求值），while_bodyBB(循环执行语句），endloopBB(跳出while循环）。无条件跳转至condBB，condBB里visit expression，对表达式求值，结果保存在全局变量，由表达式的值跳转至while_bodyBB或endloopBB, while_bodyBB里visit statement，最后无条件跳转至endloopBB。

##### 10.void CminusBuilder::visit(syntax_return_stmt &node)<br />

(1)visit的结点：return_stmt

结点包含的信息：

```C
struct syntax_return_stmt: syntax_statement {
	virtual void accept(syntax_tree_visitor&) override final;
	// should be nullptr if return void
	std::shared_ptr<syntax_expression> expression;
};
```

结点对应产生式`return-stmt→return ; ∣ return expression ;`

C-minus语义：return语句可以返回值，也可以不返回值。

未声明为void类型的函数必须返回整型值。

return会将程序的控制转移给当前函数的调用者，而main函数的return会使得程序终止

(2)设计：若`node.expression!=nullptr`则有表达式，visit expression,将值存在全局变量中，CreateRet()返回这个值；若`node.expression==nullptr`，则CreateRetVoid()。

##### 11.void CminusBuilder::visit(syntax_var &node)

(1)访问变量的函数，执行完毕后全局变量Result中保存的是var的地址。

(2)如果是普通变量，就是此变量名对应的在符号表中记录的地址；如果是数组元素，就使用CreateInBoundsGEP通过数组首地址与偏移量获得对应的元素地址。

(3)此处涉及判断数组index是否小于0的处理，如果数组索引下标小于0，需要调用neg_idx_except函数；原本我以为直接调用neg_idx_except函数即可，但程序是动态执行的，不可能在.cpp中就完成判断，这就相当于在.cminus文件中存在这样的语句，需要控制流：

```C
if (array_index < 0) {
	neg_idx_except();
}
```

##### 12.void CminusBuilder::visit(syntax_assign_expression &node)

(1)赋值语句处理，首先得到赋值语句中被赋值变量的地址，再得到赋值的表达式的值，将表达式的值存入变量地址即可。

```C
Value *var_address;
node.var->accept(*this);
var_address=Result;
node.expression->accept(*this);//对表达式求值，表达式结果放在全局变量Result中
Value* expression_value=Result;//记录右值
expression_value=Result;
builder.CreateStore(expression_value,var_address);//将表达式的值存入var，即存入变量
```

##### 13.void CminusBuilder::visit(syntax_simple_expression &node)

(1)简单表达式，可能为加法表达式additive_expression，也可能为两个加法表达式的关系运算。

(2)如果simple_expression中的additive_expression_r为空，即说明simple_expression就是加法表达式，而不是关系运算，此时也不用进行赋值，因为Result中保存的是additive_expression_l的值，也是此时simple_expression的值。

```C
node.additive_expression_l->accept(*this);//计算表达式左值的数值，结果存在Result中
```

(3)如果additive_expression_l不为空，说明simple_expression为关系运算，调用虚函数来得到右值，按照node.op的不同与左值进行比较，比较结果赋值给Result，作为simple_expression的值。

```c
node.additive_expression_r->accept(*this);//计算表达式右值，结果存在全局变量Result
```

##### 14.void CminusBuilder::visit(syntax_additive_expression &node)

(1)计算加法表达式，加法表达式可能只有一个term，也可能是`addivitive op term`。

(2)如果node.additive_expression为空，说明additive_expression就是term。

```C
node.term->accept(*this);
```

(4)如果node.additive_expression不为空，说明需要进行计算，通过：

```C
node.additive_expression->accept(*this);
```

得到additive_expression的值，根据node.op的不同进行运算，结果赋值给Result，作为加法表达式的值。

##### 15.void CminusBuilder::visit(syntax_term &node)

(1)term可能为factor，也可能是`term op factor`。

(2)如果是factor，term的值就是factor的值（如果factor由var归约，Result中记录的是var的地址，需要CreateLoad来得到factor的值）。

```C
node.factor->accept(*this);
```

(4)如果是term op factor，计算term的值，再根据node.op与factor的值进行计算即可。

```C
node.term->accept(*this);//计算term的数值
```

##### 16.void CminusBuilder::visit(syntax_call &node)

(1)函数调用，先从符号表中查找函数，然后遍历参数向量计算实参，使用实参向量来Createcall。

```C
llvm::Value *val=scope.find(node.id);
……//遍历参数向量，计算参数向量中的表达式，得到实参向量real_arg
auto call=builder.CreateCall(val,real_arg);//调用函数
```

### 四、实验总结

1.通过这次实验，我们了解到了编译器的中间代码生成部分的具体操作。之前我们实现了词法分析器，语法分析器，这一次我们能通过词法流生成的语法树来生成`LLVM IR`的中间代码。通过不同节点的自顶向下的调用，能将`LLVM IR`的代码生成分配给不同的结点。在中间代码实现时，我们首先需要了解基本的`C++`语法，并且需要对LLVM IR的代码有一定的了解，至少需要学会如何查阅官方文档来实现我们的翻译需求。并且我们对汇编语言也有了更加深入的了解，比如它是如何做内存分配，如何在不同的类型间做出比较，如何传递参数等。我们也掌握了很好的解决问题的方法，比如通过对比`clang -S -emit-llvm xxx.c`指令生成的`LLVM IR`文件与我们自己的`cpp`代码生成的`LLVM IR`文件作出比对，这一途径帮助我们解决了很多不容易观察到的问题。

2.这次实验我们小组从对LLVM IR没有完全理解到完成了整个实验，经历了几天加班加点地写代码与调试；此前lab3-0中我们学习的是对固定代码的翻译，而lab3-1我们需要实现的是对任意语法树的翻译，这个跨度在我们没有实现时显得非常艰难，我们实现之后又发现许多用法我们在lab3-0中已经学习了，但同时也学习了许多新的用法，收获许多LLVM的知识。

3.此次实验为小组实验，我们小组成员各自负责一部分实验内容，分工合作，在一位同学处理控制流的时候其余同学可以先调试其他的问题，并行解决问题，提高实验效率。

### 五、实验反馈

1.我们做实验的时候有一种迷茫、大海捞针的感觉。首先是由于对于LLVM的体系不够熟悉，所以在查找文档时经常会遇到查找不到的情况(对于某个函数到底是属于哪一个模块，或者哪一个类)。其次，虽然这个文档看上去很全面，但是它没有足够的例子和解释，即便是查找到了它也完全不了解怎么用(经常进行尝试和猜测)。而且它的很多用法我们完全不知道它的存在，更不能很好地使用它们(比如类型的判断，之后出现了很多由于类型方面不匹配的问题，让我们完全摸不着头脑)。

2.这个实验作为小组实验，在分工上我们选择的是每个同学负责一部分，这样的分工方式首先确实可以提高效率，每个同学只需要了解自己负责部分的代码；但另一方面，这样一来每个同学就只了解自己负责部分的代码，其余部分就没有足够的时间精力了解，对整个实验内容无法完整掌握。

