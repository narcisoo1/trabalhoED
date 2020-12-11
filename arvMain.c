#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "arvHead.h"
#include <string.h>

int main(){
	srand(time(NULL));
	double inicioTime;
	double fimTime;

	int v[10] = {};
	
	for(int i = 0; i < 10; ++i){
		v[i]= 1+rand()%50000;	
	}

	for(int i = 0; i < 10; ++i){
		//ENCAPSULAMENTO	
		record *r = alocaRec();	

		printf("arvore %d\n", i+1);

		arvore *arv = criaArv();
		arv = geraValores(arv, 150);
		FILE *arq;
		int tamPath[10] = {};
		
		inicioTime = (double)clock();
		for(int j = 0; j < 10; ++j){
			if(arq = fopen("path.txt", "a")){
				fprintf(arq, "Elemento: %d\n", v[j]);
				buscaArv(arv, v[j], arq, &tamPath[j]); //retorna flag
			}else{
				perror("Error ");
				exit(1);
			}
			fprintf(arq,"\n\n");
			fclose(arq);
		}
		fimTime = (double)clock();
		liberaArv(arv);
		liberaRec(r);
		printf("Time execution: %.2fns\n", (fimTime-inicioTime)*1000000000/ (double) CLOCKS_PER_SEC); //Nano
	}
}