#include <iostream>
#include "Tetris.h"
using namespace std;
using namespace GAME_TTS;

int main(){
    srand(time(nullptr));
    int row;
    int column;
    int key;
    //This part tests the Tetromino class
    cout << "-------------Testing Tetromino class----------"<<endl;
    cout << "Choose Tetromino Type"<<endl;
    cout << "\t1 - I"<< endl;
    cout << "\t2 - O"<< endl;
    cout << "\t3 - L"<< endl;
    cout << "\t4 - S"<< endl;
    cout << "\t5 - Z"<< endl;
    cout << "\t6 - T"<< endl;
    cout << "\t7 - J"<< endl;
    cout << "Choice: ";
    while((!(cin>>key)) || (key<1 || key>7)){
        cout << "Wrong choice: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    Tetromino tetro(static_cast<TType>(key-1));
    cout << "Testing Tetromino \"print\" function."<<endl;    
    tetro.print();
    cout << "Testing Tetromino \"rotate\" function."<<endl;
    cout << "\tRotating right"<<endl;
    tetro.rotate(2);
    tetro.print();
    cout << "\tRotating left"<<endl;
    tetro.rotate(1);    
    tetro.print();

    
    //This part tests the Tetris class
    cout << "-------------Testing Tetris class----------"<<endl;
    cout << "Enter height : ";
    cin >> row;
    cout << "Enter width : ";
    cin >> column;
    cout << "Testing Constructor" << endl;
    Tetris game(row,column);
    cout << "Choose Tetromino Type"<<endl;
    cout << "\t1 - I"<< endl;
    cout << "\t2 - O"<< endl;
    cout << "\t3 - L"<< endl;
    cout << "\t4 - S"<< endl;
    cout << "\t5 - Z"<< endl;
    cout << "\t6 - T"<< endl;
    cout << "\t7 - J"<< endl;
    cout << "\t8 - Q(Quit)"<< endl;
    cout << "Choice: ";
    while((!(cin>>key)) || (key<=0 || key>8)){
        cout << "Wrong choice: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    if(key == 8){
        exit(0);
    }
    Tetromino tetro2(static_cast<TType>(key-1));
    cout << "Adding tetromino to the board(Testing \"+=\" operator)"<<endl;
    game += tetro2;
    cout << "Testing Tetris \"draw\" function."<<endl;
    game.draw();
    cout << "Testing Tetris \"animate\" function."<<endl;
    game.animate();
}