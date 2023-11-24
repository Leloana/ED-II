#ifndef PROFUNDIDADE_H
#define PROFUNDIDADE_H

#include "grafo.h"

enum Cor {
    BRANCO,//Branco e o node ainda nao explorado
    CINZA,//cinza e o no que esta sendo explorado no momento
    PRETO//e o no ja explorado
};

typedef struct _infovertice {
    enum Cor cor;
    int valor;
    int distancia; // Distância a partir do vértice de origem
    int anterior; // Vértice anterior na busca em largura
}InfoVertice;

void visitaEmProfundidade(Vertice partida, int quantVertices);

void profudidade(Vertice partida, InfoVertice* info);

#endif 
