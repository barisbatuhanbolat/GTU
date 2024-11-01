#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*Declarations of functions*/
int dice();
void printMap(char map[15][30]);
void game();
void move_2();
void move_1();
int startGame();
/*I declare my game area map as a global*/
char map[15][30] = {
    {'.', '.', '.', '.','.', '.','.', '.','.', '.','.', '.','.', '.','.', '.','.', '.','.', '.','.', '.','.', '.','.', '.','.', '.','.', '.'},
    {':', '1', ' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ','X', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ':'},
    {':', '_', '.', '.','.', '.','.', '.','.', '.','.', '.','.', '.','.', '.','.', '.','.', '.','.', '.','.', '.','.', '.','.', '.',' ', ':'},
    {':', ' ', ':', '2',' ', ' ',' ', ' ',' ', ' ','X', ' ',' ', ' ',' ', ' ',' ', ' ','X', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ':',' ', ':'},
    {':', ' ', ':', '_','.', '.','.', '.','.', '.','.', '.','.', '.','.', '.','.', '.','.', '.','.', '.','.', '.','.', '.',' ', ':',' ', ':'},
    {':', ' ', ':', ' ',':', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ':','X', ':',' ', ':'},
    {':', ' ', ':', ' ',':', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ':',' ', ':',' ', ':'},
    {':', ' ', ':', ' ',':', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ':',' ', ':','X', ':'},
    {':', ' ', ':', ' ',':', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ':',' ', ':',' ', ':'},
    {':', ' ', ':', ' ',':', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ':',' ', ':',' ', ':'},
    {':', ' ', ':', ' ','.', '.','.', '.','.', '.','.', '.','.', '.','.', '.','.', '.','.', '.','.', '.','.', '.','.', '.','X', ':',' ', ':'},
    {':', ' ', ':', ' ',' ', ' ',' ', ' ',' ', ' ','X', ' ',' ', ' ',' ', ' ',' ', ' ','X', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ':',' ', ':'},
    {':', ' ', '.', '.','.', '.','.', '.','.', '.','.', '.','.', '.','.', '.','.', '.','.', '.','.', '.','.', '.','.', '.','.', '.',' ', ':'},
    {':', ' ', ' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ','X', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ':'},
    {'.', '.', '.', '.','.', '.','.', '.','.', '.','.', '.','.', '.','.', '.','.', '.','.', '.','.', '.','.', '.','.', '.','.', '.','.', '.'}
};

int main(){
    /*In main function I call main game function*/
    int r=0;
    /*Necessary for rand function*/
    srand(time(NULL));
    game();

}
/*This function prints map to the screen*/
void printMap(char map[15][30]){

    map[4][3] = '_';
    map[2][1] = '_';
    int i,j;
    for(i=0; i<15; i++) {
        for(j=0;j<30;j++) {
            if(map[i][j] == '1'){
                printf("\033[0;33m");
                printf("%c",map[i][j]);
                printf("\033[0;37m");
            }
            else if(map[i][j] == '2'){
                printf("\033[0;34m");
                printf("%c",map[i][j]);
                printf("\033[0;37m");
            }
            else if((i==1 && j == 14) || (i==7 && j == 28) || (i==13 && j == 14) || (i==3 && j == 10) || (i==3 && j == 18) || (i==5 && j == 26) || (i==10 && j == 26) || (i==11 && j == 10) || (i==11 && j == 18) ){
                printf("\033[0;31m");
                printf("%c",map[i][j]);
                printf("\033[0;37m");
            }
            else if((i==4 && j==3) || (i==2 && j==1)){
                printf("\033[0;32m");
                printf("%c",map[i][j]);
                printf("\033[0;37m");
            }
            else if(map[i][j] != '1' || map[i][j] != '2' || map[i][j] != 'X' || map[i][j] != '_'){
                printf("%c",map[i][j]);
            }
        }
        printf("\n");
   }
}
/*This function returns a random integer in a range of [1,6] to the functions*/
int dice(){
    int r;

    r = (rand()%6)+1;

    return r;
}
/*This functions decides and returns the # of the player who will start the game.*/
int startGame(){
    int p1,p2,r1,r2;
    
    printf("\033[0;33m");
    printf("PLAYER 1....press ENTER the dice");
    if(getchar() == '\n') r1 = dice();
    printf("DICE: %d\n",r1);
    printf("\033[0;37m");

    printf("\033[0;34m");
    printf("PLAYER 2....press ENTER the dice");
    if(getchar() == '\n') r2 = dice();
    printf("DICE: %d\n",r2);
    printf("\033[0;37m");

    if(r1>r2){
        return 1;
    }
    if(r2>r1){
        return 2;
    }
    if(r1 == r2){
        printf("Same Dice value... Try again\n");       
        printf("\033[0;33m");
        printf("PLAYER 1....press ENTER the dice");
        if(getchar() == '\n') r1 = dice();
        printf("DICE: %d\n",r1);
        printf("\033[0;37m");

        printf("\033[0;34m");
        printf("PLAYER 2....press ENTER the dice");
        if(getchar() == '\n') r2 = dice();
        printf("DICE: %d\n",r2);
        printf("\033[0;37m");

        if(r1>r2){
            return 1;
        }
        if(r2>r1){
            return 2;
        }
        if(r2 == r1){
            printf("Same Dice value... Try again\n");       
            printf("\033[0;33m");
            printf("PLAYER 1....press ENTER the dice");
            if(getchar() == '\n') r1 = dice();
            printf("DICE: %d\n",r1);
            printf("\033[0;37m");     

            printf("\033[0;34m");
            printf("PLAYER 2....press ENTER the dice");
            if(getchar() == '\n') r2 = dice();
            printf("DICE: %d\n",r2);
            printf("\033[0;37m");

            if(r1>r2){
                return 1;
            }            
            if(r2>r1){
                return 2;
            }        
        }
    }
}
/*This function manages the moves of the Player 1 if the Player 2 starts first.*/
void move_1(){
    int i,j,r1,flag;
    char temp;
            for(i=1;i<14;i++){
                for(j=1;j<29;j++){
                    if(map[i][j] == '1'){
                        printf("\033[0;33m");
                        printf("PLAYER 1....press ENTER the dice");
                        if(getchar() == '\n') r1 = dice();
                        printf("DICE: %d\n",r1);
                        printf("\033[0;37m");
                    
                        if(map[i][j] == '1' && i==1 && j==28){
                            temp = map[i][j];
                            map[i+r1][j] = temp;
                            map[i][j] = ' ';
                            printMap(map);
                            break;
                        }
                        if(map[i][j] == '1' && i==13 && j==28){
                            temp = map[i][j];
                            map[i][j-r1] = temp;
                            map[i][j] = ' '; 
                            printMap(map);
                            break;
                        }   
                        if(map[i][j] == '1' && i==13 && j==1){
                            temp = map[i][j];
                            map[i-r1][j] = temp;
                            map[i][j] = ' ';
                            printMap(map);
                            break;
                        }
                        if(map[i][j] == '1'){
                            if(i==1){
                                if(j+r1>28){
                                    temp = map[i][j];
                                    map[i+(j+r1-28)][28] = temp;
                                    map[i][j] = ' ';
                                    printMap(map);
                                    break;
                                }
                                if(j==28){
                                    temp = map[i][j];
                                    map[i+r1][j] = temp;
                                    map[i][j] = ' ';
                                    printMap(map);
                                    break;
                                }
                                if(j<28 && j>=1){
                                    if(j+r1 == 14){
                                        if(i == 1 && j == 12){
                                            printf("Penalty for Player 1\n ");
                                            printMap(map);
                                            break;
                                        }
                                        else{
                                            printf("Penalty for Player 1\n ");
                                            temp = map[i][j];
                                            map[i][12] = temp;
                                            map[i][j] = ' ';  
                                            printMap(map);
                                            break;
                                        }                        
                                    }
                                    else{
                                        temp = map[i][j];
                                        map[i][j+r1] = temp;
                                        map[i][j] = ' ';
                                        printMap(map);
                                        break;

                                    }
                                }
                            }
                            if((i>1 && i<13) && j == 28){
                                if(i+r1 == 7){
                                    if(i==5 && j==28){
                                        printf("Penalty for Player 1\n ");
                                        printMap(map);
                                        return;
                                    }
                                    else{
                                        printf("Penalty for Player 1\n ");
                                        temp = map[i][j];
                                        map[5][28] = temp;
                                        map[i][j] = ' ';  
                                        printMap(map);
                                        return;
                                    }                              
                                }
                                if(i+r1>13){
                                    temp = map[i][j];
                                    map[13][j-(i+r1-13)] = temp;
                                    map[i][j] = ' ';
                                    printMap(map);
                                    return;                                    
                                }
                                else{
                                    temp = map[i][j];
                                    map[i+r1][28] = temp;
                                    map[i][j] = ' ';
                                    printMap(map);
                                    return;                                        
                                }
                            }
                            if(i == 13){
                                if(j==28){
                                    temp = map[i][j];
                                    map[i][j-r1] = temp;
                                    map[i][j] = ' ';  
                                    printMap(map);
                                    break;
                                }
                                if(j-r1<1){
                                    temp = map[i][j];
                                    map[i-((r1-j)%28)-1][1] = temp;
                                    map[i][j] = ' ';
                                    printMap(map);
                                    break;
                                }
                                if(j==1){
                                    temp = map[i][j];
                                    map[i-r1][j] = temp;
                                    map[i][j] = ' ';
                                    printMap(map);
                                    break;                                  
                               }   
                                if(j<28 && j>1){
                                    temp = map[i][j];
                                    map[i][j-r1] = temp;
                                    map[i][j] = ' ';
                                    printMap(map);
                                    break;
                                }
                                if(j-r1 == 14){
                                    if(i == 13 && j == 16){
                                        printf("Penalty for Player 1\n ");
                                        printMap(map);
                                        break;
                                    }
                                    else{
                                        printf("Penalty for Player 1\n ");
                                        temp = map[i][j];
                                        map[13][16] = temp;
                                        map[i][j] = ' ';  
                                        printMap(map);
                                        break;
                                    }                              
                                }
                            }
                            if((i>1 && i<13) && j==1){
                                if(i-r1<1){
                                    temp = map[i][j];
                                    map[1][1] = temp;
                                    map[i][j] = ' '; 
                                    printf("******Player 1 Won the Game******\n"); 
                                    exit(0);
                                }
                                if(i-r1 == 1){
                                    temp = map[i][j];
                                    map[1][1] = temp;
                                    map[i][j] = ' '; 
                                    printf("******Player 1 Won the Game******\n"); 
                                    exit(0);
                                }
                                else{
                                    temp = map[i][j];
                                    map[i-r1][j] = temp;
                                    map[i][j] = ' ';
                                    printMap(map);
                                    break;
                                }   
                            }
                            break;
                        }
                    }               
                }
            }           
}
/*This function manages the moves of the Player 2 if the Player 1 starts first.*/
void move_2(){
    int r,i,j,k,flag=0;
    char temp;
        printf("\033[0;34m");
        printf("PLAYER 2....press ENTER the dice");
        if(getchar() == '\n') r = dice();
        printf("DICE: %d\n",r);
        printf("\033[0;37m");        
        for(i=0;i<15;i++){
            for(j=0;j<30;j++){
                if(map[i][j] == '2'){
                    if(i==11 && j== 3){
                        temp = map[i][j];
                        map[i-r][j] = temp;
                        map[i][j] = ' ';
                        printMap(map);
                        break;                        
                    }
                    if(i==11 && j== 26){
                        temp = map[i][j];
                        map[i][j-r] = temp;
                        map[i][j] = ' ';
                        printMap(map);
                        break;                        
                    }
                    if(i==3 && j== 26){
                        temp = map[i][j];
                        map[i+r][j] = temp;
                        map[i][j] = ' ';
                        printMap(map);
                        break;                        
                    }                                        
                    if(i==3){
                        if(j+r==10){
                            if(i==3 && j==8){
                                printf("Penalty for Player 2\n ");
                            }
                            else{
                                printf("Penalty for Player 2\n ");
                                map[3][8] = '2';
                                map[i][j] = ' ';
                                printMap(map);
                                break;
                            }
                        }
                        if(j+r == 18){
                            if(i==3 && j==16){
                                printf("Penalty for Player 2\n ");
                            }
                            else{
                                printf("Penalty for Player 2\n ");
                                map[3][16] = '2';
                                map[i][j] = ' ';
                                printMap(map);
                                break;
                            }                            
                        }
                        if(j>=3 && j<26 && j+r<26){
                            map[i][j+r] = '2';
                            map[i][j] = ' ';
                            printMap(map);
                            break;
                        }
                        if(j+r>26){
                            map[i+((j+r)%24)-2][26] = '2';
                            map[i][j] = ' ';
                            printMap(map);
                            break;
                        }
                        if(j+r==26){
                            map[3][26] = '2';
                            map[i][j] = ' ';
                            printMap(map);                            
                            break;
                        }
                    }
                    if((i>3 && i<11)&& j==26){
                        if(i+r==5){
                            if(i==3 && j==26){
                                printf("Penalty for Player 2\n ");
                            }
                            else{
                                printf("Penalty for Player 2\n ");
                                map[3][26] = '2';
                                map[i][j] = ' ';
                                printMap(map);
                                return;
                            }
                        }
                        if(i+r == 10){
                            if(i==8 && j==26){
                                printf("Penalty for Player 2\n ");
                            }
                            else{
                                printf("Penalty for Player 2\n ");
                                map[8][26] = '2';
                                map[i][j] = ' ';
                                printMap(map);
                                return;
                            }                            
                        }
                        if(i+r>11){
                            temp = map[i][j];
                            map[11][j-(i+r)%9] = temp;
                            map[i][j] = ' ';
                            return;
                        }
                        else{
                            temp = map[i][j];
                            map[i+r][j] = temp;
                            map[i][j] = ' ';  
                            return;
                        }
                        printMap(map);
                    }
                    if(i==11){
                        if(j-r == 10){
                            if(i==11 && j==12){
                                printf("Penalty for Player 2\n ");
                            }
                            else{
                                printf("Penalty for Player 2\n ");
                                map[11][12] = '2';
                                map[i][j] = ' ';
                                printMap(map);
                                break;
                            }                             
                        }
                        if(j-r == 18){
                            if(i==11 && j==20){
                                printf("Penalty for Player 2\n ");
                            }
                            else{
                                printf("Penalty for Player 2\n ");
                                map[11][20] = '2';
                                map[i][j] = ' ';
                                printMap(map);
                                break;
                            }                             
                        }                        
                        if(j==26){
                            temp = map[i][j];
                            map[i][j-r] = temp;
                            map[i][j] = ' ';  
                            printMap(map);
                            break;
                        }
                        if(j-r<3){
                            temp = map[i][j];
                            map[i-((r-j)%24)-2][3] = temp;
                            map[i][j] = ' ';  
                            printMap(map);
                            break;
                        }
                        if(j==3){
                            temp = map[i][j];
                            map[i-r][j] = temp;
                            map[i][j] = ' ';
                            printMap(map);
                            break;
                        }
                        else{
                            temp = map[i][j];
                            map[i][j-r] = temp;
                            map[i][j] = ' ';
                            printMap(map);
                        }                        
                    }
                    if((i>3 && i<11)&& j==3){
                        if(i-r<3){
                            temp = map[i][j];
                            map[1][3] = temp;
                            map[i][j] = ' '; 
                            printf("******Player 2 Won the Game******\n");
                            exit(0);
                        }
                        if(i-r == 3){
                            temp = map[i][j];
                            map[3][3] = temp;
                            map[i][j] = ' ';
                            printf("******Player 2 Won the Game******\n"); 
                            exit(0);
                        }
                        else{
                            temp = map[i][j];
                            map[i-r][j] = temp;
                            map[i][j] = ' ';
                            printMap(map);
                            break;
                        }                        
                    }
                    break;
                }
            }
        }
    //}
}
/*This is my primary game function*/     
/*It takes integer from startgame() function to decide who is stars first*/
/*This function is divided into two branches according to the incoming value.*/
/*The first of these branches is when the first player starts first, and the second branch is when the second player starts first.*/
/*In these situations, whichever player starts first, his moves are done in this function without the need for an extra function.*/
/*For the other player, an extra function is called.*/
void game(){
    int i,j,r1,r,k,l,flag;
    char c,temp;
    printMap(map);
    printf("To start the game players should dice and decide who is going to start first according to it\n");    
    c=startGame();
    if(c==1){
        printf("******Player 1 will start the game******\n");
        while(1){
            for(i=1;i<14;i++){
                for(j=1;j<29;j++){
                    if(map[i][j] == '1'){
                        printf("\033[0;33m");
                        printf("PLAYER 1....press ENTER the dice");
                        if(getchar() == '\n') r1 = dice();
                        printf("DICE: %d\n",r1);
                        printf("\033[0;37m");
                    
                        if(map[i][j] == '1' && i==1 && j==28){
                            if(i+r1 == 7){
                                if(i==5 && j==28){
                                    printf("Penalty for Player 1\n");
                                }
                                else{
                                    printf("Penalty for Player 1\n");
                                    temp = map[i][j];
                                    map[5][28] = temp;
                                    map[i][j] = ' ';  
                                }                              
                            }
                            else{
                                temp = map[i][j];
                                map[i+r1][j] = temp;
                                map[i][j] = ' ';
                            }
                        }
                        if(map[i][j] == '1' && i==13 && j==28){
                            temp = map[i][j];
                            map[i][j-r1] = temp;
                            map[i][j] = ' '; 
                        }   
                        if(map[i][j] == '1' && i==13 && j==1){
                            temp = map[i][j];
                            map[i-r1][j] = temp;
                            map[i][j] = ' ';
                        }
                        if(map[i][j] == '1'){
                            if(i==1){
                                if(j+r1>28){
                                    temp = map[i][j];
                                    map[i+(j+r1-28)][28] = temp;
                                    map[i][j] = ' ';
                                }
                                if(j==28){
                                    temp = map[i][j];
                                    map[i+r1][j] = temp;
                                    map[i][j] = ' ';
                                }
                                if(j<28 && j>=1){
                                    if(j+r1 == 14){
                                        if(i == 1 && j == 12){
                                            printf("Penalty for Player 1\n");
                                        }
                                        else{
                                            printf("Penalty for Player 1\n");
                                            temp = map[i][j];
                                            map[i][12] = temp;
                                            map[i][j] = ' ';  
                                        }                        
                                    }
                                    else{
                                        temp = map[i][j];
                                        map[i][j+r1] = temp;
                                        map[i][j] = ' ';
                                    }
                                }
                            }
                            if((i>1 && i<13) && j == 28){
                                if(i+r1>13){
                                    temp = map[i][j];
                                    map[13][j-(i+r1-13)] = temp;
                                    map[i][j] = ' ';
                                }
                                else{
                                    if(i+r1 == 7){
                                        if(i==5 && j==28){
                                            printf("Penalty for Player 1\n");
                                        }
                                        else{
                                            printf("Penalty for Player 1\n");
                                            temp = map[i][j];
                                            map[5][28] = temp;
                                            map[i][j] = ' ';  
                                        }                              
                                    }
                                    else{
                                        temp = map[i][j];
                                        map[i+r1][j] = temp;
                                        map[i][j] = ' ';
                                    }                                                     
                                }
                            }
                            if(i == 13){
                                if(j==28){
                                    temp = map[i][j];
                                    map[i][j-r1] = temp;
                                    map[i][j] = ' ';  
                                }
                                if(j-r1<1){
                                    temp = map[i][j];
                                    map[i-((r1-j)%28)-1][1] = temp;
                                    map[i][j] = ' ';
                                }
                                if(j==1){
                                    temp = map[i][j];
                                    map[i-r1][j] = temp;
                                    map[i][j] = ' ';
                               }   
                                if(j<28 && j>1){
                                    if(j-r1 == 14){
                                        if(i == 13 && j == 16){
                                            printf("Penalty for Player 1\n");
                                        }
                                        else{
                                            printf("Penalty for Player 1\n");
                                            temp = map[i][j];
                                            map[13][16] = temp;
                                            map[i][j] = ' ';  
                                        }                              
                                    }
                                    else{
                                        temp = map[i][j];
                                        map[i][j-r1] = temp;
                                        map[i][j] = ' ';
                                    }
                                }
                            }
                            if((i>1 && i<13) && j==1){
                                if(i-r1<1){
                                    temp = map[i][j];
                                    map[1][1] = temp;
                                    map[i][j] = ' '; 
                                    printf("******Player 1 Won the Game******\n"); 
                                    exit(0);
                                }
                                if(i-r1 == 1){
                                    temp = map[i][j];
                                    map[1][1] = temp;
                                    map[i][j] = ' '; 
                                    printf("******Player 1 Won the Game******\n"); 
                                    exit(0);
                                }
                                else{
                                    temp = map[i][j];
                                    map[i-r1][j] = temp;
                                    map[i][j] = ' ';
                                }   
                            }
                        }
                        move_2();
                    }               
                }
            }
        }   
    }

    if(c==2){
        printf("******Player 2 will start the game******\n");
        while(1){        
            for(i=0;i<15;i++){
                for(j=0;j<30;j++){
                    if(map[i][j] == '2'){
                        printf("\033[0;34m");
                        printf("PLAYER 2....press ENTER the dice");
                        if(getchar() == '\n') r = dice();
                        printf("DICE: %d\n",r);
                        printf("\033[0;37m");                        
                        if(i==11 && j== 3){
                            temp = map[i][j];
                            map[i-r][j] = temp;
                        }
                        if(i==11 && j== 26){
                            if(j-r == 10){
                                if(i==11 && j==12){
                                    printf("Penalty for Player 2\n");
                                    //map[11][12] = '2';
                                }
                                else{
                                    printf("Penalty for Player 2\n");
                                    temp = map[i][j];
                                    map[11][12] = temp;
                                    map[i][j] = ' ';
                                    
                                }                             
                            }
                            else if(j-r == 18){
                                if(i==11 && j==20){
                                    printf("Penalty for Player 2\n");
                                    //map[11][20] = '2';
                                }
                                else{
                                    printf("Penalty for Player 2\n");
                                    temp = map[i][j];
                                    map[11][20] = temp;
                                    map[i][j] = ' ';
                                }                             
                            }
                            else{
                                temp = map[i][j];
                                map[i][j-r] = temp;
                                map[i][j] = ' ';
                            }
                        }
                        if(i==3 && j== 26){
                            if(i+r==5){
                                if(i==3 && j==26){
                                    printf("Penalty for Player 2\n");
                                    //map[3][26] = '2';
                                }
                                else{
                                    printf("Penalty for Player 2\n");
                                    temp = map[i][j];
                                    map[3][26] = temp;
                                    map[i][j] = ' ';
                                }
                            }
                            else if(i+r == 10){
                                if(i==8 && j==26){
                                    printf("Penalty for Player 2\n");
                                    //map[8][26] = '2';
                                }   
                                else{
                                    printf("Penalty for Player 2\n");
                                    temp = map[i][j];
                                    map[8][26] = '2';
                                    map[i][j] = ' ';
                                }                            
                            }
                            else{
                                temp = map[i][j];
                                map[i+r][j] = temp;
                                map[i][j] = ' ';
                            }
                        }
                        if(map[i][j] == '2'){
                            if(i==3){
                                if(j+r==10){
                                    if(i==3 && j==8){
                                        printf("Penalty for Player 2\n");
                                        //map[3][8] = '2';
                                    }
                                    else{
                                        printf("Penalty for Player 2\n");
                                        temp = map[i][j];
                                        map[3][8] = temp;
                                        map[i][j] = ' ';
                                    }
                                }
                                else if(j+r == 18){
                                    if(i==3 && j==16){
                                        printf("Penalty for Player 2\n");
                                        //map[3][16] = '2';
                                    }
                                    else{
                                        printf("Penalty for Player 2\n");
                                        temp = map[i][j];
                                        map[3][16] = temp;
                                        map[i][j] = ' ';
                                    }                            
                                }
                                else if(j>=3 && j<26 && j+r<26){
                                    map[i][j+r] = '2';
                                    map[i][j] = ' ';
                                }
                                else if(j+r>26){
                                    map[i+((j+r)%24)-2][26] = '2';
                                    map[i][j] = ' ';
                                }
                                else if(j+r==26){
                                    map[3][26] = '2';
                                    map[i][j] = ' ';                            
                                }
                            }
                            if((i>3 && i<11) && j==26){
                                if(i+r==5){
                                    if(i==3 && j==26){
                                        printf("Penalty for Player 2\n");
                                        //map[3][26] = '2';
                                    }
                                    else{
                                        printf("Penalty for Player 2\n");
                                        temp = map[i][j];
                                        map[3][26] = temp;
                                        map[i][j] = ' ';
                                    }
                                }
                                else if(i+r == 10){
                                    if(i==8 && j==26){
                                        printf("Penalty for Player 2\n");
                                        //map[8][26] = '2';
                                    }   
                                    else{
                                        printf("Penalty for Player 2\n");
                                        temp = map[i][j];
                                        map[8][26] = '2';
                                        map[i][j] = ' ';
                                    }                            
                                }
                                else if(i+r>11){
                                    temp = map[i][j];
                                    map[11][j-(i+r)%9] = temp;
                                    map[i][j] = ' ';
                                    flag = 1;
                                }
                                else{
                                    if(flag != 1){
                                        temp = map[i][j];
                                        map[i+r][j] = temp;
                                        map[i][j] = ' ';  
                                    }
                                }   
                            }
                            if(i==11){
                                if(j-r == 10){
                                    if(i==11 && j==12){
                                        printf("Penalty for Player 2\n");
                                        //map[11][12] = '2';
                                    }   
                                    else{
                                        printf("Penalty for Player 2\n");
                                        temp = map[i][j];
                                        map[11][12] = temp;
                                        map[i][j] = ' ';

                                    }                             
                                }
                                else if(j-r == 18){
                                    if(i==11 && j==20){
                                        printf("Penalty for Player 2\n");
                                        //map[11][20] = '2';
                                    }
                                    else{
                                        printf("Penalty for Player 2\n");
                                        temp = map[i][j];
                                        map[11][20] = temp;
                                        map[i][j] = ' ';
                                    }                             
                                }                        
                                else if(j==26){
                                    temp = map[i][j];
                                    map[i][j-r] = temp;
                                    map[i][j] = ' ';  
                                }
                                else if(j-r<3){
                                    temp = map[i][j];
                                    map[i-((r-j)%24)-2][3] = temp;
                                    map[i][j] = ' ';  
                                }
                                else if(j==3){
                                    temp = map[i][j];
                                    map[i-r][j] = temp;
                                    map[i][j] = ' ';
                                }
                                else{
                                    temp = map[i][j];
                                    map[i][j-r] = temp;
                                    map[i][j] = ' ';
                                
                                }                            
                            }
                            if((i>3 && i<11)&& j==3){
                                if(i-r<3){
                                    temp = map[i][j];
                                    map[3][3] = temp;
                                    map[i][j] = ' '; 
                                    printf("******Player 2 Won the Game******\n");
                                    exit(0);
                                }   
                                else if(i-r == 3){
                                    temp = map[i][j];
                                    map[3][3] = temp;
                                    map[i][j] = ' ';
                                    printf("******Player 2 Won the Game******\n"); 
                                    exit(0);
                                }
                                else if(i-r >3){
                                    temp = map[i][j];
                                    map[i-r][j] = temp;
                                    map[i][j] = ' ';

                                }
                            }
                        }
                        move_1();
                    }
                }
            }
        }
    }
}