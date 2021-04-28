#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "Arvore.h"


int main(){
    Arvore *m;
    //FILE* saida;
    char* entrada;
    char le[100];
    int* i;
    float res = 0;
    i = (int*)malloc(sizeof(int));
    *i = 1;

    char sinais[5] = {'+', '-', '*', '/'};
    char numeros[11] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

    //saida = fopen('arvore.txt', 'w'); //Arquivo de saida com a notacao textual da arvore
    scanf("%s", le);
    entrada = strdup(le);
    m = CriaArvore(entrada, sinais, numeros, i);
    res = LeECalculaArvore(m , res, sinais);
    printf("%.2f", res);
    //ImprimeArvore(m);

    return 0;
}