#include "list.h"

typedef struct node{

    Item data;

    struct node *next;
    struct node *prev;

} node;

typedef struct list{

    node* head;

    node* tail;

    int size;
    int capacity; 

} _list;

typedef struct ITE{

    node *atual;
    bool reverse;

}_Iterator;

Lista createLst(int capacidade){

    _list* aux = malloc(sizeof(_list));

    aux->head = NULL;
    aux->tail = NULL;

    aux->size = 0;

    if(capacidade>=0)aux->capacity = capacidade;
        else aux->capacity = CAPAC_ILIMITADA;

    return (Lista)aux;
}

Posic insertBefore(Lista L,Posic p, Item info){
    _list* B = (_list*)L;
    node* n = (node*) p;

    node* aux = malloc(sizeof(node));
    aux->data = info;

    if(!isFullLst(B)){
        if(p == B->head){
            B->head = aux;
            n->prev = aux;
            aux->prev = NULL;
            aux->next = n;
        }
        
        else{
        n->prev->next = aux;
        aux->prev = n->prev;
        aux->next = n;
        n->prev = aux;
        }

        B->size++;
        return aux;
    }
    else{

    printf(" A Lista ESTA CHEIA!!\n");
    return 0;
    }
}

Posic insertAfterLst(Lista L,Posic p, Item info){
    _list* B = (_list*)L;
    node* n = (node*) p;

    node* aux = malloc(sizeof(node));
    aux->data = info;

    if(!isFullLst(B)){
        if(p == B->tail){
            n->next = aux;
            aux->prev = n;
            aux->next = NULL;
        }
        
        else{
        n->next->prev = aux;
        aux->next = n->next;
        aux->prev = n;
        n->next = aux;
        }

        B->size++;
        return aux;
    }
    else{

    printf(" A Lista ESTA CHEIA!!\n");
    return 0;
    }
}

Posic insertLst(Lista L, Item info){
    _list* B = (_list*)L;

    if(!isFullLst(B)){
    node* aux = malloc(sizeof(node));

    aux->data = info;

    aux->next = NULL;

    if(B->head == NULL){
        B->head = aux;
        B->tail = aux;
    }
    else{

        aux->prev = B->tail;
        B->tail->next = aux;
        B->tail = aux;
    }

    B->size ++;

    return aux;    

    }
    else{

    printf(" A Lista ESTA CHEIA!!\n");
    return 0;
    }
}

Item popLst(Lista L){
    if(L){
    _list* aux = (_list*) L;
    node*n = aux->head;
    Item X = aux->head->data;

    if(n->next != NULL){
    aux->head = n->next;
    aux->head->prev = NULL;
    free(n);
    }
    else {
        free(n);
        aux->head = NULL;
    }
    aux->size --;
    return X;
    }
    else return 0;
}

void removeLst(Lista L, Posic p){
    if(L){
    _list* B = (_list*) L;
    node* n = (node*)p;

    if(n == B->head){
        popLst(L);
    }
    else if(n == B->tail){
        n->prev->next = NULL;
        free(n);
    }
    else{
        n->prev->next = n->next;
        n->next->prev = n->prev;
        free(n);
    }
    B->size--;
    }
}

void killLst(Lista L){
    _list* aux = (_list*) L;
    while(aux->head != NULL) popLst(aux);
}

int lengthLst(Lista L){
    _list* aux = (_list*) L;
    return aux->size;
}

int maxLengthLst(Lista L){
    _list* aux = (_list*) L;
    if(aux->capacity > 0)return aux->capacity;
    else return CAPAC_ILIMITADA;
}

bool isEmptyLst(Lista L){
    _list* aux = (_list*) L;
    if(aux->head == NULL)return true;
    else return false;
}

bool isFullLst(Lista L){
    if(lengthLst(L) == maxLengthLst(L))return true;
    else return false;
}

Item getLst(Lista L, Posic p){
   return ((node*) p)->data;
}

Posic getFirstLst(Lista L){
    _list* B = (_list*) L;
    return B->head;
}

Posic getLastLst(Lista L){
    _list* B = (_list*) L;
    return B->tail;
}

Posic getNextLst(Lista L,Posic p){
    node* n = (node*) p;
    return n->next;
}

Posic getPreviousLst(Lista L,Posic p){
    node* n = (node*) p;
    return n->prev;
}

Iterador createIterator(Lista L, bool reverso) {
    _Iterator* B = (_Iterator*)malloc(sizeof(_Iterator));
    _list* A = (_list*) L;

    B->reverse = reverso;

    if(B->reverse)B->atual = getLastLst(A);
    else B->atual = getFirstLst(A);

    return B;
}

bool isIteratorEmpty(Lista L, Iterador it){
    _Iterator* B = (_Iterator*) it;
    _list* A = (_list*) L;

    if(isEmptyLst(A))return true;

    else if(B->reverse){
        if(B->atual == ((node*)getFirstLst(A))->prev)return true;
        else return false;
    }
    else{
        if(B->atual == ((node*)getLastLst(A))->next)return true;
        else return false;
    }
}

Item getIteratorNext(Lista L, Iterador it) {
        _Iterator* B = (_Iterator*)it;
        _list* A = (_list*)L;
        
        Item X = B->atual->data;

        if (B->reverse) {
            B->atual = (node*)getPreviousLst(A, B->atual);
        }
        else {
            B->atual = (node*)getNextLst(A, B->atual);
        }
        return X;

}

void killIterator(Lista L, Iterador it) {
    free(it);
}

Lista map(Lista L,Apply f){
    _list* aux = (_list*)L;
    _list* B = createLst(maxLengthLst(aux));
    _Iterator* K = createIterator(aux,false);

    while(!isIteratorEmpty(aux,K))insertLst(B,f(getIteratorNext(aux,K)));
    killIterator(aux,K);
    return (Lista)B;
}

Lista filter(Lista L, Check f) {
    _list* aux = (_list*)L;
    _list* B = createLst(maxLengthLst(aux));
    Iterador K = createIterator(aux, false);

    while (!(isIteratorEmpty(aux, K))) {
        Item info = getIteratorNext(aux, K);
        if (f(info)) {
            insertLst(B, info);
        }
    }
    killIterator(L, K);
    return (Lista)B;
}

void fold(Lista L, ApplyClosure f, Clausura c) {
    _list* aux = (_list*) L;
    Iterador K = createIterator(aux , false);

    while (!(isIteratorEmpty(aux, K))) {
        f(c,getIteratorNext(aux, K));
    }
    killIterator(aux, K);
}