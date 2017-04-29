#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>


//creates a new storage for channel data structure in the heap memory and returns its pointer
//declaration: ch_<typename>* mkch_<typname>(int size); 
CHAN(TN)* MAKE_CHAN(TN)(int size) {
    CHAN(TN)* new_chan=(CHAN(TN)*)malloc(sizeof(CHAN(TN)));
    new_chan->fd=(int*)malloc(sizeof(int)*2);
    if (pipe(new_chan->fd)<0) {
        printf("Error creating pipe");
        free(new_chan->fd);
        free(new_chan);
        exit(1);    
    }
    new_chan->size=size;
}

//pushes new value into channel pipe
//declaration: void ach_<typename>(ch_<typename>* C, <type> value);
void ADD_CHAN(TN)(CHAN(TN)* C, T value) {
}

//removes the oldest value from channel and returns it
//declaration: <type> pch_<typename>(ch_<typename>* C);
T POP_CHAN(TN)(CHAN(TN)* C) {
}

//frees channel 
//declaration: void fch_<typename>(ch_<typename>* C);
void FREE_CHAN(TN)(CHAN(TN)* C) {
}

//frees channel and its elements which uses allocated memory
//declaration: void afch_<typename>(ch_<typename>* C);
void ALLOC_FREE_CHAN(TN)(CHAN(TN)* C) {
}
