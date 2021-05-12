/*
    Arvore.c
    Trabalho II - Estrutura de Dados UFES 2020/2 - Patricia Dockhorn Costa
    Alunos: Joao Gabriel de Barros e Tales Viana
    Data: 28/04/2021
    github: JoaoGBarros || Talesvf
*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Arvore.h"

struct arvore{
    char* valor;
    int id;
    Arvore* direita;
    Arvore* esquerda;
};

static char Busca(char c, char* string){
    // Busca na string recebida o caracter c, caso o encontre, ele eh retornado, se nao eh retornado o char 'n'
    for(int i = 0; i < strlen(string); i++){
        if(c == string[i]){
            return c;
        }
    }
    return 'n';
}


static Arvore* CriaArvoreVazia(){
    Arvore* arv;

    arv = (Arvore*)malloc(sizeof(Arvore));
    arv->valor = NULL;
    arv->id = 0;
    arv->direita = NULL;
    arv->esquerda = NULL;

    return arv;
}

//((((5)-(3))*((4)/(1)))+(10))
Arvore* CriaArvore(char* equacao, char* sinais, char* numeros, int* i, int *qtd){
    Arvore *arvore;
    int cont = 1;
    char b;
    char* a = (char*)malloc(5 * sizeof(char)); 
    a[1] = '\0';
    a[2] = '\0';
    a[3] = '\0';
    a[4] = '\0';
    arvore = CriaArvoreVazia();
    *qtd = *qtd + 1;
    arvore->id = *qtd;
    
    
    while(1){
        //Toda vez q um parentese for aberto, eh criada uma nova arvore filha para a esquerda, caso ja existe alguma, para direita
        if(equacao[*i] == '('){
            *i = *i + 1;
            
            if(!arvore->esquerda){
                arvore->esquerda = CriaArvore(equacao, sinais, numeros, i, qtd);
            }else{
                arvore->direita = CriaArvore(equacao, sinais, numeros, i, qtd);
            }

        }
        
        //Verifica se o caracter esta na string se sinais(+, -, *, /) e retorna qual deles eh, caso nao encontre, retorna 'n'.
        a[0] = Busca(equacao[*i], sinais);
        if(*a != 'n'){
            *i = *i + 1;
            arvore->valor = strdup(a);
        }
        
        //Verifica se o caracter esta na string de numeros de 0 a 9 e retorna qual deles eh, caso nao encontre, retorna 'n'.
        a[0] = Busca(equacao[*i], numeros);
        if(*a != 'n'){ 
            *i = *i + 1;
            while(1){

                /* 
                * Caso encontre um numero, ele verifica nas proximas posicoes 
                *da string a existencia de mais numeros, e caso encontre, 
                * adiciona esse caracter na string, se nao, o loop eh quebrado
                * e logo em seguida a string eh alocada no arvore->valor
                */

                b = Busca(equacao[*i],numeros);
                if(Busca(b, numeros) != 'n'){
                    a[cont] = b;
                    cont++;
                    *i = *i + 1;
                }else{
                    break;
                }
            }
            arvore->valor = strdup(a);
        }

        // Toda vez que um parentese eh fechado o loop while eh quebrado e a arvore eh retornada
        if(equacao[*i] == ')') {
            *i = *i + 1;
            free(a);
            break;
        }
        //Caso o indice seja maior ou igual ao tamanho da string da equacao, o loop while eh quebrado e a arvore eh 
        if(*i >= strlen(equacao)-1){
            free(a);
            break;
        }  
    }
    return arvore;
}

float LeECalculaArvore(Arvore* a, float res, char* sinais){
    int i;
    if(Busca(*(a->valor), sinais) != 'n'){ 
        //Se a arvore em questao for um sinal, eh verificado o sinal e eh chamada recursivamente a funcao, mandando dessa vez, a arvore esquerda e direita.
        if(Busca(*(a->valor), sinais) == '+'){
            res = LeECalculaArvore(a->esquerda, res, sinais) + LeECalculaArvore(a->direita, res, sinais);
        }
        else if(Busca(*(a->valor), sinais) == '-'){
            res = LeECalculaArvore(a->esquerda, res, sinais) - LeECalculaArvore(a->direita, res, sinais);
        }
        else if(Busca(*(a->valor), sinais) == '*'){
            res = LeECalculaArvore(a->esquerda, res, sinais) * LeECalculaArvore(a->direita, res, sinais);
        }
        else if(Busca(*(a->valor), sinais) == '/'){
            res = LeECalculaArvore(a->esquerda, res, sinais) / LeECalculaArvore(a->direita, res, sinais);
        }
    }
    else{
        //Caso ela nao seja um sinal, e sim um numero, eh feita uma conversao para obter o valor da string em float.
        for(i = 0;i < strlen(a->valor);i++){
            res += (float)(a->valor[i] - '0') * pow(10, (strlen(a->valor) - i - 1));
        }
    }
    return res;
}

void DestroiArvore(Arvore* a){

    /*
    *Caso a arvore exista faz a liberacao de seu valor, alocado pelo strdup, 
    *logo em seguida eh utilizada recursao para liberar as arvores pela esquerda e direita.
    *Apos isso, a arvore eh liberada
    */

    if(a){
        free(a->valor);
        DestroiArvore(a->esquerda);
        DestroiArvore(a->direita);
        free(a);
    }
}

void ImprimeArvore(FILE *dot, Arvore* a, char* sinais, char* numeros, int *contador, int *qtd){
    /* Foi utilizado um contador para fazer controle de prints especificos que marcam inicio e fim de certa arvore. 
     * Eh printado os dados da arvore e logo em seguida, utilizando recursao, eh printada informacoes das arvores à esquerda e direita,
     * caso exista alguma, e o contador soma +1. Caso o contador for  maior ou igual a qtd(quantidade de arvores) eh printado o "}", que marca o fim da arvore.
    */

    if(a){
        if(*contador == 0){
            fprintf(dot, "strict graph {\n");
            *contador += 1;
        }
        fprintf(dot, "no%d[label=", a->id);

        if(Busca(*(a->valor), sinais) != 'n'){
            fprintf(dot, "%c%s%c];\n", '"', a->valor, '"');
        }

        if(Busca(*(a->valor), numeros) != 'n'){
            fprintf(dot, "%s];\n", a->valor);
        }
        
        if(a->esquerda){
            fprintf(dot, "no%d--no%d;\n", a->id, a->esquerda->id);
            ImprimeArvore(dot, a->esquerda, sinais, numeros, contador, qtd);
            *contador += 1;
        }

        if(a->direita){
            fprintf(dot, "no%d--no%d;\n", a->id, a->direita->id);
            ImprimeArvore(dot, a->direita, sinais, numeros, contador, qtd);
            *contador += 1;
        }

        if(*contador >= *qtd){
            fprintf(dot, "}\n");
        }
    }
}


