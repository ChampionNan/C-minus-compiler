
Lab2实验报告
====
## 姓名：陈炳楠
## 学号：PB17111650
## 1.实验要求
这次实验是需要结合Lab1实现的词法分析器来实现一个语法分析器。
### (1)
首先我们需要根据助教的指导适当调整lab1的代码，将之前我们的实现进
适当的分割，并且在只和lab2相关的代码部分通过助教的示例加上适当
的宏定义以避免与lab1的冲突。
### (2)
之后需要补全`common.c`中的文件遍历函数，来读入C-程序。
### (3)
第三，需要完成语法分析器的语法及其相应的语法树的构建。包括
`token`， `type`， `syntax`， `yyerror`等的实现。
### (4)
最后会将构建好的语法树通过调用助教实现的函数完成输出到文件的操作。

## 2.实验设计
### (1)词法分析器的变动
这里着重需要我们注意的是对`IDENTIFIER`和`NUMBER`的处理。`IDENTIFIER`
在lab1中只是做了简单的识别，在lab2中，我们需要通过语法分析器中的
`union`更准确地得到它的转换后的类型，而不是使用`yylcal`的默认值。
将其通过`strup`转换为`char*`型以便之后语法分析器获取名字。对于
`NUMBER`，我们是明确需要它的 `int`类型数值，所以使用了`atoi`
函数。最后还有对于空白的处理是不需要返回，因为在词法分析器中
没有对应的语法来匹配。如果返回该类`token`，则没有办法继续分析。
### (2)语法分析器的实现
-1.union<br>
我们需要一个联合体来定义我们的终结符，非终结符的类型，来获取它们的值，方便我们语法分析树
的构建。<br>
-2.%token & %type<br>
我们需要将终结符，非终结符在文件开头做出定义，重要的是非终结符的
声明中的类型定义，之后在树的建造中类型是`SyntaxTreeNode *`所
以将它们声明为该类型，方便建树。<br>
-3.构建规则<br>
规则是：定义式左侧的非终结符需要新建节点，右侧的终结符需要新建
节点，将右侧的节点全部加入到左侧节点的孩子中。左侧的节点起归约作用
之前没有出现，需要建新节点，右侧的非终结符其实以及是之前归约过的
无需新建，而终结符未出现过，需要新建。<br>
-4.`yyerror`<br>
我在这里调用了`extern`外部变量，借助之前的词法分析器来获取更
详细的信息。<br>
-5.输出语法树的设计<br>
对于需要归约的终结符，为了文件的简洁，使用了相同的临时变量(声明为全局变量)完成结点的
构造。并且对于同一终结符不同的归约项，将它们放在不同的行，便于我们的阅读。

## 3.实验结果
### (1)输出结果
#### -1.测试样例

```("lab2_array.cminus")
int main(void) {
    int array[1];
    array[f()] = 0;
    return 0;
}

```

#### -2.输出的语法树

```
>--+ program
|  >--+ declaration-list
|  |  >--+ declaration
|  |  |  >--+ fun-declaration
|  |  |  |  >--+ type-specifier
|  |  |  |  |  >--* int
|  |  |  |  >--* main
|  |  |  |  >--* (
|  |  |  |  >--+ params
|  |  |  |  |  >--* void
|  |  |  |  >--* )
|  |  |  |  >--+ compound-stmt
|  |  |  |  |  >--* {
|  |  |  |  |  >--+ local-declarations
|  |  |  |  |  |  >--+ local-declarations
|  |  |  |  |  |  |  >--* epsilon
|  |  |  |  |  |  >--+ var-declaration
|  |  |  |  |  |  |  >--+ type-specifier
|  |  |  |  |  |  |  |  >--* int
|  |  |  |  |  |  |  >--* array
|  |  |  |  |  |  |  >--* [
|  |  |  |  |  |  |  >--* 1
|  |  |  |  |  |  |  >--* ]
|  |  |  |  |  |  |  >--* ;
|  |  |  |  |  >--+ statement-list
|  |  |  |  |  |  >--+ statement-list
|  |  |  |  |  |  |  >--+ statement-list
|  |  |  |  |  |  |  |  >--* epsilon
|  |  |  |  |  |  |  >--+ statement
|  |  |  |  |  |  |  |  >--+ expression-stmt
|  |  |  |  |  |  |  |  |  >--+ expression
|  |  |  |  |  |  |  |  |  |  >--+ var
|  |  |  |  |  |  |  |  |  |  |  >--* array
|  |  |  |  |  |  |  |  |  |  |  >--* [
|  |  |  |  |  |  |  |  |  |  |  >--+ expression
|  |  |  |  |  |  |  |  |  |  |  |  >--+ simple-expression
|  |  |  |  |  |  |  |  |  |  |  |  |  >--+ additive-expression
|  |  |  |  |  |  |  |  |  |  |  |  |  |  >--+ term
|  |  |  |  |  |  |  |  |  |  |  |  |  |  |  >--+ factor
|  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  >--+ call
|  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  >--* f
|  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  >--* (
|  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  >--+ args
|  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  >--* epsilon
|  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  >--* )
|  |  |  |  |  |  |  |  |  |  |  >--* ]
|  |  |  |  |  |  |  |  |  |  >--* =
|  |  |  |  |  |  |  |  |  |  >--+ expression
|  |  |  |  |  |  |  |  |  |  |  >--+ simple-expression
|  |  |  |  |  |  |  |  |  |  |  |  >--+ additive-expression
|  |  |  |  |  |  |  |  |  |  |  |  |  >--+ term
|  |  |  |  |  |  |  |  |  |  |  |  |  |  >--+ factor
|  |  |  |  |  |  |  |  |  |  |  |  |  |  |  >--* 0
|  |  |  |  |  |  |  |  |  >--* ;
|  |  |  |  |  |  >--+ statement
|  |  |  |  |  |  |  >--+ return-stmt
|  |  |  |  |  |  |  |  >--* return
|  |  |  |  |  |  |  |  >--+ expression
|  |  |  |  |  |  |  |  |  >--+ simple-expression
|  |  |  |  |  |  |  |  |  |  >--+ additive-expression
|  |  |  |  |  |  |  |  |  |  |  >--+ term
|  |  |  |  |  |  |  |  |  |  |  |  >--+ factor
|  |  |  |  |  |  |  |  |  |  |  |  |  >--* 0
|  |  |  |  |  |  |  |  >--* ;
|  |  |  |  |  >--* }

```


### (2)函数调用的先后次序及对应的产生式
每当词法分析器传过来一个`token`时便会调用`yyparse()`函数来匹配产生式。
表达式左侧的是右边产生式需要归约到的非终结符（建立新节点），右边的终结符（建立新节点）和非终结符会作为子节点归约到左边。<br>
该示例程序有一个`main`函数，其中调用了`f()`函数。整个程序使用的产生式与语法树相对应的如下:<br>
program → declaration-list<br>
declaration-list → declaration<br>
declaration → fun-declaration<br>
fun-declaration → type-specifier ID ( params ) compound-stmt<br>
type-specifier → int<br>
params → void<br>
compound-stmt → { local-declaration statement-list }<br>
local-declarations → local-declarations var-declaration<br>
local-declarations → empty<br>
var-declaration → type-specifer ID [ NUM ] ;<br>
type-specifier → int<br>
statement-list → statement-list statement<br>
statement-list → statement-list statement<br>
statement-list → empty<br>
statement → expression-stmt<br>
expression-stmt → expression ; <br>
expression → var = expression <br>
var → ID [ expression ]<br>
expression → simple-expression <br>
simple-expression → additive-expression <br>
additive-expression → term<br>
term → factor<br>
factor → call<br>
call → ID ( args )<br>
args → empty<br>
expression → simple-expression<br>
simple-expression → additive-expression<br>
additive-expression → term <br>
term → factor<br>
factor → NUM<br>
statement → return-stmt<br>
return-stmt → return expression ; <br>
expression → simple-expression<br>
simple-expression → additive-expression<br>
additive-expression → term<br>
term → factor<br>
factor → NUM <br>

## 4.实验难点(有很多细节上的问题)
### (1)终结符返回问题
开始时并没有很理解词法分析器返回`token`的意义，于是对于`comment`,
空白符等也做出返回，但它们不参与匹配，会导致无法进行；并且起初我以为
对于`IDENTIFIER`和`NUMBER`来说，转换好类型即可，无序返回，但其实还是
需要进行匹配，只是我们会拿到合适的值。这个点当时困扰了我很久。(这个之后会由于
输出空节点导致`Segmentation Fault`)
### (2)终结符声明的问题
当时以为终结符只需声明即可，便没有在意顺序，但导致了分析错误。之后
在同学的指导下比对了词法分析器头文件的`token`顺序，发现有很大的
问题，并且同时也生成了`*.output`文件来比对。算是学会了找问题的
一种方法，但状态很多，并不是很会用那个分析。
### (3)语法树构建的问题
起初并没有很明白树的形成原理，只是一味地生成新节点，加入左边节点，
后来才明白了基于LALR的语法树的实现步骤。
### (4)初始准备的报错
对于树节点的声明类似`SyntaxTreeNode *tempo;`，无法成功跑通
`make`操作，通过`issue`上同学的帮助，将其改为`struct _SyntaxTreeNode *tempo;`
成功通过。之前我有尝试找出`circular dependency`但没有效果。
### (5)错误位置
对于错误点我导入了行数，起始和终结位置。但我感觉助教给的模版中
对于comment的匹配无法完成其中行数的正确计算？
### (6)移进归约冲突
通过学习，得知移进和归约冲突需要重新定义语法的优先级来实现。<br>
下面挑出几种情况尝试解决。<br>
#### -1. selection-stmt 相关(学习issue#62)
selection-stmt的两种归约方式：<br>
*selection-stmt → `if` `(` expression `)` statement 
    | `if` `(` expression `)` statement `else` statement<br>
```
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE
… 
%%
…
Stmt : IF ( Exp ) Stmt  %prec LOWER_THAN_ELSE
    |IF ( Exp ) Stmt ELSE Stmt
```
在这里提前声明了ELSE的优先级高于LOWER_THAN_ELSE，无方向上的结合性，所以当遇到冲突时
会优先匹配IF-ELSE的情况。这样便解决了关于selention-stmt的冲突。

#### -2.var相关
var的两种归约方式：var → `ID` | `ID` `[` expression `]`<br>
```
%nonassoc LOWER_THAN_LB
%nonassoc LBRACKET
var → ID %prec LOWER_THAN_LB
    | ID LBRACKET expression RBRACKET
```
这样在遇到冲突时会首选var → ID LBRACKET expression RBRACKET, 避免了冲突。
## 5.实验总结
总体来时实验的操作难度并没有很大，但很耗时间和精力，由于以下几点：<br>
### (1)bison机制完全不了解
开始做实验时，助教只是给了简单的bison示例，但对于完成实验来说是
很不够的，你能很好的借鉴它们的部分，但如果你想在出错时很快找到
错误点，那么你需要很好的了解到bison究竟是如何与flex对接的，bison
中的一些结构是怎么使用的。
### (2)编译环境不同产生的问题
对于树的声明当时make提示找不到，很是困惑，那个问题很难解决，如果没有
在issue上提出的话，并且好像也不是所有人有这样的问题，这令我很奇怪。
### (3)很难debug
作为一个类似工程的项目，在没有很了解机制下真是太难找到出错点了，并且
各个文件的包含关系也让我晕头转向。
### (4)segmentation fault
我开始时遇到的segmentation fault是由于输出空白节点所导致的，之后看到同学有由于union
中的字符串类型的使用未分配空间导致的。这种报错可能的情况很多，点也很多，不好分析。
## 6.实验反馈
### (1)教程方面的完善
#### -1.教程上的详细化
助教可能觉得会简单，所以在每次讲授时还是很简练。但简单的讲解可能导致的结果
就是不会记得助教讲过什么，得之后通过零零散散的助教提供的教程自我学习。
但有时候网上的教程会由于环境的不同而产生一些很难debug的奇怪问题。<br>
#### -2.教程指导的顺序化
开始时对于阅读的教程、操作的顺序不是很明白，不太清楚从什么地方开始。
助教最好能将零散的教程汇集起来，系统一点。让我们清楚地明白操作的顺序。
### (2)commits的减少
希望助教之后能更加完善工程的结构和测试的样本，频繁的commits来更新文件变得有些麻烦。比如
助教在开始时设置的文件个数是10，当测试文件后来变多时导致了文件名的错乱，后来才意识到
是由于个数过少导致的问题。之后发现助教已经更改过这个地方，但我并没有更新。
### 最后，助教对于我们一直是很包容，对于我们的反馈也积极的响应，谢谢助教！

