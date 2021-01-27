#include<iostream>
using namespace std;


template <class T> class safeArray; template <class T>  class safeMatrix;
//need to declare else the ostream operator starts to complain 
template <class T>  ostream& operator<<(ostream& os, safeArray<T> s); template <class T> ostream& operator<< (ostream& os, safeMatrix<T> s);

//safe array class
template <class T> class safeArray {
private:
    int low, high; //high and low boundry
    T *p; // pointer
public:
     safeArray(){
        low = 0; //zero is where the array starts
        high = -1; //-1 so we dont hit the boundry
        p = NULL; //pointer set to point to null
    }//end default constructor

    // single parameter constructor 
    //takes in a length i
    //and sets the array to  n -1
        safeArray(int i){
            low = 0; //lower boundery
            high = i - 1;//upper boundry
            p = new T[i];//pointer initlizied to the safeArray me as high
        }//end conversion constructor

    //safeArray array constructor
    //takes in two params high and low for the array
        safeArray(int l, int h){
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

        safeArray(const safeArray<T> &s){
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


        ~safeArray(){
            delete[] p;
        }//end destructor 

    //int becomes a T
    //the brackets are overloaded
     T& operator[](int i){   
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
 
     safeArray & operator=(const safeArray &s){  
        //if the object we're looking at is already 
        //been made or equal then just return a pointer to the obj
        if (this == &s) return *this;
        //delete pointer
        delete[] p;
        //otherwise assignment operator
        //create the new obj
        //and make a pointer with the size of the array
        int size = s.high - s.low + 1;
        p = new T[size];
        //assign each of the items 
        for (int i = 0; i < size; i++) 
            p[i] = s.p[i];
        //create low and high variables and return a pointer
        low = s.low;
        high = s.high;

        return *this;
    }//end reference operator
    //
    friend ostream& operator<< <T>(ostream& os, safeArray<T> s);
};//end safe array

//safe matrix
template <class T> class safeMatrix {

     private:
        //4 global variables
        //lowerBound pairs with upperBound
        //lowerBound2 pairs with upperBound2
        //point of this is to  represent Rows and Cols
        int row_high,row_low,col_high,col_low,newRow, newCol, rowSize, Colsize; 
        //row =  upperbound - lowerBound
        //col = upperBound2 - lowerBound2
    safeArray <safeArray <T> > myMatrix; //safe array of safe arrays

public:
    //2 param constructor user doesn't need to specify low
    // low is set to zero in this constructor
    //only need to pick the the size of the row and col
     //this constructor gives the user to pick the low, 
     //the low is the starting point in the program
     //the first hight would be the row specific lenght
    //the second high is for the col
    safeMatrix(int row, int col) {
          if (row < 0){
            cout<<"error out of bounds, row high cannot be a negative value aborting program......."<<endl;
            exit(1);
          }else if( col < 0){
            cout<<"error out of bounds, col high cannot be a negative value aborting program......"<<endl;
            exit(1);
          }
          else{
            //1. set the params
            //row = row_high - row_low -------->upperBoundry
             this->row_high = row;
             this->row_low = 0;
             //col = col_high - col_low  ------->lowerBoundry 
             this->col_high = col;
             this->col_low = 0;
              myMatrix = safeArray<safeArray<T> >(this->row_low, this->row_high);//the rows
              int i = 0;
              while (i< this->row_high+1){
                safeArray<T> myTempMatrix(this->col_low, this->col_high);//the cols
                myMatrix[i] = myTempMatrix;//since its an array within an array, need to 
                 //derefrence the internal
                //at the end of the his loop the the NXM matrix size is complete
                i++;//next elt
            }//end while
          }//end else
    }//end 2 param constructor

    //return columns and rows
    int& getColHigh(){
        return this->col_high;
    }

    int& getColLow(){
        return this->col_low;
    }
    int& getRowHigh(){
        return this->row_high;
    }
    int& getRowLow(){
        return this->row_low;
    }

    safeMatrix() {
    }
   //this is for the user that wants to define the low and high of each row and column
        safeMatrix(int row_low, int row_high, int col_low, int col_high){
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
                    myMatrix[i] = myTempMatrix; 
                    i++;
                }//end while
          }//end else
        }//end param constructor

        //copy constructor
    safeMatrix(safeMatrix<T>& obj){
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
                myMatrix[i] = obj[i];
                i++;
            }//end while
    }//end copy constructor
    //call destructor
    ~safeMatrix() {}//destructor 
        safeArray <T> &operator[](int i) {
        if (i < row_low ){
            cout<<"error out of bounds, row high cannot be a negative value aborting program......."<<endl;
            exit(1);
        }else if (i > row_high) {
           cout<<"error out of bounds, row high cannot be a negative value aborting program......."<<endl;
            exit(1);
        }
        return myMatrix[i];
    }//end bracket overload

       void printMe(){
            int i = this->row_low;
            while(i < this->row_high + 1){
                //equals each member of the row, 
                //once we've reached the last column
                //print the entire row out.
                safeArray<T> result = myMatrix[i];
                cout<<"Row position "<< i+1<<": " << result <<endl;
                i++;
            }//end while
        }//end class
};//end safe matrix

//very neat table class
class VeryNeatTable{
	public:
		safeMatrix<int> myTable; //my Table which is of type SafeMatrix
        //row will hold the size of the rows
        //col will hold the size of the cols
        //hold col and row will be place holders
		int row, col, holdMyRow, holdMyCol;
		VeryNeatTable(int x,int y){ //2 param constructor
            this->myTable = safeMatrix<int>(x,y); //initlizes with a two param constuctor
            //length of the row, //length of the columns
            row = x , col = y , holdMyRow = 0, holdMyCol = 0;
            int i = 0,j; //iterators for the loop
            while(i < x){
                j = 0;
                while(j < y){
                    this->myTable[i][j] = INT32_MAX; //fill the array
                    j++; //move forward
                }//end inner while 
                i++;
            }//end outter while
		}//end constructor

    //simple find function,
    //if the element is in the table return true
    //other wise return false
    bool find(int h){
        int i, j;
        i = 0;
        while( i <= this->row){
            j = 0;
            //if h is the paramter we are looking for then 
            //return true, other wise false
            while(j <= this->col){
                if(myTable[i][j] == h) return true;
                else return false;
            j++;
            }//end inner while
        i++;
        }// end outer while
        return false;
	}// end find function

    //algorithm 
    //start at one  end
    //when we hit the 
	int getMin(){
        //mXn time
        int i,j;
        // will hold the size of the rows
        //j will be the size of the cols
        i = this->row; j = this->col;
        //my smallest equals some obscene big number
        //  any element in the table
        //will assume or be smaller than mysmallest
        //nxm search until i found the element
        int mySmallest = INT32_MAX; 
        while(i!= 0){
            while(j!=0){
                if (myTable[i][j] < mySmallest ) mySmallest = myTable[i][j] ; // we are at 0 return the smallest number
            j--;// move back
            }//end inner while
        i--;//move backwards
        }//end outter while
    return mySmallest;
	}// end find min 
	
    //returns true if element is in vnt
    void printMe(){
        for (int i = 0; i <row; i++) {
            for (int j = 0; j <col; j++) {
                cout << myTable[i][j] << " ";
            }//end inner for loop
        cout<<endl;
	    }//end for loop
    }//end print me


    // add numbers to the VNT 
    void add(int num){
        //varaibles for this function
        int myTemp,myTemp2; //tempory var hold
        int i, j, k, h; //iterators 
        bool checkMe; // check condition

		if(holdMyCol < col) holdMyRow++;
		else if(holdMyRow < row){
			cout << " At Max capacity";
			exit(1);//abort program if the container is full
		}else{
            //varaibles 
			holdMyCol = 0;
			myTable[holdMyRow][holdMyCol] = num;
            i = 0;
            //fill the cols
            while(i <= this->col){
                j = 0;
                //check every element before and present
                //to insert
                // if smaller swap places
                //otherwise continue
                while(j <= this->col){
                    //condition
                    myTemp = myTable[holdMyRow][i];
                    myTemp2 = myTable[holdMyRow][j];
                    checkMe = myTemp > myTemp2 ? true: false;
                    if(checkMe) swap(myTemp,myTemp2);// if we found a value that is smaller than swap out	
                    j++;
                }//inner while
                i++;//move i forward
                holdMyRow = 0;
            }//outer while
            
            //rows
            k = 0;
            //same idea as above 
            // if an element is smaller than
            //what we are looking at then swap the elements
            while(k <= this->row){
                h = 0;// reset h
                while(h <= this->row){
                    myTemp = myTable[k][holdMyCol];
                    myTemp2 = myTable[j][holdMyCol];
                    //quick check condition to see if the elements are smaller
                    checkMe = myTemp > myTemp2 ? true: false;
                    if(checkMe) swap(myTemp,myTemp2);
                    h++;
                }//inner while
                k++;
            }//outter while	
	
		    holdMyCol++;//move forward so we can check the next elt
		}//end else
        //once we've done any sorting from the previoud adding add the new element 
        //into the table 
		myTable[holdMyRow][holdMyCol] = num;
        //and add to hold my col
		holdMyCol++;
    }//end Add function
	
    //sort function

    //simple void function if the element prior is 
    //smaller than the element after do a quick a swap
	void sort(int myArray[], int length){
        int i, j;
        i=0;
        while(i < length ){
            j=0;
            while(j < length){
                if(myArray[i] < myArray[j]) swap(myArray[i],myArray[j]);	
                j++;
            }//end inner while
            i++;
        }//end outter while
    }//sort
};//end VNT class 

//Had trouble with the ostream had to bring them outside, here is the one for each class
//safe matrix print out
template <class T>
ostream& operator<<(ostream & os, safeMatrix <T> s){
    for (int i = s.row_low; i <= s.row_high; i++){
        for (int j = s.col_low; j <= s.col_high; j++){
            os << s.matrix[i][j] << " ";
        }//end inner for function
        os << endl;
    }//end outter for
    return os;
}//end safeMatrix function
//safe array print out
template <class T>
ostream& operator<<(ostream &os, safeArray <T> s){
    int size = s.high - s.low + 1;
    for (int i = 0; i < size; i++)
        cout << s.p[i] << " ";
    return os;
}//end safe array print out function
    // vnt print out
  ostream& operator<<(ostream & os, VeryNeatTable  &a){
	for (int i = a.row; i != -1; i--) {
	    for (int j = a.col; j != -1; j--) {
		    if(a.myTable[i][j] != 0) cout << a.myTable[i][j] << " ";
	    }//end inner for loops 
        cout << endl;
	}//end outter for loop
	return os;
 }//end vnt print function table

int main(){

/*
First Fill a VNT a approximately halfway
using the a.add() function and using a sequence
of neither ascending or descending numbers
(i.e. some numbers should be greater than the number added
to the VNT before them and some should be less than the number
added to the VNT before them)
Then print the VNT a
then remove a number using a.getmin();
then remove another number using a.getmin();
then print out the VNT a again
*/

  VeryNeatTable a(10,10);
  int addedNumber = 0;
  for(int i = 0; i <= 9; i++){
    addedNumber = (i*31)%50;
    a.add(addedNumber);
    //cout<<addedNumber<<endl;
  }
//   a.add(6);
//   a.add(1);
 
//   a.add(-1);
    cout<<"Printing VNT"<<endl;
  
  //a.printMe();
  //cout<<
  


//use whatever method you want to print the VNT
//it can be a member function or you can just loop
//through or however else you want to print it
//this is just an example of what it could look like
//it doesn't have to look like this


  //remove 2 numbers (if you removed a different number that's also okay)
  a.getMin();
  a.getMin();
  //now print it again
  cout<<a<<endl;

/*
now use find on some numbers that are and are not in the VNT
print out which one's you're using find on and whether find returns
true or false
*/
  int firstSearched = 100;
  int secondSearched = 0;
  int thirdSearched = 31;

  //the following statements will print something like:
  //"100 is in VNT is: false"
  cout<< firstSearched << " is in VNT is: " << a.find(firstSearched) << endl;
  cout<< secondSearched << " is in VNT is: " << a.find(secondSearched) << endl;
  cout<< thirdSearched << " is in VNT is: " << a.find(thirdSearched) << endl;


  /*
  Now create a 1d int array with 50 integers in neither ascending or 
  descending order as explained earlier and print out the unsorted version
  */
  int arraySize = 50;
  int* k = new int[arraySize];
  cout<<"The array initially is:"<< endl;
  for(int i = 0; i < arraySize; i++){
    addedNumber = (i*31)%50;
    k[i] = addedNumber;
    cout<< addedNumber << " ";
  }
  cout<<endl<<endl;

  /*
  Now use the sort method from the VNT class to 
  sort the array k. It doesn't have to look like how I wrote it
  you can create a VNT instance and use that or you can call the function
  statically from the VNT class
  */

  a.sort(k, arraySize);
  
  //now reprint the now sorted array k

  cout<<"The array, now sorted by VNT, is:"<<endl;
  for(int i = 0; i < arraySize; i++){
    cout<< k[i] << " ";
  }
  cout<<endl;

  //You're done

	return 0;
	
}//end main