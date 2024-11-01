#include <stdio.h>
#include "util.h"

void fraction_print(int numerator, int denominator) {
    printf("%d//%d", numerator, denominator);
}  /* end fraction_print */

void fraction_add(int n1, int d1, int n2, int d2, int * n3, int * d3) {
    *n3 = n1*d2 + n2*d1;
    *d3 = d1*d2;
    fraction_simplify(n3, d3);
} /* end fraction_add */

void fraction_sub(int n1, int d1, int n2, int d2, int * n3, int * d3) {
    *n3 = n1*d2 - n2*d1;
    *d3 = d1*d2;								/*In this part I made some calculations for fractions*/
    fraction_simplify(n3, d3);
} /* end fraction_sub */

void fraction_mul(int n1, int d1, int n2, int d2, int * n3, int * d3) {
    *n3 = n1*n2;
    *d3 = d1*d2;
    fraction_simplify(n3, d3);
} /* end fraction_mul */

void fraction_div(int n1, int d1, int n2, int d2, int * n3, int * d3) {
    *n3 = n1*d2;
    *d3 = d1*n2;
    fraction_simplify(n3, d3);
} /* end fraction_div */

/* Simplify the given fraction such that they are divided by their GCD */

void fraction_simplify(int * n, int * d) {
	int i,gcd=1,n4,d4;					

	if(*n<0){									
		n4 = *n * (-1);
		for(i=1; i <= n4 && i <= *d; i++){
			if(n4%i==0 && *d%i==0){
				gcd = i;
			}
		}										
	}								/*In this section, I specified 3 different conditions according to the state of the numbers coming into the function.
		 							Because if the	number coming to the function is negative, a single loop to find gcd doesn't work.*/
	if(*d<0){
		d4 = *d * (-1);	
		for(i=1; i <= *n && i <= d4; i++){
			if(*n%i==0 && d4%i==0){
				gcd = i;
			}
		}		
	}
	if(*n>0 && *d>0){
		
		for(i=1; i <= *n && i <= *d; i++){
			if(*n%i==0 && *d%i==0){
				gcd = i;
			}
		}
	}

	printf("\nSimplified fraction :  %d//%d",*n/gcd,*d/gcd);		/*And for the printing part of this function, I printed the fraction before and after the simplification.*/
	printf("\nNormal fraction : ");
} /* end fraction_div */
