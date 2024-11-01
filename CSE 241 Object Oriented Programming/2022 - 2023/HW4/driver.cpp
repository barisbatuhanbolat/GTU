#include <iostream>
#include <vector>
#include "DayOfYearSet.h"  
using namespace std;
using namespace GTUHW4;
int main () {

    int day,month,count,count2,count3;

    cout << "--------------------DayOfYear Class--------------------" << endl;

    cout << "Enter day: ";
    cin >> day;
    cout << "Enter month: ";
    cin >> month;

    cout << "Testing DayOfYear constructor." << endl;
    DayOfYearSet::DayOfYear d1(month,day);
    cout << d1 << endl;
    cout << endl;
    
    cout << "Testing DayOfYear copy constructor (d1 to d2)." << endl;
    DayOfYearSet::DayOfYear d2(d1);
    cout << d2 << endl;
    cout << endl;

    cout << "Get functions" << endl;
    cout << "Day: " << d1.getDay() << "  Month: "  << d1.getMonth() <<endl;
    cout << endl;

    cout << "Preincrement operator overload for DayOfYear" << endl;
    ++d1;
    cout << d1 << endl;
    cout << endl;

    cout << "Inequality operator overload for DayOfYear" << endl;
    if(d2 != d1)
        cout << "d2 is not equal with d1" << endl;
    cout << endl;

    cout << "Assignment operator overload for DayOfYear(d1 to d2)" << endl;
    d2 = d1;
    cout << d2 << endl;
    cout << endl;

    cout << "Equality operator overload for DayOfYear" << endl;
    if(d2 == d1)
        cout << "d2 is equal with d1" << endl;
    cout << endl;

    cout << "-------------------DayOfYearSet Class------------------" << endl;

    cout << "Creating a list of DayOfYear objects for the DayOfYearSet object" << endl;
    DayOfYearSet::DayOfYear x0(4,3);
    DayOfYearSet::DayOfYear x1(6,5);
    DayOfYearSet::DayOfYear x2(8,7);
    vector<DayOfYearSet> sets;
    DayOfYearSet s1{x0,x1,x2};
    decltype(s1) resSet;
    cout << "Printing DayOfYearSet" << endl;
    cout << s1 << endl;
    sets.push_back(s1);
    do{
        cout << "-------------------------MENU-------------------------" << endl;
        cout << "\t1 - Print all sets(DayOfYearSet objects)" << endl;
        cout << "\t2 - Create a set" << endl;
        cout << "\t3 - Add new day to set" << endl;
        cout << "\t4 - Remove a day from set(Remove Function)" << endl;
        cout << "\t5 - Remove a day from set(-operator)" << endl;
        cout << "\t6 - Comparing of two sets" << endl;
        cout << "\t7 - Union of two sets" << endl;
        cout << "\t8 - Difference of two sets" << endl;
        cout << "\t9 - Intersection of two sets" << endl;
        cout << "\t10 - Complement of a set" << endl;
        cout << "\t11 - Exit" << endl;
        cout << "Choice: " ;
        cin >> count;

        if(count == 1)
        {
            for(auto i = 0; i<sets.size();i++)
                cout << "s[" << i+1 << "] = " << sets[i] << endl;
            
        }
        
        else if(count == 2)
        {
            day = 0; month = 0;
            while(day != -1 && month != -1){
                cout << "Enter day: ";
                cin >> day;
                if(day != -1){
                    cout << "Enter month: ";
                    cin >> month;
                    if(month != -1){
                        DayOfYearSet::DayOfYear d3(month,day);
                        resSet = resSet + d3;
                    }
                }
            }
            sets.push_back(resSet);
            resSet.reset();
            
        }
        else if(count == 3)
        {
            for(auto i = 0; i<sets.size();i++)
                cout << "s[" << i+1 << "] = " << sets[i] << endl;
            cout << "Choose set: ";
            cin >> count2;
            if(count2 >sets.size() || count2 < 1){
                cout << "Wrong choice" << endl;
                exit(-1);
            }
            cout << "Enter day: ";
            cin >> day;
            cout << "Enter month: ";
            cin >> month;
            DayOfYearSet::DayOfYear d3(month,day);
            sets[count2-1] = sets[count2-1] + d3;
            
        }
        else if(count == 4)
        {
            for(auto i = 0; i<sets.size();i++)
                cout << "s[" << i+1 << "] = " << sets[i] << endl;
            cout << "Choose set: ";
            cin >> count2;
            if(count2 >sets.size() || count2 < 1){
                cout << "Wrong choice" << endl;
                exit(-1);
            }
            cout << "Enter day to remove: ";
            cin >> day;
            cout << "Enter month tot remove: ";
            cin >> month;
            DayOfYearSet::DayOfYear d3(month,day);
            sets[count2-1].remove(d3);
                        
        }
        else if(count == 5)
        {
            for(auto i = 0; i<sets.size();i++)
                cout << "s[" << i+1 << "] = " << sets[i] << endl;
            cout << "Choose set: ";
            cin >> count2;
            if(count2 >sets.size() || count2 < 1){
                cout << "Wrong choice" << endl;
                exit(-1);
            }            
            cout << "Enter day to remove: ";
            cin >> day;
            cout << "Enter month tot remove: ";
            cin >> month;
            DayOfYearSet::DayOfYear d3(month,day);
            sets[count2-1] = sets[count2-1] - d3;
            
        }
        else if(count == 6)
        {
            for(auto i = 0; i<sets.size();i++)
                cout << "s[" << i+1 << "] = " << sets[i] << endl;
            cout << "Choose set 1: ";
            cin >> count2;
            if(count2 >sets.size() || count2 < 1){
                cout << "Wrong choice" << endl;
                exit(-1);
            } 
            cout << "Choose set 2: ";
            cin >> count3;
            if(count3 >sets.size() || count3 < 1 || count2 == count3){
                cout << "Wrong choice" << endl;
                exit(-1);
            }
            if(sets[count2-1] == sets[count3-1])
                cout << "Two sets are equal" << endl;
            else if(sets[count2-1] != sets[count3-1])
                cout << "Two sets are not equal" << endl;
            
        }
        else if(count == 7)
        {
            for(auto i = 0; i<sets.size();i++)
                cout << "s[" << i+1 << "] = " << sets[i] << endl;
            cout << "Choose set 1: ";
            cin >> count2;
            if(count2 >sets.size() || count2 < 1){
                cout << "Wrong choice" << endl;
                exit(-1);
            } 
            cout << "Choose set 2: ";
            cin >> count3;
            if(count3 >sets.size() || count3 < 1 || count2 == count3){
                cout << "Wrong choice" << endl;
                exit(-1);
            }
            resSet = sets[count2-1] + sets[count3-1];
            cout << "Union (s1 + s2): "  << resSet <<endl;
            
        }
        else if(count == 8)
        {
            for(auto i = 0; i<sets.size();i++)
                cout << "s[" << i+1 << "] = " << sets[i] << endl;
            cout << "Choose set 1: ";
            cin >> count2;
            if(count2 >sets.size() || count2 < 1){
                cout << "Wrong choice" << endl;
                exit(-1);
            }  
            cout << "Choose set 2: ";
            cin >> count3;
            if(count3 >sets.size() || count3 < 1 || count2 == count3){
                cout << "Wrong choice" << endl;
                exit(-1);
            }
            resSet = sets[count2-1] - sets[count3-1];
            cout << "Difference (s1 - s2): "  << resSet <<endl;
            
        }
        else if(count == 9)
        {
            for(auto i = 0; i<sets.size();i++)
                cout << "s[" << i+1 << "] = " << sets[i] << endl;
            cout << "Choose set 1: ";
            cin >> count2;
            if(count2 >sets.size() || count2 < 1){
                cout << "Wrong choice" << endl;
                exit(-1);
            }  
            cout << "Choose set 2: ";
            cin >> count3;
            if(count3 >sets.size() || count3 < 1 || count2 == count3){
                cout << "Wrong choice" << endl;
                exit(-1);
            }
            resSet = sets[count2-1] ^ sets[count3-1];
            cout << "Intersection (s1 ^ s2): "  << resSet <<endl;
                        
        }
        else if(count == 10)
        {
            for(auto i = 0; i<sets.size();i++)
                cout << "s[" << i+1 << "] = " << sets[i] << endl;
            cout << "Choose set to complement: ";
            cin >> count2;
            if(count2 >sets.size() || count2 < 1){
                cout << "Wrong choice" << endl;
                exit(-1);
            }
            resSet = !sets[count2-1];
            cout << "Complement(!s1): " << resSet << endl;
            
        }
        else if(count == 11)
        {
            exit(0);
                    
        }
    }while(count != 11);

}