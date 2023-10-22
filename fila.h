#ifndef FILA_H
#define FILA_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef void* Queue;
//Cria uma fila simples com capacidade = "capacidade" e inicializando o comeco e o final da fila em -1
Queue createQueue(int capacidade);
//Checa se a fila esta vazia retornando se o comeco da fila == -1
bool isEmptyQ(Queue fila); 
//Insere o valor de elemento na fila
void insertQueue(Queue fila, int elemento);
//remove o primeiro elemento da fila
int removeQueue(Queue fila);
//Da free em todos os elementos da fila e depois no ponteiro dela mesma
void killQueue(Queue fila);

#endif
