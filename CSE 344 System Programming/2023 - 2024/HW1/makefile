all: clean compile run

run:
	@./a.out

compile: main.c utils.c
	@gcc -o a.out main.c utils.c

clean:
	@rm -f *.out
	@rm -f *.log
