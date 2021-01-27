//Written by Alex Salazar 11/2
//big int part 2 
#include <stdlib.h>
#include <memory>
#include <iostream>
#include<algorithm>
#include <string>
#include "BigInt.cpp"
//#define numberofBytes 10000
//#include "myBlock.cpp"
using namespace std;
bool isSmaller(string str1, string str2);
void createBigInt(string one, string two){
    //--->Big IntClass Test
    //  convert string into char array for the class
    //string one = "0";
    //we need the length of the string
    int n = one.length();
    //need a c string  to the hold the user string
    char char_array[n + 1]; //declare the c string
    //finally copy th r contents into the char array
    strcpy(char_array, one.c_str());
    BigInt a(char_array);

    //string two = "12";
    //we need the length of the string
    int n2 = one.length();
    //need a c string  to the hold the user string
    char char_array2[n2 + 1]; //declare the c string
    //finally copy thr contents into the char array
    strcpy(char_array2, two.c_str());
    BigInt b(char_array2);

    cout<<"my String: "<<a.getString()<<endl;
    cout<<"my 2nd String: "<<b.getString()<<endl;

   // cout<<char_array2<<endl;
    cout<<"\nAddition: "<<endl;
    BigInt c = a + b;
    c.printMe();
    //---------------------------------->Testing multiplication
    cout<<"\nMultiplication: "<<endl;
    c = a *b ;
    c.printMe();
    //---------------------------------->Testing subtraction
    cout<<"\nSubtraction: "<<endl;
    c = a - b;
    c.printMe();

    //---------------------------------->Testing Division
    cout<<"\nDivision: "<<endl;
    c = a / b; 
    c.printMe();
}//end create big int

int main(){
    //test memory manager
    //myBlock* one = new myBlock(sizeof("apples"), 100);

    // cout<<"This Program takes two inputs"<<endl;
    // string a, b; 
    // cout<<"Enter your first input"<<endl;
    // cin>>a;
    // cout<<"Enter another"<<endl;
    // cin>>b;
    //call function to create big int with params
     string a, b; 
     a = "10";
     b = "10"; 
    createBigInt(a, b);

    return 0;
}//end main
