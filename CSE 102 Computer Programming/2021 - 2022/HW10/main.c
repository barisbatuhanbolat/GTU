#include <stdio.h>
#include <stdlib.h>

/*Defining first stack size*/
#define STACK_BLOCK_SIZE 10
#define EMPTY 0

/*Declaring stack*/
typedef struct{
    int currentsize;
    int maxsize;
    int *array;
}Stack;

/*Function declarations*/
int init(Stack * s);
Stack * init_return();
void push(Stack *stack, int d);
int pop(Stack* stack);
void fillFirstTower(Stack* firstTower,int towerSize);
void changeDiskLocation(Stack *towerFrom, Stack *towerTo, int t1, int t2);


int main(){
    int towerSize;
    /*Declaring stack pointers*/
    Stack *firstTower, *secondTower, *thirdTower;    
    
    printf("Enter Tower Size = ");
    scanf("%d",&towerSize);
    /*A tower has only one dik is invalid*/
    while(towerSize == 1){
        printf("\033[1;31m");
        printf("!!!A tower with only one disk cannot be solved!!!\n");
        printf("\033[0m");
        printf("Enter Tower Size = ");
        scanf("%d",&towerSize);
    }
    
    /*Initialization of stacks*/
    firstTower = init_return();
    secondTower = init_return();
    thirdTower = init_return();

    /*If the number of blocks received from the user(towerSize) is larger than the array size of the stacks we created, */
    /*I realloc the arrays with the number of blocks received from the user.*/
    if(towerSize > firstTower->maxsize){
        firstTower->maxsize = towerSize;
        secondTower->maxsize = towerSize;
        thirdTower->maxsize = towerSize;
        
        /*Reallocation part*/
        firstTower->array = (int*) malloc(firstTower -> maxsize * sizeof(int));
        secondTower->array = (int*) malloc(secondTower -> maxsize * sizeof(int));
        thirdTower->array = (int*) malloc(thirdTower -> maxsize * sizeof(int));
    }

    /*I calculate the smallest number of steps to solve this problem. */
    /*I declare moveT as a long int because the maximum value of the int variable is exceeded in the towerSize entered more than 32.*/
    long int moveT = 1;
    for(int i = 0;i<towerSize;i++){
        moveT = moveT*2;
    }
    moveT = moveT - 1;

    /*Filling the first tower.*/
    fillFirstTower(firstTower,towerSize);
    /*If number of blocks on one tower is even then movement starts From first tower to second tower*/
    if (towerSize % 2 == 0){
        int j = 1;
        while(j<=moveT){
            switch(j%3){
                case 1:
                    changeDiskLocation(firstTower, secondTower, 1, 2);
                    break;
                case 2:
                    changeDiskLocation(firstTower, thirdTower, 1, 3);
                    break;
                case 0:
                    changeDiskLocation(thirdTower, secondTower, 3, 2);
                    break;
            }
            j++;
        }
    }
    /*If number of blocks on one tower is odd then movement starts From first tower to third one*/
    else if(towerSize % 2 != 0){
        int j = 1;
        while(j<=moveT){
            switch(j%3){
                case 1:
                    changeDiskLocation(firstTower, thirdTower, 1, 3);
                    break;
                case 2:
                    changeDiskLocation(firstTower, secondTower, 1, 2);
                    break;
                case 0:
                    changeDiskLocation(secondTower, thirdTower, 2, 3);
                    break;   
            }
            j++;
        }
    }
}
/*This function checks the stack initialized correctly*/
int init(Stack * s){
    if(s->array != NULL){
        return 1;
    }
    else{
        return 0;
    }
}
/*This function initialize an empty stack and return it according to "init" function*/ 
Stack * init_return(){
    Stack* stack = (Stack*) malloc(sizeof(Stack));
    stack -> currentsize = -1;
    stack -> maxsize = STACK_BLOCK_SIZE;
    stack -> array = (int*) malloc(stack -> maxsize * sizeof(int));

    if(init(stack) == 1){
        return stack;
    }
}
/*This function add a new item to stack*/
void push(Stack *stack, int d){
    if (stack->currentsize == stack->maxsize - 1){
        return;
    }
    else{
        ++(stack -> currentsize);
        stack -> array[stack -> currentsize] = d;
    }
}
/*This functiom fills the first stack by using push function*/
void fillFirstTower(Stack* firstTower,int towerSize){
    for (int i = towerSize; i >= 1; i--){
        push(firstTower, i);
    }
}
/*This function gets the element at the top of a stack(tower) and send it.*/
int pop(Stack* stack){
    int out;
    if (stack->currentsize == -1){
        return EMPTY;
    }
    else{
        out = stack -> array[stack -> currentsize];
        stack->currentsize--;
        return out;
    }
}
/*This function take a disk from towers by using pop function and add that disk to another tower by using push function*/
void changeDiskLocation(Stack *towerFrom, Stack *towerTo, int t1, int t2){
    int firstDisk, thirdDisk;
    /*Taking disks from given towers top*/
    firstDisk = pop(towerFrom);
    thirdDisk = pop(towerTo);

    if (firstDisk == EMPTY){
        push(towerFrom, thirdDisk);
        printf("Move the disk %d from '%d' to '%d'\n",thirdDisk, t2, t1);
    }
 
    else if (thirdDisk == EMPTY){
        push(towerTo, firstDisk);
        printf("Move the disk %d from '%d' to '%d'\n",firstDisk, t1, t2);
    }
    /*According to rule the big disc should be below the small disc.*/
    else{
        if (firstDisk > thirdDisk){
            push(towerFrom, firstDisk);
            push(towerFrom, thirdDisk);
            printf("Move the disk %d from '%d' to '%d'\n",thirdDisk, t2, t1);
        }

        else{
            push(towerTo, thirdDisk);
            push(towerTo, firstDisk);
            printf("Move the disk %d from '%d' to '%d'\n",firstDisk, t1, t2);
        }
    }
}
