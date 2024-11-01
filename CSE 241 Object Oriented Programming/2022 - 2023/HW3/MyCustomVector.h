#ifndef MYCUSTOMVECTOR_H
#define MYCUSTOMVECTOR_H

class MyCustomVector{
    public:
        MyCustomVector();
        MyCustomVector( int num );
        //MyCustomVector( const MyCustomVector &m );
        MyCustomVector operator =( MyCustomVector rhs );
        MyCustomVector operator =(int *rhs);
        int & operator[]( int pos );
        int * getArr();
        int size( void ) const;
    private:
        int length;
        int *arr;
};

#endif