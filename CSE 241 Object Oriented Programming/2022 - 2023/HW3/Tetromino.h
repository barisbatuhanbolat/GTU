#include "MyCustom2DVector.h"
using namespace std;
using namespace GAME_MC2V;
namespace GAME_TTR{
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
        MyCustom2DVector rotate(const int &choice);
        void print() const;
        /*Custom get functions*/
        MyCustom2DVector getTetro () const;
        TType getShape();
    private:
        TType shape;           // Hold tetromino shape.
        MyCustom2DVector tetroMain;

    };
}

