#ifndef LISTA_H
#define LISTA_H

typedef void* Lista;
typedef void* Node;

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "grafo.h"

Lista newList();

void insertList(Lista L,Aresta data);

bool isEmptyList(Lista L);

Node getFistList(Lista L);

Node getNextList(Node atual);

Aresta getData(Node atual);

void printList(Lista L);


#endif