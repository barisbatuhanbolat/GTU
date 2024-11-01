#include <iostream>
#include <vector>
#include "Tetromino.h"
using namespace std;

int main(){ 
	vector<Tetromino> Tetris;
	int tetroNumber;
	char key;
	//Getting inputs from users and checking their validity
	cout << "How many tetrominos?" << endl;
	cin >> tetroNumber;
	while(tetroNumber <0){
		cout << "Wrong Input: ";
		cin >> tetroNumber;
	}
	cout << "What are the types? " << endl;
	//Creating Tetromino object and put it in Tetris vector
	for(int i=0;i<tetroNumber;i++){
		cin >> key;
		while(key != 'I' && key != 'O'&& key != 'T'&& key != 'J'&& key != 'L'&& key != 'S'&& key != 'Z'){
			cout << "Wrong Input: ";
			cin >> key;
		}
		Tetromino newTetro(static_cast<Shapes>(key));
		Tetris.push_back(newTetro);
	}
	//Printing user selected Tetrominos  
	cout << "Your Tetrominos " << endl;
	for(Tetromino i : Tetris)
		i.print();
	//Arranging all Tetrominos for the best fit  

	cout << "Best Fitting" << endl;
	for(int i = 0;i<tetroNumber;i++){
		Tetris[i].canFit(Tetris[i+1],'r');
	}
	//Printing arranged tetrominos(I couldn't solve how to print them horizontaly)
	for(Tetromino i : Tetris)
		i.print();
}