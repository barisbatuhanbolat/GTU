#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <time.h>
#include <signal.h>

#define BUFFER_SIZE 1024

int port;
char *ip;

void send_order(const char *server_ip, int port, int order_id, int x, int y, int client_id)
{
    struct sockaddr_in server_address;
    int sock = 0;
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);
    char order[BUFFER_SIZE];

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Socket creation error");
        return;
    }

    int opt = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
    {
        perror("setsockopt");
        close(sock);
        return;
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);

    if (inet_pton(AF_INET, server_ip, &server_address.sin_addr) <= 0)
    {
        perror("Invalid address/ Address not supported");
        close(sock);
        return;
    }

    if (connect(sock, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        perror("Connection Failed Server not available.. exiting\n");
        close(sock);
        exit(EXIT_FAILURE);
    }

    snprintf(order, BUFFER_SIZE, "Order %d from location (%d, %d)", order_id, x, y);
    send(sock, order, strlen(order), 0);
    printf("> PID %d.. Order sent: %s\n", client_id, order);

    close(sock);
}

void send_cancel_message(const char *server_ip, int port, int client_pid)
{
    struct sockaddr_in server_address;
    int sock = 0;
    char cancel_message[BUFFER_SIZE];

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Socket creation error");
        return;
    }

    int opt = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
    {
        perror("setsockopt");
        close(sock);
        return;
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);

    if (inet_pton(AF_INET, server_ip, &server_address.sin_addr) <= 0)
    {
        perror("Invalid address/ Address not supported");
        close(sock);
        return;
    }

    if (connect(sock, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        perror("Connection Failed Server not available.. exiting\n");
        close(sock);
        exit(EXIT_FAILURE);
    }

    snprintf(cancel_message, BUFFER_SIZE, "Cancel PID %d", client_pid);
    send(sock, cancel_message, strlen(cancel_message), 0);

    close(sock);
}

void signal_handler(int signum)
{
    if (signum == SIGINT || signum == SIGTERM)
    {
        printf("\n^C signal.. cancelling orders.. editing log..\n");
        send_cancel_message(ip, port, getpid());
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
int main(int argc, char *argv[])
{
    if (argc != 6)
    {
        fprintf(stderr, "Usage: %s <ip> <portnumber> <numberOfClients> <p> <q>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    ip = argv[1];
    port = atoi(argv[2]);
    int numberOfClients = atoi(argv[3]);
    int p = atoi(argv[4]);
    int q = atoi(argv[5]);
    int client_pid = getpid();

    setup_signal_handler(SIGINT);
    setup_signal_handler(SIGTERM);

    srand(time(0));
    printf("> HungryVeryMuch %s %d %d %d %d\n", ip, port, numberOfClients, p, q);

    struct sockaddr_in server_address;
    int sock = 0;
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);

    char client_info[BUFFER_SIZE];

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }

    else
    {
        int opt = 1;
        if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
        {
            perror("setsockopt");
            close(sock);
            exit(EXIT_FAILURE);
        }
        else
        {
            server_address.sin_family = AF_INET;
            server_address.sin_port = htons(port);

            if (inet_pton(AF_INET, ip, &server_address.sin_addr) <= 0)
            {
                perror("Invalid address/ Address not supported");
                close(sock);
                exit(EXIT_FAILURE);
            }
            else
            {
                if (connect(sock, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
                {
                    perror("Connection Failed Server not available.. exiting\n");
                    close(sock);
                    exit(EXIT_FAILURE);
                }

                snprintf(client_info, BUFFER_SIZE, "Client PID %d: %d clients, p=%d, q=%d", client_pid, numberOfClients, p, q);
                send(sock, client_info, strlen(client_info), 0);

                close(sock);

                for (int i = 0; i < numberOfClients; i++)
                {
                    int order_id = i + 1;
                    int customer_x = rand() % p;
                    int customer_y = rand() % q;

                    send_order(ip, port, order_id, customer_x, customer_y, client_pid);
                    usleep(100000);
                }

                printf("> ...\n> All customers served\n> log file written ..\n");
            }
        }
    }
    return 0;
}
