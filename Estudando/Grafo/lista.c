#include "lista.h"

typedef struct no{
    struct no* proximo;
    struct no* anterior;

    Aresta data;
}node;

typedef struct list{
    node* primeiro;
    node* ultimo;
}lista;

Lista newList(){
    lista* aux = calloc(1, sizeof(lista));
    
    aux->primeiro = NULL;
    aux->ultimo = NULL;

    return aux;
}

void insertList(Lista L,Aresta data){
    lista* aux = (lista*) L;
    node* n = calloc(1, sizeof(node));

    n->data = data;
    n->proximo = NULL;

    if(aux->primeiro == NULL){
        n->anterior = NULL;
        aux->primeiro = n;
    }
    else{
        n->anterior = aux->ultimo;
        n->anterior->proximo = n;
    }
    
    aux->ultimo = n;
}

bool isEmptyList(Lista L){
    lista* aux = (lista*) L;
    
    if(aux->primeiro == NULL) return true;
    else return false;
}

Node getFistList(Lista L){
    lista* aux = (lista*) L;
    return aux->primeiro;
}

Node getNextList(Node atual){
    if(atual == NULL)return NULL;

    node* aux = (node*) atual;
    return aux->proximo;
}

Aresta getData(Node atual){
    if(atual == NULL)return NULL;
    
    node* aux = (node*) atual;
    return aux->data;
}

void printList(Lista L){
    lista* aux = (lista*) L;
    node* n = aux->primeiro;

    while(n != NULL){
        printf("%d  ", getPeso(n->data));//Escreve o peso das arestas da lista de adjacencias

        n = n ->proximo;
    }
}