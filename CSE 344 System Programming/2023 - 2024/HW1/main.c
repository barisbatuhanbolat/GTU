#include <stdio.h>
#include "utils.h"

int main() {
    char command[MAX_LINE_LEN];
    char **args;
    pid_t pid;
    char log[MAX_LINE_SIZE];

    while (1) {
        write(STDOUT_FILENO, "$ ", 2);
        ssize_t bytesRead = read(STDIN_FILENO, command, sizeof(command));
        if (bytesRead == -1) {
            perror("read");
            return 1;
        }
        command[strcspn(command, "\n")] = '\0';
        
        if (strcmp(command, "exit") == 0) {
            for (int j = 0; args[j] != NULL; j++) {
                free(args[j]);
            }
            free(args);
            sprintf(log,"Exited\n");
            logFile(log);
            exit(0);
        }
        else if(strcmp(command,"gtuStudentGrades") == 0){
            write(STDOUT_FILENO, "Available commands:\n", 20);
            write(STDOUT_FILENO, "1 - gtuStudentGrades <filename>\n", 31);
            write(STDOUT_FILENO, "--Creates the file if it doesn't exists.\n", 42);
            write(STDOUT_FILENO, "2 - addStudentGrade <name> <grade> <filename> \n", 48);
            write(STDOUT_FILENO, "--Appends student and grade to the end of the file.\n", 53);
            write(STDOUT_FILENO, "3 - searchStudent <name> <filename> \n", 38);
            write(STDOUT_FILENO, "--Returns student name surname and grade.\n", 41);
            write(STDOUT_FILENO, "4 - sortAll <filename>\n", 23);
            write(STDOUT_FILENO, "--Prints all of the entries sorted by their names.\n", 51);
            write(STDOUT_FILENO, "5 - showAll <filename>\n", 24);
            write(STDOUT_FILENO, "--Prints all of the entries in the file.\n", 41);
            write(STDOUT_FILENO, "6 - listGrades <filename>\n", 27);
            write(STDOUT_FILENO, "--Prints first 5 entries.\n", 26);
            write(STDOUT_FILENO, "7 - listSome <numofEntries> <pageNumber> <filename>\n", 52);
            write(STDOUT_FILENO, "--e.g. listSome 5 2 \"grades.txt\" command will list entries between 5th and 10th.\n", 82);
            
            sprintf(log,"Usage Printed\n");
            logFile(log);
        }
        else{
            args = split_command(command);
            int i = 0;
            for (int j = 0; args[j] != NULL; j++) {
                i++;
            }
            switch (i) {
                case 2:
                    if(strcmp(args[0], "gtuStudentGrades") == 0){
                        int f_flag=0;
                        if (access(args[1], F_OK) != 0) {
                            int fd = open(args[1], O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR);
                            if (fd == -1) {
                                perror("open");
                                exit(EXIT_FAILURE);
                            }
                            close(fd);
                            f_flag = 1;
                        }
                        if(f_flag){
                            sprintf(log,"File not found. A new file named %s was created.\n",args[1]);
                            logFile(log);
                        }
                        else{
                            sprintf(log,"File exists.\n");
                            logFile(log);
                        }
                    }
                    else if(strcmp(args[0], "sortAll") == 0){
                        sortAll(args[1]);
                        sprintf(log,"All entries in the %s are sorted alphabetically.\n",args[1]);
                        logFile(log);
                    }
                    else if(strcmp(args[0], "showAll") == 0){
                        showAll(args[1]);
                        sprintf(log,"All entries in the %s are printed in the screen.\n",args[1]);
                        logFile(log);
                    }
                    else if(strcmp(args[0], "listGrades") == 0){
                        listGrades(args[1]);
                        sprintf(log,"First 5 entries in the  %s are printed in the screen.\n",args[1]);
                        logFile(log);
                    }
                    else {
                        ssize_t wrongCommand = write(STDOUT_FILENO, "Command not found\n", strlen("Command not found\n"));
                        if (wrongCommand == -1) {
                            perror("Error writing to STDOUT");
                            return EXIT_FAILURE;
                        }
                    }
                    break;
                case 3:
                    if(strcmp(args[0], "searchStudent") == 0){
                        char * found_student = searchStudent(args[1],args[2]);
                        if(found_student != NULL){
                            ssize_t studentWritten = write(STDOUT_FILENO, found_student, strlen(found_student));
                            ssize_t newLineWritten = write(STDOUT_FILENO, "\n", 2);
                            if (studentWritten == -1 || newLineWritten == -1) {
                                perror("Error writing to STDOUT");
                                return EXIT_FAILURE;
                            }
                            sprintf(log,"%s is found in %s .\n",found_student,args[2]);
                            logFile(log);
                        }
                        else{
                            sprintf(log,"%s is not found in %s .\n",args[1],args[2]);
                            logFile(log);
                        }
                        
                    }
                    else {
                        ssize_t wrongCommand = write(STDOUT_FILENO, "Command not found\n", strlen("Command not found\n"));
                        if (wrongCommand == -1) {
                            perror("Error writing to STDOUT");
                            return EXIT_FAILURE;
                        }
                    }                    
                    break;
                case 4:
                    if(strcmp(args[0], "addStudentGrade") == 0){
                        addStudentGrade(args[1],args[2],args[3]);
                        sprintf(log,"%s is added to %s with grade %s .\n",args[1],args[3],args[2]);
                        logFile(log);
                    }
                    else if(strcmp(args[0], "listSome") == 0){
                        listSome(atoi(args[1]),atoi(args[2]),args[3]);
                        sprintf(log,"The %s entries on page %s of the %s file were printed to the screen.\n",args[1],args[2],args[3]);
                        logFile(log);
                    }
                    else {
                        ssize_t wrongCommand = write(STDOUT_FILENO, "Command not found\n", strlen("Command not found\n"));
                        if (wrongCommand == -1) {
                            perror("Error writing to STDOUT");
                            return EXIT_FAILURE;
                        }
                    }                    
                    break;
                default:
                    pid = fork();
                    if (pid < 0) {
                        ssize_t bytes_written = write(STDERR_FILENO, "Fork failed\n", strlen("Fork failed\n"));
                        if (bytes_written == -1) {
                            perror("Error writing to STDERR");
                            return EXIT_FAILURE;
                        }                        
                        for (int j = 0; args[j] != NULL; j++) {
                            free(args[j]);
                        }
                        free(args);
                        exit(1);
                    } 
                    else if (pid == 0) {
                        execvp(command, args);
                        ssize_t bytes_written2 = write(STDERR_FILENO, "Command not found\n", strlen("Command not found\n"));
                        if (bytes_written2 == -1) {
                            perror("Error writing to STDERR");
                            return EXIT_FAILURE;
                        }                            
                        for (int j = 0; args[j] != NULL; j++) {
                            free(args[j]);
                        }
                        free(args);
                        exit(1);
                    } 
                    else {
                        int status;
                        waitpid(pid, &status, 0);
                    }
                    break;
            }
        }
    }
    for (int j = 0; args[j] != NULL; j++) {
        free(args[j]);
    }
    free(args);
    return 0;
}