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
    ~Tetromino();
    Tetromino(TType bloktype);
    vector<vector<int>> rotate(const int &choice);
    void print() const;
    void operator=(Tetromino &newT);
    /*Custom get functions*/
    vector<vector<int>> getTetro () const;
    TType getShape();
private:
    TType shape;           // Hold tetromino shape.
    vector<vector<int>> tetroMain;

};
