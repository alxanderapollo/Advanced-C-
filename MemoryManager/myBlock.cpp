#include "myBlock.h"
#include <stddef.h> 
#include <memory>
#include <iostream>
# define myEpsilon 100
using namespace std;

//default constructor
myBlock::myBlock(){
    theObject = nullptr;
    cout<<"default constructor called"<<endl;
}

myBlock::myBlock(int lengthOfString){
    //check for space

    //create 3 blocks just once
   if(initlized == false) {
       CallmeOnce();//initlize the three blocks

   }
    if(Allocate(lengthOfString)){
    
        //length of the object plus the number of its bytes
        this->sizeOfMyObj = lengthOfString;

        //subtract from the overall size allocated
        //class ptr
        theObject = new char[this->sizeOfMyObj];


    }//if this is true will allocate  a block
    else{
        cout<<"nothing was allocated, not enough space"<<endl;
    }
}//end of my Block

//sizes
int myBlock:: getNumberOfUsedBlocks(){
    return this->myBlocks;
}//end get number of blocks allocated

int myBlock::sizeofBlock(){
     //allocatedNode* q = (allocatedNode)theObject;
    return (sizeof this->theObject);//return the size of the object
}//end size

//sizes for object memory pool
void myBlock::decrementSize(int bytes){//used when allocating space in the overall pool
    this->overallAlocation -=(sizeof(bytes));
    cout<<"Succesfully added to the memory pool"<<endl;
}
void myBlock::restoreSize(int bytes){//used when deallocating memory and returns memory to the overall object pool
    this->overallAlocation += (sizeof(bytes));
    cout<<"returned "<<sizeof(bytes)<<" bytes, to overall memory."<<endl;
}
int myBlock::currentSizeOfObjectPool(){//gives the overall size of the memory pool
    return this->overallAlocation; 
}

//links 3 blocks together
void myBlock::CallmeOnce(){
    //first node points to the begining of the list
    //empty 
    //points to the front of the list
    FirstNode = static_cast<myHead *> (myMemoryAddress);
    FirstNode->tag = 0;
    FirstNode->size = 0;
    //left and rught
    FirstNode->LLink = (myHead*)((char*) myMemoryAddress + (overallAlocation) - sizeof(myTail*) - sizeof(myHead*));
    FirstNode->RLink = (myHead*) ((char*) myMemoryAddress + (sizeof(myHead) - sizeof(myTail)));

    //tail 
    myFirstTail = (myTail*)((char*)myMemoryAddress + sizeof(myHead*));
    myFirstTail->size = 0;
    myFirstTail->upLink = FirstNode;//connect the first node

    //body block points to the tail
    BodyNode = (myHead*)((char*) myFirstTail - sizeof(myTail*) - sizeof(myHead*)); 
    BodyNode ->size = 0;
    BodyNode ->tag = 0;
    BodyNode->RLink = (myHead*)((char*) myMemoryAddress + (overallAlocation) - sizeof(myTail*) - sizeof(myHead*));
    BodyNode->LLink = (myHead*) ((char*) myMemoryAddress + (sizeof(myHead) - sizeof(myTail)));

    //tail of the middle block  points to the head of the first block
    myBodyTail = (myTail*)((char*)BodyNode + sizeof(myHead*));
    myBodyTail->size = 0;
    myBodyTail->upLink = BodyNode;//connect the first node

    //final Block points to tain 
    LastNode = (myHead*)((char*) BodyNode - sizeof(myTail*) - sizeof(myHead*)); 
    LastNode->tag = 0;
    LastNode->size = 0;
    BodyNode->RLink = (myHead*)((char*) myMemoryAddress + (overallAlocation) - sizeof(myTail*) - sizeof(myHead*));
    BodyNode->LLink = (myHead*) ((char*) myMemoryAddress + (sizeof(myHead) - sizeof(myTail)));

    //last node tail
    myLasttTail = (myTail*)((char*)myMemoryAddress + sizeof(myHead*));
    myLasttTail->size = 0;
    myLasttTail->upLink = LastNode;//connect the first node

   initlized = true;//set true once
}//end call me once

//allocate recives (n) - which is the length of the object
bool myBlock::Allocate(int lengthOfN){
    int diff;
    
    myHead *p; //top of the block
    myTail* tail;//bottom of the block
    int epsilon =  myEpsilon;

    bool checkMe = (sizeof(p)>= lengthOfN) ? true : false;

    // algorithm
    //first p is set to the right link of av
   p = av->RLink;
   do{ 
        //----->check size
        //want to make sure the size of the object is not bigger than
        //the memory means in the pool so check first
        if(checkMe) {
        //check if the next block is big enough
        //diff<--size(p) - n
        diff = (sizeof(p) - lengthOfN);
            
            //diff<epsilon
            if(diff<epsilon){//------------>first case
                //[Rlink(Llink(p))  <-- Rlink(p)]
                p->RLink->LLink = p->RLink;
                //Llink(Rlink(p))<--Llink(p)
                p->LLink->RLink = p->LLink;
                p->tag = 1;//upper tag at the top of the block
                //to be moved around 
                //tail = (myTail*)((char*)p + p->size + sizeof(myHead)); 
                av = p->LLink;//set av to point to the nexly allocatted block, which is the
                //new starting point
                return true;
            }//end first case
            else{//------------->second case --lower case 
                
                //diff will now equal the size of p + its tail
                diff = sizeof(p)+sizeof(tail) + lengthOfN; //and size of the tail? + sizeof(tail)
                p->size = diff;
                //set uplink to point to p
                tail->upLink = (myHead*)(((char*)p) + diff - 1); //postion of p
                p->tag = 0;// p tag is 0 - top block isnt allocated
                p->size = lengthOfN;
               tail->tag = 1;
            return true;
            }//end second case
       
         //move the ptr forward to check other blocks
    }
    p = p->RLink;
    }while(p!= av->RLink); //stop if we have reached av //end Allocate
    p = nullptr;tail = nullptr;
 return false;
}//end allocate

void myBlock::Free(myHead *p){
    int onTheLeft, onTheRight;
    int n = p->size; 
    myHead *q; myTail *k;

    //case1 if both adjacent tags are in use
   q = ((myHead*)((char*)p + n )); //p+n
   k =  ((myTail*)((char*)p - n ));//p-1

    //p-1           p+n
    if(q->tag == 1 && k->tag == 1){
        //set the tag to free
        p->tag = 0;
        //upLink
        p->LLink = av;
        p->RLink = av->RLink;
        p->LLink->RLink = p; av->RLink= p;
    }
    //p+n                 p-1
   if( k->tag == 1 &&  q->tag == 0 ){ //case 2 
    
        //start of left block
        k->upLink = (myHead*)(((char*)p) - 1);
        q->size = (sizeof(q) + n);

        k->upLink = (myHead*)(((char*)p) + n - 1);
        p->tag = 0;//set the tag to zed

    }
    if( k->tag == 0 &&  q->tag == 1 ){ //case 3 

        p->RLink->LLink->((myHead*)sizeof((char*)p) + n) = p;
        p->LLink->RLink->(sizeof((char*)p) + n) = p;
        p->RLink  = p->RLink->((myHead*)((char*)p) + n);
        p->size = n + sizeof(p) + n;
        k->upLink->(sizeof(p) + sizeof(p) - 1);
        p->tag = 0;
    }//end if
    if( av = p ) av = p;
    else {//case 4
    //both adjacent blocks are free
        p->RLink = p->LLink->(sizeof((char*)p) + n);
        p->LLink->RLink->(sizeof((char*)p) + n) = p->LLink->(sizeof((char*)p) + n);
        q = k->upLink->(sizeof(p) - 1);
            if(av = (myHead*)(sizeof(p) + n)) 
                av = p->LLink->(sizeof(p)+ n);
    }//end else
}//end free

//deallocate the ptr
myBlock::~myBlock(){
    cout<<"Deleting class ptr"<<endl;
    delete [] theObject;
}
void* myBlock::operator new(size_t size){
    
     cout<<"size of allocation: "<<size<<endl;
    void *p = malloc(size);//creates the size of the object

    //keeping track of the number of free blocks
     cout<<"size of allocation: "<<size<<" bytes"<<endl;
    //when the algo is implemented ill keep track of the amount of space inside 
    //of each block
    myBlocks++;
    cout<<"\n Successfully allocated a block!! number of blocks allocated: "<<myBlocks<<endl;
    return p; 
//    return new char [size];
}//end operator new
void myBlock::operator delete(void* myMemory){
    myBlocks--;
    cout<<"Freed up memory bytes"<<endl;
    free(myMemory);//delete the ptr
}//end operator Delete