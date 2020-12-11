#include "arvHead.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

struct arvore{
	arvore *dir;
	arvore *esq;
	int dado;
};

struct data{
	int elemento;
	int tamPath;
	int existInTree;
};

struct record{
	char nomeArv[100];
	float time;
	data dataElement[10];
};

record *alocaRec(void){
	record *r;
	if(r = malloc(sizeof(record))){
		return r;
	}else{
		perror("Erro ");
		exit(1);
	}
}
void liberaRec(record *r){
	free(r);
}

arvore* criaArv(void){
	return NULL;
}

arvore* alocaArv(const int valor){
	arvore *arv;
	if(arv = (arvore*)malloc(sizeof(arvore))){
		arv->dado = valor;
		arv->dir = NULL;
		arv->esq = NULL;
		return arv;
	}else{
		perror("Error ");
		exit(1);
	}
}

void insereArv(arvore **arv, const int valor){
	if(*arv == NULL){
		*arv = alocaArv(valor);
	}else if((**arv).dado < valor){
		insereArv(&(**arv).dir, valor);
	}else if((**arv).dado > valor){
		insereArv(&(**arv).esq, valor);
	}
}

int alturaArv(arvore *arv){
	int alt = -1;

	if(arv == NULL){
		return alt;
	}else{
		int e = alturaArv(arv->dir);
		int d = alturaArv(arv->esq);
		if(e > d){
			alt = e+1;
		}else{
			alt = d+1;
		}
	}
	return alt;
}

arvore* geraValores(arvore *arv, const int tamAltura){
	
	int h = 0;
	int inicio = 1;
	int limite = 2147483647;

	for(int i = 1; i < 2147483647 && h < tamAltura; ++i){
		
		srand(i);
		
		int aleatorio = abs(geraAleatorio(inicio, limite) - rand());
		
		abs((aleatorio %= i));

		if(aleatorio <= 0)
			aleatorio = 1+rand();

		insereArv(&arv, aleatorio);
		
		int antH = h;
		h = alturaArv(arv);
		
		// if(antH != h){
		// 	printf("%d %d\n",aleatorio, h);
		// }
		
		++inicio;
		--limite;
		if(inicio > limite){
			inicio = 1;
			limite = 2147483647;
		}
	}
	return arv;
}

int geraAleatorio(const int inicio, const int limite){
	srand(time(NULL));
	return abs(inicio+ (rand()%limite));
}

void liberaArv(arvore *arv){
	if(arv != NULL){
		liberaArv(arv->esq);
		liberaArv(arv->dir);
		free(arv);
	}
}

int buscaArv(arvore *arv, const int elemento, FILE *arq, int *tamPath){	
	if(arv != NULL){
		if(arv->dado == elemento){
			(*tamPath) += 1;
			fprintf(arq, "%d\n", elemento);
			//printf("%d\n", elemento);
			return 1;
		}else if(arv->dado > elemento){
			fprintf(arq, "%d\n", arv->dado);
			//printf("%d\n", arv->dado);
			(*tamPath) += 1;
			buscaArv(arv->dir, elemento, arq, tamPath);
		}else{
			fprintf(arq, "%d\n", arv->dado);
			//printf("%d\n", arv->dado);
			(*tamPath) += 1;
			buscaArv(arv->esq, elemento, arq, tamPath);
		}
	}else{
		fprintf(arq, "Elemento não contido na árvore\n");
		//printf("Elemento %d não contido na árvore\n", elemento);
		return 0;
	}
}