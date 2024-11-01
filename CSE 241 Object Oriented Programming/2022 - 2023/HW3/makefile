all: clear clean compile run
	
clear: 
	@echo "Clearing Terminal."
	clear
	@echo "Clearing Complete"

compile: driver2.cpp
	@echo "------------------------------------------------"
	@echo "Compiling driver2.cpp"
	@g++ -c driver2.cpp Tetris.cpp Tetromino.cpp MyCustom2DVector.cpp
	@g++ -o driver2.out driver2.o Tetris.o Tetromino.o MyCustom2DVector.o
	@echo "Compiling of driver2.cpp Complete"
run:
	@echo "------------------------------------------------"
	@echo "Running driver2."
	./driver2.out
	@echo "Running Complete"	
clean:
	@echo "Cleaning the files"
	@rm -f *.om
	@rm -f driver2.out
	@rm -f driver2.o 
	@rm -f Tetris.o
	@rm -f Tetromino.o
	@rm -f MyCustom2DVector.o
	@echo "Cleaning Complete"