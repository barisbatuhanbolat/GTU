all: clear clean compile run
	
clear: 
	@echo "Clearing Terminal."
	clear
	@echo "Clearing Complete"

compile: main.cpp
	@echo "Compiling..."
	@g++ -c main.cpp Tetromino.cpp
	@g++ -o main.out main.o Tetromino.o
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
	@rm -f Tetromino.o
	@echo "Cleaning Complete"
