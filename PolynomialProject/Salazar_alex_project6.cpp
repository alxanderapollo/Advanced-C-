 #include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <map> //need it so i can call the hash map

using namespace std;

//stream operators
ifstream inputFile;// file to be opened & read
ofstream outputFile("output.txt");// file to print results.

//hashmaps to hold results or pass data
map<int, vector<int> > poly1, cann, add, sub, mult; 

//for printing and saving information purposes
//  string sumResult, MultResult, DifferenceResult,outPutResult;
 stringstream sumStream ,multStream, diffStream, outputStream;

int main (){
    //read file

    string fileName = "input.txt";
	inputFile.open(fileName);

    int coef, exp; //read in polynomials
    int countMyLines = 0;//will count the lines every iteration, important for knowning when to start doing all the arithmetic stuff
    string word; // will be the string that prints out everything
    
    //prompt to make sure the entred filename is correct, else read contents
    if(inputFile.fail()){
        cout <<"File name must be incorrect or Not placed in folder";
    }else{

        while(inputFile >> coef >>exp){
            
            //store values inside of the hashmap
            poly1[exp].push_back(coef);
            cann[exp].push_back(coef);

            //check to see if we are at the end of line
            char c = inputFile.get();
            if(c =='\n' || c == '\r'){
                countMyLines++;//end of a line increment
                //if read two lines do arithmetic magic

                stringstream cannStream; string cannString;
                int multiplicationTotal;
                //if we are at the end of a new line dump the cann on the screen
                int myrunningTotal = 0; 
                cannStream<<"Cann: ";
                for(auto mapIt = cann.rbegin(); mapIt != cann.rend(); mapIt++){
                    myrunningTotal = 0;  
                    multiplicationTotal =1;
                    // cout<<mapIt->first<<": ";
                   for(auto c : mapIt->second){
                       myrunningTotal += c;
                   }//end inner for

                  mult[mapIt->first].push_back(myrunningTotal);

                      if(myrunningTotal == 1) cannStream<<"x^"<<mapIt->first<<" + ";
                       else if (mapIt->first == 0) cannStream<<myrunningTotal;
                       else  cannStream<<myrunningTotal<<"x^"<<mapIt->first<<" + ";
                    
                }//end  for

                
                cannString += cannStream.str();
                cannString.resize(cannString.size() - 2);
                outputFile<<cannString<<endl;
                cann.clear();
                
                if(countMyLines % 2 == 0){
                stringstream sumStream ,multStream, diffStream, outputStream;
                string result;// hold the result of the string

                
                sumStream<<"Addition ";
                int runningTotal = 0;//running total for sum
                for(auto mapIt = poly1.rbegin(); mapIt != poly1.rend(); mapIt++){ 
                    runningTotal = 0; 
                    // cout<<mapIt->first<<": ";
                   for(auto c : mapIt->second){
                     runningTotal+= c;
                     //cout<<runningTotal<<" ";

                    }//end inner for
                    //cout<<runningTotal<<endl; 

                    //dont want to store zeroes 
                    if(mapIt->first == 0) sumStream<<runningTotal<< " + ";
                    else sumStream<<runningTotal<<"x^"<<mapIt->first<<" + ";
                    //cout<<mapIt->first<<": ";

                    
                }//end  for
                //cout<<endl;
                result += sumStream.str();// store the result
                result.resize(result.size() - 2);
                
                outputFile<<result<<endl;
                result = "";

               diffStream<<"subtraction ";
                //subtraction
                int runningTotalSubtraction = 0;//running total for subtraction
                for(auto ii=poly1.rbegin(); ii!=poly1.rend(); ++ii){
                    //cout << (*ii).first << ": ";
                    vector <int> inVect = (*ii).second;
                    unsigned j=0;
                    //runningTotalSubtraction = inVect[j];
                    for (; j<inVect.size(); j++){
                        int first, second;
                        first = inVect[j]; // 0
                        if(j+1 >= inVect.size()){
                        //sub[(*ii).first].push_back(inVect[j]);
                            //cout<<inVect[j];
                            runningTotalSubtraction = inVect[j];
                            break;
                        }else{
                            j = j+1;
                            second = inVect[j]; // 1
                            if(second - first == 0){ continue;//sub[(*ii).first].push_back(0);
                            }
                            else {
                            if(second< first){
                                //cout<<first - second;
                                runningTotalSubtraction = first - second;
                            }else if(second> first){
                                //cout<<(second - first);
                                runningTotalSubtraction = (second - first);
                            }//end else if
                            }//end else   
                        }//end else

                    }//end for

                    //if the number is negative dont add a negative sign

                    //else add a negative sign


                     if (runningTotalSubtraction == 0) diffStream<<" 0";
                     else if (runningTotalSubtraction < 0) diffStream<<runningTotalSubtraction<<"x^"<<(*ii).first<<" + ";
                     else diffStream<<"- "<<runningTotalSubtraction<<"x^"<<(*ii).first<<" ";


                    // if((*ii).first == 0) diffStream<< "-"<<runningTotalSubtraction;
                    // // else if (runningTotalSubtraction < 0 )cout<<  ----------------------->this case if the number is already less than 0 dont add a negative sign
                    // else if (runningTotalSubtraction == 0) diffStream<<" 0";
                    // else diffStream<<" - "<<runningTotalSubtraction<<"x^"<<(*ii).first;

                    //cout<<endl;
                }//end outter fo
                //cout<<endl;
                result += diffStream.str();// store the result
                result.resize(result.size() - 1);
                
                outputFile<<result<<endl;
                result = "";


                multStream<<"Multiplication ";
                //running total for sum
                for(auto mapIt = mult.rbegin(); mapIt != mult.rend(); mapIt++){ 
                   int runningMult = 1; //multipling numbers
                    // cout<<mapIt->first<<": ";
                   for(auto c : mapIt->second){
                     runningMult*= c;
                     //cout<<runningTotal<<" ";

                    }//end inner fo

                    //cout<<runningTotal<<endl; 

                    //dont want to store zeroes 
                    if(mapIt->first == 0) multStream<<runningMult<< " + ";
                    else if(runningMult == 0) continue;
                    else multStream<<runningMult<<"x^"<<mapIt->first<<" + ";
                    //cout<<mapIt->first<<": ";
                    
                }//end  for
                //cout<<endl;
                result += multStream.str();// store the result
                result.resize(result.size() - 2);
                
                outputFile<<result<<endl;
                result = "";

                poly1.clear();
                // mult.clear();
                }//end magic if
                //poly1.clear();
            }//end of the line if check
        }//end read the file loop
        
    }//end for
    return 0;
}