//linked list's methods' definitions
#include <assert.h>

#ifdef ALLOC_T //T used allocated type

//Free a chain of connected nodes that  uses allocated memory to store data
//declaration: void afll_<typename>(ll_<typename>* L)
void ALLOC_FREE(TN)(NODE(TN)* L) {
    assert(L!=NULL);
    NODE(TN)* holder=L;
    while (holder!=NULL) {
        NODE(TN)* i=holder;
        holder=holder->next;
        free(i->value);
        free(i);
    }
}
#endif

//Free a chain of connected nodes in the memory
//declaration: void fll_<typename>(ll_<typename>* L)
void FREE(TN)(NODE(TN)* L) {
    assert(L!=NULL);
    NODE(TN)* holder=L;
    while (holder!=NULL) {
        NODE(TN)* i=holder;
        holder=holder->next;
        free(i);
    }
}

//Create a new node data storage in the memory heap and return its pointer
//declaration: ll_<typename>* mkll_<typename>(<type> value);
NODE(TN)* MAKE(TN)(T value) {
    NODE(TN)* holder = (NODE(TN)*)malloc(sizeof(NODE(TN)));
    T added_val;
    added_val=value;
    holder->value=added_val;
    holder->next=NULL;
    return holder;
}
