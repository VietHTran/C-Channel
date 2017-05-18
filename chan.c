#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/sem.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>

#ifdef T
#ifdef TN

#include "chan.h"

//Private methods

#define initsem(SEMID,I,VAL) do {                           \
    checkerr((semctl(SEMID,I,SETVAL,VAL)<0),                \
            "Error initializing semaphore");                \
} while(0)

#define P(SEMID,I) do {                                     \
    struct sembuf ops[1];                                   \
    ops[0].sem_num=I;                                       \
    ops[0].sem_op=-1;                                       \
    ops[0].sem_flg=0;                                       \
    checkerr((semop(SEMID,ops,1)<-1),                       \
            "Error waiting for signal");                    \
} while(0) 

#define V(SEMID,I) do {                                     \
    struct sembuf ops[1];                                   \
    ops[0].sem_num=I;                                       \
    ops[0].sem_op=1;                                        \
    ops[0].sem_flg=0;                                       \
    checkerr((semop(SEMID,ops,1)<-1),                       \
            "Error sending signal");                        \
} while(0) 

//creates a new storage for channel data structure in the heap memory and returns its pointer
//declaration: ch_<typename>* mkch_<typname>(int size); 
CHAN(TN) MAKE_CHAN(TN)(int size) {
    checkerr((size<0),"Invalid Size");
    CHAN(TN) chan;
    chan.size=size;

    chan.sharedmem = mmap(0,(size+2)*sizeof(T),
            PROT_READ|PROT_WRITE,
            MAP_ANONYMOUS|MAP_SHARED,-1,0);
    checkerr((chan.sharedmem==(caddr_t)-1),
            "Error creating shared memory");

    chan.buffer=(T*)chan.sharedmem;
    chan.in=chan.buffer+sizeof(T)*chan.size;
    chan.out=chan.buffer+sizeof(T)*(chan.size+1);
    *chan.in=*chan.out=0;

    chan.semid=semget(IPC_PRIVATE, 3, IPC_CREAT|0600);
    checkerr(chan.semid<0,"Error creating semaphores");

    initsem(chan.semid,SEM_USED,0);
    initsem(chan.semid,SEM_SPACE,size);
    initsem(chan.semid,SEM_MUTEX,1);
    return chan;
}

//pushes new value into channel
//declaration: void ach_<typename>(ch_<typename>* C, <type> value);
void ADD_CHAN(TN)(CHAN(TN)* C, T value) {
    P(C->semid,SEM_SPACE);
    P(C->semid,SEM_MUTEX);
    C->buffer[*C->in]=value;
    *C->in=(*C->in+1)%C->size;
    V(C->semid,SEM_MUTEX);
    V(C->semid,SEM_USED);
}

//removes the oldest value from channel and returns it
//declaration: <type> pch_<typename>(ch_<typename>* C);
T POP_CHAN(TN)(CHAN(TN)* C) {
    P(C->semid,SEM_USED);
    P(C->semid,SEM_MUTEX);
    T value=C->buffer[*C->out];
    *C->out=(*C->out+1)%C->size;
    V(C->semid,SEM_MUTEX);
    V(C->semid,SEM_SPACE);
    return value;
}

//frees channel 
//declaration: void fch_<typename>(ch_<typename>* C);
void FREE_CHAN(TN)(CHAN(TN)* C) {
    checkerr((semctl(C->semid,0,IPC_RMID))<0,
            "Error terminating semaphore");
}

#undef initsem
#undef P
#undef V

#endif
#endif
