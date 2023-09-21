#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "list.h"

#define TAM 99
//Calculo que define a posicao do elemento na hash pela DOBRA
int hashPosic(int value){
    int valor = value;
    char CHAVE[7];
    sprintf(CHAVE,"%d", valor);//Converte valor para string
    printf("\nCHAVE EM STRING = %s",CHAVE);
    int tam = strlen(CHAVE);
    printf("\nTAMANHO DA STRING = %d\n", tam);
    int num[6];

    if(tam > 6){
        printf("\n!!!TAMANHO INVALIDO, INSIRA UM ELEMENTO DE ATE 6 DIGITOS!!!\n");
        return 0 ;
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
    printf("%d }", num[5]);

    printf("\n\n");
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

    printf("Dobra 1 = {%d, %d, %d, %d}",dobra1[0],dobra1[1],dobra1[2],dobra1[3]);

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

    printf("\n\nHash tem 2 digitos de casas = {%s}", Resultado);

    dobraFinal = atoi(Resultado);

    return dobraFinal;
}
//Insira a hash table e o tamanho para inicializar as listas
void initHash(Lista hash[], int tamanho){
    for(int i = 0;i < tamanho; i++){
            Lista aux = createLst(-1);
            hash[i] = aux;
    }
}

int main(void){
    Lista vetor[TAM];
    initHash(vetor,6);
    int num;

    for(int i = 0; i < TAM; i++){
        printf("\nDIGITE A CHAVE %d = ", i);
        scanf("%d", &num);
        
        int posic = hashPosic(num);
        Lista aux = vetor[posic];
        printf("\nPOSIC %d = %d\n", i, posic);
        printf("\n========================================");
        insertLst(aux,(Item)num);//Insere o novo valor no final da lista
    }
}