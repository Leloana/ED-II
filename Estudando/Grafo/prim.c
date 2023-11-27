#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define V 5 // Número de vértices no grafo

// Função para encontrar a aresta com o menor peso que conecta um vértice já incluído ao conjunto de vértices ainda não incluídos
int minpesoMin(int pesoMin[], int jaVisitado[]) {
    int min = INT_MAX;
    int min_index;

    for (int i = 0; i < V; i++) {
        if (jaVisitado[i] == 0 && pesoMin[i] < min) {
            min = pesoMin[i];
            min_index = i;
        }
    }
    return min_index;
}


// Função para imprimir a árvore geradora mínima
void printMST(int parent[], int graph[V][V]) {
    printf("Aresta   Peso\n");
    for (int i = 1; i < V; i++) {
        printf("%d - %d    %d\n", parent[i], i, graph[i][parent[i]]);
    }
}

// Função que implementa o algoritmo de Prim
void primMST(int graph[V][V]) {
    int parent[V]; // Array para armazenar a árvore geradora mínima
    int pesoMin[V];    // Array para armazenar o peso mínimo das arestas

    int jaVisitado[V]; // jaVisitado[i] será verdadeiro se o vértice i estiver incluído na árvore geradora mínima

    // Inicialização
    for (int i = 0; i < V; i++) {
        pesoMin[i] = INT_MAX;
        jaVisitado[i] = 0;
    }

    // O primeiro vértice sempre será o nó raiz, e sua chave será 0
    pesoMin[0] = 0;
    parent[0] = -1; // O primeiro nó não tem pai na árvore

    // Construção da árvore geradora mínima
    for (int count = 0; count < V - 1; count++) {
        // Escolhe o vértice com a chave mínima do conjunto de vértices ainda não processados
        int u = minpesoMin(pesoMin, jaVisitado);
        printf(" %d ", u);
        // Marca o vértice escolhido como processado
        jaVisitado[u] = 1;

        // Atualiza as chaves e os pais dos vértices adjacentes ao vértice escolhido
        for (int v = 0; v < V; v++) {
            if (jaVisitado[v] == 0 && graph[u][v] != 0 && graph[u][v] < pesoMin[v]) {
                parent[v] = u;
                pesoMin[v] = graph[u][v];
            }
        }
    }

    // Imprime a árvore geradora mínima
    printMST(parent, graph);
}

int main() {
    // Exemplo de uso
    int graph[V][V] = {{0, 2, 0, 6, 1},
                       {2, 0, 3, 8, 1},
                       {0, 3, 0, 0, 7},
                       {6, 8, 0, 0, 9},
                       {1, 1, 7, 9, 0}};

    primMST(graph);

    return 0;
}
