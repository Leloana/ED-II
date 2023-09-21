#ifndef LIST_H
#define LIST_H
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef void *Lista;
typedef void *Posic;
typedef void *Item;

typedef void *Iterador;
typedef void *Clausura;

#define NIL NULL
#define CAPAC_ILIMITADA -1
// cria uma lista setando head e tail para NULL
Lista createLst(int capacidade);
// insere o item no fim da lista retornando sua posiçao
Posic insertLst(Lista L, Item info);
// insere o item antes do no indicado por p, retorna sua posicao
Posic insertBefore(Lista L,Posic p, Item info);
// insere o item depois do no indicado por p, retorna sua posicao
Posic insertAfterLst(Lista L,Posic p, Item info); 
// retorna o tamanho atual da lista
int lengthLst(Lista L);
// retorna o tamanho maximo da lista
int maxLengthLst(Lista L);
// checa se a lista esta vazia
bool isEmptyLst(Lista L);
// checa se a lista esta cheia
bool isFullLst(Lista L);
// remove o nó indicado por p
void removeLst(Lista L, Posic p);
// remove primeiro nó da lista
Item popLst(Lista L);
// apaga a lista com consecutivos popLst
void killLst(Lista L);
// retorna o item do nó indicado por p
Item getLst(Lista L, Posic p);
// retorna a posiçao do primeiro nó
Posic getFirstLst(Lista L);
// retorna a posiçao do último nó
Posic getLastLst(Lista L);
// retorna a posicao do nó posterior a p
Posic getNextLst(Lista L,Posic p);
// retorna a posicao do nó anterior a p
Posic getPreviousLst(Lista L,Posic p);
// cria iterador : False = le a lista normal, true = ao contrario
Iterador createIterator(Lista L, bool reverso);
// checa se o iterador esta vazio
bool isIteratorEmpty(Lista L, Iterador it);
// retorna o item do nó em que o iterador esta e avança
Item getIteratorNext(Lista L, Iterador it);
// apaga iterador
void killIterator(Lista L, Iterador it);

typedef Item (*Apply)(Item item);
typedef bool (*Check)(Item item);
typedef void (*ApplyClosure)(Clausura c, Item item);
//retorna lista que recebe itens da lista principal modificados por funcao f
Lista map(Lista L,Apply f);
//retorna lista que recebe itens da lista principal que passaram por bool f
Lista filter(Lista L, Check f);
// aplica funçao f(L,C)em toda lista L
void fold(Lista L, ApplyClosure f, Clausura c);

#endif