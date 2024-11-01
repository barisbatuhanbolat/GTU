#include <iostream>
#include <vector>
#include "Tetromino.h"
using namespace std;
Tetromino::Tetromino():rotC(0),shape(Shapes::X){ //Default constuctor
} 
Tetromino::Tetromino(Shapes choice):rotC(0),vec(4){ //This constructor function creates objects with their variables
	if(choice== Shapes::I){
		vec[0] = {
				{'I','I','I','I'}
		};
		vec[1] = {
				{'I'},
				{'I'},
				{'I'},
				{'I'}
		};
		vec[2]  = {
				{'I','I','I','I'}
		};
		vec[3]  = {
				{'I'},
				{'I'},
				{'I'},
				{'I'}
		};		

	}
	else if(choice== Shapes::O){	
		vec[0]  = {
				{'0','O'},
				{'0','0'}
		};
		vec[1]= {
				{'0','O'},
				{'0','0'}
		};
		vec[2] = {
				{'0','O'},
				{'0','0'}
		};
		vec[3] = {
				{'0','O'},
				{'0','0'}
		};								
	}
	else if(choice== Shapes::T){	
		vec[0] = {
				{'T','T','T'},
				{' ','T'}
		};
		vec[1]= {
				{' ','T'},
				{'T','T'},
				{' ','T'}
		};
		vec[2] = {
				{' ','T'},
				{'T','T','T'}
		};
		vec[3] = {
				{'T'},
				{'T','T'},
				{'T'}
		};						
	}
	else if(choice== Shapes::J){	
		vec[0] = {
				{' ','J'},
				{' ','J'},
				{'J','J'}
		};
		vec[1]= {
				{'J'},
				{'J','J','J'}
		};
		vec[2]= {
				{'J','J'},
				{'J'},
				{'J'}
		};
		vec[3]= {
				{'J','J','J'},
				{' ',' ','J'}
		};						
	}
	else if(choice== Shapes::L){	
		vec[0] = {
				{'L'},
				{'L'},
				{'L','L'}
		};
		vec[1]= {
				{'L','L','L'},
				{'L'}
		};
		vec[2] = {
				{'L','L'},
				{' ','L'},
				{' ','L'}
		};
		vec[3] = {
				{' ',' ','L'},
				{'L','L','L'}
		};			
	}			
	else if(choice== Shapes::S){	
		vec[0] = {
				{' ','S','S'},
				{'S','S'}
		};
		vec[1]= {
				{'S'},
				{'S','S'},
				{' ','S'}
		};
		vec[2] = {
				{' ','S','S'},
				{'S','S'}
		};
		vec[3] = {
				{'S'},
				{'S','S'},
				{' ','S'}
		};
	}
	else if(choice== Shapes::Z){	
		vec[0] = {
				{'Z','Z'},
				{' ','Z','Z'}
		};
		vec[1]= {
				{' ','Z'},
				{'z','Z'},
				{'z'}
		};
		vec[2] = {
				{'Z','Z'},
				{' ','Z','Z'}
		};
		vec[3] = {
				{' ','Z'},
				{'z','Z'},
				{'z'}
		};							
	}
	shape = choice;
	tetroMain = vec[0];

}

//This three get functions helps us to use one objects variables in another 
vector<vector<char> > Tetromino::getVec(){
	return tetroMain;
}
Shapes Tetromino::getShape(){
	return shape;
}
int Tetromino::getRot(){ 
	return rotC;
}
bool Tetromino::canFit(Tetromino &other,char relPos){ //This long function checks the compatibility of a tetromino with respect 
	if(shape == Shapes::I){								//to the tetromino next to it and makes the necessary rotations.
		if(other.getShape() == Shapes::I){
			while(true){
				if((rotC == 0 && other.getRot() == 0) || (rotC == 0 && other.getRot() == 2) || 
				(rotC == 1 && other.getRot() == 1) || (rotC == 1 && other.getRot() == 3) ||
				(rotC == 2 && other.getRot() == 2) || (rotC == 2 && other.getRot() == 0) ||
				(rotC == 3 && other.getRot() == 3) || (rotC == 3 && other.getRot() == 1) ){
					return true;
				}
				else{
					other.rotate(relPos);
				}
			}
		}
		else if(other.getShape() == Shapes::O){
			while(true){
				if((rotC == 1 && other.getRot() == 0) || (rotC == 1 && other.getRot() == 1)||
				(rotC == 1 && other.getRot() == 2)||(rotC == 1 && other.getRot() == 3)||
				(rotC == 3 && other.getRot() == 0) || (rotC == 3 && other.getRot() == 1)||
				(rotC == 3 && other.getRot() == 2)||(rotC == 3 && other.getRot() == 3)){
					return true;				
				}
				else{
					rotate(relPos);
				}
			}
		}
		else if(other.getShape() == Shapes::T){
			while(true){
				if((rotC == 0 && other.getRot() == 0) || (rotC == 0 && other.getRot() == 1)||
				(rotC == 0 && other.getRot() == 2) || (rotC == 2 && other.getRot() == 0) ||
				(rotC == 2 && other.getRot() == 1) || (rotC == 2 && other.getRot() == 2) ||
				(rotC == 1 && other.getRot() == 3) || (rotC == 3 && other.getRot() == 3)){
					return true;
				}
				else{
					other.rotate(relPos);
				}	
			}
		}
		else if(other.getShape() == Shapes::J){
			while(true){
				if((rotC == 0 && other.getRot() == 0) || (rotC == 0 && other.getRot() == 3)||
				(rotC == 2 && other.getRot() == 0) || (rotC == 2 && other.getRot() == 3) ||
				(rotC == 1 && other.getRot() == 1) || (rotC == 1 && other.getRot() == 2) ||
				(rotC == 3 && other.getRot() == 1) || (rotC == 3 && other.getRot() == 2)){
					return true;
				}
				else{
					other.rotate(relPos);
				}							
			}
		}
		else if(other.getShape() == Shapes::L){
			while (true){
				if((rotC == 0 && other.getRot() == 3) || (rotC == 2 && other.getRot() == 3) ||
				(rotC == 1 && other.getRot() == 0) || (rotC == 1 && other.getRot() == 1)){
					return true;
				}
				else{
					other.rotate(relPos);
				}					
			}
		}
		else if(other.getShape() == Shapes::S){
			while(true){
				if((rotC == 0 && other.getRot() == 1) || (rotC == 0 && other.getRot() == 3)||
				(rotC == 2 && other.getRot() == 1) || (rotC == 2 && other.getRot() == 3) ||
				(rotC == 1 && other.getRot() == 0) || (rotC == 1 && other.getRot() == 2) ||
				(rotC == 3 && other.getRot() == 0) || (rotC == 3 && other.getRot() == 2)){
					return true;				
				}
				else{
					other.rotate(relPos);
				}				
			}
		}
		else if(other.getShape() == Shapes::Z){
			while(true){
				if((rotC == 0 && other.getRot() == 0) || (rotC == 0 && other.getRot() == 2)||
				(rotC == 2 && other.getRot() == 0) || (rotC == 2 && other.getRot() == 2) ||
				(rotC == 1 && other.getRot() == 1) || (rotC == 1 && other.getRot() == 3) ||
				(rotC == 3 && other.getRot() == 1) || (rotC == 3 && other.getRot() == 3)){
					return true;				
				}
				else{
					other.rotate(relPos);
				}
			}
		}
	}
	else if(shape == Shapes::O){
		if(other.getShape() == Shapes::I){
			while(true){
				if((rotC == 0 && other.getRot() == 0) || (rotC == 0 && other.getRot() == 2) || 
				(rotC == 0 && other.getRot() == 1) || (rotC == 0 && other.getRot() == 3)){
					return true;
				}
				else{
					other.rotate(relPos);
				}
			}
		}
		else if(other.getShape() == Shapes::O){
			while(true){
				if((rotC == 0 && other.getRot() == 0)){
					return true;				
				}
				else{
					rotate(relPos);
				}
			}
		}
		else if(other.getShape() == Shapes::T){
			while(true){
				if((rotC == 0 && other.getRot() == 3)){
					return true;
				}
				else{
					other.rotate(relPos);
				}	
			}
		}
		else if(other.getShape() == Shapes::J){
			while(true){
				if((rotC == 0 && other.getRot() == 1) || (rotC == 0 && other.getRot() == 2)){
					return true;
				}
				else{
					other.rotate(relPos);
				}							
			}
		}
		else if(other.getShape() == Shapes::L){
			while (true){
				if((rotC == 0 && other.getRot() == 0) || (rotC == 0 && other.getRot() == 1) ||
				(rotC == 0 && other.getRot() == 2)){
					return true;
				}
				else{
					other.rotate(relPos);
				}					
			}
		}
		else if(other.getShape() == Shapes::S){
			while(true){
				if((rotC == 0 && other.getRot() == 0) || (rotC == 0 && other.getRot() == 2)){
					return true;				
				}
				else{
					other.rotate(relPos);
				}				
			}
		}
		else if(other.getShape() == Shapes::Z){
			while(true){
				if((rotC == 0 && other.getRot() == 1) || (rotC == 0 && other.getRot() == 3)){
					return true;				
				}
				else{
					other.rotate(relPos);
				}
			}
		}
	}	
	else if(shape == Shapes::T){
		if(other.getShape() == Shapes::I){
			while(true){
				if((rotC == 0 && other.getRot() == 0) || (rotC == 0 && other.getRot() == 2)||
				(rotC == 1 && other.getRot() == 1) || (rotC == 1 && other.getRot() == 3)||
				(rotC == 2 && other.getRot() == 0) || (rotC == 2 && other.getRot() == 2)||
				(rotC == 3 && other.getRot() == 0) || (rotC == 3 && other.getRot() == 2)){
					return true;
				}
				else{
					other.rotate(relPos);
				}
			}
		}
		else if(other.getShape() == Shapes::O){
			while(true){
				if((rotC == 0 && other.getRot() == 0)||(rotC == 1 && other.getRot() == 0) ||
				(rotC == 2 && other.getRot() == 0)||(rotC == 3 && other.getRot() == 0)){
					return true;				
				}
				else{
					rotate(relPos);
				}
			}
		}
		else if(other.getShape() == Shapes::T){
			while(true){
				if((rotC == 0 && other.getRot() == 2)||(rotC == 1 && other.getRot() == 3)||
				(rotC == 2 && other.getRot() == 0)||(rotC == 2 && other.getRot() == 1)||
				(rotC == 3 && other.getRot() == 2)){
					return true;
				}
				else{
					other.rotate(relPos);
				}	
			}
		}
		else if(other.getShape() == Shapes::J){
			while(true){
				if((rotC == 0 && other.getRot() == 1) ||(rotC == 1 && other.getRot() == 1)||
				(rotC == 1 && other.getRot() == 2)||(rotC == 2 && other.getRot() == 0)||
				(rotC == 3 && other.getRot() == 0)){
					return true;
				}
				else{
					other.rotate(relPos);
				}							
			}
		}
		else if(other.getShape() == Shapes::L){
			while (true){
				if((rotC == 0 && other.getRot() == 3)||(rotC == 1 && other.getRot() == 0)||
				(rotC == 1 && other.getRot() == 1)||(rotC == 2 && other.getRot() == 3)||
				(rotC == 3 && other.getRot() == 3)){
					return true;
				}
				else{
					other.rotate(relPos);
				}					
			}
		}
		else if(other.getShape() == Shapes::S){
			while(true){
				if((rotC == 0 && other.getRot() == 0) || (rotC == 0 && other.getRot() == 2)||
				(rotC == 1 && other.getRot() == 0) || (rotC == 1 && other.getRot() == 2)||
				(rotC == 2 && other.getRot() == 1) || (rotC == 2 && other.getRot() == 3)||
				(rotC == 3 && other.getRot() == 0) || (rotC == 3 && other.getRot() == 2)){
					return true;				
				}
				else{
					other.rotate(relPos);
				}				
			}
		}
		else if(other.getShape() == Shapes::Z){
			while(true){
				if((rotC == 0 && other.getRot() == 0) || (rotC == 0 && other.getRot() == 2)||
				(rotC == 1 && other.getRot() == 1) || (rotC == 1 && other.getRot() == 3)||
				(rotC == 2 && other.getRot() == 0) || (rotC == 2 && other.getRot() == 2)||
				(rotC == 3 && other.getRot() == 1) || (rotC == 3 && other.getRot() == 3)){
					return true;				
				}
				else{
					other.rotate(relPos);
				}
			}
		}
	}
	else if(shape == Shapes::J){
		if(other.getShape() == Shapes::I){
			while(true){
				if((rotC == 0 && other.getRot() == 1) || (rotC == 0 && other.getRot() == 3) || 
				(rotC == 1 && other.getRot() == 0) || (rotC == 1 && other.getRot() == 2) ||
				(rotC == 2 && other.getRot() == 0) || (rotC == 2 && other.getRot() == 2) ||
				(rotC == 3 && other.getRot() == 3) || (rotC == 3 && other.getRot() == 1) ){
					return true;
				}
				else{
					other.rotate(relPos);
				}
			}
		}
		else if(other.getShape() == Shapes::O){
			while(true){
				if((rotC == 0 && other.getRot() == 0) || (rotC == 1 && other.getRot() == 0)||
				(rotC == 2 && other.getRot() == 0)||(rotC == 3 && other.getRot() == 0)){
					return true;				
				}
				else{
					rotate(relPos);
				}
			}
		}
		else if(other.getShape() == Shapes::T){
			while(true){
				if((rotC == 0 && other.getRot() == 3) || (rotC == 1 && other.getRot() == 0)||
				(rotC == 1 && other.getRot() == 1) || (rotC == 2 && other.getRot() == 0) ||
				(rotC == 2 && other.getRot() == 1) || (rotC == 2 && other.getRot() == 2) ||
				(rotC == 3 && other.getRot() == 3) ){
					return true;
				}
				else{
					other.rotate(relPos);
				}	
			}
		}
		else if(other.getShape() == Shapes::J){
			while(true){
				if((rotC == 0 && other.getRot() == 1) || (rotC == 0 && other.getRot() == 3)||
				(rotC == 1 && other.getRot() == 3) || (rotC == 2 && other.getRot() == 1) ||
				(rotC == 3 && other.getRot() == 1) || (rotC == 3 && other.getRot() == 2)){
					return true;
				}
				else{
					other.rotate(relPos);
				}							
			}
		}
		else if(other.getShape() == Shapes::L){
			while (true){
				if((rotC == 0 && other.getRot() == 0) || (rotC == 1 && other.getRot() == 3) ||
				(rotC == 2 && other.getRot() == 1) || (rotC == 3 && other.getRot() == 0)||
				(rotC == 0 && other.getRot() == 1)){
					return true;
				}
				else{
					other.rotate(relPos);
				}					
			}
		}
		else if(other.getShape() == Shapes::S){
			while(true){
				if((rotC == 0 && other.getRot() == 1) || (rotC == 0 && other.getRot() == 3)||
				(rotC == 1 && other.getRot() == 1) || (rotC == 1 && other.getRot() == 3) ||
				(rotC == 2 && other.getRot() == 0) || (rotC == 2 && other.getRot() == 2) ||
				(rotC == 3 && other.getRot() == 1) || (rotC == 3 && other.getRot() == 3)){
					return true;				
				}
				else{
					other.rotate(relPos);
				}				
			}
		}
		else if(other.getShape() == Shapes::Z){
			while(true){
				if((rotC == 0 && other.getRot() == 1) || (rotC == 0 && other.getRot() == 3)||
				(rotC == 1 && other.getRot() == 0) || (rotC == 1 && other.getRot() == 2) ||
				(rotC == 2 && other.getRot() == 1) || (rotC == 2 && other.getRot() == 3) ||
				(rotC == 3 && other.getRot() == 1) || (rotC == 3 && other.getRot() == 3)){
					return true;				
				}
				else{
					other.rotate(relPos);
				}
			}
		}
	}
	else if(shape == Shapes::L){
		if(other.getShape() == Shapes::I){
			while(true){
				if((rotC == 0 && other.getRot() == 0) || (rotC == 0 && other.getRot() == 2) || 
				(rotC == 3 && other.getRot() == 1) || (rotC == 3 && other.getRot() == 3) ||
				(rotC == 1 && other.getRot() == 0) || (rotC == 1 && other.getRot() == 2)){
					return true;
				}
				else{
					other.rotate(relPos);
				}
			}
		}
		else if(other.getShape() == Shapes::O){
			while(true){
				if((rotC == 0 && other.getRot() == 0) || (rotC == 1 && other.getRot() == 0)||
				(rotC == 2 && other.getRot() == 0)||(rotC == 3 && other.getRot() == 0)){
					return true;				
				}
				else{
					rotate(relPos);
				}
			}
		}
		else if(other.getShape() == Shapes::T){
			while(true){
				if((rotC == 0 && other.getRot() == 0) || (rotC == 0 && other.getRot() == 1)||
				(rotC == 3 && other.getRot() == 3) || (rotC == 2 && other.getRot() == 3) ||
				(rotC == 1 && other.getRot() == 2) ){
					return true;
				}
				else{
					other.rotate(relPos);
				}	
			}
		}
		else if(other.getShape() == Shapes::J){
			while(true){
				if((rotC == 0 && other.getRot() == 0) || (rotC == 3 && other.getRot() == 1)||
				(rotC == 3 && other.getRot() == 2) || (rotC == 2 && other.getRot() == 2) ||
				(rotC == 1 && other.getRot() == 1)){
					return true;
				}
				else{
					other.rotate(relPos);
				}							
			}
		}
		else if(other.getShape() == Shapes::L){
			while (true){
				if((rotC == 0 && other.getRot() == 2) || (rotC == 3 && other.getRot() == 0) ||
				(rotC == 3 && other.getRot() == 1) || (rotC == 3 && other.getRot() == 2)||
				(rotC == 2 && other.getRot() == 0) || (rotC == 2 && other.getRot() == 1)||
				(rotC == 1 && other.getRot() == 3)){
					return true;
				}
				else{
					other.rotate(relPos);
				}					
			}
		}
		else if(other.getShape() == Shapes::S){
			while(true){
				if((rotC == 0 && other.getRot() == 1) || (rotC == 0 && other.getRot() == 3)||
				(rotC == 3 && other.getRot() == 0) || (rotC == 3 && other.getRot() == 2) ||
				(rotC == 2 && other.getRot() == 0) || (rotC == 2 && other.getRot() == 2) ||
				(rotC == 1 && other.getRot() == 0) || (rotC == 1 && other.getRot() == 2)){
					return true;				
				}
				else{
					other.rotate(relPos);
				}				
			}
		}
		else if(other.getShape() == Shapes::Z){
			while(true){
				if((rotC == 0 && other.getRot() == 0) || (rotC == 0 && other.getRot() == 2)||
				(rotC == 3 && other.getRot() == 1) || (rotC == 3 && other.getRot() == 3) ||
				(rotC == 2 && other.getRot() == 1) || (rotC == 2 && other.getRot() == 3) ||
				(rotC == 1 && other.getRot() == 1) || (rotC == 1 && other.getRot() == 3)){
					return true;				
				}
				else{
					other.rotate(relPos);
				}
			}
		}
	}
	else if(shape == Shapes::S){
		if(other.getShape() == Shapes::I){
			while(true){
				if((rotC == 0 && other.getRot() == 0) || (rotC == 0 && other.getRot() == 2) || 
				(rotC == 2 && other.getRot() == 0) || (rotC == 2 && other.getRot() == 2) ||
				(rotC == 1 && other.getRot() == 1) || (rotC == 1 && other.getRot() == 3) ||
				(rotC == 3 && other.getRot() == 1) || (rotC == 3 && other.getRot() == 3)){
					return true;
				}
				else{
					other.rotate(relPos);
				}
			}
		}
		else if(other.getShape() == Shapes::O){
			while(true){
				if((rotC == 0 && other.getRot() == 0) || (rotC == 1 && other.getRot() == 0)||
				(rotC == 2 && other.getRot() == 0)||(rotC == 3 && other.getRot() == 0)){
					return true;				
				}
				else{
					rotate(relPos);
				}
			}
		}
		else if(other.getShape() == Shapes::T){
			while(true){
				if((rotC == 0 && other.getRot() == 2) || (rotC == 2 && other.getRot() == 2)||
				(rotC == 1 && other.getRot() == 3) || (rotC == 3 && other.getRot() == 3)){
					return true;
				}
				else{
					other.rotate(relPos);
				}	
			}
		}
		else if(other.getShape() == Shapes::J){
			while(true){
				if((rotC == 0 && other.getRot() == 0) || (rotC == 2 && other.getRot() == 0)||
				(rotC == 1 && other.getRot() == 1) || (rotC == 3 && other.getRot() == 1) ||
				(rotC == 1 && other.getRot() == 2) || (rotC == 3 && other.getRot() == 2)){
					return true;
				}
				else{
					other.rotate(relPos);
				}							
			}
		}
		else if(other.getShape() == Shapes::L){
			while (true){
				if((rotC == 0 && other.getRot() == 2) || (rotC == 2 && other.getRot() == 2) ||
				(rotC == 1 && other.getRot() == 2) || (rotC == 3 && other.getRot() == 2)){
					return true;
				}
				else{
					other.rotate(relPos);
				}					
			}
		}
		else if(other.getShape() == Shapes::S){
			while(true){
				if((rotC == 0 && other.getRot() == 0) || (rotC == 2 && other.getRot() == 2)||
				(rotC == 0 && other.getRot() == 2) || (rotC == 3 && other.getRot() == 2) ||
				(rotC == 2 && other.getRot() == 0) || (rotC == 2 && other.getRot() == 0) ||
				(rotC == 1 && other.getRot() == 0) || (rotC == 1 && other.getRot() == 2) ||
				(rotC == 3 && other.getRot() == 0) || (rotC == 3 && other.getRot() == 2)){
					return true;				
				}
				else{
					other.rotate(relPos);
				}				
			}
		}
		else if(other.getShape() == Shapes::Z){
			while(true){
				if((rotC == 0 && other.getRot() == 1) || (rotC == 0 && other.getRot() == 3)||
				(rotC == 2 && other.getRot() == 1) || (rotC == 2 && other.getRot() == 3) ||
				(rotC == 1 && other.getRot() == 1) || (rotC == 3 && other.getRot() == 1) ||
				(rotC == 1 && other.getRot() == 3) || (rotC == 3 && other.getRot() == 3)){
					return true;				
				}
				else{
					other.rotate(relPos);
				}
			}
		}
	}
	else if(shape == Shapes::Z){
		if(other.getShape() == Shapes::I){
			while(true){
				if((rotC == 0 && other.getRot() == 0) || (rotC == 0 && other.getRot() == 2) || 
				(rotC == 2 && other.getRot() == 0) || (rotC == 2 && other.getRot() == 2) ||
				(rotC == 1 && other.getRot() == 0) || (rotC == 1 && other.getRot() == 2) ||
				(rotC == 3 && other.getRot() == 0) || (rotC == 3 && other.getRot() == 2)){
					return true;
				}
				else{
					other.rotate(relPos);
				}
			}
		}
		else if(other.getShape() == Shapes::O){
			while(true){
				if((rotC == 0 && other.getRot() == 0) || (rotC == 1 && other.getRot() == 0)||
				(rotC == 2 && other.getRot() == 0)||(rotC == 3 && other.getRot() == 0)){
					return true;				
				}
				else{
					rotate(relPos);
				}
			}
		}
		else if(other.getShape() == Shapes::T){
			while(true){
				if((rotC == 0 && other.getRot() == 1) || (rotC == 0 && other.getRot() == 2)||
				(rotC == 2 && other.getRot() == 1) || (rotC == 2 && other.getRot() == 2)||
				(rotC == 1 && other.getRot() == 0) || (rotC == 1 && other.getRot() == 2)||
				(rotC == 3 && other.getRot() == 0) || (rotC == 3 && other.getRot() == 2)){
					return true;
				}
				else{
					other.rotate(relPos);
				}	
			}
		}
		else if(other.getShape() == Shapes::J){
			while(true){
				if((rotC == 0 && other.getRot() == 0) || (rotC == 2 && other.getRot() == 0)||
				(rotC == 2 && other.getRot() == 1) || (rotC == 0 && other.getRot() == 1) ||
				(rotC == 1 && other.getRot() == 0) || (rotC == 3 && other.getRot() == 0)){
					return true;
				}
				else{
					other.rotate(relPos);
				}							
			}
		}
		else if(other.getShape() == Shapes::L){
			while (true){
				if((rotC == 0 && other.getRot() == 2) || (rotC == 2 && other.getRot() == 2) ||
				(rotC == 1 && other.getRot() == 3) || (rotC == 3 && other.getRot() == 3)){
					return true;
				}
				else{
					other.rotate(relPos);
				}					
			}
		}
		else if(other.getShape() == Shapes::S){
			while(true){
				if((rotC == 0 && other.getRot() == 1) || (rotC == 0 && other.getRot() ==3)||
				(rotC == 2 && other.getRot() == 1) || (rotC == 2 && other.getRot() == 3) ||
				(rotC == 1 && other.getRot() == 0) || (rotC == 1 && other.getRot() == 2) ||
				(rotC == 3 && other.getRot() == 0) || (rotC == 3 && other.getRot() == 2)){
					return true;				
				}
				else{
					other.rotate(relPos);
				}				
			}
		}
		else if(other.getShape() == Shapes::Z){
			while(true){
				if((rotC == 0 && other.getRot() == 0) || (rotC == 0 && other.getRot() == 2)||
				(rotC == 2 && other.getRot() == 0) || (rotC == 2 && other.getRot() == 0) ||
				(rotC == 1 && other.getRot() == 1) || (rotC == 1 && other.getRot() == 3) ||
				(rotC == 3 && other.getRot() == 1) || (rotC == 3 && other.getRot() == 3)){
					return true;				
				}
				else{
					other.rotate(relPos);
				}
			}
		}
	}
	return false;
}


void Tetromino::print(){  // This function prints the current vector
    for (int i = 0; i < tetroMain.size(); i++) {
        for (auto it = tetroMain[i].begin();it != tetroMain[i].end(); it++)
            cout << *it << " ";
        cout << endl;
    }
	cout << endl;
}
void Tetromino::rotate(char rotation){  //This function rotates the specified direction according to thir current positions
	if(shape == Shapes::O){
		return;
	}
	if(rotation == 'r'){
		if(rotC<=2){
			tetroMain = vec[rotC+1];
			rotC++;
		}
		else{
			tetroMain = vec[0];
			rotC=0;			
		}
	}
	else if(rotation == 'l'){
		if(rotC>0){
			tetroMain = vec[rotC-1];
			rotC--;
		}
		else{
			tetroMain = vec[3];
			rotC=3;		
		}
	}
}