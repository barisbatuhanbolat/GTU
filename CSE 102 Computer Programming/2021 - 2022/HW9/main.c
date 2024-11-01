#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*Struct and Unions*/
union Person 
{
    char name[50];
    char address[50];
    int phone;
};

union Loan 
{ 
    float arr[3];
}; 

struct BankAccount 
{ 
    union Person Customer; 
    union Loan Loans[3];
    int loan_t;/*Variable for Loan Counter*/
};
/*Funciton Declarations*/
void writeFile(int id,float loan,int loan_count,int period);
struct BankAccount * newLoan(struct BankAccount *accounts,int count,char *search);
float calculateLoan(float amount, int period, float interestRate);
void listCustomers(struct BankAccount *accounts,int count);
struct BankAccount * addCustomer(struct BankAccount *accounts,int *count);
void getReport(int choice);

int main(){
	int choice,choice2,count=1;
    char search[50];
    struct BankAccount *accounts;
    /*I created Bank account array using calloc*/
    accounts = (struct BankAccount*)calloc(count,sizeof(struct BankAccount));
    /*I use do-while loop for program*/
    do{
        printf("======================================\n");
        printf("Welcome the the Bank Management System\n");
        printf("======================================\n");
        printf("\t1. List All Customers\n"
                "\t2. Add New Customer\n"
                "\t3. New Loan Application\n"
                "\t4. Report Menu\n"
                "\t5. Exit System\n");
        printf("Choice: ");
        scanf("%d",&choice);

        if(count<=50){
            switch (choice){
                case 1:
                    listCustomers(accounts,count);
                    break;
                case 2:
                    accounts = addCustomer(accounts,&count);
                    break;
                case 3:
                    printf("Enter the name of the customer to apply for the loan = ");
                    fflush(stdin);
                    scanf(" %[^\n]%*c",search);
                    accounts = newLoan(accounts,count,search);
                    break;
                case 4:
                    printf("=============Report Menu==============\n");
                    printf("\t1. Customer Report\n"
                            "\t2. Loan Report\n");
                    printf("Choice: ");
                    scanf("%d",&choice2);
                    if(choice2 == 1 || choice2 == 2){
                        getReport(choice2);
                    }
                    else{
                        printf("Invalid Choice\n");
                    }
                    break;
                case 5:
                    exit(0);
                    break;
                default:
                    printf("Invalid Choice\n");
                    break;
            }
        }
        else{
            printf("Banking system keeps maximum 50 customer in same time\n");
            
        }
    }while(choice != 5);
}
/*This function opens a txt file according to given value*/
/*If it opens a customers.txt file it prints all customers with details*/
/*If it opens the loans.txt file, the user is asked which user's loan he wants to print,*/
/*and according to the response, the desired part of the file is printed.*/
void getReport(int choice){
    char line[100];
    char line2[100];
    char line3[100];
    char ids[5];
    char loan_s[5];
    int id,loan_c;
    /*Reads customers.txt file and prints all customers to the screen*/
    if(choice  == 1){
        FILE *customers = fopen("customers.txt","r");
        if(customers == NULL){
            printf("Customer File not exists\n");
            return;
        }
        while(!feof(customers)){
            fgets(line,100,customers);
            if(feof(customers)) break;
            printf("%s",line);
        }
        fclose(customers);
    }
    /*Reads loans.txt file and prints the desired loans*/
    else if(choice == 2){
        FILE *loans = fopen("loans.txt","r");
        if(loans == NULL){
            printf("Loan File not exists\n");
            return;
        }
        printf("!!!If you dont know the Customer ID please choose option 1 first in fourth menu!!!\n");
        printf("Enter Customer ID = ");
        fflush(stdin);
        scanf(" %[^\n]%*c",ids);
        printf("Enter which loan for this customer  = ");
        fflush(stdin);
        scanf(" %[^\n]%*c",loan_s);
        strcpy(line2,"Customer ID = ");
        strcat(line2,ids);
        strcat(line2," Loan Count = ");
        strcat(line2,loan_s);
        strcat(line2,"\n");
        printf("\n%s",line2);
        while(!feof(loans)){
            fgets(line,100,loans);
            if(strcmp(line,line2) == 0){
                while(strcmp(line3,"======================================\n") != 0){
                    fgets(line3,100,loans);
                    printf("%s",line3);
                }
            }
        }
        printf("\n");
    }
}
/*Writes calculated loans to the loans.txt file*/
void writeFile(int id,float loan,int loan_count,int period){
    FILE *fptr = fopen("loans.txt","a+");
    fprintf(fptr,"Customer ID = %d Loan Count = %d\n",id,loan_count);
    fprintf(fptr,"Total Credit Value = %.4f\n",loan);
    for(int j = 1;j<=period;j++){
        fprintf(fptr,"%d. Month Installment = %.4f\n",j,loan/period);
    }
    fprintf(fptr,"======================================\n");
    fclose(fptr);
}
/*According to given name this function gets some parameters from user and calculate new loan for given name*/ 
struct BankAccount * newLoan(struct BankAccount *accounts,int count,char *search){
    int i,j,flag = 0,period;
    for(i = 0;i<count;i++){
        /*Searching name inside struct*/
        if(strcmp(accounts[i].Customer.name,search) == 0){
            if(accounts[i].loan_t<=3){
                printf("Please enter Loan Amount = ");
                while(scanf("%f",&accounts[i].Loans[(accounts[i].loan_t)-1].arr[0]) != 1){
                    printf("!!! Please enter a valid Loan Amount = ");
                    getchar();
                }
                printf("Please enter Loan InterestRate(%%) = ");
                while(scanf("%f",&accounts[i].Loans[(accounts[i].loan_t)-1].arr[1]) != 1){
                    printf("!!! Please enter a valid Loan InterestRate");
                    getchar();
                }
                printf("Please enter Loan Period = ");
                while(scanf("%f",&accounts[i].Loans[(accounts[i].loan_t)-1].arr[2]) != 1){
                    printf("!!! Please enter a valid Loan Period = ");
                    getchar();
                }
                flag = 1;
                break;
            }
            else{
                printf("\nThis Customer cannot take any loan\n\n");
                break;
            }
        }
        else{
            flag = 2;
        }
    }
    if(flag == 2){
        printf("\nThere is no customer with this name\n\n");
    }
    if(flag == 1){
        period = (int)(accounts[i].Loans[(accounts[i].loan_t)-1].arr[2]);
        /*Calculating new loan by using calculateLoan function*/
        accounts[i].Loans[(accounts[i].loan_t)-1].arr[0] = calculateLoan(accounts[i].Loans[(accounts[i].loan_t)-1].arr[0],period,accounts[i].Loans[(accounts[i].loan_t)-1].arr[1]/100);
        /*Writing new loan to loans.txt*/
        writeFile(i+1,accounts[i].Loans[(accounts[i].loan_t)-1].arr[0],accounts[i].loan_t,period);
        /*Increasing loan counter*/
        (accounts[i].loan_t)++;
    }
    return accounts;
}
/*Recursive calculation for loan*/
float calculateLoan(float amount, int period, float interestRate){
    /*Finish condition*/
    if(period == 0){
        return amount;
    }
    /*Calculating new amount of loan*/
    amount =  amount * (1+interestRate);
    /*Decreasing period when calling function again(doing recursion)*/
    calculateLoan(amount,--period,interestRate);
}

/*This Function prints all customer's ids , names and their loans*/
void listCustomers(struct BankAccount *accounts,int count){
    int i,j=0;
    double sum;
    if(count == 1){
        printf("There is no customer in database\n");
        return;
    }
    for(i=0;i<count-1;i++){
        sum = 0;
        printf("Customer ID = %d\n",i+1);
        printf("Customer Name = %s\n",accounts[i].Customer.name);
        printf("Loans = [%.2f",accounts[i].Loans[0].arr[0]);
        sum  = accounts[i].Loans[0].arr[0];
        for(j=1;j<accounts[i].loan_t-1;j++){
            printf(" + %.2f",accounts[i].Loans[j].arr[0]);
            sum = sum + accounts[i].Loans[j].arr[0];
        }
        printf("] => %.2lf\n",sum);
        printf("\n");
    }
}
/*This function increases dynamicly the given array by adding new customers*/
struct BankAccount * addCustomer(struct BankAccount *accounts,int *count){
    int i;
    int *phone;
    char *address;
    address = (char *)calloc(50,sizeof(char));
    phone  = (int *)malloc(sizeof(int));
    FILE *fptr = fopen("customers.txt","a+");
    /*Creating a new array with one more length than the given array.*/
    struct BankAccount *new_account;
    new_account = (struct BankAccount*)calloc((*count)+1,sizeof(struct BankAccount));
    /*Getting new customers information from user to strcut and writes them into customers.txt*/
    printf("Please enter customer name = ");
    fflush(stdin);
    scanf(" %[^\n]%*c",new_account[*count-1].Customer.name);
    fprintf(fptr,"Customer ID : %d\n",*count);
    fprintf(fptr,"Customer Name : %s\n",new_account[*count-1].Customer.name);
    printf("Please enter customer phone = ");
    while(scanf("%d",phone) != 1){
        printf("Please enter a valid phone = ");
        getchar();
    }
    fprintf(fptr,"Customer Phone : %d\n",*phone);
    printf("Please enter customer address = ");
    fflush(stdin);
    scanf(" %[^\n]%*c",address);
    fprintf(fptr,"Customer Address : %s\n",address);
    fprintf(fptr,"======================================\n");
    new_account[*count-1].loan_t = 1;
    /*Copying old array datas to new array*/
    for(i=0;i<*count-1;i++){
            new_account[i] = accounts[i];
    }
    /*Freeing old array*/
    if(accounts != NULL){   
        free(accounts);
    }
    /*Increasing the size of array*/
    (*count)++;
    /*Closing customers.txt file*/
    fclose(fptr);
    /*Freeing unnecessary variables*/
    free(address);
    free(phone);
    /*Returning new array*/
    return new_account;
}
