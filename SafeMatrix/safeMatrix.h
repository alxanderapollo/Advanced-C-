//Written by alex Salazar 10/14
//This is the safe matrix header file.
// It is pretty bear and only built for the purpose of doing matrix multiplication 
//enabled by the safe array, it creates a 2D safe array to carry out matrix multiplication
#ifndef safeMatrix_H_
#define safeMatrix_H_
#include "safeArray.h" //inlcude the safe array class 
template <class T>
    class safeMatrix{ 
            private:
            //4 global variables
            //lowerBound pairs with upperBound
            //lowerBound2 pairs with upperBound2
            //point of this is to  represent Rows and Cols
            int row_high,row_low,col_high,col_low,newRow, newCol, rowSize, Colsize; 
            //row =  upperbound - lowerBound
            //col = upperBound2 - lowerBound2

            safeArray<safeArray <T> > *myMatrix; //safe array of safe arrays
           public:

           //2 param constructor user doesn't need to specify low
           // low is set to zero in this constructor
           //only need to pick the the size of the row and col
            safeMatrix(int row, int col);
            //this constructor gives the user to pick the low, 
            //the low is the starting point in the program
            //the first hight would be the row specific lenght
            //the second high is for the col
            
            //return invidual col and row params 
            int& getColHigh();
            int& getColLow();
            int& getRowHigh();
            int& getRowLow();

            //takes in one paramerters, sets the array to n - 1
            safeMatrix(int row_low, int row_high, int col_low, int col_high);
            
            //copy constructor
            safeMatrix(safeMatrix<T>& obj); 
            //destructor
            ~safeMatrix();
            
            //overloading brackets,and print function
            //safeMatrix<T>& operator*(safeMatrix& obj); //overloaded multiplication
            safeArray<T>& operator[](int i); //over load the brackets
            void printMe();//print function so i dont have to use the overload the ostream explicitly.
            friend ostream& operator<<(ostream& os, const safeMatrix<T> s);     
    };//end safeMatrix 
#endif 