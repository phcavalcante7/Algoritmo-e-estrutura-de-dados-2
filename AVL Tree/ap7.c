/*
Autor: Pedro Henrique Cavalcante
Turma: Noturno
*/

///Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#define RUBRO 1
#define NEGRO 0
#define TAM 99999

///TAD - arvore avl && arn
typedef struct arv{
    int valor, altura;
    struct arv* esq;
    struct arv* dir;
}tipoArvore;
typedef struct arvore {
    int valor, altura, cor;
    struct arv* pai;
    struct arv* esq;
    struct arv* dir;
}tipoARN;

///Funções e procedimentos para AVL
int altura(tipoArvore *t)
{
    int hEsq, hDir;

    if(t == NULL)       //raiz nula
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
void rotacaoR(tipoArvore** t)
{
    tipoArvore* tAux;

    if((*t)->esq == NULL) return;

    tAux = (*t)->esq;
    (*t)->esq = tAux->dir;
    tAux->dir = (*t);
    (*t)->altura = altura(*t);
    tAux->altura = altura(tAux);
    *t = tAux;
}

void rotacaoL(tipoArvore** t)
{
    tipoArvore* tAux;

    if( (*t)->dir == NULL) return;

    tAux = (*t)->dir;
    (*t)->dir = tAux->esq;
    tAux->esq = (*t);
    (*t)->altura = altura(*t);
    tAux->altura = altura(tAux);
    *t = tAux;
}

void ini_Arvore(tipoArvore* t)
{
    t->esq = NULL;
    t->dir = NULL;
    t->altura = 0;
}

int altura_Aux_Balancemento(tipoArvore* t) //retorna a altura de um no que nao seja nulo
{
    if(t == NULL)
        return 0;
    else
        return t->altura;
}

void balanceia(tipoArvore** t)
{
    int difAltura = altura_Aux_Balancemento((*t)->esq) - altura_Aux_Balancemento((*t)->dir);
    tipoArvore* tAux;

    if(difAltura > 1) { //AVL Desbalanceada (esq > dir)
        tAux = (*t)->esq;
        difAltura = altura_Aux_Balancemento(tAux->esq) - altura_Aux_Balancemento(tAux->dir);
        if(difAltura < 0) //vendo se vai ser LL ou LR
            rotacaoL(&((*t)->esq));
        rotacaoR(t);
    } else if(difAltura < -1) {//AVL Desbalanceada (dir > esq)
        tAux = (*t)->dir;
        difAltura = altura_Aux_Balancemento(tAux->esq) - altura_Aux_Balancemento(tAux->dir);
        if(difAltura > 0) //vendo se vai ser RL ou RR
           rotacaoR(&((*t)->dir));
        rotacaoL(t);
    }
}

void insere(tipoArvore** t, int v)
{
    tipoArvore* tAux;

    if( (*t) == NULL) {     //no chave null
        tAux = (tipoArvore*) malloc(sizeof (tipoArvore)); //aloc din
        ini_Arvore(tAux);
        tAux->valor = v;
        *t = tAux;
    } else if(v < (*t)->valor) //novo valor < no chave, insere na esquerda
        insere(&((*t)->esq), v);
      else if(v >= (*t)->valor)  //novo valor >= no chave, insere na direita
        insere(&((*t)->dir), v);

    (*t)->altura = altura(*t);
    balanceia(t);
}

tipoArvore* menor_Node(tipoArvore* t) //buscando o menor no da sub-arvore
{
    if(t->esq == NULL) return t;
    else return menor_Node(t->esq);
}

tipoArvore* pesquisa(tipoArvore* t, int v)
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

void deleta(tipoArvore** t, int v)
{
    tipoArvore* tAux;

    if((*t) == NULL) return;    //caso nao possua filhos

    if(v < (*t)->valor)         //caso o no a ser deletado seja menor
        deleta(&((*t)->esq), v);
    else if(v > (*t)->valor)    //caso seja maior
        deleta(&((*t)->dir), v);
    else {                      //caso seja o no raiz
        if((*t)->esq == NULL) {
            tAux = (*t)->dir;
            free(*t);
            *t = tAux;
            return;
        } else if((*t)->dir == NULL) {
            tAux = (*t)->esq;
            free(*t);
            *t = tAux;
            return;
        }
        tAux = menor_Node((*t)->dir);
        (*t)->valor = tAux->valor;
        deleta(&((*t)->dir), tAux->valor);
    }
    (*t)->altura = altura(*t);
    balanceia(t);
}

void free_AVL(tipoArvore* a)
{
    if(a != NULL){
        free_AVL(a->esq);
        free_AVL(a->dir);
        free(a); //free raiz
    }
}

///Funções e procedimentos para ARN

///Principal
int main() {
    //--vars--
    int id = 0, aux, pesq;
    int entrada[TAM], busca[TAM];
    tipoArvore* t = NULL;

    //--input--
    //-------------1-------------
    do {
        scanf("%d", &entrada[id]);
        aux = entrada[id];
        id++;
    } while(aux > 0);

    id = 0;
    //-------------2-------------
    do {
        scanf("%d", &busca[id]);
        aux = busca[id];
        id++;
    } while(aux > 0);

    //-------------3-------------
    scanf("%d", &pesq);

    id = 0;
    while(entrada[id] > 0) { //Inserindo os elementos na arvore
        insere(&t, entrada[id]);
        id++;
    }

    //--output--
    //-------------1-------------
    printf("%d, %d, %d\n", altura(t)-1, altura(t->esq), altura(t->dir));

    id = 0;
    while(busca[id] > 0) {  //Pesquisa na arvore
        if(pesquisa(t, busca[id]) == NULL) //caso nao tenha o elemento
            insere(&t, busca[id]);
        else
            deleta(&t, busca[id]);
        id++;
    }

    //-------------2-------------
    if(pesquisa(t, pesq) == NULL)
        printf("Valor nao encontrado");
    else {
        printf("%d, %d, %d", altura(pesquisa(t, pesq))-1, altura(pesquisa(t, pesq)->esq), altura(pesquisa(t, pesq)->dir));
    }

    //--free--
    free_AVL(t);
    return 0;
}
