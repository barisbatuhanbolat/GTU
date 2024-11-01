#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "util.h"
/*Driver program*/
int main(){
    int choice,choice2;
    database *d;
    table *t;
    char name[MAXSTRINGSIZE];

    do{
        printf("---------------MENU---------------\n");
        printf("\t1 - Create Database\n"      
                "\t2 - Create and Insert Table\n"
                "\t3 - Show Tables by names\n"
                "\t4 - Describe table\n"
                "\t5 - Remove Table\n"
                "\t6 - Exit\n");
        printf("Choice = ");
        scanf("%d",&choice);

        switch(choice){
            case 1:
                printf("Enter the new database name = ");
                fflush(stdin);
                scanf(" %[^\n]%*c",name);
                d = create_database(name);
                printf("%s\n",d->name);
                break;
            case 2:
                d->tList = insert_table(d, t);
                (d->n)++;
                break;
            case 3:
                show_table(d);
                break;
            case 4:
                printf("Enter the name of the table = ");
                fflush(stdin);
                scanf(" %[^\n]%*c",name);
                tables *f;
                f = d->tList;
                for(int i = 0;f!=NULL;i++){
                    if(strcmp(f->t->tName,name) == 0){
                        desc_table(d,f->t);
                        break;
                    }
                    else{
                        f = f->next;
                    }
                }
                break;  
            case 5:
                printf("Enter the name of the table = ");
                fflush(stdin);
                scanf(" %[^\n]%*c",name);
                d->tList = remove_table(d,name);
                break;
        }
    }while(choice != 6);

}
