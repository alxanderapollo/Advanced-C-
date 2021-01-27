
#ifndef myBlock_H_
#define myBlock_H_
// #include <stddef.h> 
#include <iostream>
#include <memory>

using namespace std;

    struct myHead{
        struct myHead *RLink;// connects to the blocks that are already connected to the right of the list
        struct myHead *LLink; // conects to the blocks that are already connected to the left
        // struct FreeBlock *UPLink; //points a the next avaialble space
        int tag; // means its un allocated 
        int size;// will be the length of the block
    };
    struct myTail{
           struct myHead *upLink;// connects to the blocks that are already connected to the right of the list
           int tag ; //allocated node
           int size;
    };
class myBlock{

    private:
        inline static int overallAlocation = 100000; //since ptrs cant track size we must track it ourselves
        inline static void* myMemoryAddress = (void*)malloc(100000);
        inline static myHead *av = static_cast<myHead *> (myMemoryAddress); //point to the first space that is free in the list
        inline static myHead *FirstNode; //head node 
        inline static myTail *myFirstTail;

        inline static auto initlized = false;


        inline static myHead *LastNode; // tail node
        inline static myTail *myLasttTail;

        inline static myHead *BodyNode; // body node to be chipped
        inline static myTail *myBodyTail;

        void CallmeOnce();//initlize the pool
        //block stuff 
        inline static int myBlocks = 0;// only to exist in the class
        static int blockSize;//keep track of the allocated space thus far
        int sizeOfMyObj; //size of the block
        
    public:

        //initlize pool 
        //arithmetic purposes
        char* theObject;// will hold the char pointer
        myBlock();//default constructor
        myBlock(int lengthOfstr);
        //return the number of blocks that have been allocated
        int getNumberOfUsedBlocks();
        
        //get the size of the block
        int sizeofBlock();

        //functions that serve the size allocation varaible
        void decrementSize(int bytes);//called only when memory has been used (allocate function)
        void restoreSize(int bytes); //returns the ammt of size of the allocated vairble to the object pool(deallocate function)
        int currentSizeOfObjectPool(); //returns the size of the pool

        //allocate and free
        bool Allocate(int size);
        static void Free(myHead* ptr);

        //delete class ptr
        ~myBlock();
        //new and delete
        void* operator new(size_t size);//size_t represents the size of the object, overloading new
        void operator delete(void *memory);//for when we deallocate

};//end myBlock
#endif