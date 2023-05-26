/*
Pedro Henrique Cavalcante
Noturno
*/
#include <stdio.h>
#include <stdlib.h>

///Functions
int* create_Hash(int m) //Cria a tabela hash: representada nesse algoritmo por um vet dinamico
{
    int* vet = (int*) malloc(m * sizeof(int));

    for(int i=0; i<m; i++)
        vet[i] = 0;

    return vet;
}

int H1(int k, int m) //finding h1
{
    int h1 = k % m;
    return h1;
}

int H2(int k, int m) //finding h2
{
    int aux = m - 1;
    int h2 = k % aux;
    return 1 + h2;
}

int duplo_Hash(int key, int i, int m) //Mapeando onde vai o insert
{
    int a = H1(key, m);
    int b = H2(key, m), s;

    s = ((a + i*b) & 0x7FFFFFFF) % m;

    return s;
}

void insert_Hash(int* T,int k, int m) //Insere
{
    if(k == -1)
        return;

    int i = 0, j;
    do {
        j = duplo_Hash(k, i, m);
        if(T[j] == 0) {
            T[j] = k;
            break;
        } //else : continue
        i++;
    } while(i < m);
}

int search_Hash(int* T, int k, int m) //Busca
{
    int i = 0, j, aux;
    do {
        j =  duplo_Hash(k, i, m);
        if(T[j] == k)
            return j;
        else if(T[j] == 0)
            return -1; //not found
        i++;
    } while(i < m);
}

void delete_Hash(int* T, int k, int m) //Remove
{
    int i = 0, j, ver;
    do {
        j = duplo_Hash(k, i, m);
        if(T[j] == k) {
            T[j] = -1;
            ver = search_Hash(T, k, m); //verifying another equal key
            if(ver == -1) //no more keys
                return;
            else          //more keys must be removed
                delete_Hash(T, k, m);
        }
        i++;
    } while(i < m);
}

void print_Hash(int* T, int m) //Final output
{
    for(int i = 0; i < m; i++)
    {
        if(T[i] == 0)
            printf("%c ", 92); //'\'
        else if(T[i] == -1)
            printf("D ");
        else
            printf("%d ", T[i]);
    }
    printf("\n");
}

///main
int main() {
    //--vars--
    int m, x, key, aux;
    int* T;

    //--input--
    scanf("%d", &m);                //1
    T = create_Hash(m);

    do {
        scanf("%d", &x);            //2
        insert_Hash(T, x, m);
    } while(x >= 0);

    scanf("%d", &key);              //3

    //--output--
    aux = search_Hash(T, key, m);
    if(aux == -1) //not found
        printf("Valor nao encontrado\n");
    else
        delete_Hash(T, key, m);

    print_Hash(T, m);    //final output

    //--free--
    free(T);

    return 0;
}
