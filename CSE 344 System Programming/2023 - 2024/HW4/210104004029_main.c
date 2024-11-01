#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <time.h>
#include <errno.h>
#include <signal.h>

#define MAX_PATH 1024
#define BUFFER_SIZE 10

typedef struct
{
    char src_file[MAX_PATH];
    char dest_file[MAX_PATH];
} FileInfo;

pthread_t manager_thread;
pthread_t *worker_threads;
pthread_mutex_t buffer_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t buffer_cond_full = PTHREAD_COND_INITIALIZER;
pthread_cond_t buffer_cond_empty = PTHREAD_COND_INITIALIZER;
FileInfo buffer[BUFFER_SIZE];
int buffer_head = 0, buffer_tail = 0, buffer_count = 0;
int num_workers, buffer_size;
char src_dir[MAX_PATH], dest_dir[MAX_PATH];
int done = 0;

int num_regular_files = 0;
int num_directories = 0;
int num_fifo_files = 0;
long num_total_bytes = 0;

// A signal handler function that handles the SIGINT signal (Ctrl+C) and performs cleanup operations before exiting.
void signal_handler(int sig)
{
    if (sig == SIGINT)
    {
        write(STDOUT_FILENO, "SIGINT received. Cleaning up and exiting...\n", strlen("SIGINT received. Cleaning up and exiting...\n"));
        done = 1;
        pthread_cond_broadcast(&buffer_cond_full);
        pthread_cond_broadcast(&buffer_cond_empty);
        free(worker_threads);
        exit(1);
    }
}
// A function that inserts a FileInfo structure into the shared buffer, waiting if the buffer is full.
void insert_buffer(FileInfo file_info)
{
    pthread_mutex_lock(&buffer_mutex);
    while (buffer_count == buffer_size)
    {
        pthread_cond_wait(&buffer_cond_empty, &buffer_mutex);
    }
    buffer[buffer_tail] = file_info;
    buffer_tail = (buffer_tail + 1) % buffer_size;
    buffer_count++;
    pthread_cond_signal(&buffer_cond_full);
    pthread_mutex_unlock(&buffer_mutex);
}
// A function that removes a FileInfo structure from the shared buffer, waiting if the buffer is empty.
FileInfo remove_buffer()
{
    FileInfo file_info;
    pthread_mutex_lock(&buffer_mutex);
    while (buffer_count == 0 && !done)
    {
        pthread_cond_wait(&buffer_cond_full, &buffer_mutex);
    }
    if (done && buffer_count == 0)
    {
        pthread_mutex_unlock(&buffer_mutex);
        file_info.src_file[0] = '\0';
        file_info.dest_file[0] = '\0';
        return file_info;
    }
    file_info = buffer[buffer_head];
    buffer_head = (buffer_head + 1) % buffer_size;
    buffer_count--;
    pthread_cond_signal(&buffer_cond_empty);
    pthread_mutex_unlock(&buffer_mutex);
    return file_info;
}
// A function that copies a single file from the source path to the destination path.
void copy_file(const char *src_file, const char *dest_file)
{
    int src_fd, dest_fd;
    char buffer[4096];
    ssize_t bytes_read, bytes_written;

    src_fd = open(src_file, O_RDONLY);
    if (src_fd == -1)
    {
        write(STDERR_FILENO, "Error: Unable to open source file '", strlen("Error: Unable to open source file '"));
        write(STDERR_FILENO, src_file, strlen(src_file));
        write(STDERR_FILENO, "'\n", strlen("'\n"));
        return;
    }

    dest_fd = open(dest_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (dest_fd == -1)
    {
        write(STDERR_FILENO, "Error: Unable to open destination file '", strlen("Error: Unable to open destination file '"));
        write(STDERR_FILENO, dest_file, strlen(dest_file));
        write(STDERR_FILENO, "'\n", strlen("'\n"));
        close(src_fd);
        return;
    }

    while ((bytes_read = read(src_fd, buffer, sizeof(buffer))) > 0)
    {
        char *buf_ptr = buffer;
        ssize_t bytes_remaining = bytes_read;

        while (bytes_remaining > 0)
        {
            bytes_written = write(dest_fd, buf_ptr, bytes_remaining);
            if (bytes_written == -1)
            {
                write(STDERR_FILENO, "Error: Unable to write to destination file '", strlen("Error: Unable to write to destination file '"));
                write(STDERR_FILENO, dest_file, strlen(dest_file));
                write(STDERR_FILENO, "'\n", strlen("'\n"));
                close(src_fd);
                close(dest_fd);
                return;
            }
            bytes_remaining -= bytes_written;
            buf_ptr += bytes_written;
            num_total_bytes += bytes_written;
        }
    }

    if (bytes_read == -1)
    {
        write(STDERR_FILENO, "Error: Unable to read from source file '", strlen("Error: Unable to read from source file '"));
        write(STDERR_FILENO, src_file, strlen(src_file));
        write(STDERR_FILENO, "'\n", strlen("'\n"));
    }

    close(src_fd);
    close(dest_fd);
}
// A recursive function that copies a directory tree from the source path to the destination path, adding regular files to the shared buffer for worker threads to copy.
void copy_directory(const char *src_dir, const char *dest_dir)
{
    DIR *dir;
    struct dirent *entry;
    struct stat stat_info;
    char src_path[MAX_PATH], dest_path[MAX_PATH];
    FileInfo file_info;

    dir = opendir(src_dir);
    if (dir == NULL)
    {
        write(STDERR_FILENO, "Error: Unable to open source directory '", strlen("Error: Unable to open source directory '"));
        write(STDERR_FILENO, src_dir, strlen(src_dir));
        write(STDERR_FILENO, "'\n", strlen("'\n"));
        return;
    }

    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
        {
            continue;
        }

        snprintf(src_path, MAX_PATH, "%s/%s", src_dir, entry->d_name);
        snprintf(dest_path, MAX_PATH, "%s/%s", dest_dir, entry->d_name);

        if (lstat(src_path, &stat_info) == -1)
        {
            write(STDERR_FILENO, "Error: Unable to get file status for '", strlen("Error: Unable to get file status for '"));
            write(STDERR_FILENO, src_path, strlen(src_path));
            write(STDERR_FILENO, "'\n", strlen("'\n"));
            continue;
        }

        if (S_ISDIR(stat_info.st_mode))
        {
            if (mkdir(dest_path, stat_info.st_mode) == -1 && errno != EEXIST)
            {
                write(STDERR_FILENO, "Error: Unable to create directory '", strlen("Error: Unable to create directory '"));
                write(STDERR_FILENO, dest_path, strlen(dest_path));
                write(STDERR_FILENO, "'\n", strlen("'\n"));
                continue;
            }
            num_directories++;
            copy_directory(src_path, dest_path);
        }
        else if (S_ISREG(stat_info.st_mode))
        {
            num_regular_files++;
            strcpy(file_info.src_file, src_path);
            strcpy(file_info.dest_file, dest_path);
            insert_buffer(file_info);
        }
        else if (S_ISFIFO(stat_info.st_mode))
        {
            num_fifo_files++;
        }
    }

    closedir(dir);
}

// The manager thread function that creates the destination directory (if necessary), calls copy_directory to populate the shared buffer, and signals when it is done.
void *manager(void *arg)
{
    struct stat stat_info;
    if (stat(dest_dir, &stat_info) == -1)
    {
        if (errno == ENOENT)
        {
            if (mkdir(dest_dir, 0775) == -1)
            {
                write(STDERR_FILENO, "Error: Unable to create destination directory '", strlen("Error: Unable to create destination directory '"));
                write(STDERR_FILENO, dest_dir, strlen(dest_dir));
                write(STDERR_FILENO, "'\n", strlen("'\n"));
                exit(1);
            }
        }
        else
        {
            write(STDERR_FILENO, "Error: Unable to stat destination directory '", strlen("Error: Unable to stat destination directory '"));
            write(STDERR_FILENO, dest_dir, strlen(dest_dir));
            write(STDERR_FILENO, "'\n", strlen("'\n"));
            exit(1);
        }
    }
    else if (!S_ISDIR(stat_info.st_mode))
    {
        write(STDERR_FILENO, "Error: Destination path exists but is not a directory '", strlen("Error: Destination path exists but is not a directory '"));
        write(STDERR_FILENO, dest_dir, strlen(dest_dir));
        write(STDERR_FILENO, "'\n", strlen("'\n"));
        exit(1);
    }

    copy_directory(src_dir, dest_dir);
    done = 1;
    pthread_cond_broadcast(&buffer_cond_full);
    return NULL;
}

// The worker thread function that repeatedly removes FileInfo structures from the shared buffer and calls copy_file to copy the corresponding files.
void *worker(void *arg)
{
    FileInfo file_info;

    while (1)
    {
        file_info = remove_buffer();
        if (file_info.src_file[0] == '\0')
        {
            break;
        }
        copy_file(file_info.src_file, file_info.dest_file);
        write(STDERR_FILENO, "Copied '", strlen("Copied '"));
        write(STDERR_FILENO, file_info.src_file, strlen(file_info.src_file));
        write(STDERR_FILENO, "' to '", strlen("' to '"));
        write(STDERR_FILENO, file_info.dest_file, strlen(file_info.dest_file));
        write(STDERR_FILENO, "'\n", strlen("'\n"));
    }

    return NULL;
}

int main(int argc, char *argv[])
{
    int i;
    struct timespec start_time, end_time;
    struct sigaction sa;

    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGINT, &sa, NULL) == -1)
    {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    if (argc != 5)
    {
        write(STDOUT_FILENO, "Usage: MWCp <buffer_size> <num_workers> <src_dir> <dest_dir>\n", strlen("Usage: MWCp <buffer_size> <num_workers> <src_dir> <dest_dir>\n"));
        exit(1);
    }

    buffer_size = atoi(argv[1]);
    num_workers = atoi(argv[2]);
    strcpy(src_dir, argv[3]);
    strcpy(dest_dir, argv[4]);

    worker_threads = malloc(num_workers * sizeof(pthread_t));
    if (worker_threads == NULL)
    {
        write(STDERR_FILENO, "Error: Unable to allocate memory for worker threads\n", strlen("Error: Unable to allocate memory for worker threads\n"));
        exit(1);
    }

    clock_gettime(CLOCK_MONOTONIC, &start_time);

    pthread_create(&manager_thread, NULL, manager, NULL);
    for (i = 0; i < num_workers; i++)
    {
        pthread_create(&worker_threads[i], NULL, worker, NULL);
    }

    pthread_join(manager_thread, NULL);

    for (i = 0; i < num_workers; i++)
    {
        pthread_join(worker_threads[i], NULL);
    }

    clock_gettime(CLOCK_MONOTONIC, &end_time);

    double elapsed_time = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_nsec - start_time.tv_nsec) / 1e9;
    char msg[50];
    snprintf(msg, 50, "Elapsed time: %.3f seconds\n", elapsed_time);
    write(STDOUT_FILENO, msg, strlen(msg));

    snprintf(msg, 50, "Number of regular files copied: %d\n", num_regular_files);
    write(STDOUT_FILENO, msg, strlen(msg));

    snprintf(msg, 50, "Number of directories copied: %d\n", num_directories);
    write(STDOUT_FILENO, msg, strlen(msg));

    snprintf(msg, 50, "Number of FIFO files copied: %d\n", num_fifo_files);
    write(STDOUT_FILENO, msg, strlen(msg));

    snprintf(msg, 50, "Number of total files copied: %d\n", num_regular_files + num_directories + num_fifo_files);
    write(STDOUT_FILENO, msg, strlen(msg));

    snprintf(msg, 50, "Total bytes copied: %ld\n", num_total_bytes);
    write(STDOUT_FILENO, msg, strlen(msg));

    free(worker_threads);
    pthread_mutex_destroy(&buffer_mutex);
    pthread_cond_destroy(&buffer_cond_full);
    pthread_cond_destroy(&buffer_cond_empty);

    return 0;
}