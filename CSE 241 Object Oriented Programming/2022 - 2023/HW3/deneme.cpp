#include <iostream>
#include "MyCustom2DVector.h"
#include "Tetromino.h"

using namespace std;

int main(){

    MyCustom2DVector v1(4,4);
    MyCustom2DVector v2(4,4);
    Tetromino m(TType::I);
    int x  = 1;
    v1  = m.getTetro();
    for(int i = 0;i<4;i++){
        for(int j = 0;j<4;j++){
            cout << v1[i][j];
        }
        cout << endl;
    }
        cout << endl;   
            v1 = m.rotate(x);    

    for(int i = 0;i<4;i++){
        for(int j = 0;j<4;j++){
            cout << v1[i][j];
        }
        cout << endl;
    }    
            
}