#ifndef A2DD_H
#define A2DD_H
//Creating strong enum class
using namespace std;
enum class Shapes{I='I',O='O',T='T',J='J',L='L',S='S',Z='Z',X='X'};
//Creating Tetromino class
class Tetromino{
	public:
		Tetromino(); // Default Constractor
        Tetromino(Shapes choice);
		void print();
		//Get Functions
		Shapes getShape();
		int getRot();
		vector<vector<char> > getVec();
		//Functions for the best fit
		void rotate(char rotation);
		bool canFit(Tetromino &other,char relPos);
	private:
		Shapes shape;
		int rotC;
		//Creating 3d vector that contains all variables of Tetromino
		vector<vector<vector<char> > > vec;
		//Creating the 2D vector that contains main Tetromino vector
  		vector<vector<char> > tetroMain;
};

#endif