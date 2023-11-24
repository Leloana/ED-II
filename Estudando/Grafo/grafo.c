#include "grafo.h"

typedef struct vert{
    Lista adjacencias;//cada vertice tem sua lista de adjacencias
    int indice;//e seu identificador

}vertice;

typedef struct adj{
    int peso;
    vertice* destino;

}aresta;


Vertice newVertice(int indice){
    vertice* aux = calloc(1, sizeof(vertice));

    aux->adjacencias = newList();
    aux->indice = indice;

    return aux;
}

void addAresta(Vertice origem, Vertice destino, int peso){//unidirecional
    vertice* ori = (vertice*) origem;
    vertice* dest = (vertice*) destino;

    aresta* new = calloc(1, sizeof(aresta));
    new->peso = peso;
    new->destino = destino;

    insertList(ori->adjacencias, new);//Agora new faz parte da lista d adj de origem

}

int getIndice(Vertice V){
    vertice* aux = (vertice*) V;

    return aux->indice;
}

Lista getListaArestas(Vertice V){
    vertice* aux = (vertice*) V;

    return aux->adjacencias;
}

Vertice getVertice(Aresta A){
    if(A == NULL)return NULL;
    aresta* aux = (aresta*) A;

    return aux->destino;
}

int getPeso(Aresta A){
    aresta* aux = (aresta*) A;

    return aux->peso;
}