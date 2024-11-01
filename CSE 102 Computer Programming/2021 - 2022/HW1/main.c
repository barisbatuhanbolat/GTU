#include <stdio.h>
#include "util.h"


int main(){
	/* In this part I created some variables for the program*/
	int choice = 0,x,y,z,n,f_i,nth;
	char identity_number [11];
	int password,validation,creation,login,amount;
	float cash_amount;

	/* And in this part, I created a menu for easy access to both parts of the assignment.*/

	printf("\n-----------------Menu-----------------\n");
	printf("1-Finding Divisible && Nth Divisible\n");
	printf("2-Bank Program\n");
	printf("Please choose: ");
	scanf("%d",&choice);
	
	/*In this part, I used switch-case to evaluate the menu selection.*/
	/*A warning will be given if an invalid number is entered, along with the actions to be taken according to the two given selections.*/
	
	switch (choice){
		/*I used some variables that I created above for the desired operations for Part 1.*/
		case 1 :	
			printf("Enter the first integer: ");
			scanf("%d",&x);

			printf("Enter the second integer: ");
			scanf("%d",&y);

			printf("Enter the divisor: ");
			scanf("%d",&z);

			/*And I send them to the find_divisible function To find the first integer divisible by z between x and y.*/
			
			f_i = find_divisible(x,y,z);

			/*In find_divisible function I sent -1 error code for negative cases.*/

			if(f_i == -1){
				printf("\nThere is not any integer between %d and %d can be divided by %d\n",x,y,z);
			}

			/*And for positive cases I printed the expected value and I call new funciton named find_nth_divisible.*/

			else{
				printf("\nThe first integer between %d and %d divided by %d is %d\n",x,y,z,f_i);

				printf("Enter the number how many next: ");
				scanf("%d",&n);
		
				nth = find_nth_divisible(n,f_i,z);
				
				/*And I printed the desired result if the nth integer from the function divided by z between x and y is within the limits.
				/*I printed an error if the nth integer is not within the limits. */

				if(nth < y){
					printf("The %d. integer between %d and %d divided by %d is %d\n",n+1,x,y,z,nth);
				}	
				else{
					printf("No possible to find %d. divisible between %d and %d divided by %d\n",n+1,x,y,z);

				}
			}
			break;

		case 2 :
			printf("\n--------------Register--------------\n");

			printf("\nEnter your identity number: ");
			scanf("%s",identity_number);

			/*After I retreive ID number from the user I sent it to function named validate_identity_number*/

			validation = validate_identity_number(identity_number);

			/*And according to the result from the function, if the ID number is correct, the registration function works.*/

			if(validation == 1){
				printf("Your identity number is correct\n");
				
				/*For the registration I retreive 4 digit password from the user.*/
	
				printf("\nPlease create a password(4 digits): ");
				scanf("%d",&password);
				
				/*And I sent validated ID number and password to function.*/

				creation = create_customer(identity_number, password);
		
				/*If funciton worked as expected function returns 1*/

				if(creation == 1 ){
					printf("Account succesfully created \n");
			
					printf("\n--------------Login--------------\n");

					/*If registration function worked as expected login function will begin to start*/

					printf("\nEnter your identity number: ");
					scanf("%s",identity_number);

					printf("\nEnter your password: ");
					scanf("%d",&password);

					/*I sent ID number and password to the check_login function*/

					login= check_login(identity_number, password);

					/*If successfully logged in function returns 1 and withdrawable_amount function will begin to start*/

					if(login == 1){
						printf("Login Successful\n");
						
						printf("\nEnter your withdraw amount: ");
						scanf("%f",&cash_amount);
						
						/*After the succesful login I sent a float number named cash_amount to retreive withdrawable amount */

						amount = withdrawable_amount(cash_amount);
				
						printf("\nWithdrawable amount is: %d\n",amount);
					}
			
			/*And after this line I printed some error codes for the functions.*/

					else{
						printf("Invalid identity number or password\n");
					}
				}
				else{
					printf("Password must be 4 digits. \n");
				}
			}
			else{
				printf("Please enter a valid identity number\n");
			}

			break;

		default:
			printf("Please enter a valid choice\n");

	}
}
