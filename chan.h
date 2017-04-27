//Generic channel function declarations
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <sys/types.h>
#include <unistd.h>

#include "queue.h"

#define CHAN(TYPE_NAME) CAT(ch_,TYPE_NAME)
#define ADD_CHAN(TYPE_NAME) CAT(ach_,TYPE_NAME)
#define ALLOC_FREE_CHAN(TYPE_NAME) CAT(afch_,TYPE_NAME)
#define FREE_CHAN(TYPE_NAME) CAT(fch_,TYPE_NAME)
#define MAKE_CHAN(TYPE_NAME) CAT(mkch_,TYPE_NAME)
#define POP_CHAN(TYPE_NAME) CAT(pch_,TYPE_NAME)

//channel definition
struct CHAN(TN) {
    QUEUE(TN)* qu;
}

typedef struct CHAN(TN) CHAN(TN);

//creates a new storage for channel data structure in the heap memory and returns its pointer
//declaration: ch_<typename>* mkch_<typname>(); 
CHAN(TN)* MAKE_CHAN(TN)();

//pushes new value into channel pipe
//declaration: void ach_<typename>(ch_<typename>* C, <type> value);
void ADD_CHAN(TN)(CHAN(TN)* C, T value);

//removes the oldest value from channel and returns it
//declaration: <type> pch_<typename>(ch_<typename>* C);
T POP_CHAN(TN)(CHAN(TN)* C);

//frees channel 
//declaration: void fch_<typename>(ch_<typename>* C);
void FREE_CHAN(TN)(CHAN(TN)* C);

//frees channel and its elements which uses allocated memory
//declaration: void afch_<typename>(ch_<typename>* C);
void ALLOC_FREE_CHAN(TN)(CHAN(TN)* C);