/// Ordenacao com complexidade O(n^2) sem variavel global.

//Bibliotecas
#include <stdio.h>
#include <stdlib.h>

//Funções e Procedimentos
int *Entrada(int n)
{
    int *vet = (int*) malloc(n * sizeof(int)); //alocando memoria dinamica
    for(int i=0; i<n; i++)
        scanf("%d", &vet[i]); // 2 e 3 inputs
    return vet;
}

void Troca(int *vetA, int *vetB)
{
    int temp = *vetA;
    *vetA = *vetB;
    *vetB = temp;
}

void Ordena_bs(int *vet, int n)
{
    //Bubble Sort
    int i, j, parada = n-i-1; //parada é para o vet[j+1] nao alocar memoria fora do vetor e dar runtime error
    for(i=0; i<n; i++)
    {
        for(j=0; j<parada; j++)
        {
            if(vet[j] > vet[j+1])
                Troca(&vet[j], &vet[j+1]);
        }
    }
}

void Ver_Cura(int *doses, int *microorganismos, int n)
{
    int i, cont = 0;
    for(i=0; i<n; i++)
    {
        if(doses[i] > microorganismos[i])
            cont++;
    }
    if(cont == n) {
        printf("sim"); //output 1
    } else {
        printf("nao"); //output 2
    }
}


//Principal
int main() {
    //--var
    int *micro, *dose, pacientes;

    //--input
    scanf("%d", &pacientes); // 1 linha
    micro = Entrada(pacientes);
    dose  = Entrada(pacientes);

    //--output
    Ordena_bs(micro, pacientes);
    Ordena_bs(dose,  pacientes);
    Ver_Cura(dose, micro, pacientes);

    free(micro); //desalocando memoria
    free(dose);  //desalocando memoria
    return 0;
}
