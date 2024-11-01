#include <iostream>
#include <unistd.h> 
#include "Tetris.h"

namespace GAME_TTS{
	//Default constructor
	Tetris::Tetris():width(0),height(0){
	}
	//Constructor that takes width and height
	Tetris::Tetris(int &heightU,int &widthU):board(heightU,widthU),board_cpy(heightU,widthU){
		width = widthU;
		height = heightU;
		//Creating a custom vector that creates a board with 0,1 and 2
		MyCustom2DVector temp(height,width);
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
		MyCustom2DVector temp2(4,4);
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
		usleep(50000);
		//Clear screen
		cout << "\x1B[2J\x1B[H";	
		for (int i = 0; i <= height - 1; i++) {
			for (int j = 0; j <= width - 1; j++) {
				//cout << board[i][j];
				if(board[i][j] == BORDER)
					cout << '*';
				else if(board[i][j]== FREE)
					cout << ' ';
				else if(board[i][j] == FILLED)
					cout << 'X';
					
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
		draw();
		while (isGameOver == false) {	
			//Move downward according the fullness
			if (!isFilled(x, y+1)) {
				move(x, y + 1);
			}
			//If next block is full then rotate and move left the tetromino
			else {
				save_present_board_to_cpy();
				draw();
				return;
			}
			draw();
		}
	}
	Tetris & Tetris::operator+=(Tetromino &newT){
		x = width/2-1;
		y = 0;
		int blockType;
		m = newT;
		tetro = m.getTetro();
		//Add tetromino to the board
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				board[i+y][x + j] = board_cpy[y+i+1][x + j] + tetro[i][j];
				if (board[y+i][x + j] > 1) {
					isGameOver = true;
				}
			}
		}
		return *this;
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

	}
	//This function checks the fullness of the next block
	bool Tetris::isFilled(const int &newX, int newY) const {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
                cout << "i: " << i << " j: " << j << endl;
                
				cout << "newY+i: " << newY + i << " newX+j: " << newX + j <<  endl;

                cout << tetro[i][j] << " " << board_cpy[newY + i][newX + j] << endl;
				if (tetro[i][j] && board_cpy[newY + i][newX + j] != 0) {
					//cout << tetro[i][j] << " " << board_cpy[newY + i][newX + j] << endl;
					return true;
				}
			}
		}
		return false;
	}

}
