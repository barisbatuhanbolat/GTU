#ifndef ABSTRACT_TETRIS_H
#define ABSTRACT_TETRIS_H

#include "Tetromino.h"
#include <fstream>

using namespace std;

namespace HW5{
    class AbstractTetris
    {
        public:
            AbstractTetris();
            AbstractTetris(int &heightT,int & widthT);

            const int numberOfMoves() const;
            const int lastMove() const;
            //-------------------------------------------------
            virtual void readFromFile() = 0;
            virtual void writeToFile () const = 0;            
            virtual void draw() const = 0;
            virtual void operator+=(Tetromino & newT) = 0;
            virtual void animate() = 0;
            virtual bool isFilled(const int &x, const int &y) const = 0;
            virtual void move(const int &newX, const int &newY) = 0;
        protected:
            Tetromino m;
            int x,y;
            int xTotal;
            int yTotal;
            int lastM;
            int width;
            int height;
            bool isGameOver;

    };
}

#endif