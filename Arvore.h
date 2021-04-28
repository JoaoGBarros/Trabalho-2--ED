#ifndef ARVORE_H
#define ARVORE_H


typedef struct arvore Arvore;
Arvore* CriaArvore(char* equacao, char* sinais, char* numeros, int* i);
//void ImprimeArvore(Arvore* a);
float LeECalculaArvore(Arvore* a, float res, char* sinais);

#endif