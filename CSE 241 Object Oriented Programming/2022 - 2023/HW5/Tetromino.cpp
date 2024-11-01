#include <vector>
#include <iostream>
#include "Tetromino.h"
void Tetromino::operator=(Tetromino &newT){
   tetroMain.resize(4,vector<int>(4));
   shape = newT.shape;

   for(int i = 0;i<newT.tetroMain.size();i++){
      for(int j = 0;j<newT.tetroMain[i].size();j++){
            tetroMain[i][j] = newT.tetroMain[i][j];
      }
   }
}
Tetromino::~Tetromino(){
}
Tetromino::Tetromino():shape(TType::Def){
}
Tetromino::Tetromino(TType blockType){
      vector<vector<int>> tmp(4,vector<int>(4));
      //tetroMain.resize(4,vector<int>(4));
      for (int i = 0; i < 4; i++) {
         for (int j = 0; j < 4; j++) {
               tmp[i][j] = 0;
         }
      }
      tetroMain = tmp;
      if(blockType  == TType::I){
         tetroMain[3][0] = 1;
         tetroMain[3][1] = 1;
         tetroMain[3][2] = 1;
         tetroMain[3][3] = 1;
      }

      if(blockType  == TType::O){
         tetroMain[1][1] = 1;
         tetroMain[1][2] = 1;
         tetroMain[2][1] = 1;
         tetroMain[2][2] = 1;
      }
      if(blockType  == TType::L){
         tetroMain[0][1] = 1;
         tetroMain[1][1] = 1;
         tetroMain[2][1] = 1;
         tetroMain[2][2] = 1;
      }
      if(blockType  == TType::S){
         tetroMain[1][1] = 1;
         tetroMain[1][2] = 1;
         tetroMain[2][0] = 1;
         tetroMain[2][1] = 1;
      }
      if(blockType  == TType::Z){
         tetroMain[1][0] = 1;
         tetroMain[1][1] = 1;
         tetroMain[2][1] = 1;
         tetroMain[2][2] = 1;
      }

      if(blockType  == TType::T){
         tetroMain[1][0] = 1;
         tetroMain[1][1] = 1;
         tetroMain[1][2] = 1;
         tetroMain[2][1] = 1;
      }                                 
      if(blockType  == TType::J){
         tetroMain[0][1] = 1;
         tetroMain[1][1] = 1;
         tetroMain[2][1] = 1;
         tetroMain[2][0] = 1;
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
   vector<vector<int>> Tetromino::rotate(const int &choice){
      if(choice == 1){
         for (int x = 0; x < 2; x++) {
            for (int y = x; y < 4 - x - 1; y++) {

               int temp = tetroMain[x][y];

               tetroMain[x][y] = tetroMain[y][3 - x];

               tetroMain[y][3 - x] = tetroMain[3 - x][3 - y];

               tetroMain[3 - x][3 - y] = tetroMain[3 - y][x];

               tetroMain[3 - y][x] = temp;
            }
         }
      }
      else{
         int i = 0;
         while(i < 3){
            for (int x = 0; x < 2; x++) {
               for (int y = x; y < 4 - x - 1; y++) {

                  int temp = tetroMain[x][y];

                  tetroMain[x][y] = tetroMain[y][3 - x];

                  tetroMain[y][3 - x] = tetroMain[3 - x][3 - y];

                  tetroMain[3 - x][3 - y] = tetroMain[3 - y][x];

                  tetroMain[3 - y][x] = temp;
               }
            }
            i++;
         }
      }
      return tetroMain;
   }
//This function returns the tetromino
vector<vector<int>> Tetromino::getTetro() const{
	return tetroMain;
}