#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>
#include <dirent.h>
#include <signal.h>

#define MAX_FILE_SIZE (20 * 1024 * 1024)
#define MAX_CLIENTS 10
char directory[100];
int log_file;
int connected_clients = 0;
pid_t client_pids[MAX_CLIENTS];
char server_fifo[20];
sem_t sem;
void signal_handler(int sig, siginfo_t *siginfo, void *context) {
  if (sig == SIGINT) {
    write(STDOUT_FILENO, "\nKill signal received...\nTerminating...\n",
          strlen("\nKill signal received...\nTerminating...\n"));
    for (int i = 0; i < connected_clients; i++) {
        char client_fifo_name[256];
        snprintf(client_fifo_name, sizeof(client_fifo_name), "/tmp/%d_fifo", client_pids[i]);
        unlink(client_fifo_name);
    }
    unlink(server_fifo);
    exit(0);
  }
}

int handle_client(char *client_fifo_name,pid_t client_pid) {
    char buffer[1024];
    int n;
    int client_fd = open(client_fifo_name, O_RDONLY);
    if (client_fd == -1) {
        perror("open");
        exit(-1);
    }
    int i = 0;
    do{
        read(client_fd, &buffer, sizeof(buffer));
        buffer[strlen(buffer)] = '\0';
        sleep(1);
        if (strncmp(buffer, "help",4) == 0) {
            sem_wait(&sem);
            int client_fd_wr = open(client_fifo_name, O_WRONLY);
            if (client_fd_wr == -1) {
                perror("open");
                exit(-1);
            }
            if(strcmp(buffer, "help") == 0){
                write(client_fd_wr, "Available commands are:\nhelp, list, readF, writeT, upload, download, archServer, quit, killServer\n", 
                                    strlen("Available commands are:\nhelp, list, readF, writeT, upload, download, archServer, quit, killServer\n"));
                char log[150];
                snprintf(log,sizeof(log),"Client PID: %d used help command.\n",client_pid);
                write(log_file,log,strlen(log));                    
            }
            else if(strcmp(buffer, "help list") == 0){
                write(client_fd_wr, "list\nsends a request to display the list of files in Servers directory (also displays the list received from the Server)\n",
                                strlen("list\nsends a request to display the list of files in Servers directory (also displays the list received from the Server)\n"));                
                char log[150];
                snprintf(log,sizeof(log),"Client PID: %d used help list command.\n",client_pid);
                write(log_file,log,strlen(log));       
            }
            else if(strcmp(buffer, "help readF") == 0){
                write(client_fd_wr, "readF <file> <line #>\nrequests to display the # line of the <file>, if no line number is given the whole contents of the file is requested (and displayed on the client side)\n",
                                    strlen("readF <file> <line #>\nrequests to display the # line of the <file>, if no line number is given the whole contents of the file is requested (and displayed on the client side)\n"));
                char log[150];
                snprintf(log,sizeof(log),"Client PID: %d used help readF command.\n",client_pid);
                write(log_file,log,strlen(log));                                       
            }
            else if(strcmp(buffer, "help writeF") == 0){
                write(client_fd_wr, "writeT <file> <line #> <string>\nrequest to write the content of “string” to the #th line the <file>, if the line # is not given writes to the end of file. If the file does not exists in Servers directory creates and edits the file at the same time\n",
                                    strlen("writeT <file> <line #> <string>\nrequest to write the content of “string” to the #th line the <file>, if the line # is not given writes to the end of file. If the file does not exists in Servers directory creates and edits the file at the same time\n"));
                char log[150];
                snprintf(log,sizeof(log),"Client PID: %d used help writeF command.\n",client_pid);
                write(log_file,log,strlen(log));                 
            }
            else if(strcmp(buffer, "help upload") == 0){
                write(client_fd_wr, "upload <file>\nuploads the file from the current working directory of client to the Servers directory (beware of the cases no file in clients current working directory and file with the same name on Servers side)\n",
                                    strlen("upload <file>\nuploads the file from the current working directory of client to the Servers directory (beware of the cases no file in clients current working directory and file with the same name on Servers side)\n"));
                char log[150];
                snprintf(log,sizeof(log),"Client PID: %d used help upload command.\n",client_pid);
                write(log_file,log,strlen(log));
            }
            else if(strcmp(buffer, "help download") == 0){
                write(client_fd_wr, "download <file>\nrequest to receive <file> from Servers directory to client side\n",
                                    strlen("download <file>\nrequest to receive <file> from Servers directory to client side\n"));
                char log[150];
                snprintf(log,sizeof(log),"Client PID: %d used help download command.\n",client_pid);
                write(log_file,log,strlen(log));            
            }
            else if(strcmp(buffer, "help archServer") == 0){
                write(client_fd_wr, "archServer <fileName>.tar\nUsing fork, exec and tar utilities create a child process that will collect all the files currently available on the the Server side and store them in the <filename>.tar archive\n",
                                    strlen("archServer <fileName>.tar\nUsing fork, exec and tar utilities create a child process that will collect all the files currently available on the the Server side and store them in the <filename>.tar archive\n"));
                char log[150];
                snprintf(log,sizeof(log),"Client PID: %d used help archServer command.\n",client_pid);
                write(log_file,log,strlen(log));              
            }
            else if(strcmp(buffer, "help killServer") == 0){
                write(client_fd_wr, "Sends a kill request to the Server\n",
                                    strlen("Sends a kill request to the Server\n"));
                char log[150];
                snprintf(log,sizeof(log),"Client PID: %d used help killServer command.\n",client_pid);
                write(log_file,log,strlen(log));            
            }
            else if(strcmp(buffer, "help quit") == 0){
                write(client_fd_wr, "Send write request to Server side log file and quits\n",
                                    strlen("Send write request to Server side log file and quits\n"));
                char log[150];
                snprintf(log,sizeof(log),"Client PID: %d used help quit command.\n",client_pid);
                write(log_file,log,strlen(log));            
            }
            close(client_fd_wr);
            sem_post(&sem);
        }
        else if (strcmp(buffer, "list") == 0) {
            int client_fd_wr = open(client_fifo_name, O_WRONLY);
            if (client_fd_wr == -1) {
                perror("open");
                exit(-1);
            }
            DIR *dir;
            struct dirent *ent;
            char list_str[1024] = "";
            if ((dir = opendir(directory)) != NULL) {
                while ((ent = readdir(dir)) != NULL) {
                    if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0) {
                        strcat(list_str, ent->d_name);
                        strcat(list_str, "\n");
                    }
                }
                closedir(dir);
            }
            write(client_fd_wr, list_str, strlen(list_str));
            close(client_fd_wr);
            sem_wait(&sem);
            char log[150];
            snprintf(log,sizeof(log),"Client PID: %d listed files in server directory.\n",client_pid);
            write(log_file,log,strlen(log));
            sem_post(&sem);
        }
        else if (strncmp(buffer, "readF", 5) == 0) {
            int client_fd_wr = open(client_fifo_name, O_WRONLY);
            if (client_fd_wr == -1) {
                perror("open");
                exit(-1);
            }            
            char *filename = (char *)malloc(50 * sizeof(char));
            char filetemp[50];
            int line_num = -1;
            sscanf(buffer, "readF %s %d", filetemp, &line_num);
            sprintf(filename,"%s/%s",directory,filetemp);
            sem_wait(&sem);
            int fd = open(filename, O_RDONLY);
            if (fd == -1) {
                perror("Error opening file");
                sem_post(&sem);
            }
            sem_post(&sem);
            if(line_num >=0){
                char buffer[100];
                char *name = NULL;
                int name_count = 0;
                int bytes_read;
                int current_pos = 0;
                int line_start = 0;
                sem_wait(&sem);
                while ((bytes_read = read(fd, buffer + current_pos, 100 - current_pos - 1)) > 0) {
                    current_pos += bytes_read;
                    for (int i = 0; i < current_pos; i++) {
                        if (buffer[i] == '\n') {
                            name_count++;
                            if (name_count == line_num) {
                                int name_length = i - line_start;
                                name = (char *)malloc(name_length + 1);
                                if (name == NULL) {
                                    write(client_fd_wr,"Memory allocation failed",strlen("Line too long"));
                                    close(fd);
                                    break;
                                }
                                memcpy(name, buffer + line_start, name_length);
                                name[name_length] = '\0';
                                close(fd);
                                write(client_fd_wr,name,strlen(name));
                                break;
                            }
                            line_start = i + 1;
                        }
                    }

                    if (line_start == 0 && current_pos == 99) {
                        write(client_fd_wr,"Line too long",strlen("Line too long"));
                        close(fd);
                        sem_post(&sem);
                        break;
                    }

                    if (line_start != 0) {
                        current_pos -= line_start;
                        memmove(buffer, buffer + line_start, current_pos);
                        line_start = 0;
                    }
                }
                sem_post(&sem);
                sem_wait(&sem);
                char log[150];
                snprintf(log,sizeof(log),"Client PID: %d read %d. line of %s.\n",client_pid,line_num,filename);
                write(log_file,log,strlen(log));
                sem_post(&sem);
            }
            else{
                sem_wait(&sem);
                while (read(fd, buffer, 1024) > 0) {
                    write(client_fd_wr, buffer, strlen(buffer));
                }
                char log[150];
                snprintf(log,sizeof(log),"Client PID: %d read %s.\n",client_pid,filename);
                write(log_file,log,strlen(log));
                sem_post(&sem);
            }
            free(filename);
            close(fd);
            close(client_fd_wr);
        }
        else if (strncmp(buffer, "writeT", 6) == 0) {
            int client_fd_wr = open(client_fifo_name, O_WRONLY);
            if (client_fd_wr == -1) {
                perror("open");
                exit(-1);
            }            
            char content[1024];
            int line_num = -1;
            char *filename = (char *)malloc(50 * sizeof(char));
            char filetemp[50];
            sscanf(buffer, "writeT %s %d %s", filetemp, &line_num, content);
            sprintf(filename,"%s/%s",directory,filetemp);    
            sem_wait(&sem);
            int fd = open(filename, O_RDWR | O_CREAT, 0644);
            if (fd == -1) {
                perror("Error opening file");
                sem_post(&sem);
            }
            else {
                if (line_num > 0) {
                    char buffer[256];
                    int current_line = 1;
                    ssize_t bytes_read;
                    off_t position = 0;
                    sem_post(&sem);
                    sem_wait(&sem);
                    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
                        for (ssize_t i = 0; i < bytes_read; ++i) {
                            if (buffer[i] == '\n') {
                                current_line++;
                                if (current_line == line_num) {
                                    position = lseek(fd, 0, SEEK_CUR) - (bytes_read - i);
                                    break;
                                }
                            }
                        }
                        if (current_line >= line_num) break;
                    }
                    if (current_line < line_num) {
                        for (int i = current_line; i < line_num; ++i) {
                            write(fd, "\n", 1);
                        }
                    } 
                    else {
                        lseek(fd, position, SEEK_SET);
                    }
                    char log[150];
                    snprintf(log,sizeof(log),"Client PID: %d changed the %d line of the", client_pid,line_num);
                    strcat(log,filename);
                    strcat(log," file to '");
                    strcat(log,content);
                    strcat(log,"'\n");
                    write(log_file,log,strlen(log));
                    sem_post(&sem);
                } 
                else {
                    sem_wait(&sem);
                    lseek(fd, 0, SEEK_END);
                    char log[150];
                    snprintf(log,sizeof(log),"Client PID: %d added ",client_pid);
                    strcat(log,content); 
                    strcat(log," to the end of " );
                    strcat(log,filename);
                    strcat(log,"\n");
                    write(log_file,log,strlen(log));  
                    sem_post(&sem);                  
                }
                sem_wait(&sem);
                write(fd, "\n", 1);
                write(fd, content, strlen(content));
                close(fd);        
                sem_post(&sem);     
            }
            free(filename);
            write(client_fd_wr, "Line added succesfully.",strlen("Line added succesfully."));
            close(client_fd_wr);
        }
        else if (strncmp(buffer, "upload", 6) == 0) {
            char *filename = (char *)malloc(50 * sizeof(char));
            sscanf(buffer, "upload %s", filename);

            int client_fd_wr = open(client_fifo_name, O_WRONLY);
            if (client_fd_wr == -1) {
                perror("open");
                exit(-1);
            }

            char filepath[100];
            strcpy(filepath, directory);
            strcat(filepath, "/");
            strcat(filepath, filename);

            int bytes_received, total_bytes = 0;
            char recv_buffer[4096];

            char upfifoname[50];
            strcpy(upfifoname, client_fifo_name);
            strcat(upfifoname, "_upload");

            int upfifo = open(upfifoname, O_RDONLY);
            if (upfifo == -1) {
                perror("open");
                exit(-1);
            }
            sem_wait(&sem);
            int dest_fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
            if (dest_fd == -1) {
                perror("open destination file");
                close(upfifo);
                sem_post(&sem);
                return -1;
            }
            sem_post(&sem);
            sem_wait(&sem);
            size_t bytes_read, bytes_written, total_written = 0;
            while ((bytes_read = read(upfifo, recv_buffer, sizeof(recv_buffer))) > 0) {
                bytes_written = write(dest_fd, recv_buffer, bytes_read);
                if (bytes_written == -1) {
                    perror("write destination file");
                    close(upfifo);
                    close(dest_fd);
                    sem_post(&sem);
                    return -1;
                }
                total_written += bytes_written;
                if (total_written > MAX_FILE_SIZE) {
                    fprintf(stderr, "Error: Copied data exceeds maximum size\n");
                    close(upfifo);
                    close(dest_fd);
                    sem_post(&sem);
                    return -1;
                }
            }
            sem_post(&sem);
            if (bytes_read == -1) {
                perror("read FIFO");
                close(upfifo);
                close(dest_fd);
                return -1;
            }

            char tempbuffer1[150];
            snprintf(tempbuffer1, sizeof(tempbuffer1), "File transfer request received. Beginning file transfer:\n%ld bytes transferred\nUpload successful\n", total_written);
            write(client_fd_wr, tempbuffer1, strlen(tempbuffer1));
            sem_wait(&sem);
            char log[150];
            snprintf(log,sizeof(log),"Client PID: %d uploaded '%s' to the server directory.\n",client_pid,filename);
            write(log_file,log,strlen(log));
            sem_post(&sem);
            close(upfifo);
            close(client_fd_wr);
            close(upfifo);
            free(filename);          
        }
        else if (strncmp(buffer, "download", 8) == 0) {
            char *filename = (char *)malloc(50 * sizeof(char));
            sscanf(buffer, "download %s", filename);

            int client_fd_wr = open(client_fifo_name, O_WRONLY);
            if (client_fd_wr == -1) {
                perror("open");
                exit(-1);
            }

            char recv_buffer[4096];

            char downfifoname[50];
            strcpy(downfifoname, client_fifo_name);
            strcat(downfifoname, "_down");
            char filepath[100];
            strcpy(filepath, directory);
            strcat(filepath, "/");
            strcat(filepath, filename);    
            sem_wait(&sem);
            int downfile = open(filepath, O_RDONLY);
            if (downfile == -1) {
                perror("open");
                sem_post(&sem);
                exit(-1);
            }  
            sem_post(&sem);
            struct stat statbuf;
            if (fstat(downfile, &statbuf) == -1) {
                perror("fstat source file");
                close(downfile);
                return -1;
            }

            if (statbuf.st_size > MAX_FILE_SIZE) {
                fprintf(stderr, "Error: File size exceeds maximum (20MB)\n");
                close(downfile);
                return -1;
            }
            if (mkfifo(downfifoname, 0666) == -1 && errno != EEXIST) {
                perror("mkfifo");
                close(downfile);
                return -1;
            }            
            int downfifo = open(downfifoname, O_WRONLY);
            if (downfifo == -1) {
                perror("open1");
                exit(-1);
            }
            sem_wait(&sem);
            size_t bytes_read, bytes_written, total_written = 0;
            while ((bytes_read = read(downfile, recv_buffer, sizeof(recv_buffer))) > 0) {
                bytes_written = write(downfifo, recv_buffer, bytes_read);
                if (bytes_written == -1) {
                    perror("write destination file");
                    close(downfifo);
                    close(downfile);
                    sem_post(&sem);
                    return -1;
                }
                total_written += bytes_written;
                if (total_written > MAX_FILE_SIZE) {
                    fprintf(stderr, "Error: Copied data exceeds maximum size\n");
                    close(downfifo);
                    close(downfile);
                    sem_post(&sem);
                    return -1;
                }
            }
            sem_post(&sem);
            if (bytes_read == -1) {
                perror("read FIFO");
                close(downfifo);
                close(downfile);
                return -1;
            }

            char tempbuffer1[150];
            snprintf(tempbuffer1, sizeof(tempbuffer1), "File transfer request received. Beginning file transfer:\n%ld bytes transferred\nDownload successful\n", total_written);
            write(client_fd_wr, tempbuffer1, strlen(tempbuffer1));
            sem_wait(&sem);
            char log[150];
            snprintf(log,sizeof(log),"Client PID: %d downloaded '%s' from the server directory.\n",client_pid,filename);
            write(log_file,log,strlen(log));
            sem_post(&sem);
            close(downfifo);
            close(client_fd_wr);
            close(downfile);
            free(filename);          
        }
        else if (strncmp(buffer,"archServer", 10) == 0){
            int client_fd_wr = open(client_fifo_name, O_WRONLY);
            if (client_fd_wr == -1) {
                perror("open");
                exit(-1);
            }
            char archive_name[1024];
            sscanf(buffer, "archServer %s", archive_name);
            pid_t pid = fork();

            if (pid < 0) {
                perror("fork");
                exit(-1);
            } else if (pid == 0) {
                char *args[] = {"tar", "-cf", archive_name, directory, NULL};
                execvp("tar", args);
                perror("execvp");
                exit(1);
            }
            else {
                int status;
                wait(&status);
                char send_buffer[100];
                if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
                    strcat(send_buffer,"Archive created successfully: ");
                    strcat(send_buffer,"\n");
                    strcat(send_buffer, archive_name);
                }
                else {
                    snprintf(send_buffer,sizeof(send_buffer),"Error creating archive (status: %d)\n", status);
                }
                write(client_fd_wr,send_buffer,strlen(send_buffer));
            }
            char recv_buffer[4096];
            char downfifoname[50];
            strcpy(downfifoname, client_fifo_name);
            strcat(downfifoname, "_arch");
            sem_wait(&sem);
            int downfile = open(archive_name, O_RDONLY);
            if (downfile == -1) {
                perror("open2");
                sem_post(&sem);
                exit(-1);
            }  
            sem_post(&sem);
            struct stat statbuf;
            if (fstat(downfile, &statbuf) == -1) {
                perror("fstat source file");
                close(downfile);
                return -1;
            }

            if (statbuf.st_size > MAX_FILE_SIZE) {
                fprintf(stderr, "Error: File size exceeds maximum (20MB)\n");
                close(downfile);
                return -1;
            }
            if (mkfifo(downfifoname, 0666) == -1 && errno != EEXIST) {
                perror("mkfifo");
                close(downfile);
                return -1;
            }            
            int downfifo = open(downfifoname, O_WRONLY);
            if (downfifo == -1) {
                perror("open1");
                exit(-1);
            }
            sem_wait(&sem);
            size_t bytes_read, bytes_written, total_written = 0;
            while ((bytes_read = read(downfile, recv_buffer, sizeof(recv_buffer))) > 0) {
                bytes_written = write(downfifo, recv_buffer, bytes_read);
                if (bytes_written == -1) {
                    perror("write destination file");
                    close(downfifo);
                    close(downfile);
                    sem_post(&sem);
                    return -1;
                }
                total_written += bytes_written;
                if (total_written > MAX_FILE_SIZE) {
                    fprintf(stderr, "Error: Copied data exceeds maximum size\n");
                    close(downfifo);
                    close(downfile);
                    sem_post(&sem);
                    return -1;
                }
            }
            sem_post(&sem);
            if (bytes_read == -1) {
                perror("read FIFO");
                close(downfifo);
                close(downfile);
                return -1;
            }            
            close(downfifo);
            close(downfile);
            close(client_fd_wr);
            sem_wait(&sem);
            char log[150];
            snprintf(log,sizeof(log),"Client PID: %d achived server side files in",client_pid);
            strcat(log, archive_name);
            strcat(log, "\n");
            write(log_file,log,strlen(log));
            sem_post(&sem);
            unlink(archive_name);
        }
        else if (strcmp(buffer, "quit") == 0) {
            int client_fd_wr = open(client_fifo_name, O_WRONLY);
            if (client_fd_wr == -1) {
                perror("open");
                exit(-1);
            }            
            write(client_fd_wr, "Sending write request to server log file\nwaiting for logfile ...\nlogfile write request granted\nbye..\n", strlen("Sending write request to server log file\nwaiting for logfile ...\nlogfile write request granted\nbye..\n"));
            connected_clients--;
            close(client_fd_wr);
            unlink(client_fifo_name);
            char log[150];
            snprintf(log,sizeof(log),"Client PID: %d disconnected.\n",client_pid);
            write(log_file,log,strlen(log));
            write(STDOUT_FILENO,log,strlen(log));
            break;
        }
        else if (strcmp(buffer, "killServer") == 0) {
            int client_fd_wr = open(client_fifo_name, O_WRONLY);
            if (client_fd_wr == -1) {
                perror("open");
                exit(-1);
            }
            write(client_fd_wr, "Server shutting down...\n", strlen("Server shutting down...\n"));
            unlink(server_fifo);
            for (int i = 0; i < connected_clients; i++) {
                kill(client_pids[i], SIGTERM);
            }
            close(client_fd_wr);
            char log[150];
            snprintf(log,sizeof(log),"Client PID: %d request server shutdown.\n",client_pid);
            write(log_file,log,strlen(log));
            write(STDOUT_FILENO,log,strlen(log));
            exit(1);
            break;
        }
        else {
            int client_fd_wr = open(client_fifo_name, O_WRONLY);
            if (client_fd_wr == -1) {
                connected_clients--;
                close(client_fd_wr);
                unlink(client_fifo_name);
                char log[150];
                snprintf(log,sizeof(log),"Client PID: %d disconnected.\n",client_pid);
                write(log_file,log,strlen(log));
                write(STDOUT_FILENO,log,strlen(log));
                exit(-1);
            } 
            write(client_fd_wr, "Invalid command\n", strlen("Invalid command\n"));
            close(client_fd_wr);
        }
        sleep(1);
    }while(strncmp(buffer, "quit", 4) != 0 || strncmp(buffer, "killServer", 10) != 0);

    close(client_fd);
    close(log_file);
    unlink(client_fifo_name);
}
int main(int argc, char *argv[]) {
    if (argc != 3) {
        char tempbuffer[60];
        snprintf(tempbuffer, sizeof(tempbuffer), "Usage: %s <directory> <max_clients>\n", argv[0]);
        write(STDOUT_FILENO,tempbuffer,strlen(tempbuffer));
        exit(-1);
    }
    sprintf(server_fifo,"/tmp/%d_server_fifo",getpid());
    if (mkfifo(server_fifo, 0666) == -1 && errno != EEXIST) {
        perror("mkfifo");
        exit(1);
    }
    log_file = open("server.log", O_WRONLY | O_CREAT, 0666);
    if (log_file == -1) {
        perror("open");
        exit(-1);
    }
    if (sem_init(&sem, 1, 1) == -1) {
        perror("sem_init failed");
        exit(EXIT_FAILURE);
    }
    strcpy(directory, argv[1]);
    int max_clients = atoi(argv[2]);
    if (max_clients <= 0 || max_clients > MAX_CLIENTS) {
        fprintf(stderr, "Invalid max_clients: %d (must be 1 to %d)\n", max_clients, MAX_CLIENTS);
        exit(-1);
    }    
    char log[150];
    snprintf(log,sizeof(log),"Server started with max %d connections.\n",max_clients);
    write(log_file,log,strlen(log));
    if (access(directory, F_OK) == -1) {
        mkdir(directory, 0777);
        snprintf(log,sizeof(log),"Folder '%s' is created.\n",directory);
        write(log_file,log,strlen(log));
    }

    int server_fd = open(server_fifo, O_RDONLY | O_NONBLOCK);
    if (server_fd == -1) {
        perror("open");
        exit(1);
    }
    char tempbuffer2[50];
    snprintf(tempbuffer2, sizeof(tempbuffer2), "Server Started PID %d\n", getpid());
    write(STDOUT_FILENO,tempbuffer2,strlen(tempbuffer2));
    write(STDOUT_FILENO,"Waiting for clients...\n",strlen("Waiting for clients...\n"));    

    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_sigaction = &signal_handler;
    sa.sa_flags = SA_SIGINFO;

    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("Error setting up signal handler");
        exit(EXIT_FAILURE);
    }
    while (1) {
        if(access(server_fifo,F_OK) != 0){            
            return 1;
        }

        pid_t client_pid;
        ssize_t bytes_read = read(server_fd, &client_pid, sizeof(pid_t));
        if (bytes_read == -1) {
            perror("read");
            exit(1);
        } 
        else if (bytes_read == 0) {
            usleep(10000);
            continue;
        }

        client_pids[connected_clients++] = client_pid;
        char client_fifo_name[256];
        snprintf(client_fifo_name, sizeof(client_fifo_name), "/tmp/%d_fifo", client_pid);
        if (mkfifo(client_fifo_name, 0666) == -1 && errno != EEXIST) {
            perror("mkfifo");
            exit(-1);
        }
        if (connected_clients <= max_clients) {
            pid_t child_pid = fork();
            if (child_pid == 0) {
                close(server_fd);
                int client = open(client_fifo_name, O_WRONLY);
                if (client == -1) {
                    perror("open");
                    exit(-1);
                }
                char tempbuffer3[50];
                snprintf(tempbuffer3, sizeof(tempbuffer3), "Client with PID %d connected.\n", client_pid);
                write(STDOUT_FILENO,tempbuffer3,strlen(tempbuffer3));
                write(log_file,tempbuffer3,strlen(tempbuffer3));
                write(client,"Connection established",strlen("Connection established"));
                close(client);
                handle_client(client_fifo_name,client_pid);
                exit(0);
                break;
            }
        }
        else{
            int client = open(client_fifo_name, O_WRONLY);
            if (client == -1) {
                perror("open");
                exit(-1);
            }
            write(client,"Connection Failed. Server is full.\n",strlen("Connection Failed. Server is full.\n"));
            close(client);
        }
    }

    close(server_fd);
    close(log_file);
    unlink(server_fifo);

    for (int i = 0; i < connected_clients; i++) {
        wait(NULL);
    }
    return 0;
}
