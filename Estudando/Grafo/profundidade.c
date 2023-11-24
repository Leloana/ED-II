#include "profundidade.h"

void visitaEmProfundidade(Vertice partida, int quantVertices){
    InfoVertice infoVertices[quantVertices];

    for (int i = 0; i < quantVertices; ++i) {
        infoVertices[i].cor = BRANCO;
        infoVertices[i].valor = -1;
        infoVertices[i].distancia = 0;
        infoVertices[i].anterior = -1;
    }
    
    profudidade(partida, infoVertices);

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
}

void profudidade(Vertice partida, InfoVertice* info){
    int verticeInicial = getIndice(partida);
    if(info[verticeInicial].cor == PRETO ) return;

    // Pega lista de arestas adjacentes
    Lista adjacentes = getListaArestas(partida);
    
    if(!isEmptyList(adjacentes)){
        printf("%d ",getIndice(partida));
        // //Pega o no da lista de adjacentes
        Node no = getFistList(adjacentes);
        //Pega a aresta do no
        Aresta aresta = getData(no);
        // Pega o vertice da aresta
        Vertice adjacente = getVertice(aresta);

        while (adjacente != NULL) { 
            int destino = getIndice(adjacente);

            info[destino].cor = CINZA;
            info[destino].valor = destino;
            info[destino].distancia = info[getIndice(partida)].distancia + getPeso(aresta);
            info[destino].anterior = getIndice(partida);   

            profudidade(adjacente, info);
            
            no = getNextList(no);
            aresta = getData(no);
            adjacente = getVertice(aresta);
        }
        
    info[getIndice(partida)].cor = PRETO;

    }
    else{
        printf("%d ", getIndice(partida));
        info[getIndice(partida)].cor = PRETO;

    }
} 