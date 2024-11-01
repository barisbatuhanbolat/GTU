#include <vector>
#include <iostream>
#include "Tetromino.h"
Tetromino::Tetromino():shape(TType::Def),tetroMain(0){
   
}
Tetromino::Tetromino(TType blockType):tetroMain(4,vector<int>(4)){
   //3D vector that contains all the tetrominos
   vector<vector<vector<char> > > boy_max(7,vector<vector<char> >(4,vector<char>(4)));
   boy_max = 
   {
      {
   // I
         {0, 0, 0, 0},
         {0, 0, 0, 0},
         {0, 0, 0, 0},
         {1, 1, 1, 1}
      },
   // Square
      {
         {0, 0, 0, 0},
         {0, 1, 1, 0},
         {0, 1, 1, 0},
         {0, 0, 0, 0}
      },

      // L
      {
         {0, 1, 0, 0},
         {0, 1, 0, 0},
         {0, 1, 1, 0},
         {0, 0, 0, 0}
      },
      // S
      {
         {0, 0, 0, 0},
         {0, 1, 1, 0},
         {1, 1, 0, 0},
         {0, 0, 0, 0}
      },
      // N
      {
         {0, 0, 0, 0},
         {1, 1, 0, 0},
         {0, 1, 1, 0},
         {0, 0, 0, 0}
      },
      // T
      {
         {0, 0, 0, 0},
         {1, 1, 1, 0},
         {0, 1, 0, 0},
         {0, 0, 0, 0}
      },           
      // J
      {
         {0, 1, 0, 0},
         {0, 1, 0, 0},
         {1, 1, 0, 0},
         {0, 0, 0, 0}
      }
   };
   //Initialize the tetromino according to given type
   for(int i = 0;i<4;i++){
      for(int j = 0;j<4;j++){
         tetroMain[i][j] = boy_max[static_cast<int>(blockType)][i][j];
      }
   }
   shape = blockType;
}
//This functiın returns shape of the tetromino 
TType Tetromino::getShape(){
   return shape;
}
//This function prints the tetromino
void Tetromino::print() const{
   for ( const auto &row : tetroMain)
   {
      for ( const auto &x: row ){
         if(x == FILLED){
            if(shape == TType::I)
               cout <<'I';
            else if(shape == TType::O)
               cout <<'O';
            else if(shape == TType::L)
               cout <<'L';
            else if(shape == TType::S)
               cout <<'S';  
            else if(shape == TType::Z)
               cout <<'Z';
            else if(shape == TType::T)
               cout <<'T';
            else if(shape == TType::J)
               cout <<'J';                                                             
               
         }
         else{
            cout << ' ';
         }
      }
      cout << endl;
   }
}
//This function rotates the current tetromino
vector<vector<int>> Tetromino::rotate(){
    for (int x = 0; x < 2; x++) {

        for (int y = x; y < 4 - x - 1; y++) {

            int temp = tetroMain[x][y];
 
            tetroMain[x][y] = tetroMain[y][3 - x];
 
            tetroMain[y][3 - x] = tetroMain[3 - x][3 - y];
 
            tetroMain[3 - x][3 - y] = tetroMain[3 - y][x];
 
            tetroMain[3 - y][x] = temp;
        }
    }
   return tetroMain;
}
//This function returns the tetromino
vector<vector<int>> Tetromino::getTetro() const{
	return tetroMain;
}