//written by Alex Salazar
//10/20
//Adv c++ main file for the Safe matrix project
//this program allows for the creation of the safe array class 
//or that safe matrix class which is composed of safe arrays
//a 2D safearray(safeMatrix) can be created

//How to use this program enter a matrix below and call the multiplyMatrices function----------------------
#include "safeArray.cpp"
#include "safeMatrix.cpp"
#include <iostream>
using namespace std;

//gloab varaibles
int row_high,row_low,Col_High,Col_Low;

//multiply me, function to multiply matrices
void multiplyMatrices(safeMatrix<int> mat1, safeMatrix<int> mat2){

             //multiplication operator
             //for matrix multiplication what needs to be considered is col of the first matrix, and the row of the second matrix
            //step1 check if the col of the first matrix is eqaul to the row of the second matrix
             //if the col and row arent the same exit the program.

             int FirstCol = mat1.getColHigh() - mat1.getColLow() + 1;
             int secondRow = mat2.getRowHigh()- mat2.getRowLow() + 1;
             //this check is to see if the colum of the first matrix is not equal to the row of the second matrix
            //if the first col is not equal to the second row, set it as true otherwise false
             int checkMe = (FirstCol != secondRow) ? true: false;

            //debug
            //  cout<<"first col: "<<FirstCol<<endl;
            //  cout<<"second Row: "<<secondRow<<endl;

             
             //check
              if(checkMe){
                  cout << "the col of the first matrix must equal the 2nd matrix! Try again";
                  exit(1); //abnormal termination
              }//end if

              else{
                //2. create the resulting Matrix
                int newRow = mat1.getRowHigh() - mat1.getRowLow();
                int  newCol = mat2.getColHigh() - mat2.getColLow();
                 int colSize = mat1.getColHigh() - mat1.getColLow() + 1;
                 int holdMe = 0;//temp hold 
                //resulting matrix 
                safeMatrix<int> *result;
                result  = new safeMatrix<int> (0, newRow, 0 ,newCol);
                //3. Arithmetic 
                int a = 0;
                do {
                    int b = 0;
                    while(b<newCol+1){
                            (*result)[a][b] = 0;
                        
                        int c = 0;
                        while(c<colSize){
                            //ex  1 1   2 2
                            //    1 1   2 2
                            //hold me += (A[0][0]) * (B[0][0]) = 1*2 = resultingMatrix[0][0] = 2
                            //this done  until c is done and on
                            //hold me holds the result 
                            //and pass it on to the poostion where resulting matrix hold
                            holdMe += mat1[mat1.getRowLow() + a][mat1.getColLow() + c] * mat2[mat2.getRowLow() + c][mat2.getColLow() + b];
                            (*result)[a][b] = holdMe;
                            //increment
                            c++;
                            
                        }//end inner while
                        holdMe = 0;//clear hold me for the new numbers that will be summed and multiplied.

                    b++;
                    }//end 2nd inner while

                a++;
                }//end do
                while(a < newRow+1);
            
        cout << "\nResulting Matrices"<<endl;
        result->printMe();//return the resulting matrix 
        }//end else
}//end operator*

int main(){
    //in this porgram you have two option you can 
    //A: create a object of the safe matrix only inputting two paramters row and col 
    //so safeMatrix<ChoseYourDataType> matrix  = (n,m)

    // or you can constructor a 4 paramter matrix (row_low,row_high,col_low,col_high)
    //so safeMatrix<ChoseYourDataType> matrix  = (a,b,c,d)


    //2 param constructor test
    //for this constructor there is no need to specify the low paramters 
    //low is automatically set to 0
    //only takes row and cols 
    //so in this example 1, 1 is 2X2 matrix
    safeMatrix<int> matrixTest (1,1);
    //this is a 2 X 3 matrix 
    safeMatrix<int> matrixTest_2 (1,2);


    //debug
    // row_high = matrixTest.getRowHigh();
    // row_low = matrixTest.getRowLow();
    // cout<<"myrow high is: "<<row_high<<endl;
    // cout<<"myrow low is: "<<row_low<<endl;

    //2X2
    // 1 2
    // 3 4
    matrixTest[0][0] = 1; 
    matrixTest[0][1] = 2; 
    matrixTest[1][0] = 3; 
    matrixTest[1][1] = 4; 
    //2X3
    //5 6 7
    //8 9 10
    matrixTest_2[0][0] = 5; 
    matrixTest_2[0][1] = 6; 
    matrixTest_2[0][2] = 7; 
    matrixTest_2[1][0] = 8;  
    matrixTest_2[1][1] = 9; 
    matrixTest_2[1][2] = 10;

    cout << "First Matrix"<<endl;
    matrixTest.printMe();
    cout << "\nSecond Matrix"<<endl;
    matrixTest_2.printMe();

    //multiply the above matrices
    multiplyMatrices(matrixTest, matrixTest_2);



    //2nd example two 3X3 Matrices
    
    //Four Paramter construcor test
    safeMatrix<int> myNewMatrix (0,2,0,2);
    myNewMatrix[0][0] = 1; myNewMatrix[1][0] = 1; myNewMatrix[2][0] = 1;
    myNewMatrix[0][1] = 1; myNewMatrix[1][1] = 1; myNewMatrix[2][1] = 1;
    myNewMatrix[0][2] = 1; myNewMatrix[1][2] = 1; myNewMatrix[2][2] = 1;

    safeMatrix<int> myNewMatrix2 (0,2,0,2);
    myNewMatrix2[0][0] = 1; myNewMatrix2[1][0] = 4;  myNewMatrix2[2][0] = 7;
    myNewMatrix2[0][1] = 2; myNewMatrix2[1][1] = 5;  myNewMatrix2[2][1] = 8;
    myNewMatrix2[0][2] = 3; myNewMatrix2[1][2] = 6;  myNewMatrix2[2][2] = 9;

    cout << "\nFirst Matrix"<<endl;
    myNewMatrix.printMe();
    cout << "\nSecond Matrix"<<endl;
    myNewMatrix2.printMe();
    //multiply the matrices
    multiplyMatrices(myNewMatrix, myNewMatrix2);
   

    return 0;
}