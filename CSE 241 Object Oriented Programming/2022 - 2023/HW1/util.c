#include <stdio.h>
#include <string.h>
#include "util.h"

int find_divisible(int x, int y, int z){
	int i;
	
	/*After I retreive x and y from main I made a comparison between them. And if lower bound(x) is bigger than the upper bound(y) I returned -1 to main*/

	if(x>y){
		return -1;
	}
	/*Aftee I found the first divisible number I stopped the loop and I sent the result to the main function*/

	for(i=x;i<y+1;i++){
		if(i%z==0){
			return i;
			break;
		}

		else{
			if(i == y){
				return -1;
			}
			else{
				continue;
			}
		}
	}
}

int find_nth_divisible(int n, int f_i, int z){
	int i;
	/*For finding nth divisible number I use for loop */
	for(i=0;i<n;i++) {
		f_i = f_i + z;
	}
	/*After I found the result I sent them to the main*/
	return f_i;
}

int withdrawable_amount(float cash_amount){

	/*First, I converted the decimal number from main to integer so that the values to the right of the comma are gone.*/
	int cash_amount_integer = (int)(cash_amount);
	
	/*And to find the remainder by dividing this integer number by 10, I took the mode of the number by 10.*/
	int cash_amount_integer_remainder = cash_amount_integer%10;
	
	/*And I subtract this remainder from integer to found the withdrawable amount and I sent it to the main*/
	int result = cash_amount_integer-cash_amount_integer_remainder;

	return result;
}

int create_customer(char identity_number [ ], int password){

	/*In this function, if the entered password is 4 digits, a file named customeraccount.txt will be created and the ID number and password will be saved in it.*/

	if(password <= 9999 && password >= 1000){

		FILE *create= fopen("customeraccount.txt","w");
		
		fprintf(create,"%s,%d",identity_number,password);
		
		fclose(create);

		return 1 ;
	}
	else{
		return 0 ;
	}
}

int check_login(char identity_number [ ], int password){
		char identity_number_check [11];
		int password_check, verification;

		/*In this function, I opened the previously created file called customeraccount.txt, took the ID number and password and placed them in the created variables.*/

		FILE *login = fopen("customeraccount.txt","r");
		fscanf(login,"%11s%*c%4d",identity_number_check,&password_check);

		fclose(login);

		/*Here I used the strcmp() function from the string.h library to compare the ID number sent to the function and read from the file.*/

		verification = strcmp(identity_number,identity_number_check);
		
		/*And if the ids and passwords are the same it will send 1 to main.*/

		if(verification == 0 && password == password_check){
			return 1 ;
		}
		else{
			return 0 ;
		}
}

int validate_identity_number(char identity_number [ ]){
	int tenth_number,eleventh_number,i;
    int identity_number_integer[11];
	
	/*In order to check the validity of the ID number entered here and to make proper calculations with the digits of the ID number, I converted the entered string ID number into an integer.*/
    
	for(i=0;i<11;i++){
		identity_number_integer[i] = (identity_number[i]-'0');
	}

	/*I used the formula given at https://www.simlict.com/ to prove the accuracy of the entered ID number. */

    tenth_number = ((identity_number_integer [0] + identity_number_integer [2] + identity_number_integer [4] + identity_number_integer [6] + identity_number_integer [8]) * 7 - (identity_number_integer [1] + identity_number_integer [3] + identity_number_integer [5] + identity_number_integer [7])) % 10;
    
    eleventh_number = ((identity_number_integer [0] + identity_number_integer [1] + identity_number_integer [2] + identity_number_integer [3] + identity_number_integer [4] + identity_number_integer [5] + identity_number_integer [6] + identity_number_integer [7] + identity_number_integer [8] + tenth_number )) % 10;

	/*The numbers in the tenth and eleventh digits will be sent 1 to main if true and 0 if false.*/
	
	if(tenth_number == identity_number_integer[9] && eleventh_number == identity_number_integer[10]){
		return 1;
	}
	else{
		return 0;
	}
}


