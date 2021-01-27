//written by Alex Salazar 
//Adv c++
//10/14
#include "safeMatrix.h"
#include "safeArray.h"
#include <iostream>
using namespace std;

template <class T>
        //2 input constructor
        //both the lower boundry for col & row are determined,
        //starting at zero to whatever number >0 inputted by the user
        safeMatrix<T>::safeMatrix(int row, int col){ 
            //bounds checking
            //row and col cant be negative 
            if (row < 0){
                cout<<"error out of bounds, row high cannot be a negative value aborting program......."<<endl;
                exit(1);
            }else if( col < 0){
                cout<<"error out of bounds, col high cannot be a negative value aborting program......"<<endl;
                exit(1);

            }else{
                //1. set the params
                //row = row_high - row_low -------->upperBoundry
                this->row_high = row;
                this->row_low = 0;

                //col = col_high - col_low  ------->lowerBoundry 
                this->col_high = col;
                this->col_low = 0;
                //2.create the 2D matrix
                //create the 2D Safe array (safe array of safe arrays)
                myMatrix = new safeArray< safeArray<T> >(this->row_low, this->row_high);//the rows
                int i = 0;
                while (i< this->row_high+1){
                    safeArray<T> myTempMatrix(this->col_low, this->col_high);//the cols
                    (*myMatrix)[i] = myTempMatrix;//since its an array within an array, need to 
                    //derefrence the internal
                    //at the end of the his loop the the NXM matrix size is complete
                    i++;//next elt
                }//end while
            }//end else
        }//end 2 param constructor

    //getCol and lenght params for size
    template <class T>
        int& safeMatrix<T>::getColHigh(){
            return this->col_high;
        }
    template <class T>
        int& safeMatrix<T>::getColLow(){
            return this->col_low;
        }
    template <class T>
        int& safeMatrix<T>::getRowHigh(){
            return this->row_high;
        }
    template <class T>
        int& safeMatrix<T>::getRowLow(){
            return this->row_low;
        }

        //4 param Constructor
template <class T>
        //this is for the user that wants to define the low and high of each row and column
        safeMatrix<T>::safeMatrix(int row_low, int row_high, int col_low, int col_high){
            //eror checking low is bigger than high
             if(row_low > row_high ){
                 cout<<"row low must be assigned  smaller value than row high aborting program......"<<endl;
                 exit(1);
             }else  if(col_low > col_high  ){
                  cout<<"col low must be assigned smaller value aborting program......"<<endl;
                 exit(1);
             }else{
                //1. set the params 
                //row = row_high - row_low -------->upperBoundry
                this->row_high = row_high;
                this->row_low = row_low;

                //column = col_high - col_low ------->lowerBoundry 
                this->col_high = col_high;
                this->col_low = col_low;

                //create safe array of safe arrays with the first set of params
                myMatrix = new safeArray< safeArray<T> >(this->row_low, this->row_high); // row 
                //now create the 2D matrix
                int i = this->row_low;
                while (i< this->row_high+1){
                    //2nd piece of the 2D matrix
                    safeArray<T> myTempMatrix(this->col_low, this->col_high);
                    (*myMatrix)[i] = myTempMatrix; 
                    i++;
                }//end while
          }//end else
        }//end param constructor

template <class T> //copy constructor
    safeMatrix<T>::safeMatrix(safeMatrix<T>& obj){
            //1. first copy all the params of the obj -------->upperBoundry
            this->row_high =obj.row_high;
            this->row_low = obj.row_low;
            // ------->lowerBoundry 
            this->col_high = obj.col_high;
            this->col_low = obj.col_low;

            //2. create the 2D safe array w/ the row param and copy
            myMatrix = new safeArray< safeArray<T> > (this->row_low, this->row_high);
            int i = this->row_low; 
            while( i< this->row_high+1){
                (*myMatrix)[i] = obj[i];
                i++;
            }//end while
    }//
template <class T>
    //destructor
    safeMatrix<T>:: ~safeMatrix(){
            delete myMatrix;
        }//end destructor
template <class T>
        //overloaded brackets
    safeArray<T>& safeMatrix<T>::operator[](int i){
            return (*myMatrix)[i];
        }//end bracket operator

template <class T>
    void safeMatrix<T>::printMe(){
            int i = this->row_low;
            while(i < this->row_high + 1){
                //equals each member of the row, 
                //once we've reached the last column
                //print the entire row out.
                safeArray<T> result = (*myMatrix)[i];
                cout<<"Row position "<< i+1<<": " << result <<endl;
                i++;
            }//end while
        }//end class
