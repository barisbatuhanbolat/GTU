#include <iostream>
#include <time.h>
#include <unistd.h> 
#include "Tetris.h"
//Default constructor
Tetris::Tetris():width(0),height(0){
}
//Constructor that takes width and height
Tetris::Tetris(int &heightU,int &widthU){
    width = widthU;
    height = heightU;
	//Creating a vector that creates a board with 0,1 and 2
    vector<vector<int>> temp(height,vector<int>(width));
	for (int i = 0; i <= height - 2; i++) {
		for (int j = 0; j <= width - 2; j++) {
			//0 is down-side of border.
			if ((i == 0)||(j == 0) || (j == width - 2) || (i == width- 2)) {
				temp[i][j] = BORDER;
				
			} else {
				temp[i][j] = FREE;
			}
		}
	}
	//Assign temporary board to actual one
    board = temp;
    board_cpy = temp;
	//creating an empty tetro 
    vector<vector<int>> temp2(4,vector<int>(4));
    for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			temp2[i][j] = FREE;
		}
	}
	//Assign temporary tetro to actual one
    tetro = temp2;
    isGameOver = false;
}
//Printing board
void Tetris::draw(){
	for (int i = 0; i <= height - 1; i++) {
		for (int j = 0; j <= width - 1; j++) {
            if(board[i][j] == BORDER)
                cout << '*';
            else if(board[i][j]== FREE)
                cout << ' ';
            else if(board[i][j] == FILLED){
				cout << 'X';
			}
        }   
        cout << endl;
    }
}
//Copying board for backup
void Tetris::save_present_board_to_cpy() {
	for (int i = 0; i < height - 1; i++) {
		for (int j = 0; j < width - 1; j++) {
			board_cpy[i][j] = board[i][j];
		}
	}
}
//This function moves and rotates the tetromino tetro according to board.
void Tetris::animate() {
	while (isGameOver == false) {
        usleep(50000);
		//Clear screen
        cout << "\x1B[2J\x1B[H";
		//Move downward according the fullness
        if (!isFilled(x, y + 1)) {
            move(x, y + 1);
        }
		//If next block is full then rotate and move left the tetromino
        else {
			if(!isFilled(x-1, y)){
				fit();
				while(!isFilled(x-1, y)) {
					move(x-1, y);
				}
			}
			else if(!isFilled(x+1, y)){
					fit();
				while(!isFilled(x+1, y)) {
					move(x+1, y);
				}
			}						
            save_present_board_to_cpy();
            draw();
            return;
        }
	}
	if(isGameOver == true){
		cout << "-----------GAME OVER-----------"<< endl;
		exit(0);

	}
}
void Tetris::add(int key){
	//Inıtıalizing spawn point of tetrominos
	x = width/2-1;
	y = 0;
	int blockType;
	// Initializing the tetromino type according the key
	if(key == 8){
    	blockType = rand()%7;
	}
	else{
		blockType = key-1;
	}
	//Initializing the tetromino type
	Tetromino k(static_cast<TType>(blockType));
	m = k;
	tetro = m.getTetro();
	//Add tetromino to the board
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			board[i][x + j] = board_cpy[i+1][x + j] + tetro[i][j];
			if (board[i][x + j] >1) {
				isGameOver = true;
			}
		}
	}
}
//This function moves the tetromino
void Tetris::move(const int &newX, const int &newY) {
	//Remove block
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			board[y + i][x + j] -= tetro[i][j];
		}
	}
	//Update coordinates
	x = newX;
	y = newY;

	// assign a block with the updated value
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			board[y + i][x + j] += tetro[i][j];
		}
	}

	draw();
}
//This function checks the fullness of the next block
bool Tetris::isFilled(const int &newX, const int &newY) const {
	//because every block definition array is 4 * 4 length array. i will traverse from 0 to 4.
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (tetro[i][j] && board_cpy[newY + i][newX + j] != 0) {
				return true;
			}
		}
	}
	return false;
}

//This function rotates the tetromino according the board
void Tetris::fit(){
	vector<vector<int>> temp;
	temp = tetro;
	tetro = m.rotate();

	if (isFilled(x, y)) { // And stop if it overlaps not be rotated
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				tetro[i][j] = temp[i][j]; //return back.
			}
		}
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			board[y + i][x + j] -= temp[i][j]; //remove before changing
			board[y + i][x + j] += tetro[i][j]; //add new block data after rotation.
		}
	}
	draw();
}
