#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 100
#define MAX_EDGES 100

// Estrutura para representar uma aresta
struct Edge {
    int source, destination, weight;
};

// Estrutura para representar um grafo
struct Graph {
    int V, E;
    struct Edge edge[MAX_EDGES];
};

// Função para inicializar o grafo com V vértices e E arestas
struct Graph* createGraph(int V, int E) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = E;
    return graph;
}

// Função para relaxar uma aresta (atualizar a distância se encontrar um caminho mais curto)
void relax(struct Graph* graph, int dist[], int src, int dest, int weight) {
    if (dist[src] != INT_MAX && dist[src] + weight < dist[dest]) {
        dist[dest] = dist[src] + weight;
    }
}

// Função principal do algoritmo de Bellman-Ford
void bellmanFord(struct Graph* graph, int src) {
    int V = graph->V;
    int E = graph->E;
    int dist[MAX_VERTICES];

    // Inicializa as distâncias como infinito
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
    }

    // Define a distância do vértice de origem como 0
    dist[src] = 0;

    // Relaxa todas as arestas repetidamente
    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            relax(graph, dist, graph->edge[j].source, graph->edge[j].destination, graph->edge[j].weight);
        }
    }

    // Verifica se há ciclos de peso negativo
    for (int i = 0; i < E; i++) {
        int u = graph->edge[i].source;
        int v = graph->edge[i].destination;
        int weight = graph->edge[i].weight;
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            printf("O grafo contém ciclos de peso negativo.\n");
            return;
        }
    }

    // Imprime as distâncias mais curtas
    printf("Distâncias mais curtas a partir do vértice %d:\n", src);
    for (int i = 0; i < V; i++) {
        printf("Para o vértice %d: %d\n", i, dist[i]);
    }
}

int main() {
    // Exemplo de uso
    int V = 5; // Número de vértices
    int E = 8; // Número de arestas

    struct Graph* graph = createGraph(V, E);

    // Arestas do grafo (origem, destino, peso)
    graph->edge[0].source = 0;
    graph->edge[0].destination = 1;
    graph->edge[0].weight = -1;

    graph->edge[1].source = 0;
    graph->edge[1].destination = 2;
    graph->edge[1].weight = 4;

    graph->edge[2].source = 1;
    graph->edge[2].destination = 2;
    graph->edge[2].weight = 3;

    graph->edge[3].source = 1;
    graph->edge[3].destination = 3;
    graph->edge[3].weight = 2;

    graph->edge[4].source = 1;
    graph->edge[4].destination = 4;
    graph->edge[4].weight = 2;

    graph->edge[5].source = 3;
    graph->edge[5].destination = 2;
    graph->edge[5].weight = 5;

    graph->edge[6].source = 3;
    graph->edge[6].destination = 1;
    graph->edge[6].weight = 1;

    graph->edge[7].source = 4;
    graph->edge[7].destination = 3;
    graph->edge[7].weight = -3;

    int source_vertex = 0;
    bellmanFord(graph, source_vertex);

    return 0;
}
