%option noyywrap
%{
/*****************声明和选项设置  begin*****************/
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
int files_count = 0;
int lines = 1;
int pos_start = 1;
int pos_end = 1;

enum cminus_token_type{
	ERROR = 258,
	ADD = 259,
	SUB = 260,
	MUL = 261,
	DIV = 262,
	LT = 263,
	LTE = 264,
	GT = 265,
	GTE = 266,
	EQ = 267,
	NEQ = 268,
	ASSIN = 269,
	SEMICOLON = 270,//;
	COMMA = 271,//,
	LPARENTHESE = 272,//(
	RPARENTHESE = 273,
	LBRACKET = 274,//[
	RBRACKET = 275,
	LBRACE = 276,//{
	RBRACE = 277,
	ELSE = 278,
	IF = 279,
	INT = 280,
	RETURN = 281,
	VOID = 282,
	WHILE = 283,
	IDENTIFIER = 284,//
	NUMBER = 285,
	LETTER = 286,
	ARRAY = 287,
	EOL = 288,
	COMMENT = 289,
	BLANK = 290
};
/*****************end*****************/

%}
letter  	[a-zA-Z]
digit		[0-9]
ID 		{letter}+
NUM 		{digit}+


%%
 /****请在此补全所有flex的模式与动作  start******/
[\n]	{lines = lines + 1; pos_start = 1;pos_end = 1;return BLANK;}
[ ]		{pos_start++;pos_end++;return BLANK;}
[\t]	{pos_start++;pos_end++;return BLANK;}

"+"	{return ADD;}
"-"	{return SUB;}
"*"	{return MUL;}
"/"	{return DIV;}
"<"	{return LT;}
"<="	{return LTE;}
">"	{return GT;}
">="	{return GTE;}
"=="	{return EQ;}
"!="	{return NEQ;}
"="	{return ASSIN;}
";"	{return SEMICOLON;}
","	{return COMMA;}
"("	{return LPARENTHESE;}
")"	{return RPARENTHESE;}
"["	{return LBRACKET;}
"]"	{return PBRACKET;}
"{"	{return LBRACE;}
"}"	{return PBRACE;}
"else"	{return ELSE;}
"if"	{return IF;}
"int"	{return INT;}
"return"	{return RETURN;}
"void"	{return VOID;}
"while"	{return WHILE;}
"[]"	{return ARRAY;}
"EOL"	{return EOL;}
"/*"	{char c;char p = '\0';pos_start = pos_start+2;pos_end = pos_end+2;
		do{
		c = input();
		pos_start++;
		pos_end++;
		if(c == EOF)break;
		else if(c == '\n'){lines = lines + 1;pos_start = 1;pos_end = 1;}
		else if(p == '*' && c == '/'){return COMMENT;break;}
		p = c;
		}while(1);
	}
{ID}	{return IDENTIFIER;}
{NUM}	{return NUMBER;}
{letter}	{return LETTER;}
. 		{return ERROR;}


 /****  end******/
%%

/****************请按需求补全C代码 start*************/

/// \brief analysize a *.cminus file
///
///	\param input_file_name
/// \param output_file_name
/// \todo student should fill this function
void analyzer(char* input_file_name, char* output_file_name){
	lines = 1;
	char input_path[256] = "./testcase/";
	strcat(input_path, input_file_name);
	printf("input_path:%s\n", input_path);
	char output_path[256] = "./tokens/";
	strcat(output_path, output_file_name);
	printf("output_path:%s\n", output_path);
	if(!(yyin = fopen(input_path,"r"))){
		printf("[ERR] No input file\n");
		exit(1);
	}
	printf("[START]: Read from: %s\n", input_file_name);
	FILE *fp = fopen(output_path,"w+");
	int token;
	while(token = yylex()){
		switch(token){
            case ERROR:{
                pos_start = pos_end;pos_end = pos_start+strlen(yytext);
				fprintf(fp, "[ERR]: unable to analysize %s at %d line, from %d to %d\n", yytext, lines, pos_start, pos_end);
                break;}
			case COMMENT:break;
			case BLANK:
				break;
			case EOL:
				break;
			default :{
				pos_start = pos_end;pos_end = pos_start+strlen(yytext);
				fprintf(fp, "%s\t%d\t%d\t%d\t%d\n",yytext, token, lines, pos_start, pos_end);}
		}
	}
	fclose(fp);
	printf("[END]: Analysis completed.\n");
}

/// \brief get all file paths under 'testcase' directory
///
/// under 'testcase' directory, there could be many *.cminus files.
/// \todo student should fill this function

const char *to_search = "./testcase/";

void getAllTestcase(char filename[][256]){
	DIR *dp;
	int i = 0;
	struct dirent *dirp;
	char endpart[256];
	if((dp = opendir(to_search)) == NULL) return;
	while((dirp = readdir(dp)) != NULL){
		for(int j = 0; j < strlen(dirp->d_name); j++){
			if(dirp->d_name[j] == '.'){
				memset(endpart, '\0', 256);
				strncpy(endpart, &dirp->d_name[j+1], strlen(dirp->d_name)-j-1);
				endpart[strlen(dirp->d_name)-j] = '\0';
				if(strncmp(endpart, "cminus", 6) == 0){
					strcpy(filename[i++],dirp->d_name);
					files_count++;}
			}
		}
		//printf("ALLSearch:%s\n", filename[i-1]);	
	}
	closedir(dp);
	return;
}

/// \brief process all *.cminus file
///
/// note that: use relative path for all i/o operations
///	process all *.cminus files under 'testcase' directory,
/// then create *.tokens files under 'tokens' directory
/// \todo student should fill this function
int main(int argc, char **argv){
	char filename[10][256];
	char *input_file;
	input_file = (char*)malloc(256*sizeof(char));
	char output_file_name[256];
	char exchange[256];
	char suffix[] = ".tokens";
	getAllTestcase(filename);
	for(int i = 0; i < files_count; i++){
			for(int j = 0;filename[i][j] != '\0';j++){
				if(filename[i][j] == '.'){
					exchange[j] = '\0';
					break;
				}
				else exchange[j] = filename[i][j];
			}
			memset(input_file, '\0', 256);
			strcpy(input_file, filename[i]);
			strcat(exchange, suffix);
			strcpy(output_file_name,exchange);
			analyzer(input_file,output_file_name);
	}
	return 0;
}
/**************** end*************/
