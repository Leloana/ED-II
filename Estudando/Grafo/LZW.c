#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void LZW(char* palavra){
    int i = 0;

    char Dicionario[64][3];

    while (palavra[i+1]!= '\0'){

        Dicionario[i][0] = palavra[i];
        Dicionario[i][1] = palavra[i+1];
        Dicionario[i][2] = '\0';

        printf("\n%d = %s",i, Dicionario[i]);
        i++;
    }

    
    
}


int main(void){
    char palavra[64];
    scanf(" %s", palavra);
    //  A   B   C   A   J   K   J   A   B   J   U
    /*

    COMPRESSAO = A B C A J K J 1 J U
    DICIONARIO =
    1 = A B     5 = J K     9 = J U
    2 = B C     6 = K J
    3 = C A     7 = J A
    4 = A J     8 = 1 J
    
    */ 

    // A    B   C   A   J   K   J   1   J   U
    /*

    DESCOMPRESSAO =  A B C A J K J A B J U
    DICIONARIO =
    1 = A B
    2 = B C
    3 = C A
    4 = A J
    5 = J K
    6 = K J
    7 = J A
    8 = 1 J
    9 = J U
    */ 



    printf("\n%s\n", palavra);

    LZW(palavra);

    printf("\n\n");
    return 0;
}