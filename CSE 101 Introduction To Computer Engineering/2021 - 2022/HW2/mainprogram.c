#include <stdio.h>							//I added some needed libraries. (I added windows.h for "arduino_serial_library.h library. Because of this program doesnt work on Linux or Mac.)
#include <stdlib.h>										
#include <windows.h> 
#define true 1
#include "arduino_serial_library.h"						//To test the program, enter your current port in the port section of both functions(serial_Write aand serial_Read) in the "serialcom.h" library.
											//Library doesn't belong me. I found it on internet.
int i;																		//Firstly I defined some variables and data array
char a[] = {0};
void menu(){
	printf("Trying to open a port to Arduino\n");
	sleep(1);
	printf("Port opened\n");
	sleep(1);																//Then I created a function for menu to use easy
	printf("Trying to reach the menu\n");
	sleep(1);
	printf("1\n");
	sleep(1);
	printf("2\n");
	sleep(1);
	printf("3\n");
	sleep(1);
	printf("Menu Broughting\n\n");
	sleep(1);
	printf("## WELCOME TO GTU ARDUINO LAB        ##\n"
			"## STUDENT NAME: BARIÞ BATUHAN BOLAT		  ##\n"
			"## PLEASE SELECT FROM THE FOLLOWING  ##\n"
			"## MENU :                            ##\n"
			"(1) TURN ON LED ON ARDUINO\n"
			"(2) TURN OFF LED ON ARDUINO\n"
			"(3) FLASH ARDUINO LED 3 TIMES\n"
			"(4) SEND A NUMBER TO ARDUINO TO COMPUTE SQUARE BY ARDUINO\n"
			"(5) Button press counter (bonus item)\n"
			"(6) CLEAR THE SCREEN AND BACK TO MENU\n"
			"(0) EXIT\n");
}
void select1(){																//I created a function for select a number and add it to array to use without need menu.
			printf("PLEASE SELECT: ");										//I put the name of the function at "select1" so that it doesn't get confused with other libraries.
			scanf("%s",&a);
}
void clear(){																//I created a function to clear the screen and have a more organized program.
    int i;
    for (i = 0; i < 99;i++ ) 
    {
        printf("\n");
    }
}
int main(){
	menu();																//I call "menu" and "select1" functions.
	select1();
	while(true){															//I created an infinite loop to prevent the program from closing against my will. 
		switch(a[0]){													//I used a switch-case for compare char conditions.(I tried to made with "if" but it didn't work properly)
			case '1':													//I connect the first three conditions to the same function because what they do is check the state of the led.
			case '2':													// "1" is to light up led - "2" is to light down led.
			case '3':													//"3" is to blink led three times.
				serial_Write(a);
				select1();
				break;
			case '4':													//Fourth condition for sending number to arduino and read it's square. 
				serial_Write(a);			
				char n[10];
				printf("Enter a number to square: ");
				scanf("%s", n);
				serial_Write(n);										//Transfering a number to square.
				printf("Square of %s is: ",n);
				serial_Read();											//Reading and printing squared number in serial port.
				printf("\n");
				select1();
				break;
			case '5':
				serial_Write(a);									
				while(true) {												//The fifth condition is to read the value when the button is pressed.
					serial_Read();
				}
				break;
			case '6':
				clear();												//The sixth condition has nothing to do with the arduino. This condition clears the screen and calls the menu only when "6" is entered.
				menu();													//Doesn't work when fifth condition active.
				select1();
				break;
			case'0':
				serial_Write(a);
				printf("Port Closing and Exiting...\n");
				return 0;										//This condition is for closing the program when 0 is entered.(I used the "exit" function inside the "stdlib.h" to close the program)
				break;											//Doesn't work when fifth condition active.
		}
		
	}
	return 1;
}
