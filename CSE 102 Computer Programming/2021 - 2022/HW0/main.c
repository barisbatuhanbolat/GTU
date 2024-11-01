#include <stdio.h>
#include "util.h"


int main() {

    /* A fractional number: 13/7 */
    int num1 = 13, den1 = 7;
    /* A fractional number: 13/7 */
    int num2 = 30, den2 = 11;
    /* An unitilized fractional number */
    int num3, den3;

    printf("First number: ");
    fraction_print(num1, den1);
    printf("\n");

    printf("Second number: ");
    fraction_print(num2, den2);                                          
    printf("\n");

    printf("Addition: ");
    fraction_add(num1, den1, num2, den2, &num3, &den3);
    fraction_print(num3, den3);
    printf("\n\n");

    printf("Subtraction: ");
    fraction_sub(num1, den1, num2, den2, &num3, &den3);
    fraction_print(num3, den3);
    printf("\n\n");

    printf("Multiplication: ");
    fraction_mul(num1, den1, num2, den2, &num3, &den3);
    fraction_print(num3, den3);
    printf("\n\n");

    printf("Division: ");
    fraction_div(num1, den1, num2, den2, &num3, &den3);
    fraction_print(num3, den3);
    printf("\n\n");

    /*
     TODO: Complete this code to read two fractional numbers and print their 
             multiplication and division results...
    */
	int usernum1, userden1, usernum2, userden2, usernum3, userden3;

	printf("\nEnter the numerator for 1st number : ");
	scanf("%d",&usernum1);

	printf("\nEnter the denominator for 1st number : ");										
	scanf("%d",&userden1);

	printf("\nEnter the numerator for 2nd number : ");					
	scanf("%d",&usernum2);
										/*In this section I took two fractional numbers from the user and called two functions to add, subtract, multiply*/
	printf("\nEnter the denominator for 2nd number : ");			/*and divide them */
	scanf("%d",&userden2);

    	printf("\nUser Addition: ");
	fraction_add(usernum1, userden1, usernum2, userden2, &usernum3, &userden3);
	fraction_print(usernum3, userden3);
        printf("\n\n");

        printf("User Subtraction: ");
	fraction_sub(usernum1, userden1, usernum2, userden2, &usernum3, &userden3);
	fraction_print(usernum3, userden3);
        printf("\n\n");

    	printf("\nUser Multiplication: ");
	fraction_mul(usernum1, userden1, usernum2, userden2, &usernum3, &userden3);
	fraction_print(usernum3, userden3);
        printf("\n\n");

        printf("User Division: ");
	fraction_div(usernum1, userden1, usernum2, userden2, &usernum3, &userden3);
	fraction_print(usernum3, userden3);
        printf("\n\n");

    return(0);
}
