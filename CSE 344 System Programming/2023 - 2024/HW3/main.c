#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <ctype.h>

/* This variables defines the number of temporary automobile and pickup parking spots available (set to 4 and 8 in this code).*/
#define NUM_TEMP_PICKUP_SPOTS 4
#define NUM_TEMP_AUTOMOBILE_SPOTS 8

/* Defining semaphores*/
sem_t newPickup, inChargeforPickup[2];
sem_t newAutomobile, inChargeforAutomobile[2];

/*Shared global variables*/
int mFree_automobile = NUM_TEMP_AUTOMOBILE_SPOTS;
int mFree_pickup = NUM_TEMP_PICKUP_SPOTS;
int normal_Free_automobile = 0;
int normal_Free_pickup = 0;

/*This function prints the current number of free temporary and regular parking spots for automobiles and pickups to the console.*/
void printEmptySpaces()
{
    char buffer[100];
    int len = snprintf(buffer, sizeof(buffer), "Empty temporary spaces - Automobiles: %d, Pickups: %d\n", mFree_automobile, mFree_pickup);
    write(STDOUT_FILENO, buffer, len);
    len = snprintf(buffer, sizeof(buffer), "Empty normal spaces - Automobiles: %d, Pickups: %d\n", normal_Free_automobile, normal_Free_pickup);
    write(STDOUT_FILENO, buffer, len);
    write(STDOUT_FILENO, "---------------------------------------------------------------\n", strlen("---------------------------------------------------------------\n"));
}

/*This function simulates the arrival of car owners. It randomly decides between an automobile and a pickup truck (using rand() % 2).
If a spot is available in the temporary area for the chosen vehicle type, the car owner acquires a spot and the corresponding semaphore is signaled.
If no temporary spot is available, a message is printed indicating no available spot.
The function also checks for the program termination condition (all spots full) and exits if met.*/
void *carOwner(void *arg)
{
    int vehicleType;
    srand(time(NULL));
    while (1)
    {
        vehicleType = rand() % 2 == 0 ? 0 : 1;

        if (vehicleType == 0 && mFree_automobile > 0)
        {
            int attendant = rand() % 2;
            sem_wait(&inChargeforAutomobile[attendant]);
            mFree_automobile--;
            sem_post(&newAutomobile);
            sem_post(&inChargeforAutomobile[attendant]);
            write(STDOUT_FILENO, "-> An automobile has entered the temporary parking area.\n", strlen("-> An automobile has entered the temporary parking area.\n"));
        }
        else if (vehicleType == 1 && mFree_pickup > 0)
        {
            int attendant = rand() % 2;
            sem_wait(&inChargeforPickup[attendant]);
            mFree_pickup--;
            sem_post(&newPickup);
            sem_post(&inChargeforPickup[attendant]);
            write(STDOUT_FILENO, "-> A pickup has entered the temporary parking area.\n", strlen("-> A pickup has entered the temporary parking area.\n"));
        }
        else if (vehicleType == 0 && mFree_automobile <= 0)
        {
            write(STDOUT_FILENO, "\033[0;31m", sizeof("\033[0;31m") - 1);
            write(STDOUT_FILENO, "-> No available temporary parking spot for the arriving automobile.\n", strlen("-> No available temporary parking spot for the arriving automobile.\n"));
            write(STDOUT_FILENO, "\033[0m", sizeof("\033[0m") - 1);
        }
        else if (vehicleType == 1 && mFree_pickup <= 0)
        {
            write(STDOUT_FILENO, "\033[0;31m", sizeof("\033[0;31m") - 1);
            write(STDOUT_FILENO, "-> No available temporary parking spot for the arriving pickup.\n", strlen("-> No available temporary parking spot for the arriving pickup.\n"));
            write(STDOUT_FILENO, "\033[0m", sizeof("\033[0m") - 1);
        }
        printEmptySpaces();
        sleep(1);
        if (mFree_automobile == 0 && normal_Free_automobile == 0 && mFree_pickup == 0 && normal_Free_pickup == 0)
        {
            write(STDOUT_FILENO, "\033[0;31m", sizeof("\033[0;31m") - 1);
            write(STDOUT_FILENO, "-> All temporary and normal parking spots are full. Exiting...\n", strlen("-> All temporary and normal parking spots are full. Exiting...\n"));
            write(STDOUT_FILENO, "\033[0;31m", sizeof("\033[0;31m") - 1);
            exit(0);
        }
    }
    return NULL;
}

/*This function simulates two car attendants (identified by attendant_id).
The attendants wait for a signal on the newAutomobile or newPickup semaphore depending on their id (0 or 1).
Upon receiving a signal, the attendant checks for a free regular parking spot for the corresponding vehicle type.
If a free spot is available, the car is parked in the regular spot, and the corresponding semaphore (inChargeforAutomobile or inChargeforPickup) is signaled.
If no regular spot is available, the car remains parked in the temporary spot, and a message is printed indicating this.
The function also checks for the program termination condition and exits if met.*/
void *carAttendant(void *arg)
{
    int attendant_id = *(int *)arg;
    while (1)
    {
        if (attendant_id == 0)
        {
            sem_wait(&newAutomobile);
            sem_wait(&inChargeforAutomobile[attendant_id]);
            if (normal_Free_automobile > 0)
            {
                write(STDOUT_FILENO, "-> Attendant (1) is parking an automobile.\n", strlen("-> Attendant (1) is parking an automobile.\n"));
                mFree_automobile++;
                normal_Free_automobile--;
            }
            else
            {
                write(STDOUT_FILENO, "\033[0;31m", sizeof("\033[0;31m") - 1);
                write(STDOUT_FILENO, "-> No available parking spot for the automobile. Staying on temporary.\n", strlen("-> No available parking spot for the automobile.  Staying on temporary.\n"));
                write(STDOUT_FILENO, "\033[0m", sizeof("\033[0m") - 1);
            }
            sem_post(&inChargeforAutomobile[attendant_id]);
        }
        else
        {
            sem_wait(&newPickup);
            sem_wait(&inChargeforPickup[attendant_id]);
            if (normal_Free_pickup > 0)
            {
                write(STDOUT_FILENO, "-> Attendant (2) is parking a pickup.\n", strlen("-> Attendant (2) is parking a pickup.\n"));
                mFree_pickup++;
                normal_Free_pickup--;
            }
            else
            {
                write(STDOUT_FILENO, "\033[0;31m", sizeof("\033[0;31m") - 1);
                write(STDOUT_FILENO, "-> No available parking spot for the pickup. Staying on temporary.\n", strlen("-> No available parking spot for the pickup. Staying on temporary.\n"));
                write(STDOUT_FILENO, "\033[0m", sizeof("\033[0m") - 1);
            }
            sem_post(&inChargeforPickup[attendant_id]);
        }
        printEmptySpaces();
        if (mFree_automobile == 0 && normal_Free_automobile == 0 && mFree_pickup == 0 && normal_Free_pickup == 0)
        {
            write(STDOUT_FILENO, "\033[0;31m", sizeof("\033[0;31m") - 1);
            write(STDOUT_FILENO, "-> All temporary and normal parking spots are full. Exiting...\n", strlen("-> All temporary and normal parking spots are full. Exiting...\n"));
            write(STDOUT_FILENO, "\033[0m", sizeof("\033[0m") - 1);
            exit(0);
        }
    }
    return NULL;
}

/*This is the main function where the program execution starts. It prompts the user for the number of regular automobile and pickup parking spots using a loop to ensure valid integer input.
It then initializes the semaphores used for synchronization between threads. Subsequently, it creates three threads:
- One thread for carOwner to simulate car arrivals.
- Two threads for carAttendant to simulate the two car attendants. The main thread then waits for all the created threads to finish before destroying the semaphores and exiting the program.*/
int main()
{
    char buffer[10];
    while (1)
    {
        write(STDOUT_FILENO, "Enter max automobile parking spot: ", strlen("Enter max automobile parking spot: "));
        int bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
        if (bytes_read == -1)
        {
            perror("Error reading from stdin");
            return 1;
        }

        buffer[bytes_read] = '\0';
        int is_valid = 1;
        for (int i = 0; i < bytes_read - 1; i++)
        {
            if (!isdigit(buffer[i]))
            {
                is_valid = 0;
                break;
            }
        }

        if (is_valid)
        {
            normal_Free_automobile = atoi(buffer);
            if (normal_Free_automobile > 0)
            {
                break;
            }
            else
            {
                write(STDOUT_FILENO, "Please enter a positive integer.\n", strlen("Please enter a positive integer.\n"));
            }
        }
        else
        {
            write(STDOUT_FILENO, "Invalid input. Please enter an integer.\n", strlen("Invalid input. Please enter an integer.\n"));
        }
    }

    while (1)
    {
        write(STDOUT_FILENO, "Enter max pickup parking spot: ", strlen("Enter max pickup parking spot: "));
        int bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
        if (bytes_read == -1)
        {
            perror("Error reading from stdin");
            return 1;
        }
        buffer[bytes_read] = '\0';
        int is_valid = 1;
        for (int i = 0; i < bytes_read - 1; i++)
        {
            if (!isdigit(buffer[i]))
            {
                is_valid = 0;
                break;
            }
        }

        if (is_valid)
        {
            normal_Free_pickup = atoi(buffer);
            if (normal_Free_pickup > 0)
            {
                break;
            }
            else
            {
                write(STDOUT_FILENO, "Please enter a positive integer.\n", strlen("Please enter a positive integer.\n"));
            }
        }
        else
        {
            write(STDOUT_FILENO, "Invalid input. Please enter an integer.\n", strlen("Invalid input. Please enter an integer.\n"));
        }
    }

    printEmptySpaces();

    sem_init(&newPickup, 0, 0);
    for (int i = 0; i < 2; i++)
    {
        sem_init(&inChargeforPickup[i], 0, 1);
    }
    sem_init(&newAutomobile, 0, 0);
    for (int i = 0; i < 2; i++)
    {
        sem_init(&inChargeforAutomobile[i], 0, 1);
    }

    pthread_t ownerThread, attendantThread1, attendantThread2;
    pthread_create(&ownerThread, NULL, carOwner, NULL);
    int attendant1_id = 0;
    pthread_create(&attendantThread1, NULL, carAttendant, &attendant1_id);
    int attendant2_id = 1;
    pthread_create(&attendantThread2, NULL, carAttendant, &attendant2_id);

    pthread_join(ownerThread, NULL);
    pthread_join(attendantThread1, NULL);
    pthread_join(attendantThread2, NULL);

    sem_destroy(&newPickup);
    for (int i = 0; i < 2; i++)
    {
        sem_destroy(&inChargeforPickup[i]);
    }
    sem_destroy(&newAutomobile);
    for (int i = 0; i < 2; i++)
    {
        sem_destroy(&inChargeforAutomobile[i]);
    }

    return 0;
}