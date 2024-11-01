#include <iostream>
#include "Tetris.h"
using namespace std;

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
    tetro.rotate();
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
    cout << "\t8 - R(Random)"<< endl;
    cout << "\t9 - Q(Quit)"<< endl;
    cout << "Choice: ";
    while((!(cin>>key)) || (key<=0 || key>9)){
        cout << "Wrong choice: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    if(key == 9){
        exit(0);
    }
    cout << "Testing Tetris \"add\" function."<<endl;
    game.add(key);
    cout << "Testing Tetris \"fit\" function(Inside fit funtion rotate and move function working)."<<endl;
    game.fit();
    cout << "Testing Tetris \"draw\" function."<<endl;
    game.draw();
    cout << "Testing Tetris \"animate\" function."<<endl;
    game.animate();
}