%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./common/common.h"
#include "./syntax_tree/SyntaxTree.h"


#include "./lab1_lexical_analyzer/lexical_analyzer.h"

/*
%code requires{
	#include "./syntax_tree/SyntaxTree.h"
}*/

// external functions from lex
extern int yylex();
extern int yyparse();
extern int yyrestart();
extern FILE * yyin;
//extern YYSTYPE yylval;

// external variables from lexical_analyzer module
extern int lines;
extern int pos_start;
extern int pos_end;
extern char * yytext;
//int tempo_value; no need to get the return value

// Global syntax tree.

struct _SyntaxTree * gt;
//SyntaxTree *gt;
struct _SyntaxTreeNode *tempo;
//SyntaxTreeNode *tempo;

void yyerror(const char * s);
%}

%union {
    int num;
    char name[100];
    struct _SyntaxTreeNode *node;
    //SyntaxTreeNode *node;
/********** TODO: Fill in this union structure *********/
};

/********** TODO: Your token definition here ***********/
%token<name> ERROR ADD SUB MUL DIV LT LTE GT GTE EQ NEQ ASSIGN SEMICOLON
%token<name> COMMA LPARENTHESE RPARENTHESE LBRACKET RBRACKET LBRACE RBRACE
%token<name> ELSE IF INT RETURN VOID WHILE 
%token<name>IDENTIFIER
%token<num> NUMBER
%token<name> ARRAY LETTER 
%token EOL COMMENT BLANK

%type<node> program
%type<node> declaration-list
%type<node> declaration
%type<node> var-declaration
%type<node> fun-declaration
%type<node> type-specifier /*UNCERTAINTY*/
%type<node> params
%type<node> param-list
%type<node> param
%type<node> compound-stmt
%type<node> local-declarations
%type<node> statement-list
%type<node> statement
%type<node> expression-stmt
%type<node> selection-stmt
%type<node> iteration-stmt
%type<node> return-stmt
%type<node> expression
%type<node> var
%type<node> simple-expression
%type<node> relop
%type<node> additive-expression
%type<node> addop
%type<node> term
%type<node> mulop
%type<node> factor
%type<node> call
%type<node> args
%type<node> arg-list

/*优先级的定义，可能之后会加上IF ELSE的优先级判断类型*/

/* compulsory starting symbol */
%start program

%%
/*************** TODO: Your rules here *****************/
program :declaration-list{
						$$ = newSyntaxTreeNode("program");
						gt->root = $$;
						SyntaxTreeNode_AddChild($$, $1);
						};
declaration-list:declaration-list declaration{
	$$ = newSyntaxTreeNode("declaration-list");
	SyntaxTreeNode_AddChild($$, $1);
	SyntaxTreeNode_AddChild($$, $2);
}
				| declaration{
					$$ = newSyntaxTreeNode("declaration-list");
					SyntaxTreeNode_AddChild($$, $1);
				};

declaration:var-declaration{
	$$ = newSyntaxTreeNode("declaration");
	SyntaxTreeNode_AddChild($$, $1);
}
			| fun-declaration{
				$$ = newSyntaxTreeNode("declaration");
				SyntaxTreeNode_AddChild($$, $1);
			};

var-declaration:type-specifier IDENTIFIER SEMICOLON{
	$$ = newSyntaxTreeNode("var-declaration");
	SyntaxTreeNode_AddChild($$, $1);
	tempo = newSyntaxTreeNode($2);
	SyntaxTreeNode_AddChild($$, tempo);
	tempo = newSyntaxTreeNode(";");
	SyntaxTreeNode_AddChild($$, tempo);
}
				| type-specifier IDENTIFIER LBRACKET NUMBER RBRACKET SEMICOLON{
					$$ = newSyntaxTreeNode("var-declaration");
					SyntaxTreeNode_AddChild($$, $1);
					tempo = newSyntaxTreeNode($2);
					SyntaxTreeNode_AddChild($$, tempo);
					tempo = newSyntaxTreeNode("[");
					SyntaxTreeNode_AddChild($$, tempo);
					tempo = newSyntaxTreeNodeFromNum($4);
					SyntaxTreeNode_AddChild($$, tempo);
					tempo = newSyntaxTreeNode("]");
					SyntaxTreeNode_AddChild($$, tempo);
					tempo = newSyntaxTreeNode(";");
					SyntaxTreeNode_AddChild($$, tempo);
				};
type-specifier: INT{
	$$ = newSyntaxTreeNode("type-specifier");
	tempo = newSyntaxTreeNode("int");
	SyntaxTreeNode_AddChild($$, tempo);
	//printf("!!Meet int\n");
	// printf("Tempo-name:%s\n", tempo->name);
	//printf("Temporary ok\n");
}
				| VOID{
					$$ = newSyntaxTreeNode("type-specifier");
					tempo = newSyntaxTreeNode("void");
					SyntaxTreeNode_AddChild($$, tempo);
				};
fun-declaration:type-specifier IDENTIFIER LPARENTHESE params RPARENTHESE compound-stmt{
	$$ = newSyntaxTreeNode("fun-declaration");
	SyntaxTreeNode_AddChild($$, $1);
	tempo = newSyntaxTreeNode($2);
	SyntaxTreeNode_AddChild($$, tempo);
	tempo = newSyntaxTreeNode("(");
	SyntaxTreeNode_AddChild($$, tempo);
	SyntaxTreeNode_AddChild($$, $4);
	tempo = newSyntaxTreeNode(")");
	SyntaxTreeNode_AddChild($$, tempo);
	SyntaxTreeNode_AddChild($$, $6);
	//printf("!!Meet fun-declaration\n");
};
params:param-list{
	$$ = newSyntaxTreeNode("params");
	SyntaxTreeNode_AddChild($$, $1);
	//printf("!!Meet params\n");
}
				| VOID{
					$$ = newSyntaxTreeNode("params");
					tempo = newSyntaxTreeNode("void");
					SyntaxTreeNode_AddChild($$, tempo);
				};
param-list:param-list COMMA param{
	$$ = newSyntaxTreeNode("param-list");
	SyntaxTreeNode_AddChild($$, $1);
	tempo = newSyntaxTreeNode(",");
	SyntaxTreeNode_AddChild($$, tempo);
	SyntaxTreeNode_AddChild($$, $3);
	//printf("!!Meet param-list\n");
}
			| param{
				$$ = newSyntaxTreeNode("param-list");
				SyntaxTreeNode_AddChild($$, $1);
				//printf("!!Meet param-list\n");
			};
param:type-specifier IDENTIFIER{
	$$ = newSyntaxTreeNode("param");
	SyntaxTreeNode_AddChild($$, $1);
	tempo = newSyntaxTreeNode($2);
	SyntaxTreeNode_AddChild($$, tempo);
	//printf("!!Meet param1\n");
}
				| type-specifier IDENTIFIER ARRAY{
					$$ = newSyntaxTreeNode("param");
					SyntaxTreeNode_AddChild($$, $1);
					tempo = newSyntaxTreeNode($2);
					SyntaxTreeNode_AddChild($$, tempo);
					tempo = newSyntaxTreeNode("[]");
					SyntaxTreeNode_AddChild($$, tempo);
					//printf("!!Meet param2\n");
				};
compound-stmt:LBRACE local-declarations statement-list RBRACE{
	$$ = newSyntaxTreeNode("compound-stmt");
	tempo = newSyntaxTreeNode("{");
	SyntaxTreeNode_AddChild($$, tempo);
	SyntaxTreeNode_AddChild($$, $2);
	SyntaxTreeNode_AddChild($$, $3);
	tempo = newSyntaxTreeNode("}");
	SyntaxTreeNode_AddChild($$, tempo);
};
local-declarations:local-declarations var-declaration{
	$$ = newSyntaxTreeNode("local-declarations");
	SyntaxTreeNode_AddChild($$, $1);
	SyntaxTreeNode_AddChild($$, $2);
}
				| /*empty*/{
	$$ = newSyntaxTreeNode("local-declarations");
	tempo = newSyntaxTreeNode("epsilon");
	SyntaxTreeNode_AddChild($$, tempo);
};
statement-list:statement-list statement{
	$$ = newSyntaxTreeNode("statement-list");
	SyntaxTreeNode_AddChild($$, $1);
	SyntaxTreeNode_AddChild($$, $2);
}
				| /*empty*/{
	$$ = newSyntaxTreeNode("statement-list");
	tempo = newSyntaxTreeNode("epsilon");
	SyntaxTreeNode_AddChild($$, tempo);
};
statement:expression-stmt{
	$$ = newSyntaxTreeNode("statement");
	SyntaxTreeNode_AddChild($$, $1);
}
		| compound-stmt{
			$$ = newSyntaxTreeNode("statement");
			SyntaxTreeNode_AddChild($$, $1);
		}
		| selection-stmt{
			$$ = newSyntaxTreeNode("statement");
			SyntaxTreeNode_AddChild($$, $1);
		}
		| iteration-stmt{
			$$ = newSyntaxTreeNode("statement");
			SyntaxTreeNode_AddChild($$, $1);
		}
		| return-stmt{
			$$ = newSyntaxTreeNode("statement");
			SyntaxTreeNode_AddChild($$, $1);
		};
expression-stmt:expression SEMICOLON{
	$$ = newSyntaxTreeNode("expression-stmt");
	SyntaxTreeNode_AddChild($$, $1);
	tempo = newSyntaxTreeNode(";");
	SyntaxTreeNode_AddChild($$, tempo);
}
				| SEMICOLON{
					$$ = newSyntaxTreeNode("expression-stmt");
					tempo = newSyntaxTreeNode(";");
					SyntaxTreeNode_AddChild($$, tempo);
				};
selection-stmt:IF LPARENTHESE expression RPARENTHESE statement{
	$$ = newSyntaxTreeNode("selection-stmt");
	tempo = newSyntaxTreeNode("if");
	SyntaxTreeNode_AddChild($$, tempo);
	tempo = newSyntaxTreeNode("(");
	SyntaxTreeNode_AddChild($$, tempo);
	SyntaxTreeNode_AddChild($$, $3);
	tempo = newSyntaxTreeNode(")");	
	SyntaxTreeNode_AddChild($$, tempo);
	SyntaxTreeNode_AddChild($$, $5);
}
				| IF LPARENTHESE expression RPARENTHESE statement ELSE statement{
					$$ = newSyntaxTreeNode("selection-stmt");
					tempo = newSyntaxTreeNode("if");
					SyntaxTreeNode_AddChild($$, tempo);
					tempo = newSyntaxTreeNode("(");
					SyntaxTreeNode_AddChild($$, tempo);
					SyntaxTreeNode_AddChild($$, $3);
					tempo = newSyntaxTreeNode(")");	
					SyntaxTreeNode_AddChild($$, tempo);
					SyntaxTreeNode_AddChild($$, $5);
					tempo = newSyntaxTreeNode("else");	
					SyntaxTreeNode_AddChild($$, tempo);
					SyntaxTreeNode_AddChild($$, $7);
				};
iteration-stmt:WHILE LPARENTHESE expression RPARENTHESE statement{
	$$ = newSyntaxTreeNode("iteration-stmt");
	tempo = newSyntaxTreeNode("while");
	SyntaxTreeNode_AddChild($$, tempo);
	tempo = newSyntaxTreeNode("(");
	SyntaxTreeNode_AddChild($$, tempo);
	SyntaxTreeNode_AddChild($$, $3);
	tempo = newSyntaxTreeNode(")");
	SyntaxTreeNode_AddChild($$, tempo);
	SyntaxTreeNode_AddChild($$, $5);
};
return-stmt:RETURN SEMICOLON{
	$$ = newSyntaxTreeNode("return-stmt");
	tempo = newSyntaxTreeNode("return");
	SyntaxTreeNode_AddChild($$, tempo);
	tempo = newSyntaxTreeNode(";");
	SyntaxTreeNode_AddChild($$, tempo);
}
				| RETURN expression SEMICOLON{
					$$ = newSyntaxTreeNode("return-stmt");
					tempo = newSyntaxTreeNode("return");
					SyntaxTreeNode_AddChild($$, tempo);
					SyntaxTreeNode_AddChild($$, $2);
					tempo = newSyntaxTreeNode(";");
					SyntaxTreeNode_AddChild($$, tempo);
				};
expression:var ASSIGN expression{
	$$ = newSyntaxTreeNode("expression");
	SyntaxTreeNode_AddChild($$, $1);
	tempo = newSyntaxTreeNode("=");
	SyntaxTreeNode_AddChild($$, tempo);
	SyntaxTreeNode_AddChild($$, $3);
}
				| simple-expression{
					$$ = newSyntaxTreeNode("expression");
					SyntaxTreeNode_AddChild($$, $1);
				};
var:IDENTIFIER{
	$$ = newSyntaxTreeNode("var");
	tempo = newSyntaxTreeNode($1);
	SyntaxTreeNode_AddChild($$, tempo);
	//printf("!!Meet IDENTIFIER\n");
}
	| IDENTIFIER LBRACKET expression RBRACKET{
		$$ = newSyntaxTreeNode("var");
		tempo = newSyntaxTreeNode($1);
		SyntaxTreeNode_AddChild($$, tempo);
		tempo = newSyntaxTreeNode("[");
		SyntaxTreeNode_AddChild($$, tempo);
		SyntaxTreeNode_AddChild($$, $3);
		tempo = newSyntaxTreeNode("]");
		SyntaxTreeNode_AddChild($$, tempo);
	};
simple-expression:additive-expression relop additive-expression{
	$$ = newSyntaxTreeNode("simple-expression");
	SyntaxTreeNode_AddChild($$, $1);
	SyntaxTreeNode_AddChild($$, $2);
	SyntaxTreeNode_AddChild($$, $3);
}
				| additive-expression{
					$$ = newSyntaxTreeNode("simple-expression");
					SyntaxTreeNode_AddChild($$, $1);
				};
relop:LTE{
	$$ = newSyntaxTreeNode("relop");
	tempo = newSyntaxTreeNode("<=");
	SyntaxTreeNode_AddChild($$, tempo);
}
	| LT{
		$$ = newSyntaxTreeNode("relop");
		tempo = newSyntaxTreeNode("<");
		SyntaxTreeNode_AddChild($$, tempo);
	}
	| GT{
		$$ = newSyntaxTreeNode("relop");
		tempo = newSyntaxTreeNode(">");
		SyntaxTreeNode_AddChild($$, tempo);
	}
	| GTE{
		$$ = newSyntaxTreeNode("relop");
		tempo = newSyntaxTreeNode(">=");
		SyntaxTreeNode_AddChild($$, tempo);
	}
	| EQ{
		$$ = newSyntaxTreeNode("relop");
		tempo = newSyntaxTreeNode("==");
		SyntaxTreeNode_AddChild($$, tempo);
	}
	| NEQ{
		$$ = newSyntaxTreeNode("relop");
		tempo = newSyntaxTreeNode("!=");
		SyntaxTreeNode_AddChild($$, tempo);
	};
additive-expression:additive-expression addop term{
	$$ = newSyntaxTreeNode("additive-expression");
	SyntaxTreeNode_AddChild($$, $1);
	SyntaxTreeNode_AddChild($$, $2);
	SyntaxTreeNode_AddChild($$, $3);
}
				| term{
					$$ = newSyntaxTreeNode("additive-expression");
					SyntaxTreeNode_AddChild($$, $1);
				};
addop:ADD{
	$$ = newSyntaxTreeNode("addop");
	tempo = newSyntaxTreeNode("+");
	SyntaxTreeNode_AddChild($$, tempo);
}
	| SUB{
		$$ = newSyntaxTreeNode("addop");
		tempo = newSyntaxTreeNode("-");
		SyntaxTreeNode_AddChild($$, tempo);
	};
term:term mulop factor{
	$$ = newSyntaxTreeNode("term");
	SyntaxTreeNode_AddChild($$, $1);	
	SyntaxTreeNode_AddChild($$, $2);
	SyntaxTreeNode_AddChild($$, $3);
}
	| factor{
		$$ = newSyntaxTreeNode("term");
		SyntaxTreeNode_AddChild($$, $1);
	};
mulop:MUL{
	$$ = newSyntaxTreeNode("mulop");
	tempo = newSyntaxTreeNode("*");
	SyntaxTreeNode_AddChild($$, tempo);
}
	| DIV{
		$$ = newSyntaxTreeNode("mulop");
		tempo = newSyntaxTreeNode("/");
		SyntaxTreeNode_AddChild($$, tempo);
	};
factor:LPARENTHESE expression RPARENTHESE{
	$$ = newSyntaxTreeNode("factor");
	tempo = newSyntaxTreeNode("(");
	SyntaxTreeNode_AddChild($$, tempo);
	SyntaxTreeNode_AddChild($$, $2);
	tempo = newSyntaxTreeNode(")");
	SyntaxTreeNode_AddChild($$, tempo);
}
	| var{
		$$ = newSyntaxTreeNode("factor");
		SyntaxTreeNode_AddChild($$, $1);
	}
	| call{
		$$ = newSyntaxTreeNode("factor");
		SyntaxTreeNode_AddChild($$, $1);
	}
	| NUMBER{
		$$ = newSyntaxTreeNode("factor");
		tempo = newSyntaxTreeNodeFromNum($1);
		SyntaxTreeNode_AddChild($$, tempo);
	};
call:IDENTIFIER LPARENTHESE args RPARENTHESE{
	$$ = newSyntaxTreeNode("call");
	tempo = newSyntaxTreeNode($1);
	SyntaxTreeNode_AddChild($$, tempo);
	tempo = newSyntaxTreeNode("(");
	SyntaxTreeNode_AddChild($$, tempo);
	SyntaxTreeNode_AddChild($$, $3);
	tempo = newSyntaxTreeNode(")");
	SyntaxTreeNode_AddChild($$, tempo);
};
args:arg-list{
	$$ = newSyntaxTreeNode("args");
	SyntaxTreeNode_AddChild($$, $1);
}
	| /*empty*/{
	$$ = newSyntaxTreeNode("args");
	tempo = newSyntaxTreeNode("epsilon");
	SyntaxTreeNode_AddChild($$, tempo);
};
arg-list:arg-list COMMA expression{
	$$ = newSyntaxTreeNode("arg-list");
	SyntaxTreeNode_AddChild($$, $1);
	tempo = newSyntaxTreeNode(",");
	SyntaxTreeNode_AddChild($$, tempo);
	SyntaxTreeNode_AddChild($$, $3);
}
	| expression{
		$$ = newSyntaxTreeNode("arg-list");
		SyntaxTreeNode_AddChild($$, $1);
	};
%%

void yyerror(const char * s)
{
	// TODO: variables in Lab1 updates only in analyze() function in lexical_analyzer.l
	//       You need to move position updates to show error output below
	//yytext = yyval;
	printf("ERRORS %s happend at:%d %d %d about <%s>\n", s,lines, pos_start,pos_end,yytext);
	//printf("tempo->nameprintfstderr, "%s:%d %d %d syntax error for %s\n", s, lines,pos_start,pos_end, yytext
}

/// \brief Syntax analysis from input file to output file
///
/// \param input basename of input file
/// \param output basename of output file
void syntax(const char * input, const char * output)
{
	gt = newSyntaxTree();

	char inputpath[256] = "./testcase/";
	char outputpath[256] = "./syntree/";
	strcat(inputpath, input);
	strcat(outputpath, output);

	if (!(yyin = fopen(inputpath, "r"))) {
		fprintf(stderr, "[ERR] Open input file %s failed.", inputpath);
		exit(1);
	}
	yyrestart(yyin);
	printf("[START]: Syntax analysis start for %s\n", input);
	FILE * fp = fopen(outputpath, "w+");
	if (!fp)	return;

	// yyerror() is invoked when yyparse fail. If you still want to check the return value, it's OK.
	// `while (!feof(yyin))` is not needed here. We only analyze once.
	yyparse();

	printf("[OUTPUT] Printing tree to output file %s\n", outputpath);
	//printf("OK now\n");
	printSyntaxTree(fp, gt);
	//printf("OK1\n");
	deleteSyntaxTree(gt);
	//printf("OK2\n");
	gt = 0;

	fclose(fp);
	printf("[END] Syntax analysis end for %s\n", input);
}

/// \brief starting function for testing syntax module.
///
/// Invoked in test_syntax.c
int syntax_main(int argc, char ** argv)
{
	char filename[100][256];
	const char suffix[256] = ".syntax_tree";
	int fn = getAllTestcase(filename);
	//printf("file_count:%d\n", fn);
	for (int i = 0; i < fn; i++) {
			lines = 1;
			int name_len = strstr(filename[i], ".cminus") - filename[i];
			strncpy(output_file_name, filename[i], name_len);
			strcpy(output_file_name+name_len, suffix);
			syntax(filename[i], output_file_name);
	}
	return 0;
}
