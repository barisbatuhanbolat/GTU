#include <iostream>
#include "MyCustom2DVector.h"  

namespace GAME_MC2V{

    MyCustom2DVector::MyCustom2DVector():row(0),column(0),arr(nullptr){
    }
    MyCustom2DVector::MyCustom2DVector(int rowT,int columnT)
    {
        row = rowT;
        column = columnT;

        arr = new int*[row];
        for(int i = 0;i<row;i++)
            arr[i] = new int[column];

    }
    int * MyCustom2DVector::operator[] (int key) const
    {
        return arr[key];

    }
    int ** MyCustom2DVector::getArr(){
        return arr;
    }
    void MyCustom2DVector::operator=(const MyCustom2DVector &other)
    {
        
        if(&other == this)
            return ;
        if(other.row != row || other.column != column)
        {
            delete[] arr;
            arr = new int*[row];
            row = other.row;
            column = other.column;
            for(int i = 0;i<row;i++)
                arr[i] = new int[column];
        }
        for(int i = 0; i < row; i++ ){
            for(int j = 0;j<column;j++){
                arr[i][j] = other.arr[i][j];
            }
        }
        return;    
    }
    void MyCustom2DVector::print(){
        for(int i = 0;i<row;i++){
            for(int j = 0;j<column;j++){
                std::cout << arr[i][j];
            }
            std::cout << std::endl;
        }
    }
}