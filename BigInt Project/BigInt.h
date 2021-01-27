//written by Alex Salazar
//Big Integer Header file
//11/2
//header file for the Big integer implementation file
#ifndef BigInt_H_
#define BigInt_H_
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class BigInt{

    private:
        char* myStr;//to go through the string array 
        //string myS//tring; // to be the input of the user
        int length; 
    public:
        //constructors
        //default incase user forgets to input 
        BigInt(); 
        BigInt(char *userInput); //construct object to user specifciations
        BigInt(int num);//int conversion constructor
        BigInt(const BigInt &obj);//copy constructor
        ~BigInt(); //destructor 

        //return the string and the object
        //return the size
        int& mySize();
        //return c-string
        char* getString();
        
        //assignment operator
        BigInt& operator=(const BigInt &obj);

        //operations on the object
        BigInt& operator*(BigInt const &obj);
        string multiplyAndCarry(string& a, string& b);

        //addition
        BigInt& operator+(BigInt const  &obj);
        string sumAndCarry(string& a, string& b);//want the address of the two string since it will be changed
        
        //subtract
        BigInt& operator-(BigInt const &obj);
        string subtractAndCarry(string& a, string& b);
        
        //print function
        void printMe();
        
        //clean up functions --->functions to remove clutter
        string convertToString(char* s, int length);
        bool checkMe(string a, string b);
        //char* convertToC_String(string myString);

        //input and output
        friend ostream& operator<<(ostream& os, const BigInt& num);
        //friend istream & operator >> (istream &in, BigInt &c); 
};
#endif

