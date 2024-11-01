#include <stdio.h>
#include <stdlib.h>
#include "util.h"


int main() {
	/* In this part I created some variables for the program*/
    int TEMPERATURE,COLOR,LIGHTING,HYDROGEN;
    int choice,comp1,x4,x5,comp3;
    double PL,PW,SL,SW,x1,x2,x3,res3,res4,comp2,MASS,RADIUS;
    char res1,res2,res5,res6;
    char SETOSA[]  = "Setosa";
    char VIRGINICA[]  = "Virginica";
    char VERSICOLOR[]  = "Versicolor";
    
    /* And in this part, I created a menu for easy access to all parts of the assignment.*/
 	printf("\n-----------------Menu-----------------\n");   
    printf("1-First Problem\n");
	printf("2-Second Problem\n");
    printf("3-Third Problem\n");
	printf("Please choose: ");
	scanf("%d",&choice);

    /*In this part, I used switch-case to evaluate the menu selection.*/
	/*A warning will be given if an invalid number is entered, along with the actions to be taken according to the given selections.*/
    switch(choice){
        /*For first two part I used the given trees for creating functions*/
        case 1:
            printf("Enter PL: ");
            scanf("%lf",&PL);
            printf("Enter PW: ");
            scanf("%lf",&PW);
            printf("Enter SL: ");
            scanf("%lf",&SL);
            printf("Enter SW: ");
            scanf("%lf",&SW);
            
            if(PL >=0 && PW >=0 && SL >=0 && SW >=0){
                /*I sent the entered variables to functions*/
                res1 = dt1a(PL,PW,SL,SW);
                res2 = dt1b(PL,PW,SL,SW);
                /*And I created another function to see if the result found is the same and sent the results to this function.*/
                comp1 = compare_P1(res1,res2);
                /*According to the information received, I printed the actual result.*/
                if(comp1 == 1){
                   if(res1 == 'a'){
                        printf("Results are same and result is: %s\n",SETOSA);
                   }
                   if(res1 == 'b'){
                        printf("Results are same and result is: %s\n",VIRGINICA);
                    }
                    if(res1 == 'c'){
                        printf("Results are same and result is: %s\n",VERSICOLOR);
                    }
       
                }
                if(comp1 == 0){
                    printf("Results are not same\n");
                    if(res1 == 'a'){
                        printf("Result of Decision Tree 1: %s\n",SETOSA);
                    }
                    if(res1 == 'b'){
                        printf("Result of Decision Tree 1: %s\n",VIRGINICA);
                }
                    if(res1 == 'c'){
                        printf("Result of Decision Tree 1: %s\n",VERSICOLOR);
                    }
                    if(res2 == 'a'){
                        printf("Result of Decision Tree 2: %s\n",SETOSA);
                    }
                    if(res2 == 'b'){
                        printf("Result of Decision Tree 2: %s\n",VIRGINICA);
                    }
                    if(res2 == 'c'){
                        printf("Result of Decision Tree 2: %s\n",VERSICOLOR);
                    }          
                }               
            }
            else{
                printf("Invalid numbers\n");
            }
 
            break;
    
        case 2:
            printf("Enter x1: ");
            scanf("%lf",&x1);
            printf("Enter x2: ");
            scanf("%lf",&x2);
            printf("Enter x3: ");
            scanf("%lf",&x3);
            printf("Enter x4(1 or 0): ");
            scanf("%d",&x4);
            printf("Enter x5(1 or 0): ");
            scanf("%d",&x5);
            /*I sent the entered variables to functions*/
            res3 = dt2a(x1,x2,x3,x4,x5);
            res4 = dt2b(x1,x2,x3,x4,x5);
            /*And I created another function to see if the result found is the same and sent the results to this function.*/
            comp2 = compare_P2(res3,res4);
            /*According to the information received, I printed the actual result.*/
            if(comp2 != 0){
                printf("Results are similar and avarage is: %.2lf",comp2);
            }
            else{
                printf("Results are not similar\n");
                printf("Result of Decision Tree 1: %.2lf\n", res3);
                printf("Result of Decision Tree 2: %.2lf\n", res4);          
            }
            break;
        case 3:
            /*In the third part, I researched the Harvard Spectrum Classification for the classification of stars and created two decision trees on it.*/
            /*And I created a table based on my research. */
            /*You can find this table, trees and resources I used in the submitted file.*/
            printf("Temperature(Kelvin): ");
            scanf("%d",&TEMPERATURE);
            printf("Color(Blue(0),White(1),Yellow(2),Orange(3),Red(4)): ");
            scanf("%d",&COLOR);
            printf("Mass(Solar Masses): ");
            scanf("%lf",&MASS);
            printf("Radius(Solar Radıus): ");
            scanf("%lf",&RADIUS);
            printf("Luminosity(Very Strong(0),Strong(1),Mid(2),Weak(3),Very Weak(4)): ");
            scanf("%d",&LIGHTING);
            printf("Hydrogen Lines(Strong(0) or Weak(1)): ");
            scanf("%d",&HYDROGEN);

            /*I sent the entered variables to functions*/
            res5 = dt3a(TEMPERATURE,MASS,RADIUS,COLOR,LIGHTING,HYDROGEN);
            res6 = dt3b(TEMPERATURE,MASS,RADIUS,COLOR,LIGHTING,HYDROGEN);
            /*ASince the results of both are in characters, I sent the results of this part to the comparison function I made for the first part.*/
            comp3 = compare_P1(res5,res6);

            /*According to the information received, I printed the actual result.*/            
            if(res5 != 'x' || res6 != 'x'){
                if(comp3 = 1){
                   printf("Two Decision Tree has the same result and result is: ");
                    if(res5 == 'o'){
                        printf("O serisi\n");
                    }
                    if(res5 == 'b'){
                        printf("B serisi\n");
                    }
                    if(res5 == 'a'){
                        printf("A serisi\n");
                    }
                    if(res5 == 'f'){
                        printf("F serisi\n");
                    }   
                    if(res5 == 'g'){
                        printf("G serisi(Earth is also in this series)\n");
                    }
                    if(res5 == 'k'){
                        printf("K serisi\n");
                    }   
                    if(res5 == 'm'){
                        printf("M serisi\n");
                    }
                }
                else{
                    printf("Results are not same\n");
                    if(res5 == 'o'){
                        printf("O serisi\n");
                    }
                    if(res5 == 'b'){
                        printf("B serisi\n");
                    }
                    if(res5 == 'a'){
                        printf("A serisi\n");
                    }
                    if(res5 == 'f'){
                        printf("F serisi\n");
                    }   
                    if(res5 == 'g'){
                        printf("G serisi(Earth is also in this series)\n");
                    }
                    if(res5 == 'k'){
                        printf("K serisi\n");
                    }   
                    if(res5 == 'm'){
                        printf("M serisi\n");
                    }
                    if(res6 == 'o'){
                        printf("O serisi\n");
                    }
                    if(res6 == 'b'){
                        printf("B serisi\n");
                    }
                    if(res6 == 'a'){
                        printf("A serisi\n");
                    }
                    if(res6 == 'f'){
                        printf("F serisi\n");
                    }   
                    if(res6 == 'g'){
                        printf("G serisi(Earth is also in this series)\n");
                    }
                    if(res6 == 'k'){
                        printf("K serisi\n");
                    }   
                    if(res6 == 'm'){
                        printf("M serisi\n");
                    }        
                }
            }
            else{
                printf("No stars were found in the Harvard spectral classification that match the information you entered\n");
            }
            break;
        default:
		    printf("Invalid choice\n");
    }

    return 0;
}
