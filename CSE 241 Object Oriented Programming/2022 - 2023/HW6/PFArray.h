#ifndef PFARRAY_H
#define PFARRAY_H

#include <iostream>
#include <stdexcept>
#include <iterator>
#include <cstddef>
#include <memory>

template<class T>
class PFArray {
    private:
        int capacity;
        static int used;
        static std::shared_ptr<T[]> arr;    
    public:
        //Inner iterator class for PFArray
        class Iterator 
        {
            public:
            //Tags for declaring iterator
                using iterator_category = std::random_access_iterator_tag;
                using difference_type   = std::ptrdiff_t;
                using value_type        = T;
                using pointer           = T*;
                using reference         = T&;
                // Constructors for iterator
                Iterator() : index(0) {};
                Iterator(int indexT) : index(indexT) {};
                Iterator(const Iterator &rhs) : index(rhs.index){};
                
                //Overloaded operators
                reference operator*() const { return arr[index]; };
                pointer operator->() { return &arr[index] ;};
                Iterator& operator++();
                Iterator& operator--();
                int operator- ( const Iterator& rhs);
                Iterator operator-(int rhs);
                Iterator operator+(int rhs);
                Iterator operator+(Iterator const& rhs);
                Iterator& operator+= (const Iterator& rhs);
                Iterator& operator-= (const Iterator& rhs);
                //Friend overloaded operators
	            friend bool operator== (const Iterator& i1, const Iterator& i2)
                {
                    if (i2.index >= PFArray<T>::used)
                    {
                        return i1.index == i2.index;
                    }

                    return (*i1) == (*i2);
                }

                friend bool operator!= (const Iterator& i1, const Iterator& i2)
                {
                    if (i2.index >= PFArray<T>::used)
                    {
                        return i1.index != i2.index;
                    }

                    return (*i1) != (*i2);
                }

                friend bool operator<= (const Iterator& i1, const Iterator& i2)
                {
                    if (i2.index >= PFArray<T>::used)
                    {
                        return i1.index <= i2.index;
                    }

                    return (*i1) <= (*i2);
                }

                friend bool operator>= (const Iterator& i1, const Iterator& i2)
                {
                    if (i2.index >= PFArray<T>::used)
                    {
                        return i1.index >= i2.index;
                    }

                    return (*i1) >= (*i2);
                }

                friend bool operator< (const Iterator& i1, const Iterator& i2)
                {
                    if (i2.index >= PFArray<T>::used)
                    {
                        return i1.index < i2.index;
                    }

                    return (*i1) < (*i2);
                }

            private:
                int index = 0;
        };
        //Constructors for PFArray class
        PFArray(){};
        PFArray(int capacity); // default constructor  
        PFArray(const PFArray& other); // copy constructor
        
        //Custom functions
        int getCapacity() const;
        void print();
        void addElement(T element);

        //Overloaded operators for PFArray
        const PFArray& operator=(const PFArray& other); // assignment operator
        bool operator==(const PFArray& other) const; // equality operator   
        bool operator!=(const PFArray& right) const; // inequality operator
        T& operator[](int index); // subscript operator for non-const objects returns modifiable lvalue
        T operator[](int index) const; // subscript operator for const objects returns rvalue
        
        //Functions work with iterators
        bool empty() const;
        int size() const; // return size
        void erase(const Iterator & rmT);
        void clear();
        Iterator begin() { return Iterator(0); };
        Iterator end()   { return Iterator(used); };
        const Iterator cbegin() { return Iterator(0); };
        const Iterator cend()   { return Iterator(used); };
};

#include "PFArray.cpp"
#endif