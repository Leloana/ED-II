#include "fila.h"
#define TAM 6

// Enumeração para representar as cores dos vértices
enum Cor {
    BRANCO,
    CINZA,
    PRETO
};
// Estrutura para representar um nó na lista de adjacência
typedef  struct _node {
    int destino;
    struct _node* proximo;
}Node;

// Estrutura para representar um grafo
typedef struct _grafo {
    int V; // Número de vértices
    Node** listaAdj; // Lista de adjacência
}Grafo;

// Estrutura para representar informações sobre os vértices
typedef struct _infovertice {
    enum Cor cor;
    int distancia; // Distância a partir do vértice de origem
    int predecessor; // Vértice predecessor na busca em largura
}InfoVertice;

// Função para criar um novo nó na lista de adjacência
Node* novoNo(int destino) {
    Node* novo = (Node*)malloc(sizeof(Node));
    novo->destino = destino;
    novo->proximo = NULL;
    return novo;
}

// Função para criar um grafo com V vértices
Grafo* criarGrafo(int V) {
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
    grafo->V = V;
    grafo->listaAdj = (Node**)malloc(V * sizeof(Node*));

    // Inicializa todas as listas de adjacência como vazias
    for (int i = 0; i < V; ++i)
        grafo->listaAdj[i] = NULL;

    return grafo;
}

// Função para adicionar uma aresta ao grafo
void adicionarAresta(Grafo* grafo, int origem, int destino) {
    // Adiciona uma aresta da origem para o destino
    Node* novo = novoNo(destino);
    novo->proximo = grafo->listaAdj[origem];

    grafo->listaAdj[origem] = novo;
}

// Função para realizar a busca em largura no grafo a partir de um vértice
void buscaEmLargura(Grafo* grafo, int verticeInicial, InfoVertice* infoVertices) {
    printf("\n=======================================================");
    printf("\nBusca em Largura a partir do vértice %d: ", verticeInicial);
    // Inicializa a informação dos vértices
    for (int i = 0; i < grafo->V; ++i) {
        infoVertices[i].cor = BRANCO;
        infoVertices[i].distancia = -1;
        infoVertices[i].predecessor = -1;
    }

    // Inicializa a fila
    Queue fila = createQueue(grafo->V);

    // Marca o vértice inicial como cinza (visitado)
    infoVertices[verticeInicial].cor = CINZA;
    infoVertices[verticeInicial].distancia = 0;
    // Enfileira o vértice inicial
    insertQueue(fila, verticeInicial);
    // Loop principal da busca em largura
    while (!isEmptyQ(fila)) {
        // Desenfileira um vértice
        int verticeAtual = removeQueue(fila);

        // Percorre todos os vértices adjacentes ao vértice desenfileirado
        Node* atual = grafo->listaAdj[verticeAtual];
        while (atual != NULL) {
            int destino = atual->destino;
                

            // Enfileira o vértice adjacente se ainda não foi visitado
            if (infoVertices[destino].cor == BRANCO) {
                infoVertices[destino].cor = CINZA;
                infoVertices[destino].distancia = infoVertices[verticeAtual].distancia + 1;
                infoVertices[destino].predecessor = verticeAtual;
                printf("%d ", destino);
                insertQueue(fila, destino);
            }
            atual = atual->proximo;
        }

        // Marca o vértice como preto (totalmente explorado)
        infoVertices[verticeAtual].cor = PRETO;
    }
    // Imprime as informações sobre os vértices (distância e predecessor)
    printf("\n\nInformacoes sobre os vertices:\n");
    for (int i = 0; i < 6; ++i) {
        printf("Vertice %d: Distancia = %d, Anterior = %d, Cor = %d\n", i, infoVertices[i].distancia, infoVertices[i].predecessor,infoVertices[i].cor);
    }
    // Libera a memória alocada para a fila
    killQueue(fila);
}

// Função principal
int main() {
    // Exemplo de uso
    Grafo* grafo = criarGrafo(TAM);
    adicionarAresta(grafo, 0, 1);
    adicionarAresta(grafo, 0, 2);
    adicionarAresta(grafo, 1, 3);
    adicionarAresta(grafo, 1, 4);
    adicionarAresta(grafo, 2, 4);
    adicionarAresta(grafo, 3, 5);
    adicionarAresta(grafo, 4, 5);
    adicionarAresta(grafo, 5, 0);

    InfoVertice infoVertices[TAM];
    
    buscaEmLargura(grafo, 0, infoVertices);
    buscaEmLargura(grafo, 1, infoVertices);
    buscaEmLargura(grafo, 2, infoVertices);
    buscaEmLargura(grafo, 3, infoVertices);
    buscaEmLargura(grafo, 4, infoVertices);
    buscaEmLargura(grafo, 5, infoVertices);

    // Libera a memória alocada para o grafo
    for (int i = 0; i < grafo->V; ++i) {
        Node* atual = grafo->listaAdj[i];
        while (atual != NULL) {
            Node* proximo = atual->proximo;
            free(atual);
            atual = proximo;
        }
    }
    free(grafo->listaAdj);
    free(grafo);

    return 0;
}
