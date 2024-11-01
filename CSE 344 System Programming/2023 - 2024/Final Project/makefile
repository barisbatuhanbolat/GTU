all: pide hungry

pide: PideShop.c
	@gcc -o PideShop PideShop.c matrixOP.c -lpthread -lm

hungry: HungryVeryMuch.c
	@gcc -o HungryVeryMuch HungryVeryMuch.c
clean : 
	@rm -f PideShop
	@rm -f HungryVeryMuch