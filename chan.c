#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <sys/types.h>
#include <unistd.h>


//creates a new storage for channel data structure in the heap memory and returns its pointer
//declaration: ch_<typename>* mkch_<typname>(); 
CHAN(TN)* MAKE_CHAN(TN)() {
    CHAN(TN)* new_chan=(CHAN(TN)*)malloc(sizeof(CHAN(TN)));
    new_chan->pipe=MAKE_QUEUE(TN)();
    new_chan->is_lock=false;
}

//pushes new value into channel pipe
//declaration: void ach_<typename>(ch_<typename>* C, <type> value);
void ADD_CHAN(TN)(CHAN(TN)* C, T value) {
    while (C->is_lock) { }
    C->is_lock=true;
    ENQUEUE(TN)(C->pipe,value);
    C->is_lock=false;
}

//removes the oldest value from channel and returns it
//declaration: <type> pch_<typename>(ch_<typename>* C);
T POP_CHAN(TN)(CHAN(TN)* C) {
    while (C->is_lock || C->pipe->length==0) { }
    C->is_lock=true;
    T res=DEQUEUE(TN)(C->pipe);
    C->is_lock=false;
    return res;
}

//frees channel 
//declaration: void fch_<typename>(ch_<typename>* C);
void FREE_CHAN(TN)(CHAN(TN)* C) {
    while (C->is_lock) { }
    C->is_lock=true;
    FREE_QUEUE(TN)(C->pipe);
    free(C);
}

//frees channel and its elements which uses allocated memory
//declaration: void afch_<typename>(ch_<typename>* C);
void ALLOC_FREE_CHAN(TN)(CHAN(TN)* C) {
    while (C->is_lock) { }
    C->is_lock=true;
    ALLOC_FREE_QUEUE(TN)(C->pipe);
    free(C);
}
