#include <iostream>
#include <vector>
#include <deque>
#include "TetrisVector.h"
#include "AbstractTetris.h"
#include "TetrisArray1D.h"
#include "TetrisAdapter.h"

using namespace std;
using namespace HW5;

template <class T>
void playGame(T & game){
    int key;
    while(key != 9 ){
        cout << "Choose Tetromino Type"<<endl;
        cout << "\t1 - I"<< endl;
        cout << "\t2 - O"<< endl;
        cout << "\t3 - L"<< endl;
        cout << "\t4 - S"<< endl;
        cout << "\t5 - Z"<< endl;
        cout << "\t6 - T"<< endl;
        cout << "\t7 - J"<< endl;
        cout << "\t8 - R(Random)"<< endl;
        cout << "\t9 - Q(Quit)"<< endl;
        cout << "Choice: ";
        while((!(cin>>key)) || (key<=0 || key>9)){
            cout << "Wrong choice: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        if(key == 9){
            cout << "Last Move : " <<game.lastMove() << endl;
            cout << "Total Moves : " << game.numberOfMoves() << endl;
            cout << "Program saved to the file named \"Program.txt\"" << endl;
            game.writeToFile();
            exit(0);
        }
        if(key == 8){
            key = 1 + rand()%7;
        }
        Tetromino tetro(static_cast<TType>(key-1));

        game += tetro;
        game.animate();
    }
}


int main(){
    srand(time(nullptr));
    int row;
    int column;
    char type;
    char type2;    
    cout << "Choose Board Type(V for vector, 1 for array1D, A for adaptor) : ";
    cin >> type;
    cout << "Enter height : ";
    cin >> row;
    cout << "Enter width : ";
    cin >> column;
    if(type == 'V'){
        TetrisVector gameVec(row,column);
        playGame(gameVec);
    }
    else if(type == '1'){
        TetrisArray1D gameArr(row,column);
        playGame(gameArr);
    }
    else if(type == 'A'){
        cout << "Choose type for Adaptor(V for vector, D for deque) : ";
        cin >> type2;
        if(type2 = 'V'){
            TetrisAdapter<vector<vector<int>>,vector<int>> gameAdpV(row,column);
            playGame(gameAdpV);
        }
        else if(type2 = 'D'){
            TetrisAdapter<deque<deque<int>>,deque<int>> gameAdpD(row,column);
            playGame(gameAdpD);            
        } 
    }
}