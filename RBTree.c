#include <stdio.h>
#include <stdlib.h>

typedef int TIPOCHAVE;

typedef struct _node {
    TIPOCHAVE chave;//conteudo
    
    struct _node* pai;//Aponta para o pai, é necessário para herdar cor e outras funcionalidades
    //Filhos padrao de arvore binaria
    struct _node* esq;
    struct _node* dir;

    int color; // 0 para preto, 1 para vermelho

} Node;

typedef struct _root {
    
    Node* root;//Identifica aquele nó como raiz

} Root;


//Funcao para criar no de valor dado como "value"
Node* createNode(int value, Root* Tree){
    Node* newNode = calloc(1, sizeof(Node));
    //Inicia valores
    newNode->chave = value;
    newNode->pai = NULL;
    newNode->esq = NULL;
    newNode->dir = NULL;

    newNode->color = 1; // Nos adicionados sao vermelhos no inicio

    return newNode;
}

// Função auxiliar para a rotação à esquerda
void Rotateesq(Root* Tree, Node* node){
    Node* FilhoDir = node->dir;

    node->dir = FilhoDir->esq;

    if (FilhoDir->esq != NULL)FilhoDir->esq->pai = node;
    FilhoDir->pai = node->pai;
    
    if (node->pai == NULL)Tree->root = FilhoDir;
    else if (node == node->pai->esq)node->pai->esq = FilhoDir;
    else node->pai->dir = FilhoDir;

    FilhoDir->esq = node;
    node->pai = FilhoDir;
}

// Função auxiliar para a rotação à direita
void Rotatedir(Root* Tree, Node* node){
    Node* FilhoEsq = node->esq;

    node->esq = FilhoEsq->dir;

    if (FilhoEsq->dir != NULL)FilhoEsq->dir->pai = node;
    FilhoEsq->pai = node->pai;

    if (node->pai == NULL) Tree->root = FilhoEsq;//caso seja a raiz 
    else if (node == node->pai->dir)node->pai->dir = FilhoEsq;
    else node->pai->esq = FilhoEsq;
    
    FilhoEsq->dir = node;
    node->pai = FilhoEsq;
}

void AjeitaTree(Root* Tree, Node* node){
    while (node != Tree->root && node->pai->color == 1){//Enquanto o pai for vermelho(propriedade 4)
        Node* Pai = node->pai;
        if (Pai == Pai->pai->esq){//Pai à esquerda
            Node* tio = Pai->pai->dir;

            //========= CASO 1 ESQ =======================================
            if (tio != NULL && tio->color == 1){//Se tio for vermelho
                Pai->color = 0;//Pai recebe preto
                tio->color = 0;//tio recebe preto
                if(Pai->pai == Tree->root)Pai->pai->color = 0;//se avo for raiz recebe preto
                else Pai->pai->color = 1;//se nao recebe vermelho

                node = Pai->pai;//node vai receber avo para continuar busca

            }
            
            //========= CASO 2 ESQ =======================================
            else{
                if (node == Pai->dir){//Checa se node esta a direita
                    node = Pai;//node recebe pai
                    Rotateesq(Tree, node);//rotaciona pau a esquerda

                }
                //========= CASO 3 ESQ =======================================
                Pai->color = 0;//Pai recebe preto
                Pai->pai->color = 1;//avo recebe vermelho
                Rotatedir(Tree, Pai->pai);//rotaciona avo à direita
            }

        } else{//Mesmos casos porem o pai esta à direita
            Node* tio = Pai->pai->esq;

            //========= CASO 1 DIR =======================================
            if (tio != NULL && tio->color == 1){
                Pai->color = 0;
                tio->color = 0;
                Pai->pai->color = 1;

                node = Pai->pai;

            } 
            //========= CASO 2 DIR =======================================
            else{
                if (node == Pai->esq){
                    node = Pai;
                    Rotatedir(Tree, node);//rotaciona no a direita

                }
                //========= CASO 3 DIR =======================================
                Pai->color = 0;
                Pai->pai->color = 1;
                Rotateesq(Tree, Pai->pai);//rotaciona avo a esquerda

            }
        }
    }
    Tree->root->color = 0;//Sempre define raiz como preta
}

void insert(Root* Tree, int value){
    Node* newNode = createNode(value, Tree);//Cria o novo a nó a ser adicionado

    Node* pai = NULL;//declara nó pai que sera usado nas comparaçoes
    Node* atual = Tree->root;//"atual" é o ponteiro que percorrerá a arvore

    // Busca o local para inserir o novo nó como em uma árvore binária de busca
    while (atual != NULL) {//Se atual == NULL significa que chegou ao fim da arvore
        pai = atual;
        if (value < atual->chave)atual = atual->esq;
        else if(value > atual->chave) atual = atual->dir;
        else{
            printf("\nValor ja inserido!!\n");
            return;
        }

    }
    //atual agora é igual a NULL
    //pai é igual ao pai de current

    newNode->pai = pai;
    if (pai == NULL) {// Arvore é vazia
        Tree->root = newNode;//Raiz recebe o novo nó
        newNode->color = 0; // Raiz é preta

    } else{//Se houver arvore
        if (value < pai->chave)pai->esq = newNode;
        else pai->dir = newNode;

    }
    //Faz rotaçoes/ coloracoes necessárias para manter balanceamento da arvore
    AjeitaTree(Tree, newNode);
}

void deleteFixup(Root* Tree,Root* teste, Node* x, Node* xParent){
    Node* w;

    if((x->pai != NULL) && (x == NULL || x->color == 0)){
        printf("        BANG BANG   0");
        if(x == xParent->esq){
            printf("        BANG BANG 1  ");
            w = xParent->dir;//w e irmao de x(o que queremos deletar)

            if(w->color == 1){//se o irmao for vermelho
                w->color = 0;//irmao fica preto
                xParent->color = 1;//pai fica vermelho
                Rotateesq(teste, xParent);//rotaciona
                w = xParent->dir;
            }

            if((w->esq == NULL || w->esq->color == 0) &&(w->dir == NULL || w->dir->color == 0)){
                printf("        BANG BANG   2");
                w->color = 1;
                x = xParent;
                xParent = x->pai;
            } else{
                if(w->dir == NULL || w->dir->color == 0){
                    w->esq->color = 0;
                    w->color = 1;
                    Rotatedir(teste, w);
                    w = xParent->dir;
                }
                w->color = xParent->color;
                xParent->color = 0;
                w->dir->color = 0;
                Rotateesq(teste, xParent);
                x = Tree->root;
            }
        } 
        else{
            printf("    EITAAA  ");
            w = xParent->esq;

            if(w->color == 1){
                w->color = 0;
                xParent->color = 1;
                Rotatedir(Tree, xParent);
                w = xParent->esq;
            }

            if((w->dir == NULL || w->dir->color == 0) && (w->esq == NULL || w->esq->color == 0)){
                w->color = 1;
                x = xParent;
                xParent = x->pai;
            } else{
                if(w->esq == NULL || w->esq->color == 0){
                    w->dir->color = 0;
                    w->color = 1;
                    Rotateesq(teste, w);
                    w = xParent->esq;
                }
                printf("    Amoeba ganes");
                w->color = xParent->color;
                xParent->color = 0;
                w->esq->color = 0;
                Rotatedir(teste, xParent);
                x = Tree->root;
            }
        }
    }
    printf("    CABO");
    if (x != NULL)x->color = 0;
}


void deleteNode(Root* Tree,Root* teste, int value){
    Node* atual = Tree->root;//"atual" é o ponteiro que percorrerá a arvore
    printf("\nDeleting...\n");
    while (atual->chave != value || atual != NULL) {//Se atual == NULL significa que chegou ao fim da arvore
        if(value == atual->chave)break;
        else if (value < atual->chave)atual = atual->esq;
        else if(value > atual->chave)atual = atual->dir;

    }
    if(!atual){
        printf("\nValor nao encontrado!!\n");//Caso atual seja == NULL o valor nao existe na arvore
        return;//sai do remove
    }

    if((atual->dir == NULL) && (atual->esq == NULL)){//se for no folha
        if(atual->color == 0)deleteFixup(Tree,teste,atual, atual->pai);//se remover uma folha preta precisa corrigir
        
        if(atual->pai->esq == atual)atual->pai->esq = NULL;//zera os ponteiros do pai
        else atual->pai->dir = NULL;

        free(atual);//Caso seja uma folha 
    }
    else if((atual->dir != NULL) || (atual->esq != NULL)){//Caso Tenha algum filho
        Node* aux;
        if(atual->dir) aux = atual->dir;//aux recebe o no que existir
        else aux = atual->esq;

        while(aux->esq != NULL)aux = aux->esq;//devo procurar o menor node da parte direita
        atual->chave = aux->chave;//valor a ser deletado recebe menor valor a sua direita
        aux->chave = value;//aux recebe o valor a ser deletado

        Root auxTree;
        if(atual->dir) auxTree.root = atual->dir;//aux recebe o no que existir
        else auxTree.root = atual->esq;

        deleteNode(&auxTree,teste,value);
    }
}

// Função para imprimir a árvore em ordem
void printfTree(Node* node){
    if (node != NULL) {
        printfTree(node->esq);
        printf("%d ", node->chave);
        printfTree(node->dir);
    }
}

void DOT_Tree(Node* Tree, char* name){
    FILE* DOT = fopen(name, "a+");
    fprintf(DOT, "\n\t\t\"%d_%d\";",Tree->chave, Tree->color);
    if(Tree->esq != NULL){//mesma logica de printfTree
        fprintf(DOT, "\n\t\t\"%d_%d\" -> \"%d_%d\";\n",Tree->chave,Tree->color,Tree->esq->chave,Tree->esq->color);
        fprintf(DOT, "\t\t\"%d_%d\"  [style=filled, fillcolor=purple, fontcolor=black];\n",Tree->esq->chave,Tree->esq->color);//Nos a esquerda sao roxos
        DOT_Tree(Tree->esq, name);
    }

    if(Tree->dir != NULL){
        fprintf(DOT, "\n\t\t\"%d_%d\"-> \"%d_%d\";\n",Tree->chave,Tree->color,Tree->dir->chave,Tree->dir->color);
        fprintf(DOT, "\t\t\"%d_%d\"  [style=filled, fillcolor=red, fontcolor=black];\n",Tree->dir->chave,Tree->dir->color);//Nos a direita sao vermelhos
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

int main(void){
    Root cabeca;
    cabeca.root = NULL;

    // Inserção de valores de exemplo
    insert(&cabeca, 30);
    insert(&cabeca, 20);
    insert(&cabeca, 50);
    insert(&cabeca, 14);

    insert(&cabeca, 60);
    insert(&cabeca, 10);
    insert(&cabeca, 80);
    insert(&cabeca, 55);
    insert(&cabeca, 1);


    // Impressão em ordem
    printf("Árvore Rubro-Negra em ordem: ");
    printfTree(cabeca.root);
    printf("\n");

    FILE* DOT = AbreEscritaDot("arvore.DOT");
    DOT_Tree(cabeca.root, "arvore.DOT");
    FechaEscritaDOT("arvore.DOT");

    deleteNode(&cabeca,&cabeca,30);
    deleteNode(&cabeca,&cabeca,1);
    deleteNode(&cabeca,&cabeca,55);
    deleteNode(&cabeca,&cabeca,80);
    deleteNode(&cabeca,&cabeca,20);
    deleteNode(&cabeca,&cabeca,50);
    deleteNode(&cabeca,&cabeca,60);
    deleteNode(&cabeca,&cabeca,14);

    FILE* DOT2 = AbreEscritaDot("mudancas.DOT");
    DOT_Tree(cabeca.root, "mudancas.DOT");  
    FechaEscritaDOT("mudancas.DOT");

    printf("\n%d", cabeca.root->chave);

    return 0;
}
