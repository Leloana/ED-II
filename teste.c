#include <stdio.h>


int main (void){
    int num = 7;
    int soma = 0;
    for(int i = 1; i < num; i++){
        if((6%i) == 0){
            soma += i;
        }
    }
    if(soma == 6)printf("%d é perfeito", num);
    else printf("%d nao é perfeito", num);

    return 0;

}