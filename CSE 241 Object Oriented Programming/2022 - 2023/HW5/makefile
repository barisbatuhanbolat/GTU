all: clean clear driver2

clear:
	@clear


driver2:
	@g++ driver2.cpp AbstractTetris.cpp  Tetromino.cpp TetrisArray1D.cpp TetrisVector.cpp -o main2.out
	@./main2.out
clean:
	@echo "Cleaning the files"
	@rm -f *.om

	@rm -f main2.out
	@echo "Cleaning Complete"
