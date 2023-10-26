#include "fila.h"
#define TAM 6

// Enumeração para representar as cores dos vertices
enum Cor {
    BRANCO,//Branco e o node ainda nao explorado
    CINZA,//cinza e o no que esta sendo explorado no momento
    PRETO//e o no ja explorado
};

typedef  struct _node {
    int destino;//valor do elemento
    struct _node* proximo;
}Node;

// Estrutura para representar um grafo
typedef struct _grafo {
    int V; // Número de vértices
    Node** adjacentes; // Lista de adjacência
}Grafo;

// Estrutura para representar informações sobre os vértices
typedef struct _infovertice {
    enum Cor cor;
    int valor;
    int distancia; // Distância a partir do vértice de origem
    int anterior; // Vértice anterior na busca em largura
}InfoVertice;

// Função para criar um novo nó na lista de adjacência
Node* novoNo(int destino) {
    Node* novo = (Node*)calloc(1,sizeof(Node));
    novo->destino = destino;
    novo->proximo = NULL;
    return novo;
}

// Função para criar um grafo com V vértices
Grafo* criarGrafo(int V) {
    Grafo* grafo = calloc(1,sizeof(Grafo));
    grafo->V = V;
    grafo->adjacentes = calloc(V, sizeof(Node*));

    // Inicializa todas as listas de adjacência como vazias
    for (int i = 0; i < V; ++i)
        grafo->adjacentes[i] = NULL;

    return grafo;
}

// Função para adicionar uma aresta ao grafo
void addGrafo(Grafo* grafo, int origem, int destino) {
    // Adiciona uma aresta da origem para o destino
    Node* novo = novoNo(destino);
    novo->proximo = grafo->adjacentes[origem];

    grafo->adjacentes[origem] = novo;
}

// Função para realizar a busca em largura no grafo a partir de um vértice
void visitaEmLargura(Grafo* grafo, int verticeInicial, int quantVertices) {
    printf("\n==================================================");
    printf("\nBusca em Largura a partir do vertice %d: ", verticeInicial);
    // Inicializa a informação dos vértices
    InfoVertice infoVertices[quantVertices];

    for (int i = 0; i < grafo->V; ++i) {
        infoVertices[i].cor = BRANCO;
        infoVertices[i].valor = -1;
        infoVertices[i].distancia = -1;
        infoVertices[i].anterior = -1;
    }

    // Inicializa a fila
    Queue fila = createQueue(grafo->V);

    // Marca o vértice inicial como cinza (visitado)
    infoVertices[verticeInicial].cor = CINZA;
    infoVertices[verticeInicial].distancia = 0;
    infoVertices[verticeInicial].valor = verticeInicial;

    // Enfileira o vértice inicial
    insertQueue(fila, verticeInicial);
    // Loop principal da busca em largura
    while (!isEmptyQ(fila)) {
        // Desenfileira um vértice
        int verticeAtual = removeQueue(fila);

        // Percorre todos os vértices adjacentes ao vértice desenfileirado
        Node* atual = grafo->adjacentes[verticeAtual];
        while (atual != NULL) {
            int destino = atual->destino;
                

            // Enfileira o vértice adjacente se ainda não foi visitado
            if (infoVertices[destino].cor == BRANCO) {
                infoVertices[destino].cor = CINZA;
                infoVertices[destino].valor = destino;
                infoVertices[destino].distancia = infoVertices[verticeAtual].distancia + 1;
                infoVertices[destino].anterior = verticeAtual;
                printf("%d ", destino);
                insertQueue(fila, destino);
            }
            atual = atual->proximo;
        }

        // Marca o vértice como preto (totalmente explorado)
        infoVertices[verticeAtual].cor = PRETO;
    }
    // Imprime as informações sobre os vértices (distância e anterior)
    printf("\n\nInformacoes sobre os vertices:\n");
    for (int i = 0; i < quantVertices; ++i) {
        char* cor = NULL;
        if(infoVertices[i].cor == 0)cor = "BRANCO";
        else if (infoVertices[i].cor == 1)cor = "CINZA";
        else cor = "PRETO";

        if(infoVertices[i].valor != -1)printf("Vertice %d: Distancia = %d, Anterior = %d, Cor = %s\n",
         i,infoVertices[i].distancia, infoVertices[i].anterior,cor);
        else printf("Vertice %d: NAO ACESSADO\n", i);
    }
    // Libera a memória alocada para a fila
    killQueue(fila);
}

//funcoes para abrir arquivo dot
FILE* AbreEscritaDot(char* fn){
    FILE* dot = fopen(fn, "w");

    fprintf(dot, "\tdigraph BinaryTree {\n");
    
    fclose(dot);
    return dot;
}

void FechaEscritaDOT(char* fn){
    FILE* DOT = fopen(fn,"a+");
    fprintf(DOT,"\n\t}");
    fclose(DOT);
}

// Função principal
int main() {
    // Exemplo de uso
    int input = 0;
    int tamanho = 0;
    bool condicao = true;
    int quantidade = 0;

    printf("\nQUANTOS VERTICES TERA EM SEU GRAFO:");
    scanf("%d", &tamanho);
    Grafo* grafo = criarGrafo(tamanho);

    int controle[tamanho];
    for(int i = 0; i < tamanho; i ++)controle[i] = -1;
    FILE* DOT = AbreEscritaDot("grafo.DOT");


    while(condicao){
        printf("\n===================== GRAFOS =====================\n");
        printf("\n\tVERTICES INSERIDOS = %d", quantidade);
        
        printf("[");
        for(int k = 0; k < quantidade; k ++){
            printf("=");
        }
        for(int k = 0; k < (tamanho-quantidade); k ++){
            printf(" ");
        }
        printf("]");

        printf("\n\t[0]INSERIR UM GRAFO");
        printf("\n\t[1]VISITAR EM LARGURA");
        printf("\n\t[2]SAIR\n");
        printf("\n\tACAO = ");
        scanf("%d", &input);
        printf("\n==================================================\n");


        if(input == 0){
            int origem = 0;
            int destino = 0;

            printf("\nDIGITE A ORIGEM DO GRAFO = ");
            scanf("%d", &origem);
            int i = 0;
            bool achou = false;
            bool adiciona = true;
            for(i = 0; i < tamanho; i++){
                if(origem == controle[i])achou = true;//Checa se tem algum valor igual ja inserido
            }
            if(!achou){//Caso nao tiver o i vai ser igual ao tamanho e a quantidade aumentara 1
                if((quantidade+1) > tamanho){
                    printf("ABORTANDO INSERCAO DE GRAFO!!");
                    adiciona = false;
                }
                else{
                    controle[quantidade] = origem;
                    quantidade ++;

                    if(quantidade == tamanho)printf("TAMANHO MAXIMO DE VERTICES ALCANCADO!!");
                }
            }
            if(adiciona){
                printf("\nDIGITE O DESTINO DO GRAFO = ");
                scanf("%d", &destino);
                int j = 0;
                bool aqui = false;
                for(j = 0; j < tamanho; j++){
                    if(destino == controle[j])aqui = true;
                }

                if(!aqui){//Caso nao tiver o i vai ser igual ao tamanho e a quantidade aumentara 1
                    if((quantidade+1) > tamanho){
                        printf("ABORTANDO INSERCAO DE GRAFO!!");
                        adiciona = false;
                    }
                    else{
                        controle[quantidade] = destino;
                        quantidade ++;
                        if(quantidade == tamanho)printf("TAMANHO MAXIMO DE VERTICES ALCANCADO!!");
                    }
                }
            }
            if(adiciona){
                addGrafo(grafo, origem, destino);
                FILE* DOT = fopen("grafo.DOT", "a+");
                fprintf(DOT, "\n\t\t\"%d\" -> \"%d\";\n",origem,destino);
                fclose(DOT);
            }
        }

        else if(input == 1){
            int origem = 0;

            printf("\nDIGITE O VERTICE DE ORIGEM = ");
            scanf("%d", &origem);       

            visitaEmLargura(grafo, origem,tamanho);
        }

        else if(input == 2)condicao = false;
    }
    FechaEscritaDOT("grafo.DOT");
    return 0;
}
