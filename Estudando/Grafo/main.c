#include "lista.h"
#include "largura.h"
#include "profundidade.h"

int main(void){
    Vertice zero = newVertice(0);
    Vertice um = newVertice(1);
    Vertice dois = newVertice(2);
    Vertice tres = newVertice(3);
    Vertice quatro = newVertice(4);
    Vertice cinco = newVertice(5);
    addAresta(um,dois,10);
    addAresta(um,tres,15);
    addAresta(dois,quatro,20);
    addAresta(dois,cinco,25);
    addAresta(zero,um,25);



    visitaEmLargura(zero, 6);

    printf("\n==================================================");
    printf("\nBusca em Profundidade a partir do vertice %d: ", 0);
    visitaEmProfundidade(zero,6);

    printf("\n\nFOI");

    return 0;
}