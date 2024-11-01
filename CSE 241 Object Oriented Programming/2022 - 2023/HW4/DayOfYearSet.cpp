#include <iostream>
#include <iterator>
#include "DayOfYearSet.h"
using namespace std;

namespace GTUHW4
{
    //Copy Constructor of DayOfYear object
    DayOfYearSet::DayOfYear::DayOfYear(const DayOfYear &other)
    {
        day = other.day;
        month = other.month;
    }
    //Constructor of DayOfYear object
    DayOfYearSet::DayOfYear::DayOfYear(int monthT, int dayT)
    {
        if(1 <= monthT && monthT <= 12){
            month = monthT;
            if(1 <= dayT && dayT <= checkDay()){
                day = dayT;
            }
            else{
                cout << "Invalid Date! The default date has been set.(1,1)" << endl;
                day = 1;
                month = 1;
            }
        }
        else{
            cout << "Invalid Date! The default date has been set.(1,1)" << endl;
            day = 1;
            month = 1;
        }
    }
    //Get functions for DayOfYear object
    int DayOfYearSet::DayOfYear::getDay() const
    {
        return day;
    }
    int DayOfYearSet::DayOfYear::getMonth() const
    {
        return month;
    }
    // preincrement operator overload for DayOfYear object
    void DayOfYearSet::DayOfYear::operator++()
    {

        if (day == checkDay())
        {
            if(month == 12)
                month = 1;
            else
                month++;
            day = 1;
        }
        else
            ++day;
    }
    //Assignment operator overload for DayOfYear object
    void DayOfYearSet::DayOfYear::operator=(const DayOfYearSet::DayOfYear & other)
    {
        day = other.day;
        month = other.month;
    }
    //This function returns the right day according to month
    int DayOfYearSet::DayOfYear::checkDay()
    {
        switch (month)
        {
        case 1:
            return 31;
        case 2:
            return 28;
        case 3:
            return 31;
        case 4:
            return 30;
        case 5:
            return 31;
        case 6:
            return 30;
        case 7:
            return 31;
        case 8:
            return 31;
        case 9:
            return 30;
        case 10:
            return 31;
        case 11:
            return 30;
        case 12:
            return 31;
        default:
            return 0;
        }
    }
    //This constuctor takes a list of DayOfYear objects for DayOfYearSet objects
    DayOfYearSet::DayOfYearSet (std::initializer_list<DayOfYear> newList){
        std::initializer_list<DayOfYear>::iterator it;
        set = new DayOfYearSet::DayOfYear[newList.size()];
        _size = newList.size();
        _capacity = newList.size();
        int i;
        for (i = 0,it = newList.begin(); it != newList.end(); ++it,i++)
            set[i] = *it;
    }
    //Constructor of DayOfYearSet object with user capacity
    DayOfYearSet::DayOfYearSet(int capacity) : _capacity(capacity), _size(0)
    {
        int r;
        if (capacity < 0)
        {
            cout << "Negative capacity. Default capacity has been set.\n";
            r = 100;
        }
        else
            r = capacity;
        set = new DayOfYearSet::DayOfYear[r];
    }
    //Copy Constructor of DayOfYearSet object
    DayOfYearSet::DayOfYearSet(const DayOfYearSet &other)
    {
        set = new DayOfYearSet::DayOfYear[other._capacity];
        _capacity = other._capacity;
        _size = other.size();
        for(auto i = 0;i<_size;i++)
            set[i] = other[i];

    }
    //Destructor of DayOfYearSet object
    DayOfYearSet::~DayOfYearSet()
    {
        delete[] set;
    }
    //This function determines whether an element is in the set or not.
    bool DayOfYearSet::isDuplicate(const DayOfYear &c) const
    {
        for (auto i = 0; i < size(); ++i)
            if (set[i] == c)
                return true;
        return false;
    }
    void DayOfYearSet::reset(){
        _capacity = 20;
        _size = 0 ;
        delete[] set;
        set = nullptr;
        //set = new DayOfYearSet::DayOfYear[_capacity];
    }
    //This function removes an element from set
    int DayOfYearSet::remove(const DayOfYear &rmDay)
    {
        if(isDuplicate(rmDay)){
            for (auto i = 0; i < size(); ++i){
                if (set[i] == rmDay){
                    for (auto c = i; c < size() ; c++ ) {
                        set[ c ] = set[ c + 1 ];          
                    }
                    _size--;
                }
            }
            return 0;
        }
        return -1;
    }
 
    //Assignment operation overload for DayOfYearSet object
    void DayOfYearSet::operator=(const DayOfYearSet &other)
    {
        _capacity = other._capacity;
        _size = other.size();

        delete[] set;
        set = new DayOfYearSet::DayOfYear[_capacity];
        for (auto i = 0; i < _size; i++)
            set[i] = other.set[i];
    }
    //Equality operator overload for DayOfYearSet objects
    bool DayOfYearSet::operator==(const DayOfYearSet &other)
    {
        for (auto i = 0; i < other.size(); ++i)
            if (!isDuplicate(other[i]))
                return false;
        return true;
    }
    //Inequality operator overload for DayOfYearSet objects
    bool DayOfYearSet::operator!=(const DayOfYearSet &other)
    {
        return !(*this == other);
    }
    //Plus operator overload for adding new day in a set
    const DayOfYearSet DayOfYearSet::operator+(const DayOfYear &newDay)
    {      
        int r;
        if(size() == _capacity)
            r = _capacity*2;
        else
            r = _capacity;
        DayOfYearSet newSet(r);

        for(auto i = 0 ; i<size();i++){
            newSet.set[i] = set[i];
            ++newSet._size;  
        }
        if(!isDuplicate(newDay)){
            newSet.set[_size] = newDay;
            ++newSet._size;
        }


        return newSet;
    }
    //Plus operator overload for adding two DayOfYear objects(Union)
    const DayOfYearSet DayOfYearSet::operator+(const DayOfYearSet &other)
    {
        DayOfYearSet unionSet(_capacity);
        for (auto i = 0; i < size(); i++)
            unionSet = unionSet + set[i];
        for (auto i = 0; i < other.size(); ++i)
            unionSet = unionSet + other[i];
        return unionSet;
    }
    //Minus operator overload for difference of two DayOfYear objects(Difference)
    const DayOfYearSet DayOfYearSet::operator-(const DayOfYearSet &other)
    {
        int r = (_capacity < other._capacity) ? _capacity : other._capacity ; 
        DayOfYearSet diffSet(r);
        for (auto i = 0, j = 0; i < size(); i++, j++)
        {
            if (!(other.isDuplicate(set[i])))
                diffSet = diffSet+ set[i];
        }

        return diffSet;
    }
    //Minus operator overload for removing an element from set
    const DayOfYearSet DayOfYearSet::operator-(const DayOfYear &rmDay)
    {
        DayOfYearSet newSet(_capacity);
        newSet = *this;
        newSet.remove(rmDay);
        return newSet;

    }
    //^ operator overload for intersection of two sets
    const DayOfYearSet DayOfYearSet::operator^(const DayOfYearSet &other)
    {
        DayOfYearSet intersectionSet(_capacity);
        for (auto i = 0; i < size(); ++i){
            if (other.isDuplicate(set[i]))
            {
                intersectionSet = intersectionSet + set[i];
            }
        }
        return intersectionSet;
    }
    //! operator overload for compelement of a set
    const DayOfYearSet DayOfYearSet::operator!()
    {
        DayOfYearSet::DayOfYear day(1, 1);
        DayOfYearSet complementSet(365);
        for (auto i = 0; i < 365; ++i, ++day)
        {
            if (!isDuplicate(day))
                complementSet = complementSet + day;
        }
        return complementSet;
    }
    //Subscript operator overload for DayOfYearSet object
    const DayOfYearSet::DayOfYear &DayOfYearSet::operator[](int position) const
    {
        /*if (position > _capacity)
            cout << "Out of bounds" << endl;*/
        return set[position];
    }
    //This function returns a size of DayOfYearSet object
    int DayOfYearSet::size() const {
        return _size; 
    }
    //--------------------------Friend Functions--------------------------
    // << overload for DayOfYear object set (DayOfYearSet)
    ostream &operator<<(ostream &out, const DayOfYearSet &s)
    {
        for (int i = 0; i < s.size(); ++i)
            out << s[i] << " ";
        return out;
    }
    // << overload for single DayOfYear object
    ostream &operator<<(ostream &out, const DayOfYearSet::DayOfYear &d)
    {
        out <<"(" <<"Day: " << d.getDay() << " Month: " << d.getMonth() << ")" << ",";
        return out;
    }
    //== and != overload for comparing DayOfYear objects
    bool operator==(const DayOfYearSet::DayOfYear &d1, const DayOfYearSet::DayOfYear &d2)
    {
        return d1.getDay() == d2.getDay() && d1.getMonth() == d2.getMonth();
    }
    bool operator!=(const DayOfYearSet::DayOfYear &d1, const DayOfYearSet::DayOfYear &d2)
    {
        return !(d1 == d2);
    }
    //-------------------------------------------------------------------    
}
