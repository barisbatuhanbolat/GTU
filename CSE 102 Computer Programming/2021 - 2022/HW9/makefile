all: clear clean compile run
	
clear: 
	@echo "Clearing Terminal."
	clear
	@echo "Clearing Complete"

compile: main.c
	@echo "Compiling..."
	@gcc -c main.c
	@gcc -o main.out main.o 
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
	@echo "Cleaning Complete"
