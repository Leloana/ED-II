#include <stdio.h>
#include <stdlib.h>
#include <limits.h>//Para usar o valor INT_MAX

#define V 4 // Número de vértices no grafo

// Função para encontrar o vértice com a distância mínima
// dos vértices ainda não incluídos no conjunto de caminhos mais curtos
int minDistance(int dist[], int jaVisitado[]) {
    int min = INT_MAX;
    int min_index;

    for (int i = 0; i < V; i++) {
        // 0 é nao visitado, 1 é visitado
        if (jaVisitado[i] == 0 && dist[i] <= min) {
            min = dist[i];
            min_index = i;
        }
    }

    return min_index;
}

// Função para imprimir o array de distâncias
void printSolution(int dist[], int partida) {
    printf("Vertice inicial : %d\n", partida);
    for (int i = 0; i < V; i++) {
        printf("Vertice Final : %d Distancia: %d\n", i, dist[i]);
    }
}

// Função que implementa o algoritmo de Dijkstra para um grafo representado por uma matriz de adjacência
void dijkstra(int graph[V][V], int partida) {
    int dist[V]; // Array para armazenar as distâncias mais curtas

    // sptSet[i] é verdadeiro se o vértice i está incluído no conjunto de caminhos mais curtos
    int jaVisitado[V];

    // Inicialização de todas as distâncias como infinito e sptSet[] como falso
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        jaVisitado[i] = 0;//Nenhum ainda foi visitado
    }

    // A distância do vértice de origem para ele mesmo é sempre 0
    dist[partida] = 0;

    // Encontrar os caminhos mais curtos para todos os vértices
    for (int count = 0; count < V - 1; count++) {
        // Escolhe o vértice com a distância mínima do conjunto de vértices ainda não processados
        int u = minDistance(dist, jaVisitado);

        // Marca o vértice escolhido como processado
        jaVisitado[u] = 1;
        // Atualiza a distância dos vértices adjacentes ao vértice escolhido
        for (int i = 0; i < V; i++) {
            if (!jaVisitado[i] && graph[u][i] && dist[u] != INT_MAX && dist[u] + graph[u][i] < dist[i]) {
                dist[i] = dist[u] + graph[u][i];
            }
        }
    }

    // Imprime o array de distâncias
    printSolution(dist, partida);
}

// Função principal
int main(void) {
    /* Matriz de adjacencia
       exemplo : o elemento [0][1] é 2, isso significa que entre o vertice
       0 e o vertice 1 há uma aresta de tamanho 2.
       Os elementos que sao iguais 0 representam a ausência de uma aresta 
       entre esses vértices 
    */
    int grafo[V][V] = {{0, 5, 0, 3},
                       {5, 0, 2, 10},
                       {0, 2, 0, 0},
                       {3, 10, 0, 0}};
    /*
        Grafo montado
        0 -- (5) -- 1
        |       /  |
       (3)   (10) (2)
        |   /     |
        3 /       2

    */
    

    dijkstra(grafo, 1 );

    return 0;
}
