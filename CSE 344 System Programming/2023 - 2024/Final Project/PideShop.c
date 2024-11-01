#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>
#include <math.h>
#include <semaphore.h>
#include <complex.h>
#include <time.h>
#include "matrixOP.h"

#define BUFFER_SIZE 1024

typedef struct
{
    int id;
    char description[BUFFER_SIZE];
    int client_socket;
    int cancelled;
} Order;

typedef struct
{
    int id;
    int deliveries;
} Person;

int client_pid;
int number_of_clients;
int p;
int q;

Order orders[100];
int order_count = 0;
pthread_mutex_t order_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t order_cond = PTHREAD_COND_INITIALIZER;

Order ready_queue[100];
int ready_count = 0;
pthread_mutex_t ready_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t ready_cond = PTHREAD_COND_INITIALIZER;

Person *delivery_people;
int *cook_deliveries;

int server_fd = -1;
FILE *log_file;
pthread_t *cook_threads;
pthread_t *delivery_threads;
int cook_thread_pool_size;
int delivery_thread_pool_size;
int delivery_speed;
pthread_mutex_t log_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t delivery_mutex = PTHREAD_MUTEX_INITIALIZER;
int total_clients_served = 0;
int total_clients_expected = 0;
int total_clients_connected = 0;

volatile sig_atomic_t flag = 0;
volatile sig_atomic_t num_clients = 0;

pthread_mutex_t orders_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t ready_queue_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t cook_mutex = PTHREAD_MUTEX_INITIALIZER;

sem_t sem_oven;
sem_t sem_place;
sem_t sem_remove;
sem_t sem_orders;

int did_initialize_thread_called = 0;

void signal_handler(int signum)
{
    if (signum == SIGINT || signum == SIGTERM || signum == SIGTSTP)
    {
        fprintf(stdout, "> ^C or ^Z.. Upps quiting.. writing log file\n");
        flag = 1;
        pthread_cond_broadcast(&order_cond);
        pthread_cond_broadcast(&ready_cond);
        if (server_fd != -1)
        {
            close(server_fd);
        }
        if (log_file != NULL)
        {
            fclose(log_file);
        }
        if (did_initialize_thread_called != 0)
        {
            for (int i = 0; i < cook_thread_pool_size; i++)
            {
                pthread_cancel(cook_threads[i]);
            }
            for (int i = 0; i < delivery_thread_pool_size; i++)
            {
                pthread_cancel(delivery_threads[i]);
            }
            for (int i = 0; i < cook_thread_pool_size; i++)
            {
                pthread_join(cook_threads[i], NULL);
            }
            for (int i = 0; i < delivery_thread_pool_size; i++)
            {
                pthread_join(delivery_threads[i], NULL);
            }
            free(cook_threads);
            free(delivery_threads);
            free(delivery_people);
            free(cook_deliveries);
        }
        exit(0);
    }
}

void setup_signal_handler(int signum)
{
    struct sigaction sa;
    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(signum, &sa, NULL) == -1)
    {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
}

void log_event(const char *event)
{
    pthread_mutex_lock(&log_mutex);

    time_t now = time(NULL);
    char *time_str = ctime(&now);

    if (time_str != NULL)
    {
        time_str[strlen(time_str) - 1] = '\0';
    }

    fprintf(log_file, "[%s] %s\n", time_str, event);
    fflush(log_file);

    pthread_mutex_unlock(&log_mutex);
}

void display_prom()
{
    int max_deliveries = 0;
    int max_cook_deliveries = 0;
    int best_delivery_person = -1;
    int best_cook = -1;
    int i = 0;

    while (i < cook_thread_pool_size)
    {
        if (cook_deliveries[i] >= max_cook_deliveries)
        {
            max_cook_deliveries = cook_deliveries[i];
            best_cook = i;
        }
        fprintf(stdout, "> Cook %d prepared %d orders\n", i + 1, cook_deliveries[i]);
        i++;
    }
    i = 0;

    while (i < delivery_thread_pool_size)
    {
        if (delivery_people[i].deliveries >= max_deliveries)
        {
            max_deliveries = delivery_people[i].deliveries;
            best_delivery_person = i;
        }
        i++;
    }

    fprintf(stdout, "> done serving client @ XXX PID %d\n", client_pid);
    fprintf(stdout, "> Thanks Cook %d and Moto %d\n", best_cook + 1, best_delivery_person);
    fprintf(stdout, "> active waiting for connections\n");

    total_clients_connected = 0;
    memset(delivery_people, 0, delivery_thread_pool_size * sizeof(Person));
    memset(cook_deliveries, 0, cook_thread_pool_size * sizeof(int));
}

void *deliver(void *arg)
{
    int id = *((int *)arg);
    free(arg);
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);

    fprintf(stdout, "> Delivery person %d started.\n", id);

    num_clients = 0;
    while (!flag)
    {
        pthread_mutex_lock(&ready_mutex);
        while (ready_count == 0 && !flag)
        {
            fprintf(stdout, "> Delivery person %d waiting for ready orders.\n", id);

            num_clients += delivery_people[id].deliveries;

            if (num_clients == number_of_clients)
            {
                display_prom();
                num_clients = 0;
            }
            pthread_cond_wait(&ready_cond, &ready_mutex);
        }

        if (flag)
        {
            pthread_mutex_unlock(&ready_mutex);
            fprintf(stdout, "> Delivery person %d shutting down.\n", id);
            break;
        }

        Order order = ready_queue[--ready_count];
        pthread_mutex_unlock(&ready_mutex);

        if (order.cancelled)
        {
            fprintf(stdout, "> Order %d cancelled, delivery person %d discarding order.\n", order.id, id);
            close(order.client_socket);
            continue;
        }

        printf("> Delivery person %d delivering order %d.\n", id, order.id);

        int client_x = 0, client_y = 0;

        char *loc_start = strstr(order.description, "from location (");
        if (loc_start != NULL)
        {
            loc_start += strlen("from location (");

            char *token = strtok(loc_start, ",)");
            if (token != NULL)
            {
                sscanf(token, "%d", &client_x);
                token = strtok(NULL, ",)");
                if (token != NULL)
                {
                    sscanf(token, "%d", &client_y);
                }
            }
        }

        double shop_x = p / 2.0;
        double shop_y = q / 2.0;
        double distance = sqrt(pow(client_x - shop_x, 2) + pow(client_y - shop_y, 2));
        int sleep_time = (int)(distance * 1000000 / delivery_speed);

        char log_msg[BUFFER_SIZE];
        snprintf(log_msg, sizeof(log_msg), "Order %d: Taken by deliverer %d delivery time %d microseconds", order.id, id, sleep_time);
        log_event(log_msg);

        usleep(sleep_time);

        if (order.cancelled)
        {
            fprintf(stdout, "> Order %d cancelled, delivery person %d discarding order.\n", order.id, id);
            close(order.client_socket);
            continue;
        }

        snprintf(log_msg, sizeof(log_msg), "Order %d: Delivered by deliverer %d", order.id, id);
        log_event(log_msg);

        close(order.client_socket);

        pthread_mutex_lock(&delivery_mutex);
        delivery_people[id].deliveries++;
        pthread_mutex_unlock(&delivery_mutex);

        usleep(sleep_time);
        fprintf(stdout, "> Delivery person %d finished delivering order %d. Total deliveries by deliverer: %d\n", id, order.id, delivery_people[id].deliveries);
    }
    return NULL;
}

void *cook(void *arg)
{
    int id = *((int *)arg);
    free(arg);
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);

    printf("> Cook %d started.\n", id);

    int previous_cook_time = 0;

    while (!flag)
    {
        sem_wait(&sem_orders);

        while (1)
        {
            pthread_mutex_lock(&orders_mutex);

            if (order_count == 0)
            {
                pthread_mutex_unlock(&orders_mutex);
                break;
            }

            Order order = orders[--order_count];
            pthread_mutex_unlock(&orders_mutex);

            if (order.cancelled)
            {
                fprintf(stdout, "> Order %d cancelled, cook %d stopping preparation.\n", order.id, id);
                close(order.client_socket);
                continue;
            }

            char log_msg[BUFFER_SIZE];
            snprintf(log_msg, sizeof(log_msg), "Order %d: Preparing by Cook %d", order.id, id);
            log_event(log_msg);

            int preparation_time = calculate_pseudo_inverse_time();
            -previous_cook_time;

            if (preparation_time < 0)
            {
                preparation_time = 0;
            }
            usleep(preparation_time);

            sem_wait(&sem_oven);
            sem_wait(&sem_place);

            snprintf(log_msg, sizeof(log_msg), "Order %d: Placed in Oven by Cook %d", order.id, id);
            log_event(log_msg);

            sem_post(&sem_place);
            previous_cook_time = (calculate_pseudo_inverse_time() / 2);

            usleep(previous_cook_time);

            if (order.cancelled)
            {
                printf("> Order %d cancelled, cook %d removing from oven.\n", order.id, id);
                sem_post(&sem_oven);
                close(order.client_socket);
                continue;
            }

            sem_wait(&sem_remove);
            sem_post(&sem_remove);
            sem_post(&sem_oven);

            pthread_mutex_lock(&ready_mutex);
            ready_queue[ready_count++] = order;
            pthread_cond_signal(&ready_cond);
            pthread_mutex_unlock(&ready_mutex);

            pthread_mutex_lock(&delivery_mutex);
            cook_deliveries[id]++;
            pthread_mutex_unlock(&delivery_mutex);

            snprintf(log_msg, sizeof(log_msg), "Order %d: Ready for delivery", order.id);
            log_event(log_msg);
        }
    }

    fprintf(stdout, "> Cook %d exited.\n", id);
    return NULL;
}

void *handle_client(void *client_socket)
{
    int socket = *((int *)client_socket);
    free(client_socket);
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);

    int readed = read(socket, buffer, BUFFER_SIZE);
    if (readed < 0)
    {
        perror("Read error");
        close(socket);
        return NULL;
    }

    if (strncmp(buffer, "Client PID", 10) == 0)
    {
        sscanf(buffer, "Client PID %d: %d clients, p=%d, q=%d", &client_pid, &number_of_clients, &p, &q);
        fprintf(stdout, "> %d new customers.. Serving\n", number_of_clients);
        close(socket);
        return NULL;
    }

    pthread_mutex_lock(&order_mutex);
    Order order;
    order.id = rand();
    strcpy(order.description, buffer);
    order.client_socket = socket;

    orders[order_count++] = order;
    pthread_cond_signal(&order_cond);
    pthread_mutex_unlock(&order_mutex);

    total_clients_connected++;

    if (total_clients_connected == number_of_clients)
    {
        display_prom();
    }
    return NULL;
}

void cancel_orders(int cancel_pid)
{
    pthread_mutex_lock(&orders_mutex);
    int i = 0;
    while (i < order_count)
    {
        orders[i].cancelled = 1;
        i++;
    }
    pthread_mutex_unlock(&orders_mutex);

    pthread_mutex_lock(&ready_queue_mutex);
    i = 0;
    while (i < ready_count)
    {
        ready_queue[i].cancelled = 1;
        i++;
    }
    ready_count = 0;
    pthread_mutex_unlock(&ready_queue_mutex);
    i = 0;
    while (i < cook_thread_pool_size)
    {
        sem_post(&sem_orders);
        i++;
    }

    char buffer[BUFFER_SIZE];
    snprintf(buffer, BUFFER_SIZE, "Order cancelled by client %d", cancel_pid);
    log_event(buffer);
    fprintf(stdout, "> order cancelled @YYY PID %d\n", cancel_pid);
}

int received_orders = 0;
void hande_orders()
{
    int client_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    fprintf(stdout, "> Waiting to receive all orders at once...\n");

    if ((client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
    {
        perror("Accept");
        exit(EXIT_FAILURE);
    }
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);
    int readed = read(client_socket, buffer, BUFFER_SIZE);
    if (readed < 0)
    {
        perror("Read error");
        close(client_socket);
        return;
    }
    if (strncmp(buffer, "Client PID", 10) == 0)
    {
        sscanf(buffer, "Client PID %d: %d clients, p=%d, q=%d", &client_pid, &number_of_clients, &p, &q);
        fprintf(stdout, "> %d new customers.. Serving\n", number_of_clients);
        received_orders = 0;
    }
    close(client_socket);

    while (received_orders < number_of_clients)
    {

        if ((client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
        {
            perror("Accept");
            exit(EXIT_FAILURE);
        }

        memset(buffer, 0, BUFFER_SIZE);
        readed = read(client_socket, buffer, BUFFER_SIZE);
        if (readed < 0)
        {
            perror("Read error");
            close(client_socket);
            return;
        }

        if (strncmp(buffer, "Cancel PID", 10) == 0)
        {
            int cancel_pid;
            sscanf(buffer, "Cancel PID %d", &cancel_pid);
            cancel_orders(cancel_pid);
            return;
        }

        pthread_mutex_lock(&orders_mutex);
        Order order;
        order.id = received_orders + 1;
        snprintf(order.description, BUFFER_SIZE, "%s", buffer);
        order.client_socket = client_socket;
        order.cancelled = 0;
        orders[order_count++] = order;
        pthread_mutex_unlock(&orders_mutex);

        received_orders++;
    }

    close(client_socket);

    fprintf(stdout, "> All orders received. Total: %d\n", order_count);
    int i = 0;
    while (i < cook_thread_pool_size)
    {
        sem_post(&sem_orders);
        i++;
    }
}

int main(int argc, char *argv[])
{
    if (argc != 6)
    {
        fprintf(stderr, "Usage: %s <ip> <portnumber> <CookthreadPoolSize> <DeliveryPoolSize> <k>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *ip = argv[1];
    int port = atoi(argv[2]);
    cook_thread_pool_size = atoi(argv[3]);
    delivery_thread_pool_size = atoi(argv[4]);
    delivery_speed = atoi(argv[5]);

    srand(time(NULL));
    log_file = fopen("pide.log", "w");
    if (!log_file)
    {
        perror("Log file opening failed");
        exit(EXIT_FAILURE);
    }

    setup_signal_handler(SIGINT);
    setup_signal_handler(SIGTERM);
    setup_signal_handler(SIGTSTP);

    pthread_mutex_init(&order_mutex, NULL);
    pthread_mutex_init(&ready_mutex, NULL);
    pthread_mutex_init(&log_mutex, NULL);
    pthread_mutex_init(&delivery_mutex, NULL);
    pthread_mutex_init(&orders_mutex, NULL);
    pthread_mutex_init(&ready_queue_mutex, NULL);
    pthread_mutex_init(&cook_mutex, NULL);

    sem_init(&sem_oven, 0, 3);
    sem_init(&sem_place, 0, 1);
    sem_init(&sem_remove, 0, 1);
    sem_init(&sem_orders, 0, 0);

    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(ip);
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 128) < 0)
    {
        perror("Listen");
        exit(EXIT_FAILURE);
    }

    fprintf(stdout, "> PideShop %s %d %d %d %d\n", ip, port, cook_thread_pool_size, delivery_thread_pool_size, delivery_speed);
    fprintf(stdout, "> PideShop active waiting for connection ...\n");

    int i = 0;
    while (1)
    {
        hande_orders();
        if (i == 0)
        {
            cook_threads = malloc(sizeof(pthread_t) * cook_thread_pool_size);
            delivery_threads = malloc(sizeof(pthread_t) * delivery_thread_pool_size);
            delivery_people = malloc(sizeof(Person) * delivery_thread_pool_size);
            cook_deliveries = malloc(sizeof(int) * cook_thread_pool_size);
            int j = 0;
            while (j < cook_thread_pool_size)
            {
                cook_deliveries[j] = 0;
                int *cook_id = malloc(sizeof(int));
                *cook_id = j;
                if (pthread_create(&cook_threads[j], NULL, cook, cook_id) != 0)
                {
                    perror("Failed to create cook thread");
                    exit(EXIT_FAILURE);
                }
                j++;
            }
            j = 0;
            while (j < delivery_thread_pool_size)
            {
                delivery_people[j].id = j;
                delivery_people[j].deliveries = 0;
                int *delivery_id = malloc(sizeof(int));
                *delivery_id = j;
                if (pthread_create(&delivery_threads[j], NULL, deliver, delivery_id) != 0)
                {
                    perror("Failed to create delivery thread");
                    exit(EXIT_FAILURE);
                }
                j++;
            }
            did_initialize_thread_called = 1;
        }
        i++;
    }

    while (1)
    {
        int new_socket;
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
        {
            perror("Accept");
            continue;
        }

        int *client_socket = malloc(sizeof(int));
        if (client_socket == NULL)
        {
            perror("Memory allocation failed");
            close(new_socket);
            continue;
        }
        *client_socket = new_socket;

        pthread_t thread_id;
        if (pthread_create(&thread_id, NULL, handle_client, (void *)client_socket) < 0)
        {
            perror("Could not create thread");
            free(client_socket);
            close(new_socket);
            continue;
        }

        pthread_detach(thread_id);
    }

    if (server_fd != -1)
    {
        close(server_fd);
    }
    if (log_file != NULL)
    {
        fclose(log_file);
    }
    if (did_initialize_thread_called != 0)
    {
        for (int i = 0; i < cook_thread_pool_size; i++)
        {
            pthread_cancel(cook_threads[i]);
        }
        for (int i = 0; i < delivery_thread_pool_size; i++)
        {
            pthread_cancel(delivery_threads[i]);
        }
        for (int i = 0; i < cook_thread_pool_size; i++)
        {
            pthread_join(cook_threads[i], NULL);
        }
        for (int i = 0; i < delivery_thread_pool_size; i++)
        {
            pthread_join(delivery_threads[i], NULL);
        }
        free(cook_threads);
        free(delivery_threads);
        free(delivery_people);
        free(cook_deliveries);
    }

    pthread_mutex_destroy(&order_mutex);
    pthread_mutex_destroy(&ready_mutex);
    pthread_mutex_destroy(&log_mutex);
    pthread_mutex_destroy(&delivery_mutex);
    pthread_mutex_destroy(&orders_mutex);
    pthread_mutex_destroy(&ready_queue_mutex);
    pthread_mutex_destroy(&cook_mutex);

    sem_destroy(&sem_oven);
    sem_destroy(&sem_place);
    sem_destroy(&sem_remove);
    sem_destroy(&sem_orders);

    return 0;
}
