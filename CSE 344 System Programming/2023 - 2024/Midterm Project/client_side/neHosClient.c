#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>
#include <dirent.h>
#include <signal.h>

#define MAX_FILE_SIZE (20 * 1024 * 1024)
char client_fifo_name[50];

void signal_handler(int sig, siginfo_t *siginfo, void *context) {
  if (sig == SIGINT) {
    write(STDOUT_FILENO, "\nKill signal received...\nTerminating...\n",
          strlen("\nKill signal received...\nTerminating...\n"));
    unlink(client_fifo_name);
    exit(0);
  }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        char tempbuffer1[50];
        snprintf(tempbuffer1, sizeof(tempbuffer1), "Usage: %s <connect/tryConnect> <ServerPID>\n", argv[0]);
        write(STDOUT_FILENO,tempbuffer1,strlen(tempbuffer1));        
        exit(1);
    }

    char *server_fifo = (char *)malloc(20 * sizeof(char));
    sprintf(server_fifo,"/tmp/%d_server_fifo",atoi(argv[2]));
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_sigaction = &signal_handler;
    sa.sa_flags = SA_SIGINFO;
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("Error setting up signal handler");
        exit(EXIT_FAILURE);
    }
    if(access(server_fifo, F_OK) == 0){
        int server_fd = open(server_fifo, O_WRONLY);
        if (server_fd == -1) {
            perror("open");
            exit(1);
        }

        pid_t client_pid = getpid();

        ssize_t bytes_written = write(server_fd, &client_pid, sizeof(pid_t));
        if (bytes_written == -1) {
            perror("write");
            exit(1);
        }
        close(server_fd);

        snprintf(client_fifo_name,sizeof(client_fifo_name),"/tmp/%d_fifo",client_pid);
        while (access(client_fifo_name, F_OK) == -1) {
            sleep(1);
        }
        int client_fd = open(client_fifo_name, O_RDONLY);
        if (client_fd == -1) {
            perror("open");
            exit(1);
        }
        char response[50];
        ssize_t bytes_read = read(client_fd, &response, sizeof(response));
        if (bytes_read == -1) {
            perror("read");
            exit(1);
        }
        if(strcmp(response,"Connection established") == 0){
            write(STDOUT_FILENO,"Connection established\n",strlen("Connection established\n"));
            close(client_fd);
            usleep(10000);
            
            char buffer[1024];
            int client_fdp = open(client_fifo_name, O_WRONLY);
            if (client_fdp == -1) {
                perror("open");
                exit(1);
            }
            do{
                write(STDOUT_FILENO,"Enter comment: ",strlen("Enter comment: "));
                ssize_t bytes_read = read(STDIN_FILENO, &buffer, sizeof(buffer));
                if (bytes_read == -1) {
                    perror("read");
                    exit(1);
                }
                if(access(client_fifo_name,F_OK) != 0){
                    write(STDOUT_FILENO,"Server shutted down\n",strlen("Server shutted down\n"));
                    break;
                }            
                buffer[strcspn(buffer, "\n")] = '\0';

                bytes_written = write(client_fdp, &buffer, sizeof(buffer));
                if (bytes_written == -1) {
                    perror("write");
                    exit(1);
                }
                sleep(1);
                int client_fd_rd = open(client_fifo_name, O_RDONLY);
                if (client_fd_rd == -1) {
                    perror("open");
                    exit(1);
                }
                if(strncmp(buffer,"upload",6) == 0){
                    char *filename = (char *)malloc(50 * sizeof(char));
                    sscanf(buffer, "upload %s", filename);

                    char upfifoname[50];
                    strcat(upfifoname,client_fifo_name);
                    strcat(upfifoname,"_upload");
                    int upFile = open(filename, O_RDONLY);
                    if (upFile == -1) {
                        perror("open");
                        exit(-1);
                    }  
                    struct stat statbuf;
                    if (fstat(upFile, &statbuf) == -1) {
                        perror("fstat source file");
                        close(upFile);
                        return -1;
                    }

                    if (statbuf.st_size > MAX_FILE_SIZE) {
                        fprintf(stderr, "Error: File size exceeds maximum (20MB)\n");
                        close(upFile);
                        return -1;
                    }

                    // Create FIFO (if it doesn't exist)
                    if (mkfifo(upfifoname, 0666) == -1 && errno != EEXIST) {
                        perror("mkfifo");
                        close(upFile);
                        return -1;
                    }

                    usleep(10000);
                    int upfifo = open(upfifoname, O_WRONLY);
                    if (upfifo == -1) {
                        perror("open");
                        exit(-1);
                    }
                    sleep(1);              
                    char recv_buffer[4096];
                    size_t bytes_read, bytes_written, total_written = 0;            
                    while ((bytes_read = read(upFile, recv_buffer, sizeof(recv_buffer))) > 0) {
                        bytes_written = write(upfifo, recv_buffer, bytes_read);
                        if (bytes_written == -1) {
                            perror("write FIFO");
                            close(upFile);
                            close(upfifo);
                            return -1;
                        }
                        total_written += bytes_written;
                        if (total_written > MAX_FILE_SIZE) {
                            fprintf(stderr, "Error: Copied data exceeds maximum size\n");
                            close(upFile);
                            close(upfifo);
                            return -1;
                        }
                    }

                    if (bytes_read == -1) {
                        perror("read source file");
                        close(upFile);
                        close(upfifo);
                        return -1;
                    }

                    close(upFile);
                    close(upfifo);
                    free(filename);
                }
                else if (strncmp(buffer, "download", 8) == 0) {
                    char *filename = (char *)malloc(50 * sizeof(char));
                    sscanf(buffer, "download %s", filename);

                    char downfifoname[50];
                    strcat(downfifoname,client_fifo_name);
                    strcat(downfifoname,"_down");

                    usleep(10000);
                    int downfifo = open(downfifoname, O_RDONLY);
                    if (downfifo == -1) {
                        perror("open");
                        exit(-1);
                    }
                    sleep(1);
                    int dest_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
                    if (dest_fd == -1) {
                        perror("open destination file");
                        close(downfifo);
                        return -1;
                    }                         
                    char recv_buffer[4096];
                    size_t bytes_read, bytes_written, total_written = 0;            
                    while ((bytes_read = read(downfifo, recv_buffer, sizeof(recv_buffer))) > 0) {
                        bytes_written = write(dest_fd, recv_buffer, bytes_read);
                        if (bytes_written == -1) {
                            perror("write FIFO");
                            close(dest_fd);
                            close(downfifo);
                            return -1;
                        }
                        total_written += bytes_written;
                        if (total_written > MAX_FILE_SIZE) {
                            fprintf(stderr, "Error: Copied data exceeds maximum size\n");
                            close(dest_fd);
                            close(downfifo);
                            return -1;
                        }
                    }

                    if (bytes_read == -1) {
                        perror("read source file");
                        close(dest_fd);
                        close(downfifo);
                        return -1;
                    }

                    // Close file descriptors
                    close(dest_fd);
                    close(downfifo);
                    free(filename);
                }
                else if (strncmp(buffer, "archServer", 10) == 0) {
                char *filename = (char *)malloc(50 * sizeof(char));
                    sscanf(buffer, "archServer %s", filename);

                    char downfifoname[50];
                    strcat(downfifoname,client_fifo_name);
                    strcat(downfifoname,"_arch");

                    while(access(downfifoname, F_OK) != 0){
                        sleep(1);
                    }
                    int downfifo = open(downfifoname, O_RDONLY);
                    if (downfifo == -1) {
                        perror("open5");
                        exit(-1);
                    }
                    sleep(1);
                    int dest_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
                    if (dest_fd == -1) {
                        perror("open destination file");
                        close(downfifo);
                        return -1;
                    }                         
                    char recv_buffer[4096];
                    size_t bytes_read, bytes_written, total_written = 0;            
                    while ((bytes_read = read(downfifo, recv_buffer, sizeof(recv_buffer))) > 0) {
                        bytes_written = write(dest_fd, recv_buffer, bytes_read);
                        if (bytes_written == -1) {
                            perror("write FIFO");
                            close(dest_fd);
                            close(downfifo);
                            return -1;
                        }
                        total_written += bytes_written;
                        if (total_written > MAX_FILE_SIZE) {
                            fprintf(stderr, "Error: Copied data exceeds maximum size\n");
                            close(dest_fd);
                            close(downfifo);
                            return -1;
                        }
                    }

                    if (bytes_read == -1) {
                        perror("read source file");
                        close(dest_fd);
                        close(downfifo);
                        return -1;
                    }

                    close(dest_fd);
                    close(downfifo);
                    free(filename);                
                }
                bytes_read = read(client_fd_rd, &buffer, sizeof(buffer));
                if (bytes_read == -1) {
                    perror("read");
                    exit(1);
                }
                buffer[bytes_read] = '\0';
                close(client_fd_rd);
                write(STDOUT_FILENO,buffer,strlen(buffer));
                write(STDOUT_FILENO,"\n",strlen("\n"));
                usleep(10000);
                if((strcmp(buffer,"Sending write request to server log file\nwaiting for logfile ...\nlogfile write request granted\nbye..\n") == 0) || strcmp(buffer,"Server shutting down...\n") == 0){
                    break;
                }
            }while((strcmp(buffer,"quit") != 0) || (strcmp(buffer,"killServer") != 0));
            
            close(client_fdp);
        }
        else{
            write(STDOUT_FILENO,"Connection Failed. Server is full.\n",strlen("Connection Failed. Server is full.\n"));
        }
    }
    else{
        write(STDOUT_FILENO,"Wrong PID. Connection Failed.\n",strlen("Wrong PID. Connection Failed.\n"));
    }
    return 0;
}
