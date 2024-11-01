#include <iostream>
#include <unistd.h> 
#include "TetrisArray1D.h"
using namespace std;

namespace HW5{
    //Destructor for freeing allocated memory
    TetrisArray1D::~TetrisArray1D(){
        delete [] board;
        delete[] board_cpy;
        delete[] tetro;
    }
    //Constructor
    TetrisArray1D::TetrisArray1D(int heightT,int  widthT) : AbstractTetris(heightT,widthT){
		//Check existing file
        char key;
        string filename = "Program.txt";
        ifstream f(filename.c_str());
        bool n = f.good();
        f.close();
        //If there is a file that contains board ask user for uploading
        //Declaring board and tetro       
        if(n == true){
            cout << "A saved file for the object was found. Do you want to upload(Y/N) : ";
            cin >> key;
            if(key == 'Y' || key == 'y'){
                readFromFile();
            }
            else if(key == 'N' || key == 'n'){
                width = widthT;
                height = heightT;
                board = new int[height*width];
                for (int i = 0; i <= height - 2; i++) {
                    for (int j = 0; j <= width - 2; j++) {
                        if ((i == 0)||(j == 0) || (j == width - 2) || (i == width- 2)) {
                            board[width*i+j] = 2;
                            
                        } 
                        else {
                            board[width*i+j] = 0;
                        }
                    }
                }
            }
        }
		else{
			board = new int[height*width];
			for (int i = 0; i <= height - 2; i++) {
				for (int j = 0; j <= width - 2; j++) {
					if ((i == 0)||(j == 0) || (j == width - 2) || (i == width- 2)) {
						board[width*i+j] = 2;
						
					} 
					else {
						board[width*i+j] = 0;
					}
				}
			}
		}
		board_cpy = new int[height*width];
		tetro = new int[4*4];
        for(int i = 0;i<height;i++){
            for(int j = 0;j<width;j++){
		        board_cpy[width*i+j] = board[width*i+j];
            }
        }
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                tetro[4*i+j] = 0;
            }
        }
        isGameOver = false;

    } 
    // This function prints the board to screen
    void TetrisArray1D::draw() const{
        usleep(50000);
        cout << "\x1B[2J\x1B[H";	
        for(int i = 0;i<height;i++){
            for(int j = 0;j<width;j++){
                if(board[width*i+j] == 2)
                    cout << '*';
                else if(board[width*i+j] == 0)
                    cout << ' ';
                else if(board[width*i+j] == 1)
                    cout << 'X';
            }
            cout << endl;
        }
    }
	//This function moves the tetromino
	void TetrisArray1D::move(const int &newX, const int &newY) {
		//Remove block
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				board[width*(y +i)+x + j] -= tetro[4*i+j];
			}
		}
		//Update coordinates
		x = newX;
		y = newY;

		// Add block with the updated value
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				board[width*(y +i)+x + j] += tetro[4*i+j];
			}
		}
	}
	//This function checks the fullness of the next block
	bool TetrisArray1D::isFilled(const int &newX, const int &newY) const {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (tetro[4*i+j] && board_cpy[width*(newY + i)+newX + j] != 0) {
                    return true;
				}
			}
		}
		return false;
	}
    //This overloaded operator adds the tetromino to the board
    void TetrisArray1D::operator+=(Tetromino & newT){
        x = width/2-1;
		y = 0;
		m = newT;
        tetro = new int[16];
        //Getting tetro from Tetromino object
        for(int i = 0;i<4;i++){
            for(int j = 0;j<4;j++){
		        tetro[4*i+j] = (m.getTetro())[i][j];
            }
        }
		//Add tetromino to the board
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
                board[width*i + x + j] = board_cpy[width*(i+1)+x + j] + tetro[4*i+j];
                if (board[width*(y+i)+x + j] >1) {
                    isGameOver = true;
                }
			}
		}
    } 
    //This function moves and rotates the tetromino tetro according to the user's choice.
    void TetrisArray1D::animate() {
        try{
            if(isGameOver == true){
            //Writing board to the file when exiting
                cout << "\e[0;31m----------GAME OVER----------\e[0m" << endl;
                cout << "Last Move : " << lastMove() << endl;
                cout << "Total Moves : " << numberOfMoves() << endl;
                cout << "Program saved to the file named \"Program.txt\"" << endl;
                writeToFile();
                exit(0);
            }
            draw();
            //Asking user for rotation and horizontaly movement
            int choice,rCount=0,choice2,mCount=0;
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
            int *temp;
            temp = new int[16];
            for(int i = 0;i<4;i++){
                for(int j = 0;j<4;j++){
                    temp[4*i+j] = tetro[4*i+j];
                }
            }
            //Rotating by choice		
            for(int i=0;i<rCount;i++){
                for(int i = 0;i<4;i++){
                    for(int j = 0;j<4;j++){
                        tetro[4*i+j] = (m.rotate(choice))[i][j];
                    }
                }
            }
            //If place is filled return the old version
            if (isFilled(x, y)) {
                for (int i = 0; i < 4; i++) {
                    for (int j = 0; j < 4; j++) {
                        tetro[4*i+j] = temp[4*i+j];
                    }
                }
            }
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    board[width*(y + i)+x + j] -= temp[4*i+j]; //remove block data before rotation.
                    board[width*(y + i)+x + j] += tetro[4*i+j]; //add new block data after rotation.
                }
            }
            //Move on top horizontaly
            if(choice2 == 1){
                if (!isFilled(x-mCount, y))
                    move(x-mCount, y);
            }
            else if(choice2 == 2){
                if (!isFilled(x+mCount, y))
                    move(x+mCount, y);
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
                            board_cpy[width*i+j] = board[width*i+j];
                        }
                    }
                    draw();
                    return;
                }
                draw();
            }
            delete[] temp;
        }
        catch(const std::exception& e){
            cout << e.what() << endl;
        }
    }
    //This function reads the file puts the board
	void TetrisArray1D::readFromFile(){
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
			board = new int[height*width];
			for(int i = 0;i<temp1.size();i++){
				for(int j = 0;j<temp1[i].size();j++){
						if(temp1[i][j] == '*')
							board[width*i+j] = 2;
						else if(temp1[i][j] == 'X')
							board[width*i+j] = 1;
						else if(temp1[i][j] == ' ')
							board[width*i+j] = 0;
				}
			}
			in.close();
		}
		catch(string e){
            cout << e << " was not successfully opened.\n Please check that the file currently exists." << endl;
            exit(1);
		}
	}    
    //This function writes the board to the file
    void TetrisArray1D::writeToFile() const {
        try{
            ofstream Out("Program.txt");
            if (Out.fail()) throw "Program.txt";
            for(int i = 0;i<height;i++){
                for(int j = 0;j<width;j++){
                    if(board[width*i+j] == 2)
                        Out << '*';
                    else if(board[width*i+j] == 0)
                        Out << ' ';
                    else if(board[width*i+j] == 1)
                        Out << 'X';
                }
                Out << endl;
            }
            Out.close();
        }
		catch(string e){
            cout << e << " was not successfully opened.\n Please check that the file currently exists." << endl;
            exit(1);
		}        
	}

}