/*
    JoaoGabriel_TalesViana.c / main
    Trabalho II - Estrutura de Dados UFES 2020/2 - Patricia Dockhorn Costa
    Alunos: Joao Gabriel de Barros e Tales Viana
    Data: 28/04/2021
    github: JoaoGBarros || Talesvf
*/



#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "Arvore.h"


int main(){
    Arvore *arvore; //Estrutura Arvore

    char sinais[5] = {'+', '-', '*', '/'}; //String com sinais de operacao
    char numeros[11] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'}; //String de numeros


    FILE* entrada;
    FILE* saida;
    FILE* dot;

    char equacao[100]; //String da equacao
    float res = 0; //Inicializacao do resultado da equacao

    int* i; //Inicia um contador que vai percorrer os indices do vetor de caracteres(string) da equacao na funcao CriaArvore
    i = (int*)malloc(sizeof(int));
    *i = 1;

    int* qtd; //Inicia um contador que vai contar a quantidade de arvores criadas.
    qtd = (int*)malloc(sizeof(int));
    *qtd = 0;


    int contador = 0; //Contador utilizado na funcao ImprimeArvore

    entrada = fopen("entrada.txt", "r");
    saida = fopen("saida.txt", "w");
    dot = fopen("saida.dot", "w");


    if(!entrada){ 
        //Caso arquivo esteja vazio, eh mostrada uma mensagem de erro no arquivo de saida
        printf("ERRO");
        fprintf(saida, "ARQUIVO DE ENTRADA VAZIO");
    }else{
        while(!feof(entrada)){

            /*
             *Enquanto  ainda haver coisa para ler no arquivo, o programa vai continuar executando
             *Primeiro, ele le a string da equacao, logo em seguida chama a funcao CriaArvore, 
             *reponsavel por fazer a alocacao. Logo em seguida eh chamada a funcao LeECalculaArvore
             *essa responsavel por entrar nos nós da arvore e fazer as contas, retorna o seu valor
             *e dps o valor eh impresso no arquivo. Por ultimo, a funcao DestroiArvore eh chamada
             *liberando a memoria do ponteiro para que possa ser reutilizado dentro do while, 
             e os valores dos contadores e resultado sao resetados aos iniciais.
             */

            fscanf(entrada, "%s", equacao);
            arvore = CriaArvore(equacao, sinais, numeros, i, qtd);
            res = LeECalculaArvore(arvore , res, sinais);
            fprintf(saida, "%.2f\n", res);
            ImprimeArvore(dot, arvore, sinais, numeros, &contador, qtd);
            DestroiArvore(arvore);
            res = 0;
            *i = 1;
            *qtd = 0;
            contador = 0;
        }
    }

    free(i);
    free(qtd);
    fclose(entrada);
    fclose(dot);
    fclose(saida);

    return 0;
}