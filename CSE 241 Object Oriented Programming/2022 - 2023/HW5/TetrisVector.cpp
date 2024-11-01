#include <iostream>
#include <unistd.h> 
#include "TetrisVector.h"
using namespace std;

namespace HW5{
    TetrisVector::TetrisVector(int heightT,int  widthT) : AbstractTetris(widthT,heightT){
		//Check existing file
		char key;
        string filename = "Program.txt";
        ifstream f(filename.c_str());
        bool n = f.good();
        f.close();
        //If there is a file that contains board ask user for uploading

        if(n == true){
            cout << "A saved file for the object was found. Do you want to upload(Y/N) : ";
            cin >> key;
            if(key == 'Y' || key == 'y'){
                readFromFile();
            }
            else if(key == 'N' || key == 'n'){
                width = widthT;
                height = heightT;
				board.resize(height,vector<int>(width));
				for (int i = 0; i <= height - 2; i++) {
					for (int j = 0; j <= width - 2; j++) {
						//0 is down-side of border.
						if ((i == 0)||(j == 0) || (j == width - 2) || (i == width- 2)) {
							board[i][j] = 2;
							
						} 
						else {
							board[i][j] = 0;
						}
					}
				}
            }
        }
		else{
			board.resize(height,vector<int>(width));
			for (int i = 0; i <= height - 2; i++) {
				for (int j = 0; j <= width - 2; j++) {
					//0 is down-side of border.
					if ((i == 0)||(j == 0) || (j == width - 2) || (i == width- 2)) {
						board[i][j] = 2;
						
					} 
					else {
						board[i][j] = 0;
					}
				}
			}
		}
		board_cpy.resize(height,vector<int>(width));
		tetro.resize(4,vector<int>(4));
        board_cpy = board;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                tetro[i][j] = 0;
            }
        }
        isGameOver = false;

    } 
    //Templated draw function. This function prints the board 
    void TetrisVector::draw() const{
        usleep(50000);
        cout << "\x1B[2J\x1B[H";	
        for( auto &row : board){
            for(auto &col : row){
                if(col == 2)
                    cout << '*';
                else if(col == 0)
                    cout << ' ';
                else if(col == 1)
                    cout << 'X';
            }
            cout << endl;
        }
    }
	//This function moves the tetromino
	void TetrisVector::move(const int &newX, const int &newY) {
		//Remove block
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				board[y + i][x + j] -= tetro[i][j];
			}
		}
		//Update coordinates
		x = newX;
		y = newY;

		//Add ablock with the updated value
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				board[y + i][x + j] += tetro[i][j];
			}
		}

	}
	//This function checks the fullness of the next block
	bool TetrisVector::isFilled(const int &newX, const int &newY) const {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (tetro[i][j] && board_cpy[newY + i][newX + j] != 0) {
                    return true;
				}
			}
		}
		return false;
	}
    //+= operator overload for adding tetromino to the board
    void TetrisVector::operator+=(Tetromino & newT){
        x = width/2-1;
		y = 0;
		m = newT;
		tetro = m.getTetro();
		//Add tetromino to the board
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
                board[i][x + j] = board_cpy[i+1][x + j] + tetro[i][j];
                if (board[y+i][x + j] >1) {
                    isGameOver = true;
                }
			}
		}
    }
    void TetrisVector::animate() {
		try{
            //Writing board to the file when exiting
			if(isGameOver == true){
				cout << "\e[0;31m----------GAME OVER----------\e[0m" << endl;
				cout << "Last Move : " << lastMove() << endl;
				cout << "Total Moves : " << numberOfMoves() << endl;
				cout << "Program saved to the file named \"Program.txt\"" << endl;
				writeToFile();
				exit(0);
			}
			draw();
            //Asking user for rotation and horizontaly movement
			int choice,rCount = 0,choice2,mCount = 0;
			cout << "Enter Rotation" << endl;
			cout << "\t0 - None" << endl;
			cout << "\t1 - Left" << endl;
			cout << "\t2 - Right" << endl;
			cout << "Choice : ";
			while((!(cin>>choice)) || !(choice==1 || choice==2 || choice == 0)){
				cout << "Wrong choice: ";
				cin.clear();
				cin.ignore(10000, '\n');
			}
			cout << "Enter Rotation Count : ";
			while((!(cin>>rCount)) || (rCount<0)){
				cout << "Wrong choice: ";
				cin.clear();
				cin.ignore(10000, '\n');
			}
			cout << "Enter Move Direction" << endl;
			cout << "\t0 - None" << endl;
			cout << "\t1 - Left" << endl;
			cout << "\t2 - Right" << endl;
			cout << "Choice : ";
			while((!(cin>>choice2)) || !(choice2==1 || choice2==2 || choice2 == 0)){
				cout << "Wrong choice: ";
				cin.clear();
				cin.ignore(10000, '\n');
			}
			cout << "Enter Move Direction Count : ";
			while(!(cin>>mCount) || (mCount<0) || (mCount + abs(x) >= width)){
				cout << "Wrong choice: ";
				cin.clear();
				cin.ignore(10000, '\n');
			}
			vector<vector<int>> temp(4,vector<int>(4));
			temp = tetro;
			//Rotating by choice		
			for(int i=0;i<rCount;i++){
				tetro = m.rotate(choice);
			}
			//If place is filled return the old version
			if (isFilled(x, y)) {
				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < 4; j++) {
						tetro[i][j] = temp[i][j];
					}
				}
			}
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					board[y + i][x + j] -= temp[i][j]; //remove block data before rotation.
					board[y + i][x + j] += tetro[i][j]; //add new block data after rotation.
				}
			}
			//Move on top horizontaly
			if(choice2 == 1){
				if (!isFilled(x-mCount, y)){
					move(x-mCount, y);
				}	
			}
			else if(choice2 == 2){
				if (!isFilled(x+mCount, y)){
					move(x+mCount, y);
				}
			}
			xTotal+=mCount;
			lastM = mCount;
			while (isGameOver == false) {
				//Move downward according the fullness
				if (isFilled(x, y + 1) == false) {
					move(x, y + 1);
					lastM = 1;
					++yTotal;
				}
				else {
					for (int i = 0; i < height - 1; i++) {
						for (int j = 0; j < width - 1; j++) {
							board_cpy[i][j] = board[i][j];
						}
					}
					draw();
					return;
				}
				draw();
			}
		}
		catch(const std::exception& e){
            cout << e.what() << endl;
        }
    }
    //This function reads the file and puts the board variable
	void TetrisVector::readFromFile(){
		try{
			ifstream in("Program.txt");
			if (in.fail()) throw "Program.txt";
			vector<string> temp1;
			string id;
			while (getline(in,id))
			{
				temp1.push_back(id);
			}
			height =temp1.size();
			width = temp1[0].size();
			board.resize(height,vector<int>(width));
			for(int i = 0;i<temp1.size();i++){
				for(int j = 0;j<temp1[i].size();j++){
						if(temp1[i][j] == '*')
							board[i][j] = 2;
						else if(temp1[i][j] == 'X')
							board[i][j] = 1;
						else if(temp1[i][j] == ' ')
							board[i][j] = 0;
				}
			}
			in.close();
		}
		catch(string e){
            cout << e << " was not successfully opened.\n Please check that the file currently exists." << endl;
            exit(1);
		}
	}
	//This function writes the  board to the file
	void TetrisVector::writeToFile() const {
		try{
			ofstream Out("Program.txt");
			auto row_it = board.begin();
			auto row_end = board.end();
			
			for ( ; row_it != row_end; ++row_it )
			{
				
				auto col_it = row_it->begin();
				auto col_end = row_it->end();
				
				for ( ; col_it != col_end; ++col_it ){
						if(*col_it == 2)
							Out << '*';
						else if(*col_it == 1)
							Out << 'X';
						else if(*col_it == 0)
							Out << ' ';
				}
				Out << '\n';
			}
			Out.close();
		}
		catch(string e){
			cout << e << " was not successfully opened.\n Please check that the file currently exists." << endl;
            exit(1);
		}
	}
}