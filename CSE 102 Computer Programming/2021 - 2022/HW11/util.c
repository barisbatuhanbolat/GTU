#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "util.h"
/*This function remove a table from database*/
tables * remove_table(database *d, char *name){
    tables *f,*k;
    f = d->tList;
    for(int i = 0;f!=NULL;i++){
        if(strcmp(f->t->tName,name) == 0){
            break;
        }
        else{
            k = f;
            f = f->next;
        }
    }
    if(strcmp(f->t->tName,d->tList->t->tName) == 0){
        d->tList = d->tList->next;
        return d->tList;
    }
    k->next = f->next;
    return d->tList;

}
/*This function describes the table*/
void desc_table(database *d, table *t){
    printf("FIELD\tTYPE\tNULL\tKEY\n");
    for(int i=0;i<t->row;i++){
        printf("%s\t%s\tYES\n",(t->field)[i],(t->type)[i]);
        printf("+------------------------------------+\n");
    }
}
/*This function creates an empty database*/
database * create_database(char * name){
    database *d;
    d = (database*)malloc(sizeof(database));
    d->name = (char*)malloc(sizeof(char));
    strcpy(d->name,name);
    d->n = 0;
    d->tList = NULL;
    return d;
}
/*This function inserts a table to database*/
tables * insert_table(database *d, table *t){
    t = (table*)malloc(sizeof(table));
    int rc;
    printf("Enter the table name = ");
    t->tName = (char*)malloc(MAXSTRINGSIZE*sizeof(char));
    fflush(stdin);
    scanf(" %[^\n]%*c",t->tName);

    printf("Enter how many row do you want = ");
    scanf("%d",&rc);
    
    t->field = (char**)calloc(rc,sizeof(char*));
    t->type = (char**)calloc(rc,sizeof(char*));
    t->isNull = (int*)calloc(rc,sizeof(int));
    t->isKey = (int*)malloc(sizeof(int));
    t->row = rc;

    for(int i = 0;i<rc;i++){
       (t->field)[i] = (char*)malloc(MAXSTRINGSIZE*sizeof(char));
       (t->type)[i] = (char*)malloc(MAXSTRINGSIZE*sizeof(char));
       (t->isNull)[i] = 1;
    }

    for (int i = 0; i < rc; i++){
        printf("Enter the name of row %d = ",i+1);
        fflush(stdin);
        scanf(" %[^\n]%*c",(t->field)[i]);
        printf("Enter the type of row %d = ",i+1);
        fflush(stdin);
        scanf(" %[^\n]%*c",(t->type)[i]);
    }

    if(d->tList==NULL){
        d->tList = (tables*)malloc(sizeof(tables));
        d->tList->t = t;
        return d->tList;
    }

    tables *new;
    tables *old;
    old = d->tList;

    while(old !=NULL && old->next !=NULL){
        old = old->next;
    }
    new = (tables *)malloc(sizeof(tables));
    new->t = (table*)malloc(sizeof(table));
    new->t = t;
    new->next = NULL;
    old->next = new;

    return d->tList;
}
/*This function prints all tables in database*/
void show_table(database *d){
    if(d->tList == NULL){
        printf("There is no table in this database\n");
        return;
    }
    else if(d == NULL){
        printf("There is no database\n");
        return;        
    }
    tables *f;
    f = d->tList;
    for(int i = 0;f!=NULL;i++){
        printf("Table %d = %s\n",i+1,f->t->tName);
        f = f->next;
    }

}