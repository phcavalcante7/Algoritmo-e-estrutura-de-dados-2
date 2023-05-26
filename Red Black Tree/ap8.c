/*
Autor: Pedro Henrique Cavalcante
Turma: Noturno
*/

///Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#define RUBRO 1
#define NEGRO 0

///TAD - RBTree && AVL
struct arv {
    int valor, altura;
    struct arv *esq, *dir;
};
typedef struct arv AVLTree;

struct node {
    int valor, cor;
    struct node *pai, *esq, *dir;
};
typedef struct node *NodePtr;

///Funções e procedimentos para AVL
void initAVL(AVLTree* t)
{
    t->esq = NULL;
    t->dir = NULL;
    t->altura = 0;
}

int altura(AVLTree *t)
{
    int hEsq, hDir;

    if(t == NULL)
        return 0;
    else {
        hEsq = altura(t->esq);
        hDir = altura(t->dir);
        if(hEsq < hDir) //right bigger
            return hDir + 1;
        else            //left bigger
            return hEsq + 1;
    }
}

//Rotacoes
void rotacaoR(AVLTree** t)
{
    AVLTree* tAux;

    if((*t)->esq == NULL) return;

    tAux = (*t)->esq;
    (*t)->esq = tAux->dir;
    tAux->dir = (*t);
    (*t)->altura = altura(*t);
    tAux->altura = altura(tAux);
    *t = tAux;
}

void rotacaoL(AVLTree** t)
{
    AVLTree* tAux;

    if( (*t)->dir == NULL) return;

    tAux = (*t)->dir;
    (*t)->dir = tAux->esq;
    tAux->esq = (*t);
    (*t)->altura = altura(*t);
    tAux->altura = altura(tAux);
    *t = tAux;
}

int altura_Aux_Balancemento(AVLTree* t) //retorna a altura de um no que nao seja nulo
{
    if(t == NULL) return 0;
    else return t->altura;
}

void balanceia(AVLTree** t, int** contador)
{
    int difAltura = altura_Aux_Balancemento((*t)->esq) - altura_Aux_Balancemento((*t)->dir);
    AVLTree* tAux;

    if(difAltura > 1) { //AVL Desbalanceada (esq > dir)
        tAux = (*t)->esq;
        difAltura = altura_Aux_Balancemento(tAux->esq) - altura_Aux_Balancemento(tAux->dir);
        if(difAltura < 0) { //vendo se vai ser LL ou LR
            rotacaoL(&((*t)->esq));

        }
        rotacaoR(t);
        (**contador)++;
    } else if(difAltura < -1) {//AVL Desbalanceada (dir > esq)
        tAux = (*t)->dir;
        difAltura = altura_Aux_Balancemento(tAux->esq) - altura_Aux_Balancemento(tAux->dir);
        if(difAltura > 0) { //vendo se vai ser RL ou RR
            rotacaoR(&((*t)->dir));

        }
        rotacaoL(t);
        (**contador)++;
    }
}

void insere(AVLTree** t, int v, int* contador)
{
    AVLTree* tAux;

    if( (*t) == NULL) {     //no chave null
        tAux = (AVLTree*) malloc(sizeof (AVLTree)); //aloc din
        initAVL(tAux);
        tAux->valor = v;
        *t = tAux;
    } else if(v < (*t)->valor) //novo valor < no chave, insere na esquerda
        insere(&((*t)->esq), v, contador);
      else if(v >= (*t)->valor)  //novo valor >= no chave, insere na direita
        insere(&((*t)->dir), v, contador);

    (*t)->altura = altura(*t);
    balanceia(t, &contador);
}

AVLTree* menor_Node(AVLTree* t) //buscando o menor no da sub-arvore
{
    if(t->esq == NULL) return t;
    else return menor_Node(t->esq);
}

AVLTree* pesquisa(AVLTree* t, int v)
{
    if(t == NULL) return NULL;

    else {
        if(v == t->valor)
            return t; //pai

        else if(pesquisa(t->esq, v))
            return pesquisa(t->esq, v); //esq

        else
            return pesquisa(t->dir, v); //dir
    }
}

void freeAVL(AVLTree* a)
{
    if(a != NULL){
        freeAVL(a->esq);
        freeAVL(a->dir);
        free(a); //free raiz
    }
}

///Funções e procedimentos para ARN
NodePtr create_NIL()
{
    NodePtr t = (NodePtr) malloc(sizeof(struct node));
    t->pai = NULL;
    t->cor = NEGRO;
    t->esq = NULL;
    t->dir = NULL;
    t->valor = 0;
    return t;
}

NodePtr RBSearch(NodePtr node, int chave) //Procura em rubro negro
{
    if(node == NULL) return NULL;

    else if(chave == node->valor) return node;

    else if(chave < node->valor) return RBSearch(node->esq, chave);

    else return RBSearch(node->dir, chave);
}

void left_Rotate(NodePtr z, NodePtr* root, NodePtr NIL)
{
    NodePtr y = z->dir;
    z->dir = y->esq;

    if(y->esq != NIL)
        y->esq->pai = z;

    y->pai = z->pai;

    if(z->pai == NULL)
        (*root) = y;

    else if(z == z->pai->esq)
        z->pai->esq = y;

    else
        z->pai->dir = y;

    y->esq = z;
    z->pai = y;
}

void right_Rotate(NodePtr x, NodePtr* root, NodePtr NIL)
{
    NodePtr y = x->esq;
    x->esq = y->dir;

    if(y->dir != NIL)
        y->dir->pai = x;

    y->pai = x->pai;

    if(x->pai == NULL)
        (*root) = y;

    else if(x == x->pai->dir)
        x->pai->dir = y;

    else if(x == x->pai->esq)
        x->pai->esq = y;

    y->dir = x;
    x->pai = y;
}

//Mudar a cor caso precise e incrementar 1 ao contador do output 4
void Rubro(NodePtr node, int*** cont)
{
    if(node->cor == RUBRO) return;
    else {
        node->cor = RUBRO;
        (***cont)++;
    }
}
void Negro(NodePtr node, int*** cont)
{
    if(node->cor == NEGRO) return;
    else {
        node->cor = NEGRO;
        (***cont)++;
    }
}

void RB_INSERT_FIXUP(NodePtr B, NodePtr* root,int** contadorCor, int** contadorRotacao, NodePtr NIL) //Verifica as propriedades rubro-negras
{
    NodePtr D, C = B->pai->pai, A = B->pai;

    if(C == NULL || A->cor == NEGRO) {
        return;
    }

    if(A == C->esq) { //'A' left child
        D = C->dir;
        // case 1 : red uncle //
        if(D->cor == RUBRO) {
            Negro(A, &contadorCor);
            Negro(D, &contadorCor);
            Rubro(C, &contadorCor);
            B = C;
            if(B->pai != NULL && B->pai->cor == RUBRO) //iterative until father be black
                RB_INSERT_FIXUP(B, root, contadorCor, contadorRotacao, NIL);

        } else { // case 2 : black uncle //
                if(B == A->dir) { //lower case 2.1 : 'B' right child
                left_Rotate(A, root, NIL); // implies case 3.1
                (**contadorRotacao)++;
                //case 3.1 //
                Negro(B, &contadorCor);
                Rubro(C, &contadorCor);
                right_Rotate(C, root, NIL);
                (**contadorRotacao)++;
                } else {
                // case 3.1 : black uncle, 'A' left, 'B' left //
                Negro(A, &contadorCor);
                Rubro(C, &contadorCor);
                right_Rotate(C, root, NIL);
                (**contadorRotacao)++;
                }

        }
    } else { //'A' right child
        D = C->esq;
        if(D->cor == RUBRO) {
            Negro(A, &contadorCor);
            Negro(D, &contadorCor);
            Rubro(C, &contadorCor);
            B = C;
            if(B->pai != NULL && B->pai->cor == RUBRO)
                RB_INSERT_FIXUP(B, root, contadorCor, contadorRotacao, NIL);
        } else {
            if(B == A->esq) { //'B' left child
                right_Rotate(A, root, NIL);
                (**contadorRotacao)++;
                Negro(B, &contadorCor);
                Rubro(C, &contadorCor);
                left_Rotate(C, root, NIL);
                (**contadorRotacao)++;
            } else {
                Negro(A, &contadorCor);
                Rubro(C, &contadorCor);
                left_Rotate(C, root, NIL);
                (**contadorRotacao)++;
            }
        }
    }
    (*root)->cor = NEGRO;
}

void RB_INSERT(NodePtr* root, NodePtr NIL, int v, int* contadorCor, int* contadorRotacao) //Insert Rec da ARN
{
    NodePtr z = (NodePtr) malloc(sizeof(struct node)); // new node
    z->valor = v;
    z->esq = NIL;
    z->dir = NIL;

    //first insert
    if( (*root) == NIL) {
        z->cor = NEGRO;
        z->pai = NULL;
        (*root) = z;
    } else { //cormen insert
        NodePtr y = NULL;
        NodePtr x = (*root);

        while(x != NIL)
        {
            y = x;
            if(z->valor < x->valor)
                x = x->esq;
            else
                x = x->dir;
        }
        z->pai = y;
        if(z->valor < y->valor)
            y->esq = z;
        else
            y->dir = z;

        z->cor = RUBRO;
        RB_INSERT_FIXUP(z, root, &contadorCor, &contadorRotacao, NIL);
    }
}

int bigger(int x, int y) //Retorna o maior p auxiliar na altura negra
{
    if(x > y) return x;
    else      return y;
}

int BH(NodePtr node, NodePtr NIL) //Calcula a altura negra da arvore
{
    if(node == NIL) return 0;
    return (!node->cor) * 1 + bigger(BH(node->esq, NIL), BH(node->dir, NIL));

}

int height(NodePtr root) //Calcula a altura normal da arvore
{
    int hEsq, hDir;

    if (root == NULL)
        return -1;
    else {
        hEsq = height(root->esq);
        hDir = height(root->dir);
        if (hEsq < hDir)
            return hDir + 1;
         else
            return hEsq + 1;

    }
}

void RBFree(NodePtr node, NodePtr NIL)
{
    if(node->esq != NIL && node->dir != NIL) {
        RBFree(node->esq, NIL);
        RBFree(node->dir, NIL);
        free(node);
    } else if(node->esq != NIL) {
        RBFree(node->esq, NIL);
        free(node);
    } else if(node->dir != NIL) {
        RBFree(node->dir, NIL);
        free(node);
    } else
        free(node);
}

///Principal
int main() {
    //--vars--
    int n, entrada[999], suporte[999], id = 0;
    int swapCor = 0, rotacoesAVP = 0, rotacoesAVL = 0; //auxiliares para o 4 output
    AVLTree* avl = NULL;
    NodePtr NIL = create_NIL();
    NodePtr root = NIL;

    //--input--
    do {
        scanf("%d", &n);
        entrada[id] = n;
        suporte[id] = n;
        id++;
    } while(n >= 0);
    id = 0;
    while(entrada[id] >= 0 && suporte[id] >= 0) //INSERTS
    {
        insere(&avl, entrada[id], &rotacoesAVL);
        RB_INSERT(&root, NIL, suporte[id], &swapCor, &rotacoesAVP);
        id++;
    }

    //--output--
    printf("%d, %d, %d\n", altura(avl)-1, altura(avl->esq), altura(avl->dir));     //1
    printf("%d, %d, %d\n", height(root)-1, height(root->esq), height(root->dir));  //2
    printf("%d\n", BH(root, NIL));                                                 //3
    printf("%d, %d, %d\n", swapCor, rotacoesAVP, rotacoesAVL);                     //4

    //--free--
    freeAVL(avl);
    RBFree(root, NIL);
    free(NIL);
    return 0;
}
