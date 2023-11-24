#ifndef GRAFO_H
#define GRAFO_H

typedef void* Vertice;
typedef void* Aresta;

#include "largura.h"
#include "lista.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
//inicia ovo vertice de indice "indice"
Vertice newVertice(int indice);
//Adiciona uma nova aresta entre "origem" e "destino" de peso = "peso"
void addAresta(Vertice origem, Vertice destino, int peso);
//Retorna o indice do vertice V
int getIndice(Vertice V);
//Retorna a lista de arestas do vertice V
Lista getListaArestas(Vertice V);
//Retorna o Vertice de destino da aresta A
Vertice getVertice(Aresta A);
//Retorna o peso da aresta A
int getPeso(Aresta A);

#endif // !GRAFO_H