#ifndef DAY_OF_YEAR_SET 
#define DAY_OF_YEAR_SET  
#include <list> 
using namespace std;

namespace GTUHW4 {
    class DayOfYearSet {
        public:
            class DayOfYear {
                public:
                    DayOfYear(){};
                    DayOfYear(const DayOfYear & other);
                    DayOfYear (int monthT, int dayT);
                    int getDay () const;
                    int getMonth () const;
                    void operator++ ();
                    void operator=(const DayOfYear & other);
                    friend ostream & operator<< (ostream & out, const DayOfYear & d);
                    friend bool operator== (const DayOfYear & d1, const DayOfYear & d2);
                    friend bool operator!= (const DayOfYear & d1, const DayOfYear & d2);                    
                private:
                    int checkDay();
                    int day;
                    int month;
            };
            DayOfYearSet () : _capacity(20),_size(0),set(nullptr){};
            DayOfYearSet (int capacity);
            DayOfYearSet (std::initializer_list<DayOfYear> newList);
            DayOfYearSet (const DayOfYearSet & s);
            ~DayOfYearSet ();
            bool isDuplicate (const DayOfYear & c) const;
            void reset();
            int remove (const DayOfYear & rmDay);
            void operator= (const DayOfYearSet & other);
            bool operator== (const DayOfYearSet & other);
            bool operator!= (const DayOfYearSet & other);
            const DayOfYearSet operator+ (const DayOfYear & newDay);
            const DayOfYearSet operator+ (const DayOfYearSet & other);
            const DayOfYearSet operator- (const DayOfYear & rmDay);
            const DayOfYearSet operator- (const DayOfYearSet & other);
            const DayOfYearSet operator^ (const DayOfYearSet & other);
            const DayOfYearSet operator! ();
            const DayOfYear & operator[] (int position) const;
            int size () const;
            friend ostream & operator<< (ostream & outs, const DayOfYearSet & s);
        private:
            int _size;
            int _capacity;
            DayOfYear * set;
    };
}
#endif