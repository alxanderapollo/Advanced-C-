//written by Alex Salazar
//Safe matrix proj
//10/1
//header file for the safe array implementation file
#ifndef safeArray_H_
#define safeArray_H_
#include <iostream>
using namespace std;
template <class T>
    class safeArray{
        public:
            int low, high; //high and low boundry
            T* p;// pointer
        public:
            safeArray();//default constructor
            safeArray(int l, int h);//constructor that only takes in 2 params
            safeArray(int i);//takes in one paramerters, sets the array to n - 1
            safeArray(const safeArray &s); //copy constructor
            ~safeArray();//destructor

            //overloading brackets, assignment operator, and left shift
            T &operator[](int i); //over load the brackets
            safeArray<T>& operator=(const safeArray<T> &s); 
           // friend ostream& operator<<(ostream &os, safeArray<T> s);
    };//end safeArray 
#endif 