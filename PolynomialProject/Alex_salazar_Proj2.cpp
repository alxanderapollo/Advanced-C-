//Written by Alex Salazar 10/1
//waxman adv c++

//How this program works
//in this program i designed it to read 2 lines at a time 
//each line is reading in 2 pairs of numbers representing the int and the exponent
//the numbers are stored in 2 diffrent vectors respectively named integers, and exponenets
//the data is stored the way it is read which means it will have to be sorted, and since im reading in ints and exponenets at the same time
//the int and exponenets will correlate in the same spot they are stored respectively.
//so once i do a sort  on the exponenet, it will also happen in the integers
//once i have 2 lines of file read in worth of data, the vectors are sorted using a custom built  selection sort function with and swap function 
//in the main the files are read, in the while loop i count everytime im at the end of a line, and when ive finally reached a count of  2
//2 lines i call the arithmetic function, the arithemtic function sorts the vectors, and then computation is carried out for add, div, and mult
//then all the information is printed onto a output file 
//the vectors are cleared and the next two lines are read
//this is done until we are done reading a file. 
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

//stream objects
ifstream inputFile;// file to be opened & read
ofstream outputFile("output.txt");// file to print results.

//print the elts
void printMe( vector<int> &integers,  vector<int> &exponenets);

//for selection sort we dont need the length because we can use the the size of the vector 
void SelectionSort( vector<int> &integers,  vector<int> &exponenets);

//swap function for selection sort
void SwapQuick(vector<int> &integers, vector<int> &exponenets, int first, int second);

//sum, difference and product of the polynomials 
void arithmetic(vector<int> &integers, vector<int> &exponenets, vector<int> &integers2, vector<int> &exponenets2);


//sortthe elements from biggest exponenet to smallest
void SelectionSort( vector<int> &integers,  vector<int> &exponenets){
    int vectorSize = exponenets.size();
    int smallest; // will hold the postion of the largest elt
    for(int i = 0; i< vectorSize - 1; i++){
        smallest = i; //starts at pos 0
        for(int j = i + 1; j < exponenets.size(); j++){
            if(exponenets[j] > exponenets[smallest]) 
                smallest = j;
            SwapQuick(integers, exponenets,smallest, i);//swap me 
        }//end inner for
    }//end outter for
}//end SelectionSort
void SwapQuick( vector<int> &integers,  vector<int> &exponenets, int first, int second){
    //temp is for the exponent vector
    //temp2 is fo the integer vector

    //exponenet
     int temp, temp2;
	 temp = exponenets.at(first);
	 exponenets[first] = exponenets[second];
	 exponenets[second] = temp;

     //integer
     temp2 = integers.at(first);
	 integers[first] = integers[second];
	 integers[second] = temp2;

}//end SwapQuick
void arithmetic(vector<int> &integers, vector<int> &exponenets ,vector<int> &integers2, vector<int> &exponenets2){
    //sort the values
    SelectionSort(integers,exponenets);

    SelectionSort(integers2,exponenets2);
    //hold running values
    int sum, difference, multiplication;
    //int *prod = new int[];

    //store result - although might not need to store reading onto a file doesnt require string conversion....
    string sumResult, MultResult,DifferenceResult;

    int j;
    //the idea is to group like terms
    //two pointer solution


    3,3,2,1,0

    //if there is a more than one # that has the same exponent in the same vector space 
        //do arithmetic  for that single vector
    //same for the second vector space
    3,2,1,0

    // for (int i = 0; i<exponenets.size(); i++ ){
    //     //sum, mult and diffrence will start at 0
    //     sum = integers[i];
    //     multiplication = integers[i];
    //     difference = integers[i];

    //     j = i+1;
    //     if (exponenets[i] == exponenets[j]){
    //         while(exponenets[i] == exponenets[j] && j<exponenets.size()){

    //         sum += integers[j];
    //         multiplication *= integers[j];
    //         difference = difference -(integers[j]);
    //         //cout<< integers[j] <<endl;
    //         //cout<< difference <<endl;
    //         j++;

    //         }//end while

    //         //get i to be where j ended
    //         i = j-1; //--this might be the problem
    //     }//end if

        //reset mult  and difference
        // multiplication = 1;
        // difference = 0;


        //sum
        stringstream sumStream ,multStream, diffStream;
        sumStream<<sum<<"x"<<"^"<<exponenets.at(i)<<" + ";
        sumResult += sumStream.str();

        //mult
        multStream<<multiplication<<"x"<<"^"<<exponenets.at(i)<<" + ";
        MultResult +=  multStream.str();

        //difference
        diffStream<<difference<<"x"<<"^"<<exponenets.at(i)<<" + ";
        DifferenceResult +=  diffStream.str();

    }//end outter

    // add sum to output
    sumResult.resize(sumResult.size() - 2); //cut the plus sign at the end and white space.
    outputFile <<"\nCannonical Form:"<<endl;
    outputFile<<"Sum: "<<sumResult<<endl;
    
    //add mult to output 
    MultResult.resize(MultResult.size() - 2);
    outputFile<<"Mult: "<<MultResult<<endl;
    
    //add difference to output
    DifferenceResult.resize(DifferenceResult.size() - 2);
    outputFile<<"Diff: "<<DifferenceResult<< "\n"<<endl;

}//end arithemtic

int main(){

    //now read and open the file
     string fileName = "input.txt";
	 inputFile.open(fileName);

    string word; // will be the string that prints out everything
    //step 1 Read and store
    //first we read in a file  - input.txt
    //since the numbers are in pairs read by pairs
    int num1, exp; //num1 is the integer value, exp is the exponent value

    //vectors to hold integers and exponent
    vector<int> myIntegers;
    vector<int> myExponents;

    //second set of integers and exponenets
    vector<int> myIntegers2;
    vector<int> myExponents2;

    //counting the lines, so that every two lines it does all the computation
    int countMyLines = 1;
    int remainder;

    outputFile<<"As Read by the file not standard form:"<<endl; 
	if(inputFile.fail()){
		cout <<"File name must be incorrect or Not placed in folder";
		//return;
	}else{
        //read the file
        while (inputFile >> num1 >>exp){

        //turning everything into a string for posterity
        // numbers are read as pairs
        stringstream ss;//ss stream objused to convert into a string so it can be placed onto a file
        ss<<num1<<"x"<< "^"<<exp<<"+"; //save as string so i can clean up later
        word+= ss.str();

        //store the numbers
        if(countMyLines %2 == 1 ){
            myIntegers.push_back(num1);
            myExponents.push_back(exp);
            }else{
                 myIntegers2.push_back(num1);
                 myExponents2.push_back(exp);
            }

        //we first want to  read and stop every 2 lines to compute
        char c = inputFile.get();// this will tell us when we are at the end of a line

        //if we are at the end of a line count the line
        if(c =='\n' || c == '\r'){
            countMyLines++;
                // cout<<"we have reach the end of line # : "<<countMyLines<<endl;
                //if we have read and stored a pair of lines
                word.resize(word.size() - 1);
                outputFile<<word<<endl;
                word = "";//word is constatntly erased for modding and adding purposed to the file

                //if we've counted 2 lines carry out a computation and store 
                if((countMyLines %2) == 0){
                    arithmetic(myIntegers,myExponents, myIntegers2, myExponents2);

                    word = "";
                    //empty the vectors for the consective set of data to be read.
                    myIntegers.clear();
                    myExponents.clear();

                    myIntegers2.clear();
                    myExponents2.clear();

                    outputFile<<"\nAs Read by the file not standard form:"<<endl; 
                }//end inner if
        }//end outter if
        }//end while
    }//end else 
    return 0;
}//end main
