#include "fila.h"

// Estrutura para representar uma fila (utilizada na BFS)
typedef struct fila{
    
    int* data;
    int comeco;
    int final;
    int tamanho;
    int capacidade;

}_queue;

// Função para criar uma fila
Queue createQueue(int capacidade) {
    _queue* fila = calloc(1, sizeof(_queue));

    fila->data = calloc(capacidade, sizeof(int));
    fila->comeco = fila->final = -1;
    fila->tamanho = 0;
    fila->capacidade = capacidade;
    return fila;
}
// Função para verificar se a fila está vazia
bool isEmptyQ(Queue fila) {
    _queue* aux = (_queue*)fila;

    return aux->comeco == -1;
}

// Função para insertQueue um elemento
void insertQueue(Queue fila, int elemento) {
    _queue* aux = (_queue*)fila;
    if(aux->tamanho == aux->capacidade){
        printf("FILA CHEIA!!");
        return;
    }
    if (aux->comeco == -1)aux->comeco = 0;//inicia fila
    aux->final++;
    aux->data[aux->final] = elemento;
    aux->tamanho ++;
}

// Função para removeQueue um elemento
int removeQueue(Queue fila) {
    _queue* aux = (_queue*)fila;

    int elemento = aux->data[aux->comeco];
    if (aux->comeco == aux->final)aux->comeco = aux->final = -1;//se o comeco = final ambos recebem -1
    else aux->comeco++;// se forem diferentes o comeco aumenta 1

    return elemento;
}

void killQueue(Queue fila){
    _queue* aux = (_queue*)fila;

    free(aux->data);
    free(aux);
}