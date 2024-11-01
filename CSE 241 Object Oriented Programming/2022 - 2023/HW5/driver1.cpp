#include <iostream>
#include <vector>
#include <deque>
#include <limits.h>
#include "TetrisVector.h"
#include "AbstractTetris.h"
#include "TetrisArray1D.h"
#include "TetrisAdapter.h"

using namespace std;
using namespace HW5;

int main(){
    int row,column,key;
    cout << "------------------------Test Driver-----------------------\n"<< endl;
    cout << "Enter height : ";
    cin >> row;
    cout << "Enter width : ";
    cin >> column;    
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
    Tetromino tetro(static_cast<TType>(key-1));
    cout << "\e[0;31m----------------------------------------------------------\e[0m\n"<< endl;    
    cout << "--------------------TetrisVector Class--------------------\n"<< endl;
    cout << "\e[0;31m----------------------------------------------------------\e[0m\n"<< endl;    
    cout << "----------------TetrisVector Class Constructor----------------\n"<< endl;
    usleep(1000000);
    TetrisVector gameVec(row,column);
    cout << "----------------TetrisVector Class += operator----------------\n"<< endl;
    usleep(1000000);
    gameVec += tetro;
    cout << "-------------TetrisVector Class \"draw\" Function-------------\n"<< endl;
    usleep(1000000);
    gameVec.draw();
    cout << "-------TetrisVector Class \"move\" Function(1 step down)------\n"<< endl;
    usleep(1000000);
    gameVec.move(column/2-1,1);
    cout << "-----------TetrisVector Class \"animate\" Function------------\n"<< endl;
    usleep(1000000);
    gameVec.animate();
    cout << "-----------TetrisVector Class \"lastMove\" Function-----------\n"<< endl;
    usleep(1000000);
    cout << "Last Move:" << gameVec.lastMove() << endl;
    cout << "---------TetrisVector Class \"numberOfMoves\" Function--------\n"<< endl;
    usleep(1000000);
    cout << "NumberOfMoves : " << gameVec.numberOfMoves() << endl;        

    cout << "\e[0;31m----------------------------------------------------------\e[0m\n"<< endl;    
    cout << "--------------------TetrisArray1D Class--------------------\n"<< endl;
    cout << "\e[0;31m----------------------------------------------------------\e[0m\n"<< endl;    
    cout << "----------------TetrisArray1D Class Constructor----------------\n"<< endl;
    usleep(1000000);
    TetrisArray1D gameArr(row,column);
    cout << "----------------TetrisArray1D Class += operator----------------\n"<< endl;
    usleep(1000000);
    gameArr += tetro;
    cout << "-------------TetrisArray1D Class \"draw\" Function-------------\n"<< endl;
    usleep(1000000);
    gameArr.draw();
    cout << "-------TetrisArray1D Class \"move\" Function(1 step down)------\n"<< endl;
    usleep(1000000);
    gameArr.move(column/2-1,1);
    cout << "------------TetrisArray1D Class \"animate\" Function-----------\n"<< endl;
    usleep(1000000);
    gameArr.animate();
    cout << "-----------TetrisArray1D Class \"lastMove\" Function-----------\n"<< endl;
    usleep(1000000);
    cout << "Last Move:" << gameArr.lastMove() << endl;
    cout << "---------TetrisArray1D Class \"numberOfMoves\" Function--------\n"<< endl;
    usleep(1000000);
    cout << "NumberOfMoves : " << gameArr.numberOfMoves() << endl;       


    cout << "\e[0;31m-----------------------------------------------------------------------------------------------\e[0m\n"<< endl;    
    cout << "--------------------TetrisAdapter Class(Vector with Random Access iterator)--------------------\n"<< endl;
    cout << "\e[0;31m-----------------------------------------------------------------------------------------------\e[0m\n"<< endl;    
    cout << "----------------TetrisAdapter Class Constructor----------------\n"<< endl;
    usleep(1000000);
    TetrisAdapter<vector<vector<int>>,vector<int>> gameAdpV(row,column);
    cout << "----------------TetrisAdapter Class += operator----------------\n"<< endl;
    usleep(1000000);
    gameAdpV += tetro;
    cout << "-------------TetrisAdapter Class \"draw\" Function-------------\n"<< endl;
    usleep(1000000);
    gameAdpV.draw();
    cout << "-------TetrisAdapter Class \"move\" Function(1 step down)------\n"<< endl;
    usleep(1000000);
    gameAdpV.move(column/2-1,1);
    cout << "------------TetrisAdapter Class \"animate\" Function-----------\n"<< endl;
    usleep(1000000);
    gameAdpV.animate();
    cout << "-----------TetrisAdapter Class \"lastMove\" Function-----------\n"<< endl;
    usleep(1000000);
    cout << "Last Move:" << gameAdpV.lastMove() << endl;
    cout << "---------TetrisAdapter Class \"numberOfMoves\" Function--------\n"<< endl;
    usleep(1000000);
    cout << "NumberOfMoves : " << gameAdpV.numberOfMoves() << endl;

    cout << "\e[0;31m-----------------------------------------------------------------------------------------------\e[0m\n"<< endl;    
    cout << "--------------------TetrisAdapter Class(Deque with Random Access iterator)--------------------\n"<< endl;
    cout << "\e[0;31m-----------------------------------------------------------------------------------------------\e[0m\n"<< endl;    
    cout << "----------------TetrisAdapter Class Constructor----------------\n"<< endl;
    usleep(1000000);
    TetrisAdapter<deque<deque<int>>,deque<int>> gameAdpD(row,column);
    cout << "----------------TetrisAdapter Class += operator----------------\n"<< endl;
    usleep(1000000);
    gameAdpD += tetro;
    cout << "-------------TetrisAdapter Class \"draw\" Function-------------\n"<< endl;
    usleep(1000000);
    gameAdpD.draw();
    cout << "-------TetrisAdapter Class \"move\" Function(1 step down)------\n"<< endl;
    usleep(1000000);
    gameAdpD.move(column/2-1,1);
    cout << "------------TetrisAdapter Class \"animate\" Function-----------\n"<< endl;
    usleep(1000000);
    gameAdpD.animate();
    cout << "-----------TetrisAdapter Class \"lastMove\" Function-----------\n"<< endl;
    usleep(1000000);
    cout << "Last Move:" << gameAdpD.lastMove() << endl;
    cout << "---------TetrisAdapter Class \"numberOfMoves\" Function--------\n"<< endl;
    usleep(1000000);
    cout << "NumberOfMoves : " << gameAdpD.numberOfMoves() << endl;    


    cout << "Press enter to driver2.cpp file" << endl;
    cin.clear(); cin.ignore(INT_MAX,'\n'); 
    cin.ignore();
}