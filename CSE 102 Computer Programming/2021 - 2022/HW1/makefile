all: clear clean compile run
	
clear: 
	@echo "Clearing Terminal."
	clear
	@echo "Clearing Complete"

compile: main.c util.c util.h
	@echo "Compiling..."
	@gcc -c main.c util.c
	@gcc -o main.out main.o util.o
	@echo "Compile Complete"

run:
	@echo "Running."
	./main.out
	@echo "Running Complete"

clean:
	@echo "Cleaning the files"
	@rm -f *.om
	@rm -f main.out
	@rm -f main.o
	@rm -f util.o
	@echo "Cleaning Complete"
