/*
Autor: Pedro Henrique Cavalcante
Turma: Noturno
Data: 26/04/2023
*/
///Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

///Funcoes e procedimentos
char** input_Words(int s) //Entrada das palavras
{
    char** saida = (char**) malloc(s * sizeof(char*));

    for(int i = 0; i < s; i++)
    {
        saida[i] = (char*) malloc(20 * sizeof(char));
        scanf("%s", saida[i]);
    }
}

void testedemesa(char** w, char k[], int n)
{
    for(int i = 0; i < 26; i++)
        printf("%c", k[i]);

    for(int i = 0; i < n; i++)
        printf("%s ", w[i]);
}

///Main
int main() {
    //--var--
    int i, N;
    char key[27], **words;

    //--input--
    scanf("%d", &N);            //1 Input

    for(i=0; i < 26; i++)
        scanf("%c", &key[i]);   //2 Input
    key[27] = '\0';

    words = input_Words(N);     //3 Input

    //--output--
    testedemesa(words,  key, N);

    //--free--

    return 0;
}
