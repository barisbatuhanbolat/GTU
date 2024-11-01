#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <time.h>

#define FIFO1 "fifo1"
#define FIFO2 "fifo2"

int child_count = 0;
int n=10; 

/*
 * Signal handler function to handle SIGCHLD signal for child process termination.
 * 
 * This function is called whenever a child process terminates. It iterates
 * through potentially multiple terminated children using waitpid with WNOHANG.
 * It checks if the child exited normally and retrieves its exit status.
 * The function then prints a message to standard output indicating the child's
 * PID and exit status. Finally, it increments a counter variable
 * (child_count) to track the number of terminated child processes.
 */
void signal_handler(int sig, siginfo_t *info, void *ucontext) {
    pid_t pid;
    int status;
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        if (WIFEXITED(status)) {
            char buffer[50];
            sprintf(buffer,"Child %d terminated with exit status %d\n", pid, WEXITSTATUS(status));
            ssize_t stdWrite = write(STDOUT_FILENO, buffer, strlen(buffer));
            if (stdWrite == -1) {
                perror("Error writing to STDOUT");
                exit(EXIT_FAILURE);
            }
            child_count++;
        }
    }
}
/*
 * This main function performs the following tasks:
 *  1. Handles command-line argument validation (expects a single integer).
 *  2. Creates named pipes (FIFOs) for communication between processes.
 *  3. Sets up a signal handler (`signal_handler`) for SIGCHLD to monitor child termination.
 *  4. Generates a list of random numbers.
 *  5. Creates two child processes using fork.
 *      - Child 1: Reads the list from FIFO1, calculates the sum, writes the sum to FIFO2.
 *      - Child 2: Reads the list and command from FIFO2, calculates multiplication, 
 *                 prints sum, multiplication, and total result, validates the command.
 *  6. The parent process:
 *      - Writes the list to FIFO1 for Child 1.
 *      - Writes the "multiply" command to  FIFO2 for Child 2.
 *      - Waits for both child processes to finish using the signal handler and a counter.
 *  7. Cleans up by closing and removing the named pipes.
 */
int main(int argc, char *argv[]) {
    unlink(FIFO1);
    unlink(FIFO2);
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <integer_argument>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    int i;
    int valid = 1;
    argv[1][strlen(argv[1])] = '\0';
    for (i = 0; i < strlen(argv[1]) - 1; i++) {
        if (argv[1][i] < '0' || argv[1][i] > '9') {
            valid = 0;
            break;
        }
    }
    if (valid) {
        n = atoi(argv[1]);
        if (!(n >= 0 && n <= 100)) {
            write(STDERR_FILENO, "Not a valid number\n", strlen("Not a valid number\n"));
            exit(EXIT_FAILURE);
        } 
    } 
    else {
        write(STDERR_FILENO, "Not a number\n", strlen("Not a number\n"));
        exit(EXIT_FAILURE);
    }    

    if (mkfifo(FIFO1, 0666) < 0 || mkfifo(FIFO2, 0666) < 0) {
        perror("Error creating FIFOs");
        exit(EXIT_FAILURE);
    }

    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_sigaction = &signal_handler;
    sa.sa_flags = SA_SIGINFO;
    
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("Error setting up signal handler");
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));
    int numbers[n]; 
    for (int i = 0; i < n; i++) {
        numbers[i] = rand() % 10;
    }

    pid_t pid1, pid2;
    if ((pid1 = fork()) == 0) {    
		for(int i = 0;i<5;i++) {  
            write(STDOUT_FILENO, "Proceeding...\n", strlen("Proceeding...\n"));
            sleep(2);
        }

        int fd = open(FIFO1, O_RDONLY);
        if (fd == -1) {
            perror("Child 1 failed to open FIFO1 for reading");
            exit(EXIT_FAILURE);
        }

        int sum = 0;
        int nums2[n];
        read(fd, nums2, sizeof(nums2));
        for (int i = 0; i < n; i++) {
            sum += nums2[i];
        }

        int fd2 = open(FIFO2, O_WRONLY);
        
        if (fd2 == -1) {
            perror("Child 1 failed to open FIFO2 for writing");
            exit(EXIT_FAILURE);
        }
        write(fd2, &sum, sizeof(sum));
        close(fd);
        close(fd2);
        exit(EXIT_SUCCESS);
    } 
	else if ((pid2 = fork()) == 0) {
        int fd = open(FIFO2, O_RDONLY);
        if (fd == -1) {
            perror("Child 2 failed to open FIFO2 for reading");
            exit(EXIT_FAILURE);
        }
        
        int numbers2[n];
        read(fd, numbers2, sizeof(numbers2));  
        
        char command[10];
        read(fd, command, sizeof(command));    

        close(fd);

        int fdx = open(FIFO2, O_RDONLY);
        if (fdx == -1) {
            perror("Child 2 failed to open FIFO2 for reading");
            exit(EXIT_FAILURE);
        }

        int sum=0;  
        read(fd, &sum, sizeof(sum));       

        if (strcmp(command, "multiply") == 0) {             
            int multiplication = 1;
            for (int i = 0; i < n; i++) {
                multiplication *= numbers2[i];       
            }
            
			char buffer1[50];
            sprintf(buffer1,"Multiplication : %d , Sum : %d\n", multiplication,sum);
			write(STDOUT_FILENO, buffer1, strlen(buffer1));		
            int total_result = sum + multiplication;   

            char buffer[256];
            int len = snprintf(buffer, sizeof(buffer), "Total result: %d\n", total_result);
            write(STDOUT_FILENO, buffer, len);       
            close(fd); 
            exit(EXIT_SUCCESS);
        } 
		else {
            perror("Invalid command received by Child 2");
            exit(EXIT_FAILURE);
        }
    } 
	else {
        int fd2 = open(FIFO2, O_WRONLY);   
        if (fd2 == -1) {
            perror("Failed to open FIFOs for writing");
            exit(EXIT_FAILURE);
        }
        write(fd2, numbers, sizeof(numbers));
        char command[] = "multiply";
        write(fd2, command, sizeof(command));
        int fd1 = open(FIFO1, O_WRONLY);   
        
		if (fd1 == -1) {
            perror("Failed to open FIFOs for writing");
            exit(EXIT_FAILURE);
        }
        write(fd1, numbers, sizeof(numbers));
        while (child_count < 2) {  
            write(STDOUT_FILENO, "Proceeding...\n", strlen("Proceeding...\n"));
            sleep(2);
        }
        close(fd1);
        close(fd2); 
        unlink(FIFO1);
        unlink(FIFO2);
        exit(EXIT_SUCCESS);
    }
}
