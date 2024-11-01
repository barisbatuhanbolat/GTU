#ifndef MYCUSTOM2DVECTOR_H
#define MYCUSTOM2DVECTOR_H
namespace GAME_MC2V{
    class MyCustom2DVector{
        public:
            MyCustom2DVector();
            MyCustom2DVector(int rowT,int columnT);
            //MyCustom2DVector(const MyCustom2DVector &other);
            int * operator[](int key) const;
            void operator=(const MyCustom2DVector &other);
            int ** getArr();
            void print();
        private:
            int **arr;
            int row;
            int column;
    };
}


#endif