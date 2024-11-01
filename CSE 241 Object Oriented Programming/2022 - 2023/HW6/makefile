all: clean clear compile run

clear:
	@clear

compile:
	@g++ -c driver.cpp -std=c++11
	@g++ -o main.out driver.o
run:
	@./main.out

clean:
	@echo "Cleaning the files"
	@rm -f *.om
	@rm -f main.out
	@rm -f driver.o
	@echo "Cleaning Complete"


