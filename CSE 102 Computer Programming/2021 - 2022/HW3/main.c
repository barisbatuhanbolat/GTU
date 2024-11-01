#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define NOT_PRIME 0
#define PRIME 1


/*I declare functions I use in program*/
void write_file(int result);
void write_file_temp(FILE* file, int num1,int num2,int num3);
void print_file();
int number_of_integers();
int digit_number(int num);
void delete_old(FILE* file,int num1,int num2,int num3);
void sort_file();
int sum(int n1,int n2,int flag);
int multi(int n1,int n2,int flag);
int least_divisor(int a);
int isprime(int a);

int main(){
    /*And I declared some variables for program*/
	int y,i,operation_flag=0,choice=0,n1,n2,flag,result,count=0,j,prime_check;
    /*And I started an endless loop so that the program does not close.*/
    while(1){
        /*I created a menu for easy access for each part of program*/
        printf("------------------------MENU------------------------\n");
        printf("Select Operation\n");
        printf("1. Calculate sum/multiplication between two numbers\n"
                "2. Calculate prime numbers\n"
                "3. Show number sequence in file\n"
                "4. Sort number sequence in file\n");
        printf("----------------------------------------------------\n");
        printf("Please Choose(0 for exit): ");
        scanf("%d",&choice);
        /*I used switch case for menu parts*/
        switch(choice){
            case 1:
                printf("Please enter '0' for sum '1' for multiplication: ");
                scanf("%d",&operation_flag);   
                printf("Please enter '0' work on even numbers '1' work on odd numbers: ");
                scanf("%d",&flag);
                if(flag == 0 || flag == 1){
                    printf("Please enter two different number \n");
                    printf("Number 1: ");
                    scanf("%d",&n1);
                    printf("Number 2: ");
                    scanf("%d",&n2);
                    if(n1<0 || n2<0){
                        printf("Invalid values for n1 or n2. The program is restarting.\n");
                    }
                    /*I used switch case for operations for part 1*/
                    switch(operation_flag){
                    case 0:
                        result = sum(n1,n2,flag);
                        if(flag == 0){
                            if(n1%2 == 0){
                                printf("%d",n1+2);
                                for(i=n1+4;i<n2;i++){
                                    if(i%2 == 0){
                                        printf("+%d",i);
                                    }
                                }
                                printf("=%d\n",result);
                            }
                            if(n1%2 != 0){
                                printf("%d",n1+1);
                                for(i=n1+3;i<n2;i++){
                                    if(i%2 == 0){
                                        printf("+%d",i);
                                    }
                                }
                                printf("=%d\n",result);
                            }
                        }
                        if(flag == 1){
                            if(n1%2 == 0){
                                printf("%d",n1+1);
                                for(i=n1+3;i<n2;i++){
                                    if(i%2 != 0){
                                        printf("+%d",i);
                                    }
                                }
                                printf("=%d\n",result);
                            }
                            if(n1%2 != 0){
                                printf("%d",n1+2);
                                for(i=n1+4;i<n2;i++){
                                    if(i%2 != 0){
                                        printf("+%d",i);
                                    }
                                }
                                printf("=%d\n",result);
                            }
                        }
                        write_file(result);
                        break;
                    case 1:
                        result = multi(n1,n2,flag);
                        if(flag == 0){
                            if(n1%2 == 0){
                                printf("%d",n1+2);
                                for(i=n1+4;i<n2;i++){
                                    if(i%2 == 0){
                                        printf("*%d",i);
                                    }
                                }
                                printf("=%d\n",result);
                            }
                            if(n1%2 != 0){
                                printf("%d",n1+1);
                                for(i=n1+3;i<n2;i++){
                                    if(i%2 == 0){
                                        printf("*%d",i);
                                    }
                                }
                                printf("=%d\n",result);
                            }
                        }
                        if(flag == 1){
                            if(n1%2 == 0){
                                printf("%d",n1+1);
                                for(i=n1+3;i<n2;i++){
                                    if(i%2 != 0){
                                        printf("*%d",i);
                                    }
                                }
                                printf("=%d\n",result);
                            }
                            if(n1%2 != 0){
                                printf("%d",n1+2);
                                for(i=n1+4;i<n2;i++){
                                    if(i%2 != 0){
                                        printf("*%d",i);
                                    }
                                }
                                printf("=%d\n",result);
                            }
                        }
                        write_file(result);
                        break;
                    }
                    printf("The result is written to the results.txt file.\n");
                }
                else{
                    printf("Invalid value for flag. The program is restarting.\n");
                }
                break;
            case 2:
                printf("Please enter an integer: ");
                scanf("%d",&prime_check);

                for(i=2;i<prime_check;i++){
                    result = isprime(i);
                    if(result == PRIME){
                        printf("%d is a prime number\n",i);
                    }
                    else{
                        printf("%d is not a prime number, it is dividible by %d\n",i,result);
                    }
                }
                break;
            case 3:
                printf("Result: \n");
                print_file();
                break;
            case 4:
                sort_file();
                break;
            case 0:
                return 0;
                break;
        }
        printf("\n\n");
    }
}
/*There are functions that I use starting from this line.*/

void write_file(int result){
    FILE *results = fopen("results.txt","a");
    fprintf(results," %d",result);
    fclose(results);
}
void print_file (){
    int x;
    FILE *results = fopen("results.txt","r");
    while(fscanf(results,"%d",&x) == 1){
        printf("%d ",x);
    }
    printf("\n");
    fclose(results);
}

int number_of_integers(){
    int i=0,x;
    FILE *results = fopen("results.txt","r");
    while(fscanf(results,"%d",&x) == 1){
        i++;
    }
    fclose(results);
    return i;
}
int digit_number(int num){
    int digit=0;
    while(num > 0 ){ 
        num = num / 10;
        digit++;  
    }
    return digit;
}
void write_file_temp(FILE* file, int num1,int num2,int num3){
    FILE *tempo = fopen("tempo.txt","a");
    fprintf(tempo,"%d %d %d ",num1,num2,num3);
    fclose(tempo);
    delete_old(file , num1,num2,num3);
}
void delete_old(FILE* file, int num1,int num2,int num3){
    file = fopen("results.txt","r+");
    int number_of_digits_1,number_of_digits_2,number_of_digits_3,x,i;
    
    number_of_digits_1 = digit_number(num1);
    number_of_digits_2 = digit_number(num2);
    number_of_digits_3 = digit_number(num3);
    
    while(!feof(file)){
        fscanf(file,"%d",&x);
        if(x == num1){
            fseek(file,-1*number_of_digits_1,SEEK_CUR);
            for(i=0;i<number_of_digits_1;i++){
                fputc(' ',file);
            }
        }
        else if(x == num2){
            fseek(file,-1*number_of_digits_2,SEEK_CUR);
            for(i=0;i<number_of_digits_2;i++){
                fputc(' ',file);
            }
        }
        else if(x == num3){
            fseek(file,-1*number_of_digits_3,SEEK_CUR);
            for(i=0;i<number_of_digits_3;i++){
                fputc(' ',file);
            }
        }
    }
    num1 = 0;num2=0;num3=0;

}
void copy_back(){
    FILE *TEMPORARY = fopen("tempo.text","r+");
    FILE *ORIGINAL = fopen("results.txt","w+");
    char c;
    c = fgetc(TEMPORARY);
    while (c != EOF){
        fputc(c, ORIGINAL);
        c = fgetc(TEMPORARY);
    }
    fclose(ORIGINAL);
    fclose(TEMPORARY);
}
void sort_file(){
    int x,num1 = 1000000,num2 = 1000000, num3=1000000;
    FILE *file1 = fopen("results.txt", "r");
    while(1){
        num1 = num2 = num3 = 1000000;
        while(fscanf(file1,"%d",&x) == 1){
            if(x<num1){
                num3 = num2;
                num2 = num1;
                num1 = x;
            }
            else if(x<num2){
                num2 = num1;
                num1 = x;
            }
            else if(x<num3){
                num3 = x;
            }
        }
        write_file_temp(file1,num1,num2,num3);
        fseek(file1,1,SEEK_SET);
    }
    fclose(file1);
}

int sum(int n1,int n2,int flag){
    int i,sum=0,temp;
    if(n2<n1){
        temp=n1;
        n1=n2;
        n2=temp;
    }

    if(flag == 0){
        for(i= n1+1;i<n2;i++){
            if(i%2 == 0){
                sum = sum+i;
            }
        }
        return sum;
        
    }
    if(flag == 1){
        for(i= n1+1;i<n2;i++){
            if(i%2 != 0){
                sum = sum+i;
            }
        }
        return sum;
        
    }
}
int multi(int n1,int n2,int flag){
    int i,mult=1,temp;
    if(n2<n1){
        temp=n1;
        n1=n2;
        n2=temp;
    }

    if(flag == 0){
        for(i= n1+1;i<n2;i++){
            if(i%2 == 0){
                mult = mult*i;
            }
        }
        return mult;
        write_file(mult);
    }
    if(flag == 1){
        for(i= n1+1;i<n2;i++){
            if(i%2 != 0){
                mult = mult*i;
            }
        }
        return mult;
        write_file(mult);
    }
}
int least_divisor(int a){
    int j;
    for(j=2;j<a;j++){
        if(a%j == 0){
            return j;
        }
    }
}
int isprime(int a){
    int i,ld,flag = PRIME;
    for ( i = 2 ; i <= sqrt(a) ; i++ ){ 
        if ( a%i == 0 ){
            flag = NOT_PRIME;
            break;
        }
    }

    if(flag == NOT_PRIME){
        ld = least_divisor(a);
        return ld;
    }

    if(flag == PRIME){
       return flag;
    }
}