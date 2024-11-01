#ifndef _UTIL_H_
#define _UTIL_H_
#define MAXSTRINGSIZE 100

typedef struct table{ 
    char *tName;
    char **field;
    char **type; 
    int *isNull;
    int *isKey;
    int row;
}table; 

typedef struct tables{ 
    struct tables *next;
    table *t;
}tables;

typedef struct database{ 
    tables * tList; /* to be implemented as a linked list */ 
    int n; /* num of entries */ 
    char * name; /* database name */ 
}database;

/*In this section, I declared the function prototypes */
database * create_database(char * name);
tables * insert_table(database *d, table *t);
void show_table(database *d);
void desc_table(database *d, table *t);
tables * remove_table(database *d, char *name);

#endif /* _UTIL_H_ */