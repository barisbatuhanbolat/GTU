#include <iostream>
#include "Tetris.h"
using namespace std;

int main()
{
    //Srand for random tetromino
    srand(time(nullptr));
    int row;
    int column;
    int key;

    cout << "Enter height : ";
    cin >> row;
    cout << "Enter width : ";
    cin >> column;
    //Tetris declaration
    Tetris game(row,column);
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
            exit(0);
        }
        game.add(key);
        game.draw();
        game.animate();
    } 
}