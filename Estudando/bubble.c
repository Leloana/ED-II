#include <stdio.h>

int main(void){
    int vetor[5] = {5,3,2,6,1};

    for (int i = 0; i <5; i++)printf("%d ",vetor[i]);
    printf("\n");
    int k = 0;
    while(k < 5){
    
        int atual = vetor[k];
        int prox = vetor[k+1];
        if(k != 4 && atual > prox  ){
            printf("\nTroca efetuada:");
            printf("(%d ->%d )\n", atual, prox);
            
            vetor[k] = prox;
            vetor[k+1] = atual;

            printf("Vetor atual:");
            for (int j = 0; j <5; j++)printf("%d ",vetor[j]);
            k = 0;
        }
        else k++;
    }

    printf("\n");
    for (int i = 0; i <5; i++)printf("%d ",vetor[i]);
    return 0;
}