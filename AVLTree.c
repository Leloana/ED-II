#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int TIPOCHAVE;

// Definição de uma estrutura de nó da árvore AVL
typedef struct aux {
    TIPOCHAVE chave;

    struct aux *esq;
    struct aux *dir;
    int Height;

}NO, *PONT;
// Função para calcular a altura de um nó
int getHeight(NO* node){
    if (node == NULL) return -1;
    else return node->Height;
}

int Maior(int value, int value1){
    return (value > value1) ? value : value1;
}

int Fb(NO* Tree){
    if(Tree != NULL){
        return (getHeight(Tree->esq) - getHeight(Tree->dir));
    }
    else return 0;
}
// Funcao para atualizar a altura de um no a cada insercao
void updateHeight(NO* node){
    int esqHeight = getHeight(node->esq);
    int dirHeight = getHeight(node->dir);
    node->Height = (esqHeight > dirHeight ? esqHeight : dirHeight) + 1;
}
// Funcao para realizar uma rotacao simples a esquerda
NO* rotateLeft(NO* Tree){
    //u e o filho
    //v e o neto
    printf("ESQ\n");
    NO* u = Tree->dir;
    NO* v = u->esq;

    u->esq = Tree;
    Tree->dir = v;

    updateHeight(Tree);
    updateHeight(u);

    return u;
}
// Funcao para realizar uma rotacao simples a direita
NO* rotateRight(NO* Tree){
    printf("DIR\n");
    NO* u = Tree->esq;
    NO* v = u->dir;

    u->dir = Tree;
    Tree->esq = v;

    updateHeight(Tree);
    updateHeight(u);

    return u;
}

NO* AVL(NO* Tree){
     // Atualiza a altura do no atual
    updateHeight(Tree);

    // Verifica o fator de balanceamento e realiza as rotacoes necessárias
    int balance = Fb(Tree);
    /*
    balance maior que 1 = o lado esquerdo esta MAIOR que o direito
    balance menor que 1 = o lado esquerdo esta MENOR que o direito
    */
    // Rotação à esquerda-direita (LR)
    if (balance > 1 && Fb(Tree->esq) < 0) {
        Tree->esq = rotateLeft(Tree->esq);
        return rotateRight(Tree);//retorna no rotacionado 
    }

    // Rotação à direita-esquerda (RL)
    else if (balance < -1 && Fb(Tree->dir) > 0) {
        Tree->dir = rotateRight(Tree->dir);
        return rotateLeft(Tree);
    }

    // Rotação à direita (RR)
    else if (balance > 1 && Fb(Tree->esq) >= 0)return rotateRight(Tree);

    // Rotação à esquerda (LL)
    else if (balance < -1 && Fb(Tree->dir) <= 0)return rotateLeft(Tree);

    return Tree;

}
// Funcao para inserir um valor na arvore AVL
NO* insert(NO* Tree, int value){
    if (Tree == NULL) {//Fator de parada da recursao
        NO* newNode = calloc(1,sizeof(NO));
        newNode->chave = value;
        newNode->esq = NULL;
        newNode->dir = NULL;

        newNode->Height = 0;

        return newNode;//retorna no e add ele a raiz principal na main
    }

    if (value < Tree->chave)Tree->esq = insert(Tree->esq, value);//checa se ele vai para a esquerda
    else if (value > Tree->chave)Tree->dir = insert(Tree->dir, value);//checa se ele vai para a direita
    else return Tree; //Se o novo valor nao vai nem para esquerda nem para a direita entao ele ja existe na arvore

    Tree = AVL(Tree);

    return Tree;
}


NO* deleteNode(NO* Tree, int value){
    if(Tree == NULL)return Tree;

    if(value == Tree->chave){//se no atual for igual a value sera deletado
        if ((Tree->esq == NULL) && (Tree->dir == NULL)){//se Tree nao tiver filhos entao e folha
            free(Tree);//uma folha pode ser deletada sem problemas

            return NULL;
        }
        else if((Tree->esq == NULL) || (Tree->dir == NULL)){//se Tree tiver galho esquerdo apenas
            NO* aux;
            if(Tree->esq != NULL)aux = Tree->esq;
            else if(Tree->dir != NULL)aux = Tree->dir;
            free(Tree);

            return aux;
        }
        else{
            NO *aux = Tree->esq;//Node apagado recebera o maior a esquerda

            while(aux->dir != NULL)aux = aux->dir;//devo procurar o maior node da parte esquerda
            Tree->chave = aux->chave;//valor a ser deletado recebe maior valor a sua esquerda
            aux->chave = value;//aux recebe o valor a ser deletado
            Tree->esq = deleteNode(Tree->esq,value);
            Tree = AVL(Tree);

            return Tree;
        }
    }
    else if(value > Tree->chave)Tree->dir = deleteNode(Tree->dir,value);// se value for maior que no atual vai para a direita
    else if(value < Tree->chave)Tree->esq = deleteNode(Tree->esq,value);// se value for menor que o no atual vai para a esquerda

    Tree = AVL(Tree);

    return Tree;
}
// Função para imprimir a árvore em ordem
void inorderTraversal(NO* Tree){
    if (Tree != NULL) {
        inorderTraversal(Tree->esq);
        printf("%d ", Tree->chave);
        inorderTraversal(Tree->dir);
    }
}
//funcao para visualizar mais facil a arvore
//ROXA = À ESQUERDA (menor)
//VERMELHO = À DIREITA (maior)
void DOT_Tree(NO* Tree, char* name){
    FILE* DOT = fopen(name, "a+");
    fprintf(DOT, "\n\t\t\"%d_%d\";",Tree->chave, Tree->Height);
    if(Tree->esq != NULL){//mesma logica de printfTree
        fprintf(DOT, "\n\t\t\"%d_%d\" -> \"%d_%d\";\n",Tree->chave,Tree->Height,Tree->esq->chave,Tree->esq->Height);
        fprintf(DOT, "\t\t\"%d_%d\"  [style=filled, fillcolor=purple, fontcolor=black];\n",Tree->esq->chave,Tree->esq->Height);//Nos a esquerda sao roxos
        DOT_Tree(Tree->esq, name);
    }

    if(Tree->dir != NULL){
        fprintf(DOT, "\n\t\t\"%d_%d\"-> \"%d_%d\";\n",Tree->chave,Tree->Height,Tree->dir->chave,Tree->dir->Height);
        fprintf(DOT, "\t\t\"%d_%d\"  [style=filled, fillcolor=red, fontcolor=black];\n",Tree->dir->chave,Tree->dir->Height);//Nos a direita sao vermelhos
        DOT_Tree(Tree->dir, name);
    }

    fclose(DOT);
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
int main(void){
    NO* cabeca = NULL;
    
    for(int i = 0; i < 127;i++)cabeca = insert(cabeca,i);
    for(int i = 1; i< 127; i++)cabeca = deleteNode(cabeca, i);

    printf("arvore AVL em ordem: ");
    inorderTraversal(cabeca);
    printf("\n");

    FILE* DOT = AbreEscritaDot("arvore.DOT");
    DOT_Tree(cabeca, "arvore.DOT");
    FechaEscritaDOT("arvore.DOT");

    return 0;
}