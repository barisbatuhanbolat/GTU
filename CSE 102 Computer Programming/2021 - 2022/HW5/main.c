#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.14
/*In this part I declared some enumerated types for program*/
typedef enum{Triangle=1, Quadrilateral, Circle, Pyramid, Cylinder,Exit=0}shapes;
typedef enum{Area=1, Perimeter, Volume,exit1=0}calculators;
/*And I declared primary functions for program*/
int select_shape(int shape);
int select_calc(int calc);
int calculate(int (*f)(int),int (*l)(int));
int menu_calc();
/*And I declared some side functions for calculations*/
int calc_triangle(int calc);
int calc_quadrilateral(int calc);
int calc_circle(int calc);
int calc_pyramid(int calc);
int calc_cylinder(int calc);
/*These are printing functions*/
int main(){
    printf("\nWelcome to the geometric calculator!\n");
    /*In main funciton I call the primary function for the program*/
    calculate(select_shape,select_calc);
}
/*This function returns the selected shape based on enumerated values.*/
int select_shape(int shape){
    switch(shape){
        case Triangle:
            return Triangle;
            break;
        case Quadrilateral:
            return Quadrilateral;
            break;
        case Circle:
            return Circle;
            break;
        case Pyramid:
            return Pyramid;
            break;
        case Cylinder:
            return Cylinder;
            break;
        case Exit:
            return Exit;
            break;                                                                    
    }
}
/*This function returns the selected calculator based on enumerated values.*/
int select_calc(int calc){
    switch(calc){
        case Area:
            return Area;
            break;
        case Perimeter:
            return Perimeter;
            break;
        case Volume:
            return Volume;
            break;
        case exit1:
            return exit1;
            break;
    }    
}
/*I created this function for call the calculator menu*/
int menu_calc(){
    int choice_c;
    printf("--------------------------------\n");
    printf("Select calculator: \n");
    printf( "1. Area\n"
            "2. Perimeter\n"
            "3. Volume \n"
            "0. Exit\n");
    printf("--------------------------------\n");                
    printf("Input: ");
    scanf("%d",&choice_c);

    return choice_c;
}

/*All functions from this line to line 252 have been created for the calculations of the desired shapes.*/
/*This function performs the required calculations for the triangle and prints the desired result on the screen.*/
int calc_triangle(int calc){
    /*Declarations for variables to be used in the function.*/
    double a,b,c,s,ar_0,ar,per;
    /*Converting incoming variable to enum type for switch case operation*/
    calculators cal_1 = (calculators)calc;
    
    do{
       /*This part takes variables from the user and checks their suitability for function*/
       printf("Please enter three sides of Triangle: \n");
       while(scanf("%lf", &a)!=1 || a<0 || a==0){
            printf("ERROR ! Invalid side lenghts for Triangle. Please try again.\n");
            getchar();
       }
       while(scanf("%lf", &b)!=1 || b<0 || b==0){
            printf("ERROR ! Invalid side lenghts for Triangle. Please try again.\n");
            getchar();
       }
       while(scanf("%lf", &c)!=1 || c<0 || c==0){
            printf("ERROR ! Invalid side lenghts for Triangle. Please try again.\n");
            getchar();
       }
        /*Calculation part*/
       if((abs(b-c)<a && a<b+c) == 1){
           switch(cal_1){
               case Area:
                    s = (a+b+c)/2;
                    ar_0 = s*(s-a)*(s-b)*(s-c);
                    ar = sqrt(ar_0);
                    printf("Area of TRIANGLE : %.2lf\n",ar);
                    break;
               case Perimeter:
                    per = a+b+c;
                    printf("Perimeter of TRIANGLE : %.2lf\n",per);
                    break;                
           }
       }
       else{
            printf("ERROR ! Please enter valid three sides of Triangle: \n\n");
       }

    }while((abs(b-c)<a && a<b+c) != 1);
}

/*This function performs the required calculations for the quadrilateral and prints the desired result on the screen.*/
int calc_quadrilateral(int calc){
    /*Declarations for variables to be used in the function.*/
    double a,b,c,d,s,ar_0,ar,per;
    /*Converting incoming variable to enum type for switch case operation*/
    calculators cal_1 = (calculators)calc;

    do{
       /*This part takes variables from the user and checks their suitability for function*/ 
       printf("Please enter four sides of Quadrilateral: \n");
       while(scanf("%lf", &a)!=1 || a<0 || a==0){
            printf("ERROR ! Invalid side lenghts for Quadrilateral. Please try again.\n");
            getchar();
       }
       while(scanf("%lf", &b)!=1 || b<0 || b==0){
            printf("ERROR ! Invalid side lenghts for Quadrilateral. Please try again.\n");
            getchar();
       }
       while(scanf("%lf", &c)!=1 || c<0 || c==0){
            printf("ERROR ! Invalid side lenghts for Quadrilateral. Please try again.\n");
            getchar();
       }
       while(scanf("%lf", &d)!=1 || d<0 || d==0){
            printf("ERROR ! Invalid side lenghts for Quadrilateral. Please try again.\n");
            getchar();
       }
        /*Calculation part*/
           switch(cal_1){
               case Area:
                    s = (a+b+c+d)/2;
                    ar_0 = (s-a)*(s-b)*(s-c)*(s-d);
                    ar = sqrt(ar_0);
                    printf("Area of QUADRILATERAL : %.2lf\n",ar);
                    break;
               case Perimeter:
                    per = a+b+c+d;
                    printf("Perimeter of QUADRILATERAL : %.2lf\n",per);
                    break;                
           }
    }while(a<0 && b<0 && c<0 && d<0);
}

/*This function performs the required calculations for the circle and prints the desired result on the screen.*/
int calc_circle(int calc){
    /*Declarations for variables to be used in the function.*/
    double r,ar,per;
    /*Converting incoming variable to enum type for switch case operation*/
    calculators cal_1 = (calculators)calc;
    
    do{
       /*This part takes variables from the user and checks their suitability for function*/ 
       printf("Please enter the radius of Circle: \n");
       while(scanf("%lf", &r)!=1 || r<0 || r==0){
            printf("ERROR ! Invalid radius for Circle Please try again.\n");
            getchar();
       }
        /*Calculation part*/
        switch(cal_1){
            case Area:
                ar = PI*r*r;
                printf("Area of CIRCLE : %.2lf\n",ar);
                break;
            case Perimeter:
                per = 2*PI*r;
                printf("Perimeter of CIRCLE : %.2lf\n",per);
                break;                
           }
    }while(r<0);
}

/*This function performs the required calculations for the pyramid and prints the desired result on the screen.*/
int calc_pyramid(int calc){
    /*Declarations for variables to be used in the function.*/
    double a,h,l,ar,ar_B,ar_L,ar_S,vol,per;
    /*Converting incoming variable to enum type for switch case operation*/
    calculators calc_1 = (calculators)(calc);
    
    do{
       /*This part takes variables from the user and checks their suitability for function*/
       if(calc == Area){
        printf("Please enter the base side of Pyramid: \n");
        while(scanf("%lf", &a)!=1 || a<0 || a==0){
            printf("ERROR ! Invalid base side for Pyramid:. Please try again.\n");
            getchar();
        }
        printf("Please enter the slant height of Pyramid: \n");
        while(scanf("%lf", &l)!=1 || l<0 || l==0){
            printf("ERROR ! Invalid slant height for Pyramid:. Please try again.\n");
            getchar();
        }
       }
        if(calc == Volume){
        printf("Please enter the base side of Pyramid: \n");
        while(scanf("%lf", &a)!=1 || a<0 || a==0){
            printf("ERROR ! Invalid base side for Pyramid:. Please try again.\n");
            getchar();
        }
        printf("Please enter the height of Pyramid: \n");
        while(scanf("%lf", &h)!=1 || h<0 || h==0){
            printf("ERROR ! Invalid height for Pyramid:. Please try again.\n");
            getchar();
        }
       }
        /*Calculation part*/
        switch(calc_1){
            case Area:
                ar_B = a*a;
                ar_L = 2*a*l;
                ar_S = ar_B + ar_L;
                printf("\nBase Surface Area of a PYRAMID: %.2lf\n",ar_B);
                printf("\nLateral Surface Area of a PYRAMID: %.2lf\n",ar_L);
                printf("\nSurface Area of a PYRAMID: %.2lf\n",ar_S);
                break;
            case Perimeter:
                per = 4*a;
                printf("\nBase perimeter of PYRAMID: %.2lf\n",per);
                break;
            case Volume:
                vol = ((double)(1)/(double) (3))*a*a*h;
                printf("\nVolume of PYRAMID: %.2lf\n",vol);
                break;
        }
    }while(a<0 || h<0);
}

/*This function performs the required calculations for the cylinder and prints the desired result on the screen.*/
int calc_cylinder(int calc){
    /*Declarations for variables to be used in the function.*/
    double r,h,ar_B,ar_L,ar_S,vol,per;
    /*Converting incoming variable to enum type for switch case operation*/
    calculators calc_1 = (calculators)(calc);

    do{
       /*This part takes variables from the user and checks their suitability for function*/ 
        printf("Please enter the base radius of Cylinder: \n");
        while(scanf("%lf", &r)!=1 || r<0 || r==0){
            printf("ERROR ! Invalid base radius for Cylinder:. Please try again.\n");
            getchar();
        }
        printf("Please enter the height of Cylinder: \n");
        while(scanf("%lf", &h)!=1 || h<0 || h==0){
            printf("ERROR ! Invalid height for Cylinder:. Please try again.\n");
            getchar();
        }

        /*Calculation part*/
        switch(calc_1){
            case Area:
                ar_B = PI*r*r;
                ar_L = 2*PI*r*h;
                ar_S = 2*PI*r*(r+h);
                printf("\nBase Surface Area of a CYLINDER: %.2lf\n",ar_B);
                printf("\nLateral Surface Area of a CYLINDER: %.2lf\n",ar_L);
                printf("\nSurface Area of a CYLINDER: %.2lf\n",ar_S);
                break;
            case Perimeter:
                per = 2*PI*r;
                printf("\nBase Perimeter of a CYLINDER: %.2lf\n",per);
                break;
            case Volume:
                vol = PI*r*r*h;
                printf("Volume of Cylinder : %.2lf\n",vol);
                break;
        }
    }while(r<0 || h<0 ); 
}
/*****************MAIN CALCULATION FUNCTION*****************/
int calculate(int (*f)(int),int (*l)(int)){
    int choice,choice_c;
    do{
        /*Shape selection menu*/
        printf("--------------------------------\n");
        printf("Select shape to calculate: \n");
        printf( "1. Triangle\n"
                "2. Quadrilateral\n"
                "3. Cİrcle\n"
                "4. Pyramid\n"
                "5. Cylinder\n"
                "0. Exit\n");
        printf("--------------------------------\n");
        printf("Input: ");
        while(scanf("%d", &choice)!=1){
            printf("ERROR ! Invalid choice. Please try again.\n");
            getchar();
        }
        /*Shape and calculator type selection*/
        switch((*f)(choice)){
            case Triangle:
                choice_c = menu_calc();
                switch((*l)(choice_c)){
                    case Area:
                        calc_triangle(Area);
                        break;
                    case Perimeter:
                        calc_triangle(Perimeter);
                        break;
                    case Volume:
                        printf("\nERROR ! You cannot calculate the volume of Triangle. Please try again.\n");
                        break;
                    case exit1:
                        return 0;
                        break;
                }
                break;
            case Quadrilateral:
                choice_c = menu_calc();
                switch((*l)(choice_c)){
                    case Area:
                        calc_quadrilateral(Area);
                        break;
                    case Perimeter:
                        calc_quadrilateral(Perimeter);
                        break;
                    case Volume:
                        printf("\nERROR ! You cannot calculate the volume of Quadrilateral. Please try again.\n");
                        break;
                    case exit1:
                        return 0;
                        break;
                }
                break;
               
            case Circle:
                choice_c = menu_calc();
                switch((*l)(choice_c)){
                    case Area:
                        calc_circle(Area);
                        break;
                    case Perimeter:
                        calc_circle(Perimeter);
                        break;
                    case Volume:
                        printf("\nERROR ! You cannot calculate the volume of Circle. Please try again.\n");
                        break;
                    case exit1:
                        return 0;
                        break;
                }
                break;
            
            case Pyramid:
                choice_c = menu_calc();
                switch((*l)(choice_c)){
                    case Area:
                        calc_pyramid(Area);
                        break;
                    case Perimeter:
                        calc_pyramid(Perimeter);
                        break;
                    case Volume:
                        calc_pyramid(Volume);
                        break;
                    case exit1:
                        return 0;
                        break;
                }
                break;
            
            case Cylinder:
                choice_c = menu_calc();
                switch((*l)(choice_c)){
                    case Area:
                        calc_cylinder(Area);
                        break;
                    case Perimeter:
                        calc_cylinder(Perimeter);
                        break;
                    case Volume:
                        calc_cylinder(Volume);
                        break;
                    case exit1:
                        return 0;
                        break;
                break;
                }
        }
    }while(choice != Exit);
}