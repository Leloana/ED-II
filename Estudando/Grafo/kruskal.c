#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define V 4

// Estrutura para representar uma aresta
struct Aresta {
    int origem, destino, peso;
};

// Estrutura para representar um subconjunto para o Union-Find
struct Subset {
    int pai;
    int rank;
};

// Função para comparar as arestas com base no peso (para ordenação)
int compararArestas(const void *a, const void *b) {
    return ((struct Aresta *)a)->peso - ((struct Aresta *)b)->peso;
}

// Função para encontrar o subconjunto (representante) de um elemento i
int encontrar(struct Subset subsets[], int i) {
    if (subsets[i].pai != i)
        subsets[i].pai = encontrar(subsets, subsets[i].pai);
    return subsets[i].pai;
}

// Função para realizar a união de dois subconjuntos (por rank)
void unir(struct Subset subsets[], int x, int y) {
    int raizX = encontrar(subsets, x);
    int raizY = encontrar(subsets, y);

    if (subsets[raizX].rank < subsets[raizY].rank)
        subsets[raizX].pai = raizY;
    else if (subsets[raizX].rank > subsets[raizY].rank)
        subsets[raizY].pai = raizX;
    else {
        subsets[raizX].pai = raizY;
        subsets[raizY].rank++;
    }
}

// Função principal do algoritmo de Kruskal
void kruskal(int grafo[V][V]) {
    struct Aresta arestas[V * V];
    int numArestas = 0;

    // Preenche o array de arestas
    for (int i = 0; i < V; i++) {
        for (int j = i + 1; j < V; j++) {
            if (grafo[i][j] != 0) {
                arestas[numArestas].origem = i;
                arestas[numArestas].destino = j;
                arestas[numArestas].peso = grafo[i][j];
                numArestas++;
            }
        }
    }

    // Ordena as arestas em ordem crescente de peso
    qsort(arestas, numArestas, sizeof(struct Aresta), compararArestas);

    // Aloca espaço para os subconjuntos (representantes e ranks)
    struct Subset *subsets = (struct Subset *)malloc(V * sizeof(struct Subset));

    // Inicializa cada subconjunto com um único elemento e rank 0
    for (int i = 0; i < V; i++) {
        subsets[i].pai = i;
        subsets[i].rank = 0;
    }

    // Array para armazenar a árvore geradora mínima
    struct Aresta resultado[V];
    int indiceResultado = 0;

    // Índice usado para percorrer o array de arestas
    int i = 0;

    // O algoritmo continua até que a árvore geradora mínima tenha V-1 arestas
    while (indiceResultado < V - 1) {
        struct Aresta proximaAresta = arestas[i++];

        int raizOrigem = encontrar(subsets, proximaAresta.origem);
        int raizDestino = encontrar(subsets, proximaAresta.destino);

        // Se incluir a próxima aresta não forma um ciclo, inclui na árvore geradora mínima
        if (raizOrigem != raizDestino) {
            resultado[indiceResultado++] = proximaAresta;
            unir(subsets, raizOrigem, raizDestino);
        }
    }

    // Imprime a árvore geradora mínima
    printf("Aresta   Peso\n");
    for (int i = 0; i < indiceResultado; i++) {
        printf("%d - %d    %d\n", resultado[i].origem, resultado[i].destino, resultado[i].peso);
    }

    // Libera a memória alocada
    free(subsets);
}

int main(void) {
    int grafo[V][V] = {{0, 9, 3, 0},
                       {9, 0, 7, 2},
                       {3, 7, 0, 9},
                       {0, 2, 9, 0}};

    kruskal(grafo);

    return 0;
}
