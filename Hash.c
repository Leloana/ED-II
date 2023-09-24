#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "list.h"

#define TAM 100
//Calculo que define a posicao do elemento na hash pela DOBRA
int hashPosic(int value){
    int valor = value;
    char CHAVE[7];
    sprintf(CHAVE,"%d", valor);//Converte valor para string
    int tam = strlen(CHAVE);
    int num[6];

    if(tam > 6){
        printf("\n!TAMANHO INVALIDO, INSIRA UM ELEMENTO DE ATE 6 DIGITOS!\n");
        return -1 ;
    }
    
    //TRANSFERE DIGITO PARA VETOR
    if(tam == 6){//caso o digito tenha o tamanho maximo
        for (int i = 0 ; i < tam; i++) {
            num[5 - i] = valor % 10;
            valor /= 10;
        }
    }
    else{//caso contrario
        for (int i = 0 ; i < (6 - tam); i++) {
            num[i] = 0;
        }
        int aux = tam - 1;
        for (int i = (6 - tam) ; i < 6 ; i++) {
            num[(6 - tam) + aux] = valor % 10;
            valor /= 10;
            aux--;
        } 
    }
    
    printf("\nVETOR FORMADO = {");
    for (int i = 0 ; i < 5; i++) {
        printf("%d, ",num[i]);
    }
    printf("%d}", num[5]);

    int dobra1[4];
    if((num[0]%10) + (num[3]%10) >= 10){//se a soma do segundo digito subir 1
        dobra1[1] = num[0] + num[3] - 10;
    }
    else dobra1[1] = num[0] + num[3];

    if((num[1]%10) + (num[2]%10) >= 10){//se a soma do segundo digito subir 1
        dobra1[0] = num[1] + num[2] - 10;
    }
    else dobra1[0] = num[1] + num[2];
 
    dobra1[2] = num[4];
    dobra1[3] = num[5];

    printf("\nDobra 1 = {%d, %d, %d, %d}",dobra1[0],dobra1[1],dobra1[2],dobra1[3]);

    int dobra2[2];

    if((dobra1[0]%10) + (dobra1[3]%10) >= 10){//se a soma do segundo digito subir 1
        dobra2[1] = dobra1[0] + dobra1[3] - 10;
    }
    else dobra2[1] = dobra1[0] + dobra1[3];

    if((dobra1[1]%10) + (dobra1[2]%10) >= 10){//se a soma do segundo digito subir 1   
        dobra2[0] = dobra1[1] + dobra1[2] - 10;
    }
    else dobra2[0] = dobra1[1] + dobra1[2];  

    printf("\nDobra 2 = {%d, %d}",dobra2[0],dobra2[1]);


    int dobraFinal = 0;
    char Digito1[10];
    char Digito2[10];
    char Resultado[20];

    sprintf(Digito1,"%d", dobra2[0]);
    sprintf(Digito2,"%d", dobra2[1]);

    strcpy(Resultado,Digito1);
    strcat(Resultado,Digito2);

    dobraFinal = atoi(Resultado);

    return dobraFinal;
}

bool deleteValue(Lista hash[], int value){
    int posic = hashPosic(value);

    if(!hash[posic]){
        printf("\n\n!NUMERO NAO ENCONTRADO!");
        return false;
    }
    
    Lista aux = hash[posic];
    int num = 0;
    Posic deletPointer = getFirstLst(aux);//deletPointer recebe a cabeca da lista
    num = getLst(aux, deletPointer);

    while(num != value ){
        deletPointer = getNextLst(aux, deletPointer);//deletPointer recebe o proximo ponteiro em relacao a ele mesmo   
        if (deletPointer == NULL)break; 
        num = getLst(aux, deletPointer);
    }

    if (deletPointer == NULL){
        printf("\n\n!NUMERO NAO ENCONTRADO!");
        return false;
    }
    
    removeLst(aux, deletPointer);
    return true;
}

void printPosic(Lista hash[], int posic){
    if(hash[posic] == NULL){
        printf("\nNAO HA VALORES NESTE SETOR");
        return;
    }
    
    Lista aux = hash[posic];
    Iterador K = createIterator(aux,false);

    printf("\nLISTA[%d] = ", posic);
    while (!isIteratorEmpty(aux,K)){
        printf(" %d ", (int)getIteratorNext(aux,K));
    }
}

int main(void){
    Lista vetor[TAM] = {0};
    int Inseridos[100] = {0};
    int quantia = 0;

    int removidos[100] = {0};
    int quantiaRem = 0;

    int num;

    int input = 0;
    printf("\n=====================TABELA HASH====================\n");
    printf("\n\t\t[0]INSERIR UM VALOR\n");
    printf("\n\t\t[1]REMOVER UM VALOR\n");
    printf("\n\t\t[2]ESCREVER LISTA\n");
    printf("\n\t\t[3]SAIR\n");
    printf("\n======================================================\n");
    printf("\nACAO = ");
    
    scanf("%d", &input);

    while(input != 3){
        if(input == 0){
            printf("\nDIGITE A CHAVE = ");
            
            scanf("%d", &num);
            
            int posic = hashPosic(num);
            if(posic > 0){
                if(vetor[posic] == NULL){
                    Lista new = createLst(-1);
                    vetor[posic] = new;
                }

                Lista aux = vetor[posic];

                printf("\n\nPOSICAO = {%d}\n",posic);

                insertLst(aux,num);//Insere o novo valor no final da lista

                Inseridos[quantia] = (int)num;
                quantia++;

                printf("\nINSERIDO COM SUCESSO!!");
            }
        }
        else if(input == 1){
            printf("\nVALORES INSERIDOS: ");
            for(int i = 0; i < quantia; i ++){
                printf(" %d ", Inseridos[i]);
            }
            printf("\nVALORES REMOVIDOS: ");
            for(int i = 0; i < quantiaRem; i ++){
                printf(" %d ", removidos[i]);
            }

            int removido = 0;
            printf("\nVALOR A REMOVER = ");
            scanf("%d", &removido);

            if(deleteValue(vetor, removido)){
            removidos[quantiaRem] = removido;
            quantiaRem ++;
            printf("\n\nREMOCAO CONCLUIDA");
            }
        }

        else if(input == 2){
            int posicao = 0;
            printf("\nPOSICAO DA LISTA = ");
            scanf("%d", &posicao);
            printPosic(vetor, posicao);
            printf("\n\nESCRITA CONCLUIDA");
        }
        printf("\n======================================================\n");
        printf("\nACAO = ");
        scanf("%d", &input);
    }
    return 0;
}