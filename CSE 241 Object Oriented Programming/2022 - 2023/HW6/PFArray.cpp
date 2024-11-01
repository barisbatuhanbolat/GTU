#include <iostream>
#include "PFArray.h"

//------------------------------------Inner Iterator CLass------------------------------------------------------

//Overloaded increment operator for PFArray iterator
template<class T>
typename PFArray<T>::Iterator& PFArray<T>::Iterator::operator++()
{
    index++;
    return *this;
}
//Overloaded decrement operator for PFArray iterator
template<class T>
typename PFArray<T>::Iterator& PFArray<T>::Iterator::operator--()
{
    index--;
    return *this;
}
//Overloaded arithmetic operators for PFArray iterator
//- operator for indexs
template<class T>
int PFArray<T>::Iterator::operator-( const Iterator& rhs)
{
    return index - rhs.index;
}
//- operator for Iterator arithmetic
template<class T>
typename PFArray<T>::Iterator PFArray<T>::Iterator::operator-(int rhs)
{
    return Iterator(index - rhs);
}
//+ operator for Iterator arithmetic
template<class T>
typename PFArray<T>::Iterator PFArray<T>::Iterator::operator+(int rhs)
{
    return Iterator(index + rhs);
}
//+ operator for constant Iterator arithmetic
template<class T>
typename PFArray<T>::Iterator PFArray<T>::Iterator::operator+(Iterator const& rhs)
{
    return Iterator(index + rhs.index);
}

//Overloaded assignment operators for PFArray Iterator
template<class T>
typename PFArray<T>::Iterator& PFArray<T>::Iterator::operator+= (const Iterator& rhs)
{
    index += rhs.index;
    return (*this);
}

template<class T>
typename PFArray<T>::Iterator& PFArray<T>::Iterator::operator-= (const Iterator& rhs)
{
    index -= rhs.index;
    return (*this);
}

//------------------------------------Outer PFArray CLass------------------------------------------------------
//Implementing for static variables
template<class T>
int PFArray<T>::used = 0;

template<class T>
std::shared_ptr<T[]> PFArray<T>::arr = {};

//Constructors for PFArray
//Constructors work with capacity
template<class T>
PFArray<T>::PFArray(int capacityT){
    used = 0;
    capacity = (capacityT > 0) ? capacityT : throw std::invalid_argument("PFArray size must be greater than 0");
    std::shared_ptr<T[]> arr2(new T[capacity]);
    arr = arr2;
}
//Copy constructors
template<class T>
PFArray<T>::PFArray(const PFArray& other){
    used = other.size();
    capacity = other.getCapacity();
    
    std::shared_ptr<T[]> arr2(new T[capacity]);
    arr = arr2;

    for(int i = 0;i<used;i++){
        (*this)[i] = other[i];
    }
}

//Custom functions implementation
//Get function for capacity 
template<class T>
int PFArray<T>::getCapacity() const{
    return capacity;
}
//Print function with range based for loop
template<class T>
void PFArray<T>::print(){

    for(auto& value : (*this)){
        std::cout << value << " ";
    }
    std::cout << std::endl; 
}
//Add new element to array. Array capacity will increase when its full
template<class T>
void PFArray<T>::addElement(T element){
    if(used == capacity){
        std::shared_ptr<T[]> arr2(new T[capacity*2]);
        int i = 0;
        for(auto& value : (*this)){
            arr2[i] = value;
            ++i;
        }
        arr = arr2;
        capacity *= 2;
    }
    arr[used] = element;
    ++used;
}

//Functions work with iterators
//Get function for size
template<class T>
int PFArray<T>::size() const{
    return used;
}
//Clearing all elements in array 
template<class T>
void PFArray<T>::clear(){
    used = 0;
}
//Controls emptiness of array
template<class T>
bool PFArray<T>::empty() const {
    return (used == 0);
}

//Assignment operator overload for PFArray objects
template<class T>
const PFArray<T>& PFArray<T>::operator=(const PFArray& other){
    used = other.size();
    capacity = other.getCapacity();
    std::shared_ptr<T[]> arr2(new T[capacity]);
    arr = arr2;

    for(int i = 0;i<used;i++){
        (*this)[i] = other[i];
    }
    return (*this);    
}
//PFArray Relational Operators
template<class T>
bool PFArray<T>::operator==(const PFArray& other) const{
    if(used != other.size())
        return false;
    for(int i = 0;i<used;i++){
        if((*this)[i] != other[i])
            return false;
    }
    return true;
}

template<class T>
bool PFArray<T>::operator!=(const PFArray& other) const{
    return !(*this == other);
}

// subscript operator for non-const PFArrays;
template<class T>
T& PFArray<T>::operator[](int index) {
   // check for index out-of-range error
   if (index < 0 || index >= used) {
      throw std::out_of_range("Out of range");
   }

   return arr[index]; // T& return
}

// subscript operator for const PFArrays
template<class T>
T PFArray<T>::operator[](int index) const {
   // check for index out-of-range error
   if (index < 0 || index >= used) {
      throw std::out_of_range("Out of range");
   }

   return arr[index];
}
//erase function for deleting element pointed by the given iterator
template<class T>
void PFArray<T>::erase(const Iterator & rmT){
    if(rmT== end()){
        std::string s1 = "Element can not find to delete";
        throw s1;
    }
    std::shared_ptr<T[]> arr2(new T[capacity]);
    int i = 0;
    int temp = used;
    for (auto i1 = begin();i1!=end();++i1){
        if(*i1 != *rmT){
            arr2[i] = *i1;
            i++;
        }
        else{
            --temp;
        }
    }
    used = temp;
    arr = arr2;
}