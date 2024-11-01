#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
/*Constant macro declaritions*/
#define NUM_ROW 15
#define NUM_COL 15
#define WORD_NUM 50
#define WORD_LEN 20
/*Declaring functions*/
void file_to_array();
void random_ten_words(char s[WORD_NUM][WORD_LEN]);
void create_puzzle(char words[10][WORD_LEN]);
void print_puzzle(char puzzle[NUM_COL][NUM_ROW], int mod);
int check_direction(char puzzle[NUM_COL][NUM_ROW],int random_col, int random_row,int length,int check,char words[10][WORD_LEN],int word_counter);
void find_word(char puzzle[NUM_COL][NUM_ROW],char words[10][WORD_LEN]);
int find_word_in_puzzle(char puzzle[NUM_COL][NUM_ROW],int col,int row,char word[10][WORD_LEN],int word_counter);

int main(){
	printf("**********Word Puzzle Game**********\n");
	printf("Welcome the Word Puzzle Game.\n");
	printf("Remember !!! You can make only three mistakes\n");
    srand(time(NULL));
	file_to_array();
}/*end main*/

/*This function takes all lines from file and puts them into an array*/
void file_to_array(){ 
	FILE *list =fopen("wordlist.txt","r");
	char all_words[WORD_NUM][WORD_LEN];
    int i;
	for (i=0; i<WORD_NUM; i++){
		fgets(all_words[i],WORD_LEN,list);
	}
	fclose(list);
    
    random_ten_words(all_words);
}
/*This function takes all words from file_to_array function and choose 7 random words from that words*/
void random_ten_words(char all_words[WORD_NUM][WORD_LEN]){
    char random_words[7][WORD_LEN];
    int random_numbers[7];
    int randNum,flag,i,j,count=0;

    while(count <7) { 
		randNum =rand()%50; 
		flag =0;
		 
		for (i = 0; i < 7; i++) { 
			if(random_numbers[i] ==randNum) { 
				flag =1; 
				break;
			} 
		} 
		 
		if(flag == 0) { 
			random_numbers[count] =randNum;
            strcpy(random_words[count],all_words[random_numbers[count]]);
			count++; 
		} 
	}
	for(i=0;i<7;i++){
		if(strcmp(random_words[i],"hall") == 0){
			strcpy(random_words[i],"hall \n");
		}
	}
	printf("**********WORDS**********\n");
	printf("%s%s",random_words[0],random_words[1]);
	printf("%s%s",random_words[2],random_words[3]);
	printf("%s%s",random_words[4],random_words[5]);
	printf("%s",random_words[6]);

    create_puzzle(random_words);
}
/*This function adds words to puzzle*/
void create_puzzle(char words[7][WORD_LEN]){
	int random_row,random_col,length,continue_counter=0;
	char puzzle[NUM_COL][NUM_ROW];
	for (int i=0; i < NUM_ROW; i++){
		for (int j=0; j<NUM_COL; j++){
			puzzle[i][j]='.';
		}
	}
	int i=0;
	while (i<7){
		length=strlen(words[i])-2;
		random_col=rand()%NUM_COL;
		random_row=rand()%NUM_ROW;
		if (random_col+length <=15 && random_row+length<=15){
			switch (rand()%3){
				case 0:/*Left to right*/
					continue_counter= check_direction(puzzle,random_col,random_row,length,1,words,i);
					if(continue_counter==1)	break;	
					for (int j=0; j<length; j++){
						puzzle[random_col][random_row+j]=words[i][j];
					}
                    break;
				case 1:/*up to bottom*/
					continue_counter= check_direction(puzzle,random_col,random_row,length,2,words,i);
					if(continue_counter==1)	break;
					for (int j=0; j<length; j++){ 
						puzzle[random_col+j][random_row]=words[i][j];
					}
                    break;
				case 2:/*up left to bottom right diaonally*/
					continue_counter= check_direction(puzzle,random_col,random_row,length,3,words,i);
					if(continue_counter==1)	break;	
					for (int j=0; j<length; j++){ 
						puzzle[random_col+j][random_row+j]=words[i][j];
					}
                    break;
			}
		}
		else if (random_col-length >=0 && random_row-length >=0){
			switch (rand()%3){
				case 0:/*right to left*/
					continue_counter= check_direction(puzzle,random_col,random_row,length,4,words,i);
					if(continue_counter==1)	break;	
					for (int j=0; j<length; j++){ 
						puzzle[random_col][random_row-j]=words[i][j];
					}
                    break;
				case 1:/*bottom to up*/
					continue_counter= check_direction(puzzle,random_col,random_row,length,5,words,i);
					if(continue_counter==1)	break;	
					for (int j=0; j<length; j++){ 
						puzzle[random_col-j][random_row]=words[i][j];
					}
                    break;
				case 2:/*bottom right to up left diagonally*/
				continue_counter= check_direction(puzzle,random_col,random_row,length,6,words,i);
				if(continue_counter==1)	break;	
					for (int j=0; j<length; j++){ 
						puzzle[random_col-j][random_row-j]=words[i][j];
					}
                    break;
			}
		}
		else if(random_col-length>=0 && random_row+length<=15){
			continue_counter= check_direction(puzzle,random_col,random_row,length,7,words,i);
			if(continue_counter==1)	continue;
			else {	
				for (int j=0; j<length; j++){ /*bottom left to up right*/
					puzzle[random_col-j][random_row+j]=words[i][j];
					}
				}
		}
		else if(random_col+length<=15 && random_row-length>=0){
			continue_counter= check_direction(puzzle,random_col,random_row,length,8,words,i);
			if(continue_counter==1)	continue;
			else{	
				for (int j=0; j<length; j++){ /*up right to bottom left*/
					puzzle[random_col+j][random_row-j]=words[i][j];
					}
				}
		}
		if(continue_counter==1)	continue;		
	    i++;
    }

	find_word(puzzle,words);
}
/*This function checks the direction of words as they are placed in the puzzle.*/
int check_direction(char puzzle[NUM_COL][NUM_ROW],int random_col, int random_row,int length,int check,char word[7][WORD_LEN],int word_counter){
	int x=0,x2=0,x3=0;
	switch (check){
		case 1:
			for (int i=0; i<length; i++){
			    if (puzzle[random_col][random_row+i]=='.')
                	x3++;
                else if (puzzle[random_col][random_row+i] == word[word_counter][i])
                	x++; 
                else 
                    x2++;
		    }
            break;
		case 2:
			for (int i=0; i<length; i++){
		    	if (puzzle[random_col+i][random_row]=='.')
                	x3++; 
                else if (puzzle[random_col+i][random_row] == word[word_counter][i])
            	    x++;
                else
                    x2++;
		    }
            break;
		case 3:
			for (int i=0; i<length; i++){
			    if (puzzle[random_col+i][random_row+i]=='.')
                	x3++;
                else if (puzzle[random_col+i][random_row+i] == word[word_counter][i])
                	x++;
                else
                    x2++;
		    }
            break;
		case 4:
			for (int i=0; i<length; i++){
			    if (puzzle[random_col][random_row-i]=='.')
                	x3++;
                else if (puzzle[random_col][random_row-i] == word[word_counter][i])
                	x++;
                else 
                    x2++;
		    }   
            break;
		case 5:
			for (int i=0; i<length; i++){
			    if (puzzle[random_col-i][random_row]=='.')
                	x3++;
                else if (puzzle[random_col-i][random_row] == word[word_counter][i])
                	x++;
                else
                    x2++;
		    }
            break;
		case 6:
			for (int i=0; i<length; i++){
			    if (puzzle[random_col-i][random_row-i]=='.')
                	x3++;
                else if (puzzle[random_col-i][random_row-i] == word[word_counter][i])
                	x++;
                else
                    x2++;
		    }
            break;
		case 7:
			for (int i=0; i<length; i++){
			    if (puzzle[random_col-i][random_row+i]=='.')
                	x3++;
                else if (puzzle[random_col-i][random_row+i] == word[word_counter][i])
                	x++;
                else 
                    x2++;
		    }
            break;
		case 8:
			for (int i=0; i<length; i++){
			    if (puzzle[random_col+i][random_row-i]=='.')
                	x3++;
                else if (puzzle[random_col+i][random_row-i] == word[word_counter][i])
                	x++;
                else
                    x2++;
		    }
            break;
	}
	if (x+x3==length)
		return 0;
	else
		return 1;
}
/*This function gets the coordinates and word from the user. It tries to match them with the words in the puzzle and print the puzzle.*/
void find_word(char puzzle[NUM_COL][NUM_ROW],char word[7][WORD_LEN]){
	int total_point=0,mistake=3,success_counter=0,word_counter=0,result=0,length;
	int i,x,y;
	char choice[20];
	char input[100];
	int mode = 1;
	
	print_puzzle(puzzle,mode);

	do{
		printf("Type 'mode' to open/close random chars in puzzle\n");
		printf("Type ':q' to exit\n");
		printf("Enter coordinates(column and row) and word: ");
		scanf(" %19[^\n]",input);
		sscanf(input,"%d %d %s",&x,&y,choice);
		if(strcmp(":q",input) == 0){
			printf("Exiting...\n");
			exit(0);
		}
		/*According to the mod variable, the function can print the puzzle on the screen as the user wants.*/
		if(strcmp("mode",input) != 0){
			for(i=0;i<7;i++){
				if(strncmp(choice,word[i],strlen(word[i])-2) == 0){
					word_counter = i;
				}
				else{
					result = 0;
				}
			}

			result = find_word_in_puzzle(puzzle,x,y,word,word_counter);

			if(result == 1){
				total_point +=2;
				success_counter++;
				printf("\033[0;32m");
				printf("Founded ! You got 2 points. Your total point: %d\n",total_point);
				printf("\033[0;37m");
			}
			if(result == 0){
				mistake--;
				printf("\033[0;31m");
				printf("Wrong choice! You have only %d lefts.\n",mistake);
				printf("\033[0;37m");
			}

			if(mistake == 0){
				printf("\033[0;31m");
				printf("FAILED!! Your total point is : %d\n",total_point);
				printf("\033[0;37m");
				exit(0);
			}
			if(success_counter == 7){
				print_puzzle(puzzle,mode);
				printf("\033[0;32m");
				printf("SUCCESS !!! You won the game and your total point is: %d\n",total_point);
				printf("\033[0;37m");
				exit(0);
			}

			print_puzzle(puzzle,mode);
		}

		if(strcmp("mode",input) == 0){
			mode = -1*mode;
			print_puzzle(puzzle,mode);
		}

	}while(success_counter != 7 || mistake != 0);
}
/*This function works with find_word function. It tries the find the word in puzzle with coordinates*/
int find_word_in_puzzle(char puzzle[NUM_COL][NUM_ROW],int col,int row,char word[7][WORD_LEN],int word_counter){
	int j,i=0,length;
	
	length = strlen(word[word_counter])-2;
	
	if (puzzle[row][col]!=word[word_counter][i]){
		return 0;
	}

	else{
		i++;
		puzzle[row][col] -=32;

		if (puzzle[row][col+i] == word[word_counter][i]){
			puzzle[row][col+i] -=32;
			for (j=2; j<length; j++){
				puzzle[row][col+j] -=32;
			}
			return 1;
		}
		else if (puzzle[row+i][col] == word[word_counter][i]){
			puzzle[row+i][col] -=32;
			for (j=2; j<length; j++){
				puzzle[row+j][col] -=32;
			}
			return 1;
		}
		else if (puzzle[row+i][col+i] == word[word_counter][i]){
			puzzle[row+i][col+i] -=32;
			for (j=2; j<length; j++){
				puzzle[row+j][col+j] -=32;
			}
			return 1;
		}	
		else if (puzzle[row][col-i] == word[word_counter][i]){
			puzzle[row][col-i] -=32;
			for (j=2; j<length; j++){
				puzzle[row][col-j] -=32;
			}
			return 1;
		}
		else if (puzzle[row-i][col] == word[word_counter][i]){
			puzzle[row-i][col+i] -=32;
			for (j=2; j<length; j++){
				puzzle[row-j][col] -=32;
			}
			return 1;
		}
		else if (puzzle[row-i][col-i] == word[word_counter][i]){
			puzzle[row-i][col-i] -=32;
			for (j=2; j<length; j++){
				puzzle[row-j][col-j] -=32;
			}
			return 1;
		}
		else if (puzzle[row-i][col+i] == word[word_counter][i]){
			puzzle[row-i][col+i] -=32;
			for (j=2; j<length; j++){
				puzzle[row-j][col+j] -=32;
			}
			return 1;
		}
		else if (puzzle[row+i][col-i] == word[word_counter][i]){
			puzzle[row+i][col-i] -=32;
			for (j=2; j<length; j++){
				puzzle[row+j][col-j] -=32;
			}
			return 1;
		}
	}
}
/*This function prints the puzzle and according to given x it fulfill the empty spaces with random keys*/ 
void print_puzzle(char puzzle[NUM_ROW][NUM_COL],int mod){
    int i,j;
	if(mod == 1){
    	for(i=0;i<15;i++){
        	for(j=0;j<15;j++){
    	        if(puzzle[i][j] == '.'){
	                printf("%c ",rand()%(123-97)+97);
            	}
				else if(puzzle[i][j] <=90 && puzzle[i][j] >=65){
					printf("\033[0;33m");
					printf("%c ",'X');
					printf("\033[0;37m");
				}
				else{
            		printf("%c ",puzzle[i][j]);
				}
        	}
			printf("\n");
    	}
	}

	if(mod == -1){
    	for(i=0;i<15;i++){
        	for(j=0;j<15;j++){
				if(puzzle[i][j] <=90 && puzzle[i][j] >=65){
					printf("\033[0;33m");
					printf("%c ",'X');
					printf("\033[0;37m");
				}
				else{
            		printf("%c ",puzzle[i][j]);
				}
        	}
			printf("\n");
    	}
	}
}