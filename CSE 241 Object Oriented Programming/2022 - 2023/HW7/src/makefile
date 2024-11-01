all: clean clear doc compile run

doc:
	@echo "Creating javadoc documents for classes"
	@javadoc *.java
clear:
	@clear

compile:
	@javac driver1.java
	@javac driver2.java
run:
	@java driver1
	@java driver2

clean:
	@echo "Cleaning the files"
	@rm -f *.class
	@echo "Cleaning Complete"
