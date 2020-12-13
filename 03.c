#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct lista lista;
struct lista{a#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct lista lista;
struct lista{
	int info;
	lista *prox;
};

typedef struct arv arv;
struct arv{
	char info[100];
	arv *dir, *esq;
	lista *l;
};

void exibeArvore(arv *ar);
void arvInitLista(arv** ar);
arv *initArv(void);
lista *initList(void);
void exibeLista(lista *l);
void insereArv(arv **ar, char* valor, const int linha);
lista* insereLista(lista *l, const int linha);
void BuscaPalavra_ExibeCaminho(arv *ar, char *palavra);

void split(char *str, char *strings[], int *lenStrings, char *removeStr){
	
	char *token;

	if(!removeStr)
		token = strtok(str, " ,.\n");
	else
		token = strtok(str, removeStr);

	for(int i = 0; (token != NULL); ++i){
		strings[i] = token;
		*lenStrings = *lenStrings+1;

		if(!removeStr)
			token = strtok(NULL, " ,.\n");
		else
			token = strtok(str, removeStr);
	}
}

int main(int argc, char *argv[]){

	char *archiveName = argv[1];
	char linha[100];
	char *strings[100];
	char buscaWord[100];
	int lenStrings = 0;
	int lenArquivo = 0;
	arv *ar;
	ar = initArv();

	FILE *fp;

	//Preenche árvore

	if((fp=fopen(archiveName, "r"))){
		for(int j = 0; (fgets(linha, 99, fp)); ++j, ++lenArquivo){ //Percorre linhas do arquivo
			split(linha, strings, &lenStrings);
			for(int i = 0; i < lenStrings; ++i){ //Percorre linhas da string fatiada
				insereArv(&ar, strings[i], j+1);
			}	
			lenStrings = 0;	
		}
	}else{
		exit(1);
	}

	fclose(fp);

	exibeArvore(ar);

	printf("\nSearching for a word...\n");

	printf("word: ");
	scanf(" %99s", buscaWord);
	printf("\n");

	BuscaPalavra_ExibeCaminho(ar, buscaWord);

	if((fp = fopen(archiveName, "r"))){ //Busca palavra para remover
		int line;
		printf("\nInsert word to remove: ");
		scanf(" %s", buscaWord);
		printf("\nInsert line: ");
		scanf("%d", &line);

		if(line <= lenArquivo){ //Cria novo arquivo
			FILE *newfp;
			newfp = fopen("novo.txt", "w");
			
			if(!(newfp)) //Caso não seja possível abrir 1 dos arquivos!
				exit(1);

			for(int i = 0;fgets(linha, 99, fp); ++i){
				if(i == linha-1){ //Linha que a palavra supostamente existe
					if(strstr(linha, buscaWord)){ //Se a palavra existe na string
						printf("FATIA\n");
					}
				}
				fputs(linha, newfp);
			}
			
			//......................

			fclose(newfp);
			
		}else
			printf("Out of range...\n");
	}else{
		exit(1);
	}

	fclose(fp);

	return 0;
}

void BuscaPalavra_ExibeCaminho(arv *ar, char *palavra){
	if(ar != NULL){
		if(strcmp(ar->info, palavra) > 0){
			printf("Left: %s\n", ar->info);
			BuscaPalavra_ExibeCaminho(ar->esq, palavra);
		}else if(strcmp(ar->info, palavra) < 0){
			printf("Right: %s\n", ar->info);
			BuscaPalavra_ExibeCaminho(ar->dir, palavra);
		}else{ //Find
			printf("\nFound: ");
			printf("%s\n", ar->info);
			printf("Linhas:");
			exibeLista(ar->l);
			printf("\n");
		}
	}else{
		printf("Word not found!\n");
	}
}

lista* insereLista(lista *l, const int linha){
	lista *new;
	new = (lista*)malloc(sizeof(lista));
	new->info = linha;
	new->prox = l;
	return new;
}

void insereArv(arv **ar, char* str, const int linha){

	if(*ar == NULL){
		(*ar) = malloc(sizeof(arv));
		strcpy((*ar)->info, str);
		(*ar)->dir = NULL;
		(*ar)->esq = NULL;

		(**ar).l = initList();
			
		(**ar).l = insereLista((**ar).l, linha);

	}else if(strcmp((*ar)->info, str) > 0){ //str1 > str2
		insereArv(&(*ar)->esq, str, linha);
	}else if(strcmp((*ar)->info, str) < 0){ //str1 < str2
		insereArv(&(*ar)->dir, str, linha);
	}else { //str1 == str2
		(**ar).l = insereLista((**ar).l, linha);
	}
}


void exibeLista(lista *l){
	if(l != NULL){
		printf(" %d", l->info);
		exibeLista(l->prox);
	}
}

lista *initList(void){
	return NULL;
}

arv *initArv(void){
	return NULL;
}

void arvInitLista(arv** ar){
	(**ar).l = initList();
}

void exibeArvore(arv *ar){
	if(ar != NULL){
		printf("%s\n", ar->info);
		exibeArvore(ar->esq);
		exibeArvore(ar->dir);
	}
}
	int info;
	lista *prox;
};

typedef struct arv arv;
struct arv{
	char info[100];
	arv *dir, *esq;
	lista *l;
};

void exibeArvore(arv *ar);
void arvInitLista(arv** ar);
arv *initArv(void);
lista *initList(void);
void exibeLista(lista *l);
void insereArv(arv **ar, char* valor, const int linha);
lista* insereLista(lista *l, const int linha);
void BuscaPalavra_ExibeCaminho(arv *ar, char *palavra);

void split(char *str, char *strings[], int *lenStrings){
	char *token;

	token = strtok(str, " ,.\n");

	for(int i = 0; (token != NULL); ++i){
		strings[i] = token;
		*lenStrings = *lenStrings+1;
		token = strtok(NULL, " ,.\n");
	}
}

int main(int argc, char *argv[]){

	char archiveName[30];
	char linha[100];
	char *strings[100];
	int len = 0;
	arv *ar;
	ar = initArv();


	FILE *fp;

	strcpy(archiveName, argv[1]);

	if((fp=fopen(archiveName, "r"))){
		while((fgets(linha, 99, fp))){
			split(linha, strings, &len);
			for(int i = 0; i < len; ++i){
				insereArv(&ar, strings[i], i+1);
				//printf("%s\n", strings[i]);
			}	
			len = 0;	
		}
	}else{
		exit(1);
	}

	fclose(fp);

	exibeArvore(ar);






	// lista *l;
	// l = initList();
	
	// for(int i = 1; i < 10; ++i){
	// 	l = insereLista(l, i);
	// }

	// exibeLista(l);

	// char texto[10][50] = {"pera", "uva", "maca", "salada", "mista", "computador", "cadeira", 
	// "caderno", "geladeira", "caneta"};
	// char palavra[100];

	// //arvInitLista(&ar);

	// for(int i = 0; i < 10; ++i){
	// 	insereArv(&ar, texto[i], i);
	// }

	// exibeArvore(ar);

	// printf("\n\nSearching for a word...\n");

	// printf("word: ");
	// scanf(" %s", palavra);

	// BuscaPalavra_ExibeCaminho(ar, palavra);


	return 0;
}

void BuscaPalavra_ExibeCaminho(arv *ar, char *palavra){
	
	if(strcmp(ar->info, palavra) > 0){
		printf("left: %s\n", ar->info);
		BuscaPalavra_ExibeCaminho(ar->esq, palavra);
	}else if(strcmp(ar->info, palavra) < 0){
		printf("right: %s\n", ar->info);
		BuscaPalavra_ExibeCaminho(ar->dir, palavra);
	}else{ //Find
		printf("Find: ");
		printf("%s\n", ar->info);
		exibeLista(ar->l);
	}
}

lista* insereLista(lista *l, const int linha){
	lista *new;
	new = (lista*)malloc(sizeof(lista));
	new->info = linha;
	new->prox = l;
	return new;
}

void insereArv(arv **ar, char* str, const int linha){
	
	static int first = 0;

	if(*ar == NULL){
		(*ar) = malloc(sizeof(arv));
		strcpy((*ar)->info, str);
		(*ar)->dir = NULL;
		(*ar)->esq = NULL;

		if(!first){
			(**ar).l = initList();
			first = 1;
		}
		(**ar).l = insereLista((**ar).l, linha);

	}else if(strcmp((*ar)->info, str) > 0){ //str1 > str2
		insereArv(&(*ar)->esq, str, linha);
	}else if(strcmp((*ar)->info, str) < 0){ //str1 < str2
		insereArv(&(*ar)->dir, str, linha);
	}else { //str1 == str2
		(**ar).l = insereLista((**ar).l, linha);
	}
}


void exibeLista(lista *l){
	if(l != NULL){
		printf("%d\n", l->info);
		exibeLista(l->prox);
	}
}

lista *initList(void){
	return NULL;
}

arv *initArv(void){
	return NULL;
}

void arvInitLista(arv** ar){
	(**ar).l = initList();
}

void exibeArvore(arv *ar){
	if(ar != NULL){
		printf("%s\n", ar->info);
		exibeArvore(ar->esq);
		exibeArvore(ar->dir);
	}
}
