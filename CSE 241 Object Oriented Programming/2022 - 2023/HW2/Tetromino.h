#include <vector>
using namespace std;
enum class TType
{
	I,
    O,
    L,
    S,
    Z,
	T,
    J,
    R,
    Q,
    Def
};

enum class Rotation{
    LEFT,
    RIGHT
};

enum {
    FREE = 0, FILLED = 1,BORDER = 2
};

class Tetromino
{
public:
    Tetromino();
    Tetromino(TType bloktype);
    bool canFit(const Tetromino &second_tetromino) const;
    vector<vector<int>> rotate();
    void print() const;

    /*Custom get functions*/
    vector<vector<int>> getTetro () const;
    TType getShape();
private:
    TType shape;           // Hold tetromino shape.
    vector<vector<int>> tetroMain;

};
