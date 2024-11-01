%{
typedef struct {
  int num;
  int den;
} fraction;
typedef struct Entry {
    char id[32];
    char type;   
    fraction value;
} Entry;

typedef struct SymbolTable {
    Entry ** entries;
    int size;
    int capacity;
} SymbolTable;

typedef enum SymbolType {
    func_t, var_t
} SymbolType; 
#include "gpp_interpreter.tab.h"
#include <stdlib.h>
int line_no = 1;
%}

%option noyywrap
%option case-insensitive

DIGIT [0-9]
FRACTION {DIGIT}+b{DIGIT}+
ID [a-zA-Z][a-zA-Z0-9]*
COMMENT ;;.*

%%

"and"       { return KW_AND; }
"or"        { return KW_OR; }
"not"       { return KW_NOT; }
"equal"     { return KW_EQUAL; }
"less"      { return KW_LESS; }
"nil"       { return KW_NIL; }
"list"      { return KW_LIST; }
"append"    { return KW_APPEND; }
"concat"    { return KW_CONCAT; }
"set"       { return KW_SET; }
"def"       { return KW_DEF; }
"for"       { return KW_FOR; }
"if"        { return KW_IF; }
"exit"      { return KW_EXIT; }
"load"      { return KW_LOAD; }
"display"   { return KW_DISPLAY; }
"true"      { return KW_TRUE; }
"false"     { return KW_FALSE; }
"+"         { return OP_PLUS; }
"-"         { return OP_MINUS; }
"/"         { return OP_DIV; }
"*"         { return OP_MULT; }
"("         { return OP_OP; }
")"         { return OP_CP; }
","         { return OP_COMMA; }
{COMMENT} { /* ignore */ }

^\n							{ if (yyin == stdin) return 0; }
[ \t\r	]                   { ; }
\n						  	{  }
<<EOF>>						{ return 0; }

{FRACTION} { 
    int n,d;
    sscanf(yytext, "%d%*c%d", &n, &d); 
    fraction f;
    f.num = n;
    f.den = d;
    yylval.value = f;
    return VALUEF; 
    }
{ID} {     yylval.name = strdup(yytext); return IDENTIFIER;}
. { printf("Invalid character: %s\n", yytext); exit(1); }

%%
