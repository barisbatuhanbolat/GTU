all: 
	yacc -o gpp_interpreter.tab.c -d gpp_interpreter.y
	flex -o gpp_lexer.c gpp_lexer.l
	gcc gpp_lexer.c gpp_interpreter.tab.c -lfl -o gpp_interpreter 
clean:
	rm gpp_interpreter gpp_interpreter.tab.c gpp_lexer.c  gpp_interpreter.tab.h