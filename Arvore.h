/*
    Arvore.h
    Trabalho II - Estrutura de Dados UFES 2020/2 - Patricia Dockhorn Costa
    Alunos: Joao Gabriel de Barros e Tales Viana
    Data: 28/04/2021
    github: JoaoGBarros || Talesvf
*/


#ifndef ARVORE_H
#define ARVORE_H


typedef struct arvore Arvore;
Arvore* CriaArvore(char* equacao, char* sinais, char* numeros, int* i, int* qtd);
void ImprimeArvore(FILE *dot, Arvore* a, char* sinais, char* numeros, int * contador, int *qtd);
float LeECalculaArvore(Arvore* a, float res, char* sinais);
void DestroiArvore(Arvore* a);

#endif /*Arvore.h */