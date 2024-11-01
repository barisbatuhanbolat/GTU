all : clean compile run

run : main.out
	@./main.out
compile : main.c
	@gcc main.c -o main.out -pthread
clean :
	@rm -f *.out