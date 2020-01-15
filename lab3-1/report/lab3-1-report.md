7.void CminusBuilder::visit(syntax_expresion_stmt &node) <br />
visit的结点：expresion_stmt<br />
结点包含的信息：<br />struct syntax_expresion_stmt: syntax_statement {  <br />
virtual void accept(syntax_tree_visitor&) override final;<br />  std::shared_ptr<syntax_expression> expression;<br />
 };
<br />
结点对应产生式：expression-stmt→expression ; ∣ ;<br />
C-minus语义：表达式语句由一个可选的表达式（即可以没有表达式）和一个分号组成

我们通常使用表达式语句中的表达式计算时产生的副作用，所以这种语句用于赋值和函数调用
<br />
设计：判断是否有表达式<br />
若node.expression!=nullptr,则存在表达式，就用accept() visit expression。<br />


8.void CminusBuilder::visit(syntax_selection_stmt &node) <br />
visit的结点：selection_stmt<br />
结点包含的信息：struct syntax_selection_stmt: syntax_statement {  <br />
virtual void accept(syntax_tree_visitor&) override final;  <br />std::shared_ptr<syntax_expression> expression;  <br /> std::shared_ptr<syntax_statement> if_statement; <br /> 
// should be nullptr if no else structure exists  std::shared_ptr<syntax_statement> else_statement;<br />
};
<br />
结点对应产生式：
selection-stmt→ if ( expression ) statement ∣ if ( expression ) statement else statement
​<br />
C-minus语义：if语句中的表达式将被求值，若结果为0，则第二个语句执行（如果存在的话），否则第一个语句会执行。
<br />
设计：<br />
1）用accpt visit if语句中的expression,计算表达式的值，将值存在全局变量中。<br />
2）创建三个BasicBlock：trueBB(表达式为真时跳转的BB),elseBB(存在else时，表达式为假时跳转的BB），endBB（跳出selection-stmt）。<br />
3）根据表达式的值跳转：<br />先判断是否有else:若node.else_statement != nullptr则存在else,条件跳转到trueBB或elseBB;若不存在else,条件跳转至trueBB或endBB。<br />
4）插入BasicBlock,（elseBB只有在node.else_statement != nullptr时插入），在trueBB或elseBB里visit statement,BB最后无条件跳转至endBB<br />
5）若trueBB和elseBB里有return,可能会有如下情况：<br />
> if(expression){<br />
>   statement-list<br />
>   return-stmt<br />
> }<br />
> return-stmt<br />


> if(expression){<br />
>   statement-list<br />
>   return-stmt<br />
> }<br />
> else{<br />
> statement-list<br />
> return-stmt<br />
> }<br />

> if(expression){<br />
>   statement-list<br />
> }<br />
> else{<br />
> statement-list<br />
> return-stmt<br />
> }<br />
> return-stmt<br />

>if(expression){<br />
>   statement-list<br />
>   return-stmt<br />
> }<br />
> else{<br />
> statement-list<br />
> }<br />
> return-stmt<br />
 
则上述实现在return之后仍会跳转至endBB，显然是不对的。<br />解决方法：判断当前的trueBB和falseBB里是否有return，只有没有return时才无条件跳转到endBB。使用BasicBlock::getTerminator（），若返回值为nullptr则说明当前BB没有Terminator,就跳转到endBB,否则不跳转。由于trueBB/elseBB里return-stmt前的statement-list可能改变当前的BB，所以在getTerminator（）前用builder.GetInsertBlock()来获得当前插入的BB。


9.void CminusBuilder::visit(syntax_iteration_stmt &node)<br />
visit的结点：iteration_stmt<br />
结点包含的信息：struct syntax_iteration_stmt: syntax_statement {<br />  
virtual void accept(syntax_tree_visitor&) override final;<br />  std::shared_ptr<syntax_expression> expression;<br />   std::shared_ptr<syntax_statement> statement;<br />
};
<br />
结点对应产生式：iteration-stmt→while ( expression ) statement<br />
C-minus语义：while语句是C-中唯一的迭代语句。它执行时，会不断对表达式进行求值，并且在对表达式的求值结果为0前，循环执行执下面的语句。<br />
设计：创建三个BB，condBB（表达式求值），while_bodyBB(循环执行语句），endloopBB(跳出while循环）。无条件跳转至condBB，condBB里visit expression，对表达式求值，结果保存在全局变量，由表达式的值跳转至while_bodyBB或endloopBB, while_bodyBB里visit statement，最后无条件跳转至endloopBB。<br />
10.void CminusBuilder::visit(syntax_return_stmt &node)<br />
visit的结点：return_stmt<br />
结点包含的信息：struct syntax_return_stmt: syntax_statement {  <br />
virtual void accept(syntax_tree_visitor&) override final;  <br />
// should be nullptr if return void  <br />
std::shared_ptr<syntax_expression> expression; <br />
};
<br />
结点对应产生式return-stmt→return ; ∣ return expression ;<br />
C-minus语义：return语句可以返回值，也可以不返回值。<br />

未声明为void类型的函数必须返回整型值。<br />

return会将程序的控制转移给当前函数的调用者，而main函数的return会使得程序终止
<br />
设计：若node.expression!=nullptr则有表达式，visit expression,将值存在全局变量中，CreateRet()返回这个值；若node.expression==nullptr，则CreateRetVoid()。


