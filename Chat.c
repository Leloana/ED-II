#include <stdio.h>
#include <stdlib.h>

// Estrutura de um nó da árvore
typedef struct Node {
    int data;
    struct Node* parent;
    struct Node* left;
    struct Node* right;
    int color; // 0 para preto, 1 para vermelho
} Node;

// Estrutura de uma árvore rubro-negra
typedef struct RedBlackTree {
    Node* root;
} RedBlackTree;

// Função auxiliar para criar um novo nó
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;
    newNode->color = 1; // Por padrão, o novo nó é vermelho
    return newNode;
}

// Função auxiliar para encontrar o nó com o valor mínimo em uma árvore
Node* findMin(Node* node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

// Função auxiliar para realizar uma rotação à leftuerda
void rotateLeft(RedBlackTree* tree, Node* x) {
    Node* y = x->right;
    x->right = y->left;
    
    if (y->left != NULL) {
        y->left->parent = x;
    }
    
    y->parent = x->parent;
    
    if (x->parent == NULL) {
        tree->root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    
    y->left = x;
    x->parent = y;
}

// Função auxiliar para realizar uma rotação à righteita
void rotateRight(RedBlackTree* tree, Node* y) {
    Node* x = y->left;
    y->left = x->right;
    
    if (x->right != NULL) {
        x->right->parent = y;
    }
    
    x->parent = y->parent;
    
    if (y->parent == NULL) {
        tree->root = x;
    } else if (y == y->parent->left) {
        y->parent->left = x;
    } else {
        y->parent->right = x;
    }
    
    x->right = y;
    y->parent = x;
}

// Função auxiliar para ajustar o balanceamento após a inserção
void insertFixup(RedBlackTree* tree, Node* z) {
    while (z != tree->root && z->parent->color == 1) {
        if (z->parent == z->parent->parent->left) {
            Node* y = z->parent->parent->right;
            if (y != NULL && y->color == 1) {
                z->parent->color = 0;
                y->color = 0;
                z->parent->parent->color = 1;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    rotateLeft(tree, z);
                }
                z->parent->color = 0;
                z->parent->parent->color = 1;
                rotateRight(tree, z->parent->parent);
            }
        } else {
            Node* y = z->parent->parent->left;
            if (y != NULL && y->color == 1) {
                z->parent->color = 0;
                y->color = 0;
                z->parent->parent->color = 1;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rotateRight(tree, z);
                }
                z->parent->color = 0;
                z->parent->parent->color = 1;
                rotateLeft(tree, z->parent->parent);
            }
        }
    }
    
    tree->root->color = 0;
}

// Função para inserir um valor na árvore
void insert(RedBlackTree* tree, int data) {
    Node* newNode = createNode(data);
    Node* y = NULL;
    Node* x = tree->root;
    
    while (x != NULL) {
        y = x;
        if (newNode->data < x->data) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    
    newNode->parent = y;
    
    if (y == NULL) {
        tree->root = newNode;
    } else if (newNode->data < y->data) {
        y->left = newNode;
    } else {
        y->right = newNode;
    }
    
    insertFixup(tree, newNode);
}

// Função auxiliar para realizar a transplantação de um nó
void transplant(RedBlackTree* tree, Node* u, Node* v) {
    if (u->parent == NULL) {
        tree->root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    
    if (v != NULL) {
        v->parent = u->parent;
    }
}

// Função auxiliar para ajustar o balanceamento após a remoção
void deleteFixup(RedBlackTree* tree, Node* x) {
    while (x != tree->root && (x == NULL || x->color == 0)) {
        if (x == x->parent->left) {
            Node* w = x->parent->right;

            if (w != NULL && w->color == 1) {
                w->color = 0;
                x->parent->color = 1;
                rotateLeft(tree, x->parent);
                w = x->parent->right;
            }

            if ((w->left == NULL || w->left->color == 0) &&
                (w->right == NULL || w->right->color == 0)) {
                w->color = 1;
                x = x->parent;
            } else {
                if (w->right == NULL || w->right->color == 0) {
                    w->left->color = 0;
                    w->color = 1;
                    rotateRight(tree, w);
                    w = x->parent->right;
                }

                w->color = x->parent->color;
                x->parent->color = 0;
                w->right->color = 0;
                rotateLeft(tree, x->parent);
                x = tree->root;
            }
        } else {
            Node* w = x->parent->left;

            if (w != NULL && w->color == 1) {
                w->color = 0;
                x->parent->color = 1;
                rotateRight(tree, x->parent);
                w = x->parent->left;
            }

            if ((w->right == NULL || w->right->color == 0) &&
                (w->left == NULL || w->left->color == 0)) {
                w->color = 1;
                x = x->parent;
            } else {
                if (w->left == NULL || w->left->color == 0) {
                    w->right->color = 0;
                    w->color = 1;
                    rotateLeft(tree, w);
                    w = x->parent->left;
                }

                w->color = x->parent->color;
                x->parent->color = 0;
                w->left->color = 0;
                rotateRight(tree, x->parent);
                x = tree->root;
            }
        }
    }

    if (x != NULL) {
        x->color = 0;
    }
}



// Função para remover um valor da árvore
void deleteNode(RedBlackTree* tree, int data) {
    Node* z = tree->root;
    
    // Encontre o nó a ser removido
    while (z != NULL) {
        if (data == z->data) {
            break;
        }
        
        if (data < z->data) {
            z = z->left;
        } else {
            z = z->right;
        }
    }
    
    if (z == NULL) {
        // O valor não está na árvore
        return;
    }
    
    Node* y = z;
    int yOriginalColor = y->color;
    Node* x;
    
    if (z->left == NULL) {
        x = z->right;
        transplant(tree, z, z->right);
    } else if (z->right == NULL) {
        x = z->left;
        transplant(tree, z, z->left);
    } else {
        y = findMin(z->right);
        yOriginalColor = y->color;
        x = y->right;
        
        if (y->parent == z) {
            if (x != NULL) {
                x->parent = y;
            }
        } else {
            transplant(tree, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        
        transplant(tree, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    
    if (yOriginalColor == 0) {
        deleteFixup(tree, x);
    }
}


// Função para realizar um percurso em ordem na árvore
void inorderTraversal(Node* node) {
    if (node != NULL) {
        inorderTraversal(node->left);
        printf("%d ", node->data);
        inorderTraversal(node->right);
    }
}

void DOT_Tree(Node* Tree, char* name){
    FILE* DOT = fopen(name, "a+");
    fprintf(DOT, "\n\t\t\"%d_%d\";",Tree->data, Tree->color);
    if(Tree->left != NULL){//mesma logica de printfTree
        fprintf(DOT, "\n\t\t\"%d_%d\" -> \"%d_%d\";\n",Tree->data,Tree->color,Tree->left->data,Tree->left->color);
        fprintf(DOT, "\t\t\"%d_%d\"  [style=filled, fillcolor=purple, fontcolor=black];\n",Tree->left->data,Tree->left->color);//Nos a leftuerda sao roxos
        DOT_Tree(Tree->left, name);
    }

    if(Tree->right != NULL){
        fprintf(DOT, "\n\t\t\"%d_%d\"-> \"%d_%d\";\n",Tree->data,Tree->color,Tree->right->data,Tree->right->color);
        fprintf(DOT, "\t\t\"%d_%d\"  [style=filled, fillcolor=red, fontcolor=black];\n",Tree->right->data,Tree->right->color);//Nos a righteita sao vermelhos
        DOT_Tree(Tree->right, name);
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


int main() {
    RedBlackTree tree;
    tree.root = NULL;

    // Inserir valores de exemplo
    insert(&tree, 30);
    insert(&tree, 20);
    insert(&tree, 50);
    insert(&tree, 24);

    // Imprimir em ordem
    printf("Árvore Rubro-Negra em ordem: ");
    inorderTraversal(tree.root);
    printf("\n");

    
    // FILE* DOT = AbreEscritaDot("arvore.DOT");
    // DOT_Tree(tree.root, "arvore.DOT");
    // FechaEscritaDOT("arvore.DOT");

    // // Remover valor de exemplo
    deleteNode(&tree, 50);

    // FILE* DOT2 = AbreEscritaDot("mudancas.DOT");
    // DOT_Tree(tree.root, "mudancas.DOT");
    // FechaEscritaDOT("mudancas.DOT");


    // // Imprimir novamente após a remoção
    // printf("Árvore Rubro-Negra em ordem após a remoção: ");
    // inorderTraversal(tree.root);
    // printf("\n");

    return 0;
}
