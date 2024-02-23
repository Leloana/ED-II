#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 100

// Estrutura para representar a fila
typedef struct {
    int items[MAX_VERTICES];
    int front;
    int rear;
} Queue;

// Inicializa a fila
void initializeQueue(Queue *q) {
    q->front = -1;
    q->rear = -1;
}

// Verifica se a fila está vazia
bool isEmpty(Queue *q) {
    return q->front == -1 && q->rear == -1;
}

// Insere um elemento na fila
void enqueue(Queue *q, int value) {
    if (isEmpty(q)) {
        q->front = 0;
        q->rear = 0;
    } else {
        q->rear++;
    }

    q->items[q->rear] = value;
}

// Remove e retorna um elemento da fila
int dequeue(Queue *q) {
    int item = q->items[q->front];

    if (q->front == q->rear) {
        q->front = -1;
        q->rear = -1;
    } else {
        q->front++;
    }

    return item;
}

// Verifica se há um elemento na fila
bool hasFront(Queue *q) {
    return q->front != -1;
}

// Função para realizar a busca em largura em uma matriz de adjacência
void bfs(int graph[MAX_VERTICES][MAX_VERTICES], int vertices, int startVertex) {
    // Vetor para marcar os vértices visitados
    bool visited[MAX_VERTICES] = {false};

    // Fila para armazenar os vértices a serem visitados
    Queue q;
    initializeQueue(&q);

    // Marca o vértice inicial como visitado e o adiciona à fila
    visited[startVertex] = true;
    enqueue(&q, startVertex);

    printf("BFS starting from vertex %d: ", startVertex);

    while (hasFront(&q)) {
        // Remove um vértice da fila e imprime
        int currentVertex = dequeue(&q);
        printf("%d ", currentVertex);

        // Para todos os vértices adjacentes ao vértice atual
        for (int i = 0; i < vertices; i++) {
            if (graph[currentVertex][i] == 1 && !visited[i]) {
                // Marca o vértice como visitado e o adiciona à fila
                visited[i] = true;
                enqueue(&q, i);
            }
        }
    }

    printf("\n");
}

//Mariana

int main() {
    // Exemplo de matriz de adjacência
    int graph[MAX_VERTICES][MAX_VERTICES] = {
        {0, 1, 1, 0, 0},
        {1, 0, 0, 1, 1},
        {1, 0, 0, 0, 1},
        {0, 1, 0, 0, 0},
        {0, 1, 1, 0, 0}
    };

    int vertices = 5;
    int startVertex = 0; // Vértice inicial para a busca em largura

    bfs(graph, vertices, startVertex);

    return 0;
}
