#include "utils.h"
/*
This function searches for a student's record in a file by name. 
It uses a child process to perform the search and returns a pointer to the student's line in the file if found, otherwise it returns NULL.
*/
char * searchStudent(const char *name, const char *filename) {
    pid_t pid = fork();
    if (pid == 0) {
        int fd = open(filename, O_RDONLY);
        if (fd == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }
        ssize_t bytes_read;
        char buffer[MAX_LINE_SIZE];
        char newbuffer[MAX_LINE_SIZE];
        char *line = NULL;
        int line_length = 0;
        while ((bytes_read = read(fd, buffer, MAX_LINE_SIZE)) > 0) {
            for (int i = 0; i < bytes_read; i++) {
                if (buffer[i] == '\n') {
                    line = malloc(line_length + 1);
                    if (line == NULL) {
                        perror("Memory allocation failed");
                        exit(EXIT_FAILURE);
                    }
                    memcpy(line, buffer + i - line_length, line_length);
                    line[line_length] = '\0';
                    int j = 0;
                    for (j = 0; line[j] != '\0' && line[j] != ','; j++) {
                        newbuffer[j] = line[j];
                    }
                    newbuffer[j] = '\0';
                    if(strcmp(newbuffer,name) == 0){
                        exit(EXIT_SUCCESS);
                        return line;
                    }
                    free(line);
                    line_length = 0;
                } 
                else {
                    line_length++;
                }
            }
        }
        close(fd);
        exit(EXIT_FAILURE);
        return NULL;
    }
    else if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);
        if (status == 0) {
            ssize_t tempWrite = write(STDOUT_FILENO, "Student found successfully.\n", 
                                                    strlen("Student found successfully.\n"));
            if (tempWrite == -1) {
                perror("write");
                exit(EXIT_FAILURE);
            }
        } 
        else {            
            ssize_t tempWrite2 = write(STDOUT_FILENO, "Student search failed.\n", 
                                                    strlen("Student search failed.\n"));
            if (tempWrite2 == -1) {
                perror("write");
                exit(EXIT_FAILURE);
            }
        }        
    } 
    else {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }    
    return NULL;
}
/*
This function adds a new student's name and grade to a file. 
It uses a child process to open the file, check for duplicates, and then write the new student's information to the end of the file.
*/
void addStudentGrade(const char *name, const char *grade, const char *filename) {
    pid_t pid = fork();
    if (pid == 0) {
        int fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR);
        if (fd == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }
        char * isFound = searchStudent(name,filename);
        if(isFound != NULL){
            perror("exists");
            exit(EXIT_FAILURE);
        }
        ssize_t nameWrite = write(fd, name, strlen(name));
        ssize_t comWrite = write(fd, ", ", strlen(", "));
        ssize_t gradeWrite = write(fd, grade, strlen(grade));
        ssize_t newWrite = write(fd, "\n", strlen("\n"));

        if (nameWrite == -1 || comWrite == -1 || gradeWrite == -1 || newWrite == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }
        if (close(fd) == -1) {
            perror("close");
            exit(EXIT_FAILURE);
        }
        close(fd);
        exit(EXIT_SUCCESS);        
    }
    else if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);
        if (status == 0) {
            ssize_t tempWrite = write(STDOUT_FILENO, "Student grade added successfully.\n", 
                                                    strlen("Student grade added successfully.\n"));
            if (tempWrite == -1) {
                perror("write");
                exit(EXIT_FAILURE);
            }
        } 
        else {            
            ssize_t tempWrite2 = write(STDOUT_FILENO, "Error occurred while adding student grade.\n", 
                                                    strlen("Error occurred while adding student grade.\n"));
            if (tempWrite2 == -1) {
                perror("write");
                exit(EXIT_FAILURE);
            }
        }
    } 
    else {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
}

int compare_strings(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}
/*
This function sorts all the students in a file based on their names in ascending order. 
It uses a child process to read the entire file, store each line in an array, sort the array using qsort, and then print the sorted student records.
*/
void sortAll(char * filename){
    pid_t pid = fork();
    if (pid == 0) {
        int fd = open(filename, O_RDONLY);
        if (fd == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }
        ssize_t bytes_read;
        char buffer[MAX_LINE_SIZE];
        char nameBuffer[MAX_LINE_SIZE];
        char gradeBuffer[MAX_LINE_SIZE];
        char temp[MAX_LINE_SIZE];

        char *lines[MAX_LINE_SIZE];
        int num_lines = 0;

        int line_length = 0;
        while ((bytes_read = read(fd, buffer, MAX_LINE_SIZE)) > 0) {
            for (int i = 0; i < bytes_read; i++) {
                if (buffer[i] == '\n') {
                    lines[num_lines] = malloc(line_length + 1);
                    if (lines[num_lines] == NULL) {
                        perror("Memory allocation failed");
                        exit(EXIT_FAILURE);
                    }
                    memcpy(lines[num_lines], buffer + i - line_length, line_length);
                    lines[num_lines][line_length] = '\0';

                    num_lines++;
                    line_length = 0;
                }
                else {
                    line_length++;
                }
            }
        }
        qsort(lines, num_lines, sizeof(char *), compare_strings);
        for(int i = 0;i<num_lines;i++){
            printf("%s\n",lines[i]);
        }
        close(fd);
        exit(EXIT_SUCCESS);
    }
    else if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);
        if (status == 0) {
            ssize_t buffWrite1 = write(STDOUT_FILENO, "Students sorted successfully.\n",
                                                    strlen("Students sorted successfully.\n"));
            if (buffWrite1 == -1) {
                perror("write");
                exit(EXIT_FAILURE);
            }
        } 
        else {
            ssize_t buffWrite2 = write(STDOUT_FILENO, "Error occurred while sorted.\n",
                                                    strlen("Error occurred while sorted.\n"));
            if (buffWrite2 == -1) {
                perror("write");
                exit(EXIT_FAILURE);
            }            
        }            
    } else {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }    
}
/*
This function displays all the student records in a file.  
It uses a child process to open the file and print its entire contents.
*/
void showAll(char * filename){
    pid_t pid = fork();
    if (pid == 0) {    
        int fd = open(filename, O_RDONLY);
        if (fd == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }
        char buffer[MAX_LINE_SIZE]; 

        while (read(fd, buffer, sizeof(buffer)) > 0) {            
            ssize_t buffWrite = write(STDOUT_FILENO, buffer,strlen(buffer));
            if (buffWrite == -1) {
                perror("write");
                exit(EXIT_FAILURE);
            }
        }
        close(fd);
        exit(EXIT_SUCCESS);
    }
    else if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);
        if (status == 0) {
            ssize_t buffWrite1 = write(STDOUT_FILENO, "Students displayed successfully.\n",
                                                    strlen("Students displayed successfully.\n"));
            if (buffWrite1 == -1) {
                perror("write");
                exit(EXIT_FAILURE);
            }
        } 
        else {
            ssize_t buffWrite2 = write(STDOUT_FILENO, "Error occurred while displaying.\n",
                                                    strlen("Error occurred while displaying.\n"));
            if (buffWrite2 == -1) {
                perror("write");
                exit(EXIT_FAILURE);
            }            
        }        
    } 
    else {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }      
}
/*
This function lists the first 5 grades in a file. 
It uses a child process to open the file, read line by line, and print only the first 5 student grades encountered.
*/
void listGrades(char * filename){
    pid_t pid = fork();
    if (pid == 0) {        
        int fd = open(filename, O_RDONLY);
        if (fd == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }
        int count = 0;
        ssize_t bytes_read;
        char buffer[MAX_LINE_SIZE];
        char newbuffer[MAX_LINE_SIZE];
        char *line = NULL;
        int line_length = 0;
        while ((bytes_read = read(fd, buffer, MAX_LINE_SIZE)) > 0) {
            for (int i = 0; i < bytes_read; i++) {
                if (buffer[i] == '\n' && count<5) {
                    line = malloc(line_length + 1);
                    if (line == NULL) {
                        perror("Memory allocation failed");
                        exit(EXIT_FAILURE);
                    }
                    memcpy(line, buffer + i - line_length, line_length);
                    line[line_length] = '\0';
                    ssize_t lineWrite = write(STDOUT_FILENO, line, strlen(line));
                    ssize_t newLine = write(STDOUT_FILENO, "\n", strlen("\n"));
                    if (lineWrite == -1 || newLine == -1) {
                        perror("write");
                        exit(EXIT_FAILURE);
                    }
                    free(line);
                    line_length = 0;
                    count++;
                } 
                else {
                    line_length++;
                }
            }
        }
        close(fd);
        exit(EXIT_SUCCESS);
    }
    else if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);  
        if (status == 0) {
            ssize_t buffWrite1 = write(STDOUT_FILENO, "First 5 students listed succesfully.\n",strlen("First 5 students listed succesfully.\n"));
            if (buffWrite1 == -1) {
                perror("write");
                exit(EXIT_FAILURE);
            }
        } 
        else {
            ssize_t buffWrite2 = write(STDOUT_FILENO, "Error occurred while listing.\n",strlen("Error occurred while listing.\n"));
            if (buffWrite2 == -1) {
                perror("write");
                exit(EXIT_FAILURE);
            }            
        }           
    } 
    else {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }           
}
/*
This function displays a specified number of student records starting from a specified page number. 
It uses a child process to open the file, keep track of line count, and then print only the requested number of entries based on the page number and entries per page. 
If no records are found on the specified page, it displays a message.
*/
void listSome(int numofEntries, int pageNumber, char * filename){
    pid_t pid = fork();
    if (pid == 0) {  
        int fd = open(filename, O_RDONLY);
        if (fd == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }
        int count1 = 0;
        int count2 = 0;
        ssize_t bytes_read;
        char buffer[MAX_LINE_SIZE];
        char newbuffer[MAX_LINE_SIZE];
        char *line = NULL;
        int line_length = 0;
        int temp = 5*(pageNumber - 1);
        while ((bytes_read = read(fd, buffer, MAX_LINE_SIZE)) > 0) {            
            for (int i = 0; i < bytes_read; i++) {
                if (buffer[i] == '\n') {
                    line = malloc(line_length + 1);
                    if (line == NULL) {
                        perror("Memory allocation failed");
                        exit(EXIT_FAILURE);
                    }
                    memcpy(line, buffer + i - line_length, line_length);
                    line[line_length] = '\0';
                    if(count1 > temp && count2<numofEntries){
                        ssize_t lineWrite = write(STDOUT_FILENO, line, strlen(line));
                        ssize_t newLine = write(STDOUT_FILENO, "\n", strlen("\n"));
                        if (lineWrite == -1 || newLine == -1) {
                            perror("write");
                            exit(EXIT_FAILURE);
                        }
                        count2++;
                    }
                    free(line);
                    line_length = 0;                    
                    count1++;
                } 
                else {
                    line_length++;
                }
            }            
        }
        close(fd);
        exit(EXIT_SUCCESS);     
    }
    else if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);
        if (status == 0) {
            char buffer[100];
            int length = sprintf(buffer, "Page %d / %d Entries listed successfully\n", pageNumber, numofEntries);

            if (write(STDOUT_FILENO, buffer, length) == -1) {
                perror("Error writing to STDOUT");
                perror("write");
                exit(EXIT_FAILURE);
            }
        } 
        else {
            if (write(STDOUT_FILENO, "Error occurred while listing.\n",strlen("Error occurred while listing.\n")) == -1) {
                perror("write");
                exit(EXIT_FAILURE);
            }               
        }
    }
    else {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }        
}
char** split_command(char* str) {
    int num_tokens = 0;
    int in_quote = 0;

    char* ptr = str;
    while (*ptr) {
        if (*ptr == '"') {
            in_quote = !in_quote; 
        } else if (!in_quote && strchr(" ", *ptr)) {
            num_tokens++;
        }
        ptr++;
    }
    char** tokens;
    if (*ptr == '\0' && num_tokens == 0) {
        num_tokens++;
        tokens = malloc(2 * sizeof(char*));
        tokens[0] = malloc(strlen(str) + 1);
        strcpy(tokens[0], str);
        tokens[1] = NULL;
        return tokens;
    }
    tokens = malloc((num_tokens + 1) * sizeof(char*));
    if (!tokens) {
        return NULL; 
    }

    ptr = str;
    int token_index = 0;
    char* token_start = ptr;

    while (*ptr) {
        if (*ptr == '"') {
            in_quote = !in_quote;
        } else if (!in_quote && strchr(" ", *ptr)) {
            tokens[token_index] = malloc((ptr - token_start) + 1);
            if (!tokens[token_index]) {
                for (int j = 0; j < token_index; j++) {
                    free(tokens[j]);
                }
                free(tokens);
                return NULL;
            }
            strncpy(tokens[token_index], token_start, ptr - token_start);
            tokens[token_index][ptr - token_start] = '\0'; 

            token_index++;
            token_start = ptr + 1;
        }
        ptr++;
    }
    if (ptr > token_start) {
        tokens[token_index] = malloc(ptr - token_start + 1);
        if (!tokens[token_index]) {
            for (int j = 0; j < token_index; j++) {
                free(tokens[j]);
            }
            free(tokens);
            return NULL;
        }
        strncpy(tokens[token_index], token_start, ptr - token_start);
        tokens[token_index][ptr - token_start] = '\0';
        token_index++;
    }
    tokens[token_index] = NULL;
    for (int i = 0; i < token_index; i++) {
        if(tokens[i][0] == '"'){
            int string_len = strlen(tokens[i]);
            if (string_len > 1) {
                char *src = tokens[i] + 1;
                char *dst = tokens[i];
                while (*src && src < tokens[i] + string_len - 1) {
                    *dst++ = *src++;
                }
                *dst = '\0';
            }
        }
    }
    return tokens;
}
/*
This function writes a log message to a file named "records.log"
It appends the message to the end of the file, along with a timestamp
It takes a string containing the log message as input
It returns nothing
*/
void logFile(char * log){
    pid_t pid = fork();
    if (pid == 0) {
        int fd = open("records.log", O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR);
        if (fd == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }
        time_t current_time;
        char *formatted_time;
        current_time = time(NULL);
        formatted_time = ctime(&current_time);
        int i,j;
        for (i = j = 0; formatted_time[i] != '\0'; i++) {
            if (formatted_time[i] != '\n') {
            formatted_time[j++] = formatted_time[i];
            }
        }
        formatted_time[j] = '\0';
        
        char logWritten[MAX_LINE_SIZE];
        sprintf(logWritten,"[%s] %s",formatted_time,log);
        ssize_t logWrite = write(fd, logWritten, strlen(logWritten));
        if (logWrite == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }
        if (close(fd) == -1) {
            perror("close");
            exit(EXIT_FAILURE);
        }
        exit(EXIT_SUCCESS);
    }

    else if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);
        if (status == 0) {
            ssize_t tempWrite = write(STDOUT_FILENO, "Saved to records.log.\n", 
                                                    strlen("Saved to records.log.\n"));
            if (tempWrite == -1) {
                perror("write");
                exit(EXIT_FAILURE);
            }
        } 
        else {            
            ssize_t tempWrite2 = write(STDOUT_FILENO, "Error occurred while logging.\n", 
                                                    strlen("Error occurred while logging.\n"));
            if (tempWrite2 == -1) {
                perror("write");
                exit(EXIT_FAILURE);
            }
        }
    } 
    else {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }    
}