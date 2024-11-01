#include "AbstractTetris.h"
#include <iostream>
namespace HW5{
    

    AbstractTetris::AbstractTetris() : width(0),height(0),x(0),y(0),xTotal(0),yTotal(0){}
    AbstractTetris::AbstractTetris(int &heightT,int & widthT) : width(widthT),height(heightT),lastM(0),xTotal(0),yTotal(0){}

    const int AbstractTetris::numberOfMoves() const{
        try{
            if(xTotal + yTotal == 0)
                throw "There is no moves yet";
            else
                return (xTotal + yTotal);
        }
        catch(string e){
            cout << e << endl;
            exit(-1);
        }
	}
    const int AbstractTetris::lastMove() const{
        try{
            if(lastM == 0)
                throw "There is no move yet";
            else
                return lastM;
        }
        catch(string e){
            cout << e << endl;
            exit(-1);
        }
	}    

}