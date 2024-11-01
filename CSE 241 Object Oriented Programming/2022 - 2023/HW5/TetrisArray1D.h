#ifndef TETRISARRAY1D_H
#define TETRISARRAY1D_H
#include "AbstractTetris.h"
namespace HW5{
    
    class TetrisArray1D : public AbstractTetris{
        public:
            TetrisArray1D(){};
            TetrisArray1D(int heightT,int  widthT);
            ~TetrisArray1D();
            //-------------------------------------------------
            virtual void readFromFile() override;
            virtual void writeToFile() const override;
            virtual void draw() const override;
            virtual void operator+=(Tetromino & newT) override;
            virtual void animate() override;
            virtual bool isFilled(const int &newX, const int &newY) const override;
            virtual void move(const int &newX, const int &newY) override;
        private:
            int*board;
            int*board_cpy;
            int*tetro;
    };
}
#endif