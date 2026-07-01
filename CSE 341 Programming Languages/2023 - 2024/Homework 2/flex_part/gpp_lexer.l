/*
	Author: Barış Batuhan Bolat
	210104004029

    ----------COMPILATION------------
    flex -o gpp_lexer.c gpp_lexer.l
    gcc gpp_lexer.c -lfl -o gppLexer

    ------------EXECUTION--------------
    File reading: ./gppLexer < input.txt
    Terminal reading: ./gppLexer (Default makefile operation)
*/

%{
%}
/*DFA's for tokens*/
%%
"and" printf("KW_AND\n");
"or" printf("KW_OR\n");
"not" printf("KW_NOT\n");
"equal" printf("KW_EQUAL\n");
"less" printf("KW_LESS\n");
"nil" printf("KW_NIL\n");
"list" printf("KW_LIST\n");
"append" printf("KW_APPEND\n");
"concat" printf("KW_CONCAT\n");
"set" printf("KW_SET\n");
"def" printf("KW_DEF\n");
"for" printf("KW_FOR\n");
"if" printf("KW_IF\n");
"exit" printf("KW_EXIT\n");return 0;
"load" printf("KW_LOAD\n");
"display" printf("KW_DISPLAY\n");
"true" printf("KW_TRUE\n");
"false" printf("KW_FALSE\n");
"+" printf("OP_PLUS\n");
"-" printf("OP_MINUS\n");
"/" printf("OP_DIV\n");
"*" printf("OP_MULT\n");
"(" printf("OP_OP\n");
")" printf("OP_CP\n");
"," printf("OP_COMMA\n");

[";;"].* printf("COMMENT\n");                            /*DFA's for comment token*/
[0]|[0][.][0-9]*|[1-9][0-9]*[.]?[0-9]* printf("VALUE\n");/*DFA's for value token*/
[0-9]+b[0-9]+ printf("VALUEF\n");                        /*DFA's for fraction token*/
[0-9]+[a-zA-Z]* {printf ("SYNTAX_ERROR_DIGIT_START");}   /*DFA's for ERROR token*/
[a-zA-Z][a-zA-Z0-9]* {printf("IDENTIFIER\n");}           /*DFA's for IDENTIFIER token*/

[ \t\n]  {;}                                             /*Ignored characters*/

. { printf("SYNTAX ERROR_GENERAL");}                     /*Everything else*/

%%


