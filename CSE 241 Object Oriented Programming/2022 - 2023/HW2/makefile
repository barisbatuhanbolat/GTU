all: clear clean compile_1 run_1 compile_2 run_2
	
clear: 
	@echo "Clearing Terminal."
	clear
	@echo "Clearing Complete"

compile_1: driver1.cpp
	@echo "------------------------------------------------"
	@echo "Compiling driver1.cpp"
	@g++ -c driver1.cpp Tetris.cpp Tetromino.cpp
	@g++ -o driver1.out driver1.o Tetris.o Tetromino.o
	@echo "Compiling of driver1.cpp Complete"
run_1:
	@echo "------------------------------------------------"
	@echo "Running driver1."
	./driver1.out
	@echo "Running Complete"
compile_2: driver2.cpp
	@echo "------------------------------------------------"
	@echo "Compiling driver2.cpp"
	@g++ -c driver2.cpp Tetris.cpp Tetromino.cpp
	@g++ -o driver2.out driver2.o Tetris.o Tetromino.o
	@echo "Compiling of driver2.cpp Complete"
run_2:
	@echo "------------------------------------------------"
	@echo "Running driver2."
	./driver2.out
	@echo "Running Complete"	
clean:
	@echo "Cleaning the files"
	@rm -f *.om
	@rm -f driver1.out
	@rm -f driver2.out
	@rm -f driver1.o 
	@rm -f driver2.o 
	@rm -f Tetris.o
	@rm -f Tetromino.o
	@echo "Cleaning Complete"