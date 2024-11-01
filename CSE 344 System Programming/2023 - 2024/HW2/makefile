all: clean compile
compile: main.c
	@echo "Compiling...\n"
	@gcc -o a.out main.c -lrt
clean:
	@echo "Cleaning old files\n"
	@rm -f *.out
	@rm -f fifo1
	@rm -f fifo2
		
