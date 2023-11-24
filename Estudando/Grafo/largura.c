#include "largura.h"

enum Cor {
    BRANCO,//Branco e o node ainda nao explorado
    CINZA,//cinza e o no que esta sendo explorado no momento
    PRETO//e o no ja explorado
};

typedef struct _infovertice {
    enum Cor cor;
    int valor;
    int distancia; // Distância a partir do vértice de origem
    int anterior; // Vértice anterior na busca em largura
}InfoVertice;

// Função para realizar a busca em largura no grafo a partir de um vértice
void visitaEmLargura(Vertice partida,int quantVertices) {
    int verticeInicial = getIndice(partida);
    printf("\n==================================================");
    printf("\nBusca em Largura a partir do vertice %d: ", verticeInicial);
    // Inicializa a informação dos vértices
    InfoVertice infoVertices[quantVertices];

    for (int i = 0; i < quantVertices; ++i) {
        infoVertices[i].cor = BRANCO;
        infoVertices[i].valor = -1;
        infoVertices[i].distancia = -1;
        infoVertices[i].anterior = -1;
    }

    // Inicializa a fila
    Queue fila = createQueue(quantVertices);

    // // Marca o vértice inicial como cinza (visitado)
    infoVertices[verticeInicial].cor = CINZA;
    infoVertices[verticeInicial].distancia = 0;
    infoVertices[verticeInicial].valor = verticeInicial;

    // Enfileira o vértice inicial
    insertQueue(fila, partida);
    // Loop principal da busca em largura
    while (!isEmptyQ(fila)) {
        // Desenfileira um vértice
        Vertice atual = removeQueue(fila);
        //indice do vertice atual
        int indiceAtual = getIndice(atual);
        // Pega lista de arestas adjacentes
        Lista adjacentes = getListaArestas(atual);

        if(!isEmptyList(adjacentes)){
            //Pega o no da lista de adjacentes
            Node no = getFistList(adjacentes);
            //Pega a aresta do no
            Aresta aresta = getData(no);
            // Pega o vertice da aresta
            Vertice adjacente = getVertice(aresta);

            while (adjacente != NULL) { 
                int destino = getIndice(adjacente);
                    
                // Enfileira o vértice adjacente se ainda não foi visitado
                if (infoVertices[destino].cor == BRANCO) {
                    infoVertices[destino].cor = CINZA;
                    infoVertices[destino].valor = destino;
                    infoVertices[destino].distancia = infoVertices[indiceAtual].distancia + getPeso(aresta);
                    infoVertices[destino].anterior = indiceAtual;
                    printf("%d ", destino);
                    insertQueue(fila, adjacente);
                }
                no = getNextList(no);
                aresta = getData(no);
                adjacente = getVertice(aresta);
            }
        }
        // Marca o vértice como preto (totalmente explorado)
        infoVertices[indiceAtual].cor = PRETO;
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