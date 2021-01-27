//written by Alex Salazar
//implementation file of the safe array header file
//10/1 
//Adv c++
#include "safeArray.h"
#include <iostream>
using namespace std;
//template class 
template <class T> 
    safeArray<T>::safeArray(){
        low = 0; //zero is where the array starts
        high = -1; //-1 so we dont hit the boundry
        p = NULL; //pointer set to point to null
    }//end default constructor

//iterators
template<class T>
    T* safeArray<T>:: begin(){
        return &p[low]; //begining of the array 
    }
template<class T>
    T* safeArray<T>:: end(){
        return &p[high];// end of the array
    }
template<class T>
    T* safeArray<T>:: operator++(){
        this->p ++;
        return *this;
    } 
template<class T>
    T* safeArray<T>:: operator--(){
         this->p--;
        return *this;
    }    

template<class T>
    T* safeArray<T>:: operator++(int){
         this->p ++;
        return *this;
    }    

template<class T>
    T* safeArray<T>:: operator--(int){
        this->mPtr --;
        return *this;
    }    

    template <class T>
    // single parameter constructor 
    //takes in a length i
    //and sets the array to  n -1
        safeArray<T>::safeArray(int i){
            low = 0; //lower boundery
            high = i - 1;//upper boundry
            p = new T[i];//pointer initlizied to the safeArray me as high
        }//end conversion constructor

    template <class T>
    //safeArray array constructor
    //takes in two params high and low for the array
        safeArray<T>::safeArray(int l, int h){
            //proper array check 
            // we are checking that the lenght is not zero or smaller than zero
            if ((h - l + 1) <= 0)// if the array length is less than or equal to zero
            {
                cout << "constructor error in bounds definition" << endl;
                exit(1);//exit program
            }
            low = l; //low (class member) = l (param)
            high = h; //high (class member) = h(param)
            p = new T[h - l + 1]; // high - 0 + 1 (length)
            //pointer is  of the class type T
        }//end constructor
    // copy constructor

    template <class T> 
        safeArray<T>::safeArray(const safeArray<T> &s){
            int size = s.high - s.low + 1; //size of the
            //new array is equivalent to the obj that is being copied from
            p = new T[size]; //create a new pointer 
            //here copy all the elements from the perevious obj
            for (int i = 0; i < size; i++) 
                p[i] = s.p[i];
            //low and high value
            low = s.low;
            high = s.high;
        }//end copy constructor

    //destructor for prooperly getting rid of the pointer that was used
    template <class T> 
        safeArray<T>::~safeArray(){
            delete[] p;
        }//end destructor 

    //int becomes a T
    //the brackets are overloaded
    template <class T> 
     T& safeArray<T>:: operator[](int i){   
        //out of bounds check low should be 0 if
        //if i is smaller than zero that means
        //we are in the negative range
        //if i > high that means the boundry has been surpased
        //and we are out of bounds
        if (i < low || i > high)
        {
            cout << "index " << i << "  bounds out of range" << endl;
            exit(1);
        }
        return p[i - low];
    }//end overloaded brackets operator

    //assigning one safeArray to the other
    //pass safeArray s as a const val 
    template <class T> 
     safeArray<T>& safeArray<T>::operator=(const safeArray<T> &s){  
        //if the object we're looking at is already 
        //been made or equal then just return a pointer to the obj
        if (this == &s) return *this;
        //delete pointer
        delete[] p;
        //otherwise assignment operator
        //create the new obj
        //and make a pointer with the size of the array
        int size = s.high - s.low + 1;
        p = new int[size];
        //assign each of the items 
        for (int i = 0; i < size; i++) 
            p[i] = s.p[i];
        //create low and high variables and return a pointer
        low = s.low;
        high = s.high;
        return *this;
    }//end reference operator

    template <class T>
    ostream &operator<<(ostream &os, safeArray<T> s){
            for (int i = 0; i < (s.high - s.low); i++)
                cout << s.p[i] << " ";
            return os;
        }
    
