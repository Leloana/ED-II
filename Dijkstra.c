#include <stdio.h>
#include <stdlib.h>
#include <limits.h>//Para usar o valor INT_MAX

#define V 4 // Número de vértices no grafo

// Função para encontrar o vértice com a distância mínima
// dos vértices ainda não incluídos no conjunto de caminhos mais curtos
int minDistance(int dist[], int sptSet[]) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++) {
        if (sptSet[v] == 0 && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }

    return min_index;
}

// Função para imprimir o array de distâncias
void printSolution(int dist[], int partida) {
    printf("Partindo de %d:\n", partida);
    for (int i = 0; i < V; i++) {
        printf("Para o vértice %d: %d\n", i, dist[i]);
    }
}

// Função que implementa o algoritmo de Dijkstra para um grafo representado por uma matriz de adjacência
void dijkstra(int graph[V][V], int partida) {
    int dist[V]; // Array para armazenar as distâncias mais curtas

    // sptSet[i] é verdadeiro se o vértice i está incluído no conjunto de caminhos mais curtos
    int sptSet[V];

    // Inicialização de todas as distâncias como infinito e sptSet[] como falso
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = 0;
    }

    // A distância do vértice de origem para ele mesmo é sempre 0
    dist[partida] = 0;

    // Encontrar os caminhos mais curtos para todos os vértices
    for (int count = 0; count < V - 1; count++) {
        // Escolhe o vértice com a distância mínima do conjunto de vértices ainda não processados
        int u = minDistance(dist, sptSet);

        // Marca o vértice escolhido como processado
        sptSet[u] = 1;

        // Atualiza a distância dos vértices adjacentes ao vértice escolhido
        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    // Imprime o array de distâncias
    printSolution(dist, partida);
}

// Função principal
int main() {
    /* Matriz de adjacencia
       exemplo : o elemento [0][1] é 2, isso significa que entre o vertice
       0 e o vertice 1 há uma aresta de tamanho 2.
       Os elementos que sao iguais 0 representam a ausência de uma aresta 
       entre esses vértices 
    */
    int grafo[V][V] = {{0, 2, 0, 6},
                       {2, 0, 3, 8},
                       {0, 3, 0, 0},
                       {6, 8, 0, 0}};
    /*
        Grafo montado
        0 -- (2) -- 1
        |       /  |
       (6)   (8) (3)
        |   /     |
        3 /       2

    */
    

    dijkstra(grafo, 2 );

    return 0;
}
