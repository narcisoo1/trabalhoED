#ifndef ARV_HEAD_H
#define ARV_HEAD_H
#include <stdio.h>
typedef struct arvore arvore;
typedef struct record record;
typedef struct data data;

record *alocaRec(void);
void liberaRec(record *r);

arvore* criaArv(void);
arvore* alocaArv(const int valor);
void insereArv(arvore **arv, const int valor);
int alturaArv(arvore *arv);
arvore* geraValores(arvore *arv, const int tamAltura);
int geraAleatorio(const int inicio, const int limite);
void liberaArv(arvore *arv);
int buscaArv(arvore *arv, const int elemento, FILE *arq, int *tamPath);
#endif