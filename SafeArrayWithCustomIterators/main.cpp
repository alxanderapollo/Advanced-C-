//project 7 stl implmentation 
//tests only find and sort
//12/16

#include "safeArray.cpp"
#include<algorithm>
#include <iterator>

/*
this program only tests find in the stl and sort function,
in both the header and cpp file of safe array there are other
iterators that i have implmented
such as ++ and --, in addition to being and end

*/

int main (){
    
    int low, high;
     low = 0, high = 5;
     safeArray<int>a (low,high) ;
     a[0] = 15;
     a[1] = 12;
     a[2] = 22;
     a[3] = 14;
     a[4] = 1;

    //find function
    int search = 14; //number i am searching for
    int * findme;
    findme = std::find(a.begin(), a.end(), search);

    cout<<"Searched number: "<<search<<" number found: "<<(*findme)<<endl;

    //sort the array.
    std::sort(a.begin(),a.end());
    cout<<a<<endl;
    return 0;
}