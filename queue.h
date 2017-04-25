//Generic queue implementation
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "linkedlist.h"

#define QUEUE(TYPE_NAME) CAT(q_,TYPE_NAME)
#define MAKE_QUEUE(TYPE_NAME) CAT(mkq_, TYPE_NAME)
#define FREE_QUEUE(TYPE_NAME) CAT(fq_, TYPE_NAME)
#define ALLOC_FREE_QUEUE(TYPE_NAME) CAT(afq_, TYPE_NAME)
#define DEQUEUE(TYPE_NAME) CAT(deq_, TYPE_NAME)
#define ENQUEUE(TYPE_NAME) CAT(enq_, TYPE_NAME)
#define PEEK_QUEUE(TYPE_NAME) CAT(pkq_, TYPE_NAME)
#define EMPTY_QUEUE(TYPE_NAME) CAT(eq_, TYPE_NAME)

//queue definition
struct QUEUE(TN) {
    NODE(TN)* tail;
    NODE(TN)* front;
    int length;
};

typedef struct QUEUE(TN) QUEUE(TN);

//creates a new storage for queue data structure in the heap memory and returns its pointer
//declaration: q_<typename>* mkq_<typname>(); 
QUEUE(TN)* MAKE_QUEUE(TN)();

//pushes new value into queue
//declaration: void enq_<typename>(q_<typename>* Q, <type> value);
void ENQUEUE(TN)(QUEUE(TN)* Q, T value);

//removes the oldest value from queue and returns it
//declaration: <type> deq_<typename>(q_<typename>* Q);
T DEQUEUE(TN)(QUEUE(TN)* Q);

//gets the oldest value in queue
//declaration: <type> pkq_<typename>(q_<typename>* Q);
T PEEK_QUEUE(TN)(QUEUE(TN)* Q);

//checks if queue is empty
//declaration: bool eq_<typename>(q_<typename>* Q);
bool EMPTY_QUEUE(TN)(QUEUE(TN)* Q);

//frees queue 
//declaration: void fq_<typename>(q_<typename>* Q);
void FREE_QUEUE(TN)(QUEUE(TN)* Q);

//frees queue and its elements which uses allocated memory
//declaration: void afq_<typename>(q_<typename>* Q);
void ALLOC_FREE_QUEUE(TN)(QUEUE(TN)* Q);

#include "queue.c"
