///Bibliotecas
#include <stdio.h>
#include <stdlib.h>

///Funções e procedimentos
void Procura_Binario(int *vet, int end, int start, int key, int cont)
{
    if(end >= start) {
        cont++;
        int mid = (end + start) / 2;
        if(vet[mid] == key) {
                printf("%d", cont); //output 1
                return;
        }
        else if(vet[mid] > key) {return Procura_Binario(vet, mid-1, start, key, cont);}
        else if(vet[mid] < key) {return Procura_Binario(vet, end,   mid+1, key, cont);}
    } else {
        printf("%d nao foi encontrado", key); //output 2
        return;
    }
}

///Principal
int main() {
    //var
    int i, key, entrada;

    //input
    scanf("%d", &entrada);         //1 linha
    int *numeros = (int*) malloc(entrada * sizeof(int));
    for(i=0; i<entrada; i++)
        scanf("%d ", &numeros[i]); //2 linha
    scanf("%d", &key);             //3 linha

    Procura_Binario(numeros, entrada-1, 0, key, -1);
    free(numeros);
    return 0;
}
