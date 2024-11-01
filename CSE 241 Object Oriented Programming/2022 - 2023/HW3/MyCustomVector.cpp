#include <iostream>
#include "MyCustomVector.h"    // "" around header means "look in current directory first"

using std::cout;
using std::endl;

// default to an array of 10 integers, fill with 0
MyCustomVector::MyCustomVector()
{
    int i;
    arr = new int[4];    // new allocates RAM from system heap, [] says allocate an array
    length = 4;
    for( i = 0; i < 4; i++ )
    {
        arr[i] = 0;       // initialize array to all 0
    }
}

// allocate array of a size requested by the client if legal, fill with 0
MyCustomVector::MyCustomVector( int num )
{
    int i;
    if( num <= 0 ) // if illegal, set to default
    {
        num = 10;
    }
    arr = new int[num];
    length = num;
    for( i = 0; i < num; i++ )
    {
        arr[i] = 0;       // initialize array to all 0
    }
}
int * MyCustomVector::getArr(){
    return arr;
}
// copy constructor - invoke deep copy asignment
/*MyCustomVector::MyCustomVector( const MyCustomVector &m )
{
   *this = m;
}*/

// destructor - needed to deallocate RAM allocated in constructors


// get value at position pos using [] indexing operator
int & MyCustomVector::operator []( int pos )
{
    return arr[pos];
}

// return size, const here means it cannot change self
int MyCustomVector::size( void ) const
{
    return length;
}

// deep copy - REQUIRED if allocated RAM is used by object!
MyCustomVector MyCustomVector::operator =( MyCustomVector rhs )
{
    int i;
    if( &rhs == this ) // assignment to self?
    {
        return *this;  // if so, don't assign, just return self
    }
    if( rhs.length != length )   // rhs not the same size as myself?
    {
        delete[] arr;    // yes, clear out my data and reallocate to match
        arr = new int[rhs.length];
        length = rhs.length;
    }
    for( i = 0; i < rhs.length; i++ )  // copy all elements
    {
        arr[i] = rhs.arr[i];
    }
    return *this;      // allow a = b = c; assignment
}
MyCustomVector MyCustomVector::operator =(int *rhs)
{
    int i;
    if( rhs == this->arr ) // assignment to self?
    {
        return *this;  // if so, don't assign, just return self
    }

    for( i = 0; i < 4; i++ )  // copy all elements
    {
        arr[i] = rhs[i];
    }
    return *this;      // allow a = b = c; assignment
}
