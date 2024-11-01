%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OUT_FILE "output.txt"
extern FILE * yyin; 
extern FILE * yyout; 
extern int yyparse(); 
extern char * yytext; 

int yylex();

int yyerror(char* str) { 
    fprintf(yyout, "SYNTAX_ERROR\n");
    return 0; 
}

typedef struct {
  int num; 
  int den;
} fraction;


typedef struct Entry {
    char id[32];
    char type;   
    fraction value;
} Entry;

typedef struct Table {
    Entry ** entries;
    int size;
    int capacity;
} Table;

typedef enum Type {
    function, variable
} Type; 

Table * t;

Table * tableCreate() {
    Table * t = (Table *) malloc(sizeof(Table));
    t->size = 0;
    t->capacity = 1;
    t->entries = (Entry **) malloc(sizeof(Entry *));
    return t;
}

void tableFree() {
    int i;
    Entry ** entries = t->entries;
    for (i = 0; i < t->size; ++i)
        free(entries[i]);
    free(t->entries);
    free(t);
}

void increase() {
    int i;
    Entry ** old = t->entries;
    
    t->capacity *= 2; 
    t->entries = calloc(t->capacity, sizeof(Entry *));
    for (i = 0; i < t->size; ++i)
        t->entries[i] = old[i];
    free(old);
}

int contains(Type type, const char * id) {
    int i;
    for (i = 0; i < t->size; ++i)
        if (strcmp(t->entries[i]->id, id) == 0 && t->entries[i]->type == type)
            return i;
    return -1;
}

Entry * tableGet(Type type, const char * id) {
    int i = contains(type, id);
    return i == -1 ? NULL : t->entries[i];
}

Entry * tableDef(Type type, char * id, fraction value) {
    int i = contains(type, id);
    if (i != -1)
        return NULL;

    int size = t->size;
    Entry * new_entry = new_entry = (Entry *) malloc(sizeof(Entry));
    new_entry->value = value;
    new_entry->type = type;
    strcpy(new_entry->id, id);

    if (size == t->capacity)
        increase(t);
    t->entries[size] = new_entry;
    ++(t->size);

    return new_entry;
}

fraction createFraction(int num, int denom){
  fraction f;
  f.num = num;
  f.den = denom;
  return f; 
}
// a function to simplify a fraction
fraction simplify(fraction f) {
  int a = f.num;
  int b = f.den;
  int gcd = 1;
  while (b != 0) {
    int t = b;
    b = a % b;
    a = t;
  }
  gcd = a;
  f.num /= gcd;
  f.den /= gcd;
  return f;
}

// a function to add two fractions
fraction add(fraction f1, fraction f2) {
  fraction f;
  int lcm = f1.den * f2.den;
  f1.num *= lcm / f1.den;
  f2.num *= lcm / f2.den;
  f.num = f1.num + f2.num;
  f.den = lcm;
  f = simplify(f);
  return f;
}

// a function to subtract two fractions
fraction subtract(fraction f1, fraction f2) {
  fraction f;
  int lcm = f1.den * f2.den;
  f1.num *= lcm / f1.den;
  f2.num *= lcm / f2.den;
  f.num = f1.num - f2.num;
  f.den = lcm;
  f = simplify(f);
  return f;
}

// a function to multiply two fractions
fraction multiply(fraction f1, fraction f2) {
  fraction f;
  f.num = f1.num * f2.num;
  f.den = f1.den * f2.den;
  f = simplify(f);
  return f;
}

// a function to divide two fractions
fraction divide(fraction f1, fraction f2) {
  fraction f;
  f.num = f1.num * f2.den;
  f.den = f1.den * f2.num;
  f = simplify(f);
  return f;
}

%}

%union {
  fraction value;
  char *name;
}

%token <value> VALUEF
%token <name> IDENTIFIER
%token KW_AND KW_OR KW_NOT KW_EQUAL KW_LESS KW_NIL KW_LIST
%token KW_APPEND KW_CONCAT KW_SET KW_DEF KW_FOR KW_IF
%token KW_EXIT KW_LOAD KW_DISPLAY KW_TRUE KW_FALSE
%token OP_PLUS OP_MINUS OP_DIV OP_MULT OP_OP OP_CP OP_COMMA
%type <value> EXP
%type <value> START
%type <value> FUNCTION
%type <value> FCALL


%%

START   : FUNCTION                                      { fprintf(yyout, "Result: #function\n"); }
        | EXP                                           { fprintf(yyout, "Result: %db%d\n", $1.num, $1.den); }
        | FCALL                                         { fprintf(yyout, "Result: %db%d\n", $1.num, $1.den); }   
        | OP_OP KW_EXIT OP_CP                           { fprintf(yyout, "Exiting...\n"); exit(0); } 
        ;

EXP     : OP_OP OP_PLUS EXP EXP OP_CP                   { $$ = add($3, $4); }
        | OP_OP OP_MINUS EXP EXP OP_CP                  { $$ = subtract($3, $4); }
        | OP_OP OP_MULT EXP EXP OP_CP                   { $$ = multiply($3, $4); }
        | OP_OP OP_DIV EXP EXP OP_CP                    { $$ = divide($3, $4); }
        | IDENTIFIER                                    { Entry * e = tableGet(variable, $1); $$ = (e == NULL) ? createFraction(0, 1) : e->value; }                                   
        | VALUEF                                        { $$ = $1; }
        ;

FUNCTION: OP_OP KW_DEF IDENTIFIER EXP OP_CP             { $$ = createFraction(0, 1); tableDef(function, $3, createFraction(0, 1)); }
        | OP_OP KW_DEF IDENTIFIER EXP EXP OP_CP         { $$ = createFraction(0, 1); tableDef(function, $3, createFraction(0, 1));}
        | OP_OP KW_DEF IDENTIFIER EXP EXP EXP OP_CP     { $$ = createFraction(0, 1); tableDef(function, $3, createFraction(0, 1));}
        ;

FCALL   : OP_OP IDENTIFIER EXP EXP OP_CP                { Entry * e = tableGet(function, $2); $$ = (e == NULL) ? createFraction(0, 1) : e -> value; }
        ;
%%

int main(int argc, char * argv[]) {
  FILE * in_stream = NULL;
  FILE * out_stream = NULL;

  if (argc == 1) {
      in_stream = stdin;
      out_stream = stdout;
  }
  else {
      in_stream = fopen(argv[1], "r");
      if (!in_stream) {
          printf("File \"%s\" cannot find or open\n", argv[1]);
          return 1;
      }
      out_stream = fopen(OUT_FILE, "w");
  }

  yyin = in_stream;
  yyout = out_stream;

  t = tableCreate();

  yyparse();
  fclose(out_stream);
  tableFree(); 
}

