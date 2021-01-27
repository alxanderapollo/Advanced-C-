//written by Alex Salazar 11/2
// implementation
#include <string>
#include <stdlib.h>
#include "BigInt.h"
#include <iostream>
#include <sstream>
using namespace std;


BigInt::BigInt(){
    //initlixing an empy char array of strings 

//--->before memory manager
    //store as new block
    myStr = new char[1];
    length = 0;//nothing in the string just yet
    *myStr = '\0';

// //--->after memory manager
//     //object ptr to the myBlock class
//     myBlock* storeMe;
//     storeMe = new myBlock(length, sizeof(myStr));//return size of the ptr and length
//     length = 0;//nothing in the string just yet
//     myStr = (char *)storeMe->theObject; //ptr from  for keepsake 
//     *myStr = '\0';
}//end default constructor
BigInt::BigInt(char *userInput){
//----before memory manager 
// +1 to ensure room for null terminator
   myStr = new char[ strlen( userInput ) + 1 ];  //plus one for the terminating null
   strcpy(myStr, userInput); //copies the parameter string in userinput
   length = strlen(myStr); //returns the length of string

//------->after Memory Manager
    // //store as new block
    // length = strlen( userInput ) + 1;
    // myBlock storeMe(length, (sizeof myStr) );
    // myStr = (char *)storeMe.theObject; //char pointer points to a pointer in the memory manager

   //cout<<"The String is here : "<<*myStr<<endl;
}//end constructor

//int conversion constructor
BigInt::BigInt(int myInt){
  //for conversion
  //change to a string
  string temp = to_string(myInt);
  int length; 
  length = temp.length();
  //create char array
  myStr = new char [ length + 1 ];
  strcpy(myStr, temp.c_str());
  cout<<myStr<<endl;
  length = strlen(myStr);
}//end int conversion constructor

//copy Constructor
BigInt::BigInt(const BigInt &obj){
    //---------------->before memory manager
  // copy an existing String.str into a new
  // one after first allocating sufficient storage
  strcpy( myStr = new char[ obj.length + 1 ],  obj.myStr );
  strcpy( myStr, obj.myStr );
  this->length = obj.length;

  //---------->After memory manager
    // this->length = obj.length; //length of the string we are copying
    // //create the space
    // myBlock storeMe(this->length, (sizeof myStr));
    // myStr = (char *)storeMe.theObject;//link the object
    // strcpy( myStr,  obj.myStr );//copy the string
}//end copy constructor
//destructor
BigInt:: ~BigInt(){
    //--->before memory manager
    //cout<<"Freeing up mem"<<endl;
    delete [] myStr;//delete the array of chars
    //-------after memory manager
   // myBlock::operator delete(myStr);
}//end default constructor
//size of the object
int& BigInt::mySize(){
    return this->length;
}//end size
//return the string
char* BigInt::getString(){
    return this->myStr;
}
//assignment operator
BigInt& BigInt ::operator=(BigInt const  &obj){
//---->before memory manager
    // check whether String assigned to itself
   if ( this !=  &obj ) {
      delete[ ] myStr;    // free current storage
      length = obj.length; //set to equal lengths
      myStr = new char[ length + 1 ];  // allocate new storage
      strcpy( myStr, obj.myStr);    // copy contents
   }
//------>After MEmory Manager
//     if ( this !=  &obj ) {
//        myBlock::operator delete(myStr);    // free current storage
//       this->length = obj.length; //set to equal lengths
//       myBlock storeMe(this->length, (sizeof myStr));
//       myStr =  (char *)storeMe.theObject;  // allocate new storage
//       strcpy( myStr, obj.myStr);    // copy contents
//    }
   return *this;
}//end assignment operator

//operations multiply
BigInt& BigInt::operator*(BigInt const &obj){
    BigInt *result;//result to be sent back
    string a, b,resultString =""; 
    int len1, len2, rsLength,mySize;
    //1. convert strings
    //char arrays that have been converted
    a = convertToString(this->myStr,this->length);//convert a to a string
    b = convertToString(obj.myStr,obj.length);//convert b to a string 
    //first base case  if either of the numbers are zero no point in searching
    if(a == "0" || b == "0"){
        resultString = "0";
        char char_array[rsLength + 1];
         strcpy(char_array, resultString.c_str());
         result = new BigInt(char_array);
        return *result;
    }else{
    //2.multiply
    resultString = multiplyAndCarry(a, b);
    rsLength = resultString.length();
    char char_array[rsLength + 1];
    //copying the contents of the
    // string to char array
    strcpy(char_array, resultString.c_str());

    //3. return result
    result = new  BigInt(char_array);
    return *result;
  }
}//end multiplication
string BigInt :: multiplyAndCarry(string& a, string& b){
    //simple bases cases have been taken care of in the mother function calling this one
        //save the length of a and b
        int a_length = a.length();
        int b_length = b.length();
        //fill in construtor, im setting the size of string to the length of a + b
        //since mostly when multiplying two numbers say a and b
        //the result is some length of what would be a+b
        string resultString(a_length+b_length,'0');
        //carryMe to hold numbers that pass over, mySum will hold the running sum of each calculation
        int carryMe, mySum;
        //multiply and hold me are temp variables to make what im doing simopluer to follow 
        int multiplyHold,holdMe;
        //hold ai and b i through the iteration
        int myA, myB;
        //first while loops iterators
        int iterator = b_length - 1, iterator2, myPosition;

        //how this algo works -  elementry long multiplication
        // since multiplication is commutative meaning a*b = b*a, for this algo
        //iterating through each length will yeild a the same outcome
        //1. two for loops starting at the end a and b 
        //2. multiply both a and b , which multiplyhold will store
        //3. add everything with mySum
        //4.hold me will save what will be stored in the current position
        //5. carryMe will hold the quotient to be added to the next digit
        while(iterator>=0){
            //reset every iteration 
            carryMe = 0;
            //iterator for inner while loop
             iterator2 = a_length - 1;
            while(iterator2>=0){
                //pull out a number from a and b all the way from the end to the begining
                myA = a[iterator2] - '0';
                myB = b[iterator] - '0';
                //multiply the two numbers 
                multiplyHold = myA*myB;
                //since each pass we are making sure to store each number correctly,
                //the container that will hold the result must be accounted for as well
                //so we add the contents in that as well.
                myPosition = resultString[iterator+iterator2+1]-'0';
                //my summ will hold everything nt
                mySum =  multiplyHold+ carryMe + myPosition;
                //want to store the remainder and the quotient 
                holdMe = mySum%10;// what will be saved at current position
                carryMe = mySum/10; //saved to be added to the next digit

                resultString[iterator+iterator2+1] = holdMe+'0';
                iterator2--;//move backwards on the string
            }//end inner while

            resultString[iterator]+=carryMe;
            iterator--;
        }//end outter while
return resultString;
}//end multiply and carry
//takes a c-string and converts it to a string and returns it
string BigInt ::convertToString(char*s, int length){
    string myResult;
    int i = 0;
    while (i<length){
        myResult = myResult + s[i];
        i++;
    }
    return myResult;
}//end convert to string
//add
BigInt& BigInt::operator+(BigInt const &obj){
    //initliziers
    string a,b; //represent the two objects c-arrays
    BigInt *result; //result to be returned at the end of the function
    //string to hold contents
    string resultString;
    bool quickCheck;
    int rsLength;

    //1. first convert the c-strings into normal strings
    //char arrays are converted into strings, the algorithm works with strings and then afterwords changed back to c-strings for the result.
    a = convertToString(this->myStr,this->length);//convert current obj c string to a string
    b = convertToString(obj.myStr,obj.length);//convert 2nd obj c string  to a string 

    //for the algorithm to work we need to make sure that 2nd string is the largest since it
    //will be the one that contains the summ of the two numbers
    quickCheck  = (this->length > obj.length) ? true : false;
    if(quickCheck) swap(a, b);//swap the larger length, the second char array must be the biggest length
    
     //2. Reverse the strings, working with the string backwards
    reverse(a.begin(), a.end()); reverse(b.begin(), b.end());
    //3. sum and carray for addition
    resultString = sumAndCarry(a,b); 

    //4.convert back to a c-string
    //need the length + 1 for the null terminating string \0
    rsLength = resultString.length();
    char char_array[rsLength + 1];
    //copy the string to  c - string s 
    strcpy(char_array, resultString.c_str());

    //4. make a new object with the result and return
    result = new BigInt(char_array);
    return *result;
}//end operator+
string BigInt ::sumAndCarry(string& a,string& b){
    //intilizations
    int a_length = a.length(), b_length = b.length(),
    carryMe = 0, mySum, iterator = 0; //need the length of the strings of the strings
    string strResult = "";
    //carry, sum, iterator
    //how the algo works
    //1. we first add up all the numbers that are pulled using asci integer representation 
    //2. then we store whatever the result is.
    // for example if the sum is 19, take the mod of that so 19 mod 10 = 9, store 9 on our result
    //the 10 in 19 is stored as a one inside of carry for the next iteration and added to the next number 
    //3. when we are done with the first loop the second loop picks up where the first one left off
    //and appends the remaining numbers from the bigger string into the result
    //4. make a quick check to see if there are any remaining numbers that were left out from being added
    //5.finally reverse the strings
    while(iterator < a_length){
        mySum = a[iterator]-'0'; //get a digit
        mySum+= b[iterator]-'0';//get b digit
        mySum+= carryMe;
        //store our resulting sum
        strResult.push_back((mySum%10) + '0'); //the remainder is stored as char
        carryMe = mySum/10; // and carry is a remainder added to the next iteration
        //move iterator forward 
        iterator++;
    }//end while
    //this while loop adds the remaining numbers  picks up from where the first loop

   //add the remaining elements of the string that was bigger
    iterator = a_length; //iterator picks up where it stopped last
    while(iterator < b_length){
        mySum = b[iterator] - '0'; //get the element
        mySum += carryMe; //add any carries left over 
        strResult.push_back(mySum%10 + '0');
        carryMe = mySum/10;
        iterator++;
    }//end while

    // Any number left over append to the result
    if(carryMe) strResult.push_back(carryMe+'0');

    // String is still reversed finally reverse the string to what it was before
    reverse(strResult.begin(), strResult.end());
    return strResult;
}//end sum and carry
//subtract
BigInt& BigInt::operator-(BigInt const &obj){
    //initilizers
    BigInt *result; //result to be returned
    string a,b;
    string strResult = "";
    int rsLength;//result length
    int myIterator;
    //1. working with strings so convert to strings
    //char arrays that have been converted
    a = convertToString(this->myStr,this->length);//convert a to a string
    b = convertToString(obj.myStr,obj.length);//convert b to a string 

    //simple base case if either a or b is zero return the number that isnt zero
    if(a == "0 "){
    strResult = b;
    rsLength = strResult.length();
    char char_array[rsLength + 1];
    //copying the contents of the
    // string to char array
    strcpy(char_array, strResult.c_str());

    //4.make a new object of the type  and return that object
    result = new BigInt(char_array);
    return *result;

    }
    else if ( b == "0"){
    strResult = a;
    rsLength = strResult.length();
    char char_array[rsLength + 1];
    //copying the contents of the
    // string to char array
    strcpy(char_array, strResult.c_str());
    result = new BigInt(char_array);
    return *result;
    }
    else{

    //2. call subtract function
    strResult = subtractAndCarry(a,b);

    //3. convert back to a c-String for the object
    rsLength = strResult.length();
    char char_array[rsLength + 1];
    //copying the contents of the
    // string to char array
    strcpy(char_array, strResult.c_str());

    //4.make a new object of the type  and return that object
    result = new BigInt(char_array);
    return *result;
    }
}//end subtract
string BigInt::subtractAndCarry(string& a, string& b){
        int holdme;
        int myA, myB, myIterator, myCarry = 0;
        int saveMe;
        string myResult ="";
        //algorithm
        //1.check the lengths and if a is greater than b swap a and b and reverse the strings, also store the smaller length number of the 2
        //2. take the last elt of a and b and subtract it, if the result of that operatio is less than zero add 10 and a carry over to the next digit
        //3. since  at this point i've iterated through one of the strings its time to go through the longer length of the two
        //4. this loop goes until all the numbers of the longer length have been added to the resulting sum of the first loop
        //5. finally return the result
        //first case a or b is bigger
        bool quickCheck  = (a.length() > b.length()) ? true : false;
        if (quickCheck) swap(a, b);
        //reverse the strings
        reverse(a.begin(), a.end()); reverse(b.begin(), b.end());
        //store the smaller of the two lenghts
        if (a.length() < b.length()){
            saveMe = a.length();
        }else{
            saveMe = b.length();
        }
        //if the length of a or b is not zero 
        //subtract postions
        //otherwise append remianing string
        int itme = 0; 
        while(itme < a.length()){
        myA = (a[itme] - '0');//elt a
        myB = (b[itme] - '0'); //elt b
        //cout<<" A : "<<myA<<endl;
        //cout<<"B:  "<<myB<<endl;

        holdme = myB - myA - myCarry; //subtract elts
        if(holdme < 0) {
            holdme = holdme +10; myCarry =1;
            //cout<<" holdme : "<<holdme<<endl;
        } else myCarry = 0;

        myResult += to_string(holdme); //store the elts
        //myResult.erase(remove(myResult.begin(), myResult.end(), '-'));//erase potential negative signs
        itme++;
        //cout<<myResult<<endl;

        }//end while

    //add the rest of the number to result
    //this loop will go through the bigger length and append the rest of the elements to the end
    itme = saveMe;
    while(itme < b.length()){ 
        // cout<<itme<<endl;
        myB = (b[itme] - '0') - myCarry;
        if(myB < 0) {
            holdme = myB + 10; myCarry =1;
         //cout<<"over here "<<holdme<<endl;
        //cout<<myCarry<<endl;
        //cout<<myResult<<endl;
         myResult += to_string(holdme);
        } else myCarry = 0;
       
        itme++; //move iterator forward
    }//end while
    reverse(myResult.begin(), myResult.end());
  //cout<<myResult<<endl;
    //end else 
    return myResult;
}//end subtractAndCarry
void BigInt::printMe(){
    //print string
    cout <<this->myStr<<endl;
}//end printMe

//output 
ostream& operator <<(ostream &out, const  BigInt&c){ 
    out <<c.myStr;
    return out; 
} //end ostream