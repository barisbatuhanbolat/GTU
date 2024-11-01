#ifndef TETRIS_H
#define TETRIS_H

#include "Tetromino.h"

using namespace GAME_MC2V;
using namespace GAME_TTR;

namespace GAME_TTS{
    class Tetris{
        public:
            Tetris();
            Tetris(int &heightU,int &widthU);
            void draw();
            void animate();
            //Custom functions
            bool isFilled(const int &x, int y) const;
            void move(const int &newX, const int &newY);
            void save_present_board_to_cpy();
            Tetris& operator+=(Tetromino & newT);
        private:
            int x,y; //Coordinates    
            bool isGameOver;
            int width;
            int height;
            Tetromino m;
            MyCustom2DVector tetro;
            MyCustom2DVector board;
            MyCustom2DVector board_cpy;
    };
}
#endif