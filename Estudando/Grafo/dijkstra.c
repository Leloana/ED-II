#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "limits.h"
#define V 4

int minDistance(int dist[], bool jaVisitado[]){
    int min = INT_MAX;
    int min_index = 0;

    for(int i = 0; i < V; i++){
        if(!jaVisitado[i] && dist[i] < min){//Se ainda nao foi visitado e a distancia for menor que min
            min = dist[i];//min recebe a nova distancia
            min_index = i;//min index recebe o index
            //Isso ocorre para avaliar se os caminhos secundarios podem ser menores que os diretos
        }
    }
    return min_index;
}

void dijkstra(int grafo[V][V], int partida){
    int dist[V];
    bool jaVisitado[V];
    int pai[V];

    for (int i = 0; i < V; i++){
        dist[i] = INT_MAX;
        jaVisitado[i] = false;
        pai[i] = -1;
    }

    dist[partida] = 0;

    for(int contador = 0; contador < V-1; contador ++){
        int u = minDistance(dist, jaVisitado);
        jaVisitado[u] = true;

        for(int i = 0; i < V; i++){
            /*
            RELAXAMENTO
            1 - Analiso se os arredores de u ja foram visitados,
            2 - Se existe ligacao entre o arredor e u,
            3 - Se a (distancia acumulada de u ate a partida) + (a distancia da ligacao entre u e seu arredor) 
            é menor que a distancia acumulada de seu arredor ate a partida,

            >>>Essa ultima comparação é o que subscreve os caminhos diretos pelos indiretos menores<<<
            */
            if(!jaVisitado[i] && grafo[u][i] != 0 && dist[u] + grafo[u][i] < dist[i]){
                dist[i] = dist[u] + grafo[u][i];
                pai[i] = u;
            }
        }
    }

    for(int i = 0; i < V; i++){
        printf("Distancia (%d->%d) = %d\n",partida,i, dist[i]);
        printf("Pai de %d = %d\n", i, pai[i]);
    }
}

int main(void){

    int grafo[V][V] = {{0,9,0,4},
                       {9,0,8,1},
                       {0,8,0,0},
                       {4,1,0,0},};

   dijkstra(grafo, 1);
}