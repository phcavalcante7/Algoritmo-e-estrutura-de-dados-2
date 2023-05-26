/// Ordenacao de uma lista simplesmente encadeada com mergesort [complexidade O(n * log n)] e sem variavel global

//Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Estrutura de dado
typedef struct info {
    int chave;
    struct info *prox;
}tipoInfo;

//Functions
void insere(tipoInfo **aux, int k) //k-key
{
    tipoInfo *novo = (tipoInfo*) malloc(sizeof(tipoInfo));
    novo->chave = k;
    novo->prox  = (*aux);
    (*aux) = novo;
}

void printa_Lista(tipoInfo *aux)
{
    while(aux != NULL) {
        printf("%d ", aux->chave);
        aux = aux->prox;
    }
    printf("\n");
}

void separa_Lista(tipoInfo* aux, tipoInfo** primeira, tipoInfo** segunda)
{
    tipoInfo* slow = aux;
    tipoInfo* fast = aux->prox;
    //Corre dois nos com o fast para cada no do slow
    while(fast != NULL) {
        fast = fast->prox;
        if(fast != NULL) {
            slow = slow->prox;
            fast = fast->prox;
        }
    }
    //Slow apontando pro meio da lista
    *primeira  = aux;
    *segunda   = slow->prox;
    slow->prox = NULL;
}

tipoInfo* Merge(tipoInfo* esq, tipoInfo* dir)
{
    tipoInfo* resultado = NULL;
    //Verificando o caso base de uma das duas estarem vazias
    if(esq == NULL) {return dir;}
    else if(dir == NULL) {return esq;}

    //Juntando as duas partes
    if(esq->chave < dir->chave) {
        resultado = esq;
        resultado->prox = Merge(esq->prox, dir); //Passando +1 pro lado maior
    } else {
        resultado = dir;
        resultado->prox = Merge(esq, dir->prox); //Passando +1 pro lado maior
    }
    return resultado;
}

void ordena_ms(tipoInfo** resultado, int* deep, int n)
{

    //MergeSort
    tipoInfo* aux = *resultado;
    tipoInfo* a;
    tipoInfo* b;

    //Verificando caso base de uma lista vazia ou um no
    if( (aux == NULL) || (aux->prox == NULL) ) {return;}

    separa_Lista(aux, &a, &b);

    //Recursao para ordenar as duas partes
    ordena_ms(&a, deep, n+1);
    ordena_ms(&b, deep, n+1);
    if(n > *deep)
        *deep = n;

    //Juntando
    *resultado = Merge(a, b);
}


//Main
int main() {
    //--var
    tipoInfo *chaves = NULL;
    int n, key, profundidade = 0;

    //--init & input
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &key);
        insere(&chaves, key);
    }

    ordena_ms(&chaves, &profundidade, 1); //mergesort

    //--output
    printa_Lista(chaves);
    printf("%d\n", profundidade);

    //liberando memoria
    tipoInfo* atual = chaves;
    while(atual != NULL) {
        tipoInfo* prox = atual->prox;
        free(atual);
        atual = prox;
    }

    return 0;
}
