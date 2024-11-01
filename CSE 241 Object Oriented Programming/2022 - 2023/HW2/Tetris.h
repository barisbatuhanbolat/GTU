#ifndef TETRIS_H
#define TETRIS_H

#include <vector>
#include "Tetromino.h"

using namespace std;
class Tetris{
    public:
        Tetris();
        Tetris(int &heightU,int &widthU);
        void add(int key);
        void fit();
        void draw();
        void animate();
        //Custom functions
        bool isFilled(const int &x, const int &y) const;
        void move(const int &newX, const int &newY);
        void save_present_board_to_cpy();
    private:
        int x,y; //Coordinates    
        bool isGameOver;
        int width;
        int height;
        Tetromino m;
        vector<vector<int>> tetro;
        vector<vector<int>> board;
        vector<vector<int>> board_cpy;
};

#endif