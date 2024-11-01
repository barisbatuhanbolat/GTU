all: clear clean compile run
	
clear: 
	@echo "Clearing Terminal."
	clear
	@echo "Clearing Complete"

compile: driver.cpp
	@echo "------------------------------------------------"
	@echo "Compiling driver.cpp"
	@g++ -c driver.cpp DayOfYearSet.cpp -std=c++11
	@g++ -o main.out driver.o DayOfYearSet.o
	@echo "Compiling of driver.o Complete"
run:
	@echo "------------------------------------------------"
	@echo "Running main."
	./main.out
	@echo "Running Complete"
clean:
	@echo "Cleaning the files"
	@rm -f *.om
	@rm -f main.out
	@rm -f driver.o
	@rm -f DayOfYearSet.o
	@echo "Cleaning Complete"