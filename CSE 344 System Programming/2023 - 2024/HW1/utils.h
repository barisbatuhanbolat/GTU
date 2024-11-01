#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>

#define MAX_NAME_LEN 50
#define MAX_GRADE_LEN 3
#define MAX_LINE_LEN (MAX_NAME_LEN + MAX_GRADE_LEN + 2)
#define MAX_LINE_SIZE 1024

void addStudentGrade(const char *name, const char *grade, const char *filename);
char * searchStudent(const char *name, const char *filename);
int compare_strings(const void *a, const void *b);
void sortAll(char * filename);
void showAll(char * filename);
void listGrades(char * filename);
void listSome(int numofEntries, int pageNumber, char * filename);
char** split_command(char* str);
void logFile(char * log);
