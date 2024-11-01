#include <iostream>
#include <algorithm>
#include "PFArray.h"
#include <vector>
using namespace std;

template<class T>
void print(T x){
    cout << x << endl;
}

template<class T>
void play(PFArray<T> arr){
    cout << "----------------PFArray Class AddElement-----------------" << endl;
    int cont = 1;
    while(cont == 1){
        T element;
        cout << "Enter an element: ";
        while((!(cin>>element))){
            cout << "Wrong choice: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        arr.addElement(element);
        cout << "Do you want to continue(1(Yes)/0(No)): ";
        while((!(cin>>cont)) || (cont<0 || cont>1)){
            cout << "Wrong choice: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        if(cont == 0)
            break;
    }
    cout << "-------------------PFArray Class Print-------------------" << endl;
    arr.print();
    cout << "-------------------PFArray Class Empty-------------------" << endl;
    if(arr.empty()){
        cout << "Class is Empty" << endl;
    }
    else{
        cout << "Class is not Empty" << endl;
    }
    cout << "-------------------PFArray Class Size--------------------" << endl;
    cout << "Size of class is : " << arr.size() << endl;
    
    cout << "--------------PFArray Class Iterator(begin,cbegin)--------------" << endl;
    typename PFArray<T>::Iterator in;
    typename PFArray<T>::Iterator ic;
    in = arr.begin();
    ic = arr.cbegin();
    cout << "Modifable Iterator(arr.begin()) : " << *(in) << endl;
    cout << "Constant Iterator(arr.cbegin()) : " << *(ic) << endl;

    
    cout << "-------------------PFArray Class erase-------------------" << endl;
    cout << "Enter an element to delete: ";
    T element;
    while((!(cin>>element))){
        cout << "Wrong choice: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    auto res = find(arr.begin(),arr.end(),element);
    arr.erase(res);
    arr.print();

    cout << "-----------------PFArray Class Capacity------------------" << endl;
    cout << "Capacity of class is : " << arr.getCapacity() << endl;

    cout << "---------------------STL Sort Test-----------------------" << endl;
    
    sort(arr.begin(),arr.end());
    cout << "Sorted Array: " << endl;
    arr.print();
    
    cout << "---------------------STL Find Test-----------------------" << endl;
    cout << "Enter an element to find: ";
    while((!(cin>>element))){
        cout << "Wrong choice: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    auto i2 = find(arr.begin(),arr.end(),element);
    if(i2 != arr.end())
        cout << "Element found" << endl;
    else
        cout << "Element can not be found" << endl;

    cout << "---------------------STL For_Each Test-----------------------" << endl;

    for_each(arr.begin(), arr.end(), print<T>);    


    cout << "-------------------PFArray Class clear-------------------" << endl;
    cout << "All items cleared" << endl;
    arr.clear();
    arr.print();

} 

int main(){
    
    int choice,capacity;
    cout << "----------------PFArray Class Constructor----------------" << endl;
    cout << "1 - Integer" << endl;
    cout << "2 - Double" << endl;
    cout << "3 - Char" << endl;
    cout << "4 - String" << endl;
    cout << "5 - Bool" << endl;

    cout << "Choose Type: ";
    while((!(cin>>choice)) || (choice<=0 || choice>6)){
        cout << "Wrong choice: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    cout << "Enter capacity: ";
    while((!(cin>>capacity))){
        cout << "Wrong capacity: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    
    try{
        if(choice == 1){
            PFArray<int> intarr(capacity);
        
            play(intarr);
        }
        else if(choice == 2){
            PFArray<double> dblarr(capacity);
            play(dblarr);
        }
        else if(choice == 3){
            PFArray<char> chrarr(capacity);
            play(chrarr);
        }
        else if(choice == 4){
            PFArray<string> strarr(capacity);
            play(strarr);
        }
        else if(choice == 5){
            PFArray<bool> bllarr(capacity);
            play(bllarr);
        }
    }
    catch(string s1){
        cout << s1 << endl;
    }    
    catch(out_of_range e){
        cout << e.what() << endl;
    }
    catch(invalid_argument e){
        cout << e.what() << endl;
    }
}