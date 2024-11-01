#ifndef TETRISVECTOR_H
#define TETRISVECTOR_H

#include "AbstractTetris.h"
#include <vector>


namespace HW5{
    class TetrisVector : public AbstractTetris
    {
        public:
            TetrisVector(){};
            TetrisVector(int heightT,int  widthT);
            //-------------------------------------------------
            virtual ~TetrisVector() =  default;            
            virtual void readFromFile() override;
            virtual void writeToFile() const override;
            virtual void draw() const override;
            virtual void operator+=(Tetromino & newT) override;
            virtual void animate() override;
            virtual bool isFilled(const int &newX, const int &newY) const override;
            virtual void move(const int &newX, const int &newY) override;
        private:
            vector<vector<int>> board;
            vector<vector<int>> board_cpy;
            vector<vector<int>> tetro;
    };
}

#endif