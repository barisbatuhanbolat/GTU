all: clean clear doc compile run

doc:
	@echo "Creating javadoc documents for classes"
	@javadoc *.java
clear:
	@clear

compile:
	@javac Tetris.java
run:
	@java Tetris

clean:
	@echo "Cleaning the files"
	@rm -f *.class
	@echo "Cleaning Complete"