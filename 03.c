#include <stdio.h>
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
void split(char *str, char *strings[], int *lenStrings);
void exibeArvore_Letra(arv *ar, char letra);
void deletaNumList (arv** ar, char* word, int linha);
arv* deletaNo (arv* ar, char* word);
int qtdWord(arv *ar, char* word);

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
			if(lenStrings == 0)//Caso linha em branco
				--j;
			for(int i = 0; i < lenStrings; ++i){ //Percorre linhas da string fatiada
				insereArv(&ar, strings[i], j+1);
				
			}	
			
			lenStrings = 0;	
		}
	}else{
		exit(1);
	}

	fclose(fp);

//	exibeArvore(ar);


	for(int i = 'A'; i <= 'Z'; ++i){//Exibe palavras em ordem alfabética
		exibeArvore_Letra(ar, i);
	}


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

		if(line > 0 && line <= lenArquivo){ //Testa se linha existe
			FILE *newfp;
			newfp = fopen("novo.txt", "w");
			
			if(!(newfp)) //Caso não seja possível abrir 1 dos arquivos!
				exit(1);

			for(int i = 0;fgets(linha, 99, fp); ++i){

				if(strcmp(linha, "\n") == 0){//Linha em branco
					i--;
				}else if(i == line-1){ //Linha que a palavra supostamente existe
					if(strstr(linha, buscaWord)){ //Se a palavra existe na string
						//atualiza na arvore após a remoção
						int quantidade = 0;
						quantidade=qtdWord(ar,buscaWord);
						if (quantidade > 1){
							printf("\n\nDeletando numero da lista!!");
							deletaNumList(&ar,buscaWord,line);
						}else{
							printf("\n\nDeletando nó da árvore!!");
							ar=deletaNo(ar,buscaWord);
						}

						lenStrings = 0;		
						split(linha, strings, &lenStrings);
						char newstr[100] = {};

						for(int j = 0; j < lenStrings; ++j){
							if(strcmp(strings[j], buscaWord) != 0){
								strncat(newstr, strings[j], 99);
								strncat(newstr, " ", 99);

							}
						}
						strncat(newstr, "\n", 99);
						strcpy(linha, newstr);
					}
				}
				fputs(linha, newfp);
			}

			fclose(newfp);
			
		}else
			printf("Out of range...\n");
	}else{
		exit(1);
	}



	for(int i = 'A'; i <= 'Z'; ++i){//Exibe palavras em ordem alfabética
		exibeArvore_Letra(ar, i);
	}



	fclose(fp);

	printf("\nAdding a word...\n");



	if((fp = fopen("novo.txt", "r"))){
		int line;

		printf("word: ");
		scanf(" %s", buscaWord);
		
		printf("linha: \n");
		scanf("%d", &line);
		
		if(line > 0 && line <= lenArquivo){ //Testa se linha existe
			
			insereArv(&ar, linha, line);
			
			FILE *newfp;
			newfp = fopen("novo_novo.txt", "w");
			
			if(!(newfp)) //Caso não seja possível abrir 1 dos arquivos!
				exit(1);

			for(int i = 0;fgets(linha, 99, fp); ++i){

				if(strcmp(linha, "\n") == 0){//Linha em branco
					i--;
				}else if(i == line-1){ //Linha para adicionar palavra
					
					lenStrings = 0;		
					split(linha, strings, &lenStrings);
					char newstr[100] = {};

					for(int j = 0; j < lenStrings; ++j){
						strncat(newstr, strings[j], 99);
						strncat(newstr, " ", 99);
					}
					strncat(newstr, buscaWord, 99);
					strncat(newstr, "\n", 99);
					strcpy(linha, newstr);
				}
				fputs(linha, newfp);
			}

			fclose(newfp);
			
		}else
			printf("Out of range...\n");
	}else{
		exit(1);
	}

	fclose(fp);

	return 0;
}

void exibeArvore_Letra(arv *ar, char letra){
	if(ar != NULL){
		if(ar->info[0] == letra || ar->info[0] == letra+32){
	 		printf("%c - %s\n", letra, ar->info);
	 		printf("Linhas: ");
			exibeLista(ar->l);
			printf("\n\n");
		}
		exibeArvore_Letra(ar->esq, letra);
		exibeArvore_Letra(ar->dir, letra);
	}
}

void split(char *str, char *strings[], int *lenStrings){
	
	char *token;

	token = strtok(str, " ,.\n");
	
	for(int i = 0; (token != NULL); ++i){
		
		strings[i] = token;
		*lenStrings = *lenStrings+1;

		token = strtok(NULL, " ,.\n");	
	}
}
int qtdWord(arv *ar, char* word){
	if(ar != NULL){
		if(strcmp(ar->info, word) > 0){
			qtdWord(ar->esq, word);
		}else if(strcmp(ar->info, word) < 0){
			qtdWord(ar->dir, word);
		}else{ //Achou
			lista *lista;
			int contador=0;
			for (lista = ar->l; lista != NULL; lista = lista->prox){
				contador++;
			}
			//printf("\nContador: %d",contador);
			return contador;
		}
	}else{
		return 0;
	}
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
	}else if(strcmp((*ar)->info, str) == 0){ //str1 == str2
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

void deletaNumList (arv** ar, char* word, int linha){
	if (ar == NULL){
		return;
	}else if (strcmp((*ar)->info, word) > 0){
	deletaNumList(&(*ar)->esq, word,linha);
	}else if (strcmp((*ar)->info, word) < 0){
		deletaNumList(&(*ar)->dir, word,linha);
	}
	else {//achou o nó a remover numero da lista
		    // Store head node 
		lista* temp = (*ar)->l; 
		lista* prev = NULL; 
		
		// If head node itself holds 
		// the key to be deleted 
		if (temp != NULL && temp->info == linha) 
		{ 
			(*ar)->l = temp->prox;
			free(temp);
			return; 
		} 
	
		// Else Search for the key to be deleted,  
		// keep track of the previous node as we 
		// need to change 'prev->next' */ 
		while (temp != NULL && temp->info != linha) 
		{ 
			prev = temp; 
			temp = temp->prox; 
		} 
	
		// Unlink the node from linked list 
		prev->prox = temp->prox; 
	
		// Free memory 
		free(temp); 
	}
	return;
}

arv* deletaNo (arv* ar, char* word){
	if (ar == NULL){
		return NULL;
	}else if (strcmp(ar->info, word) > 0){
	ar->esq = deletaNo(ar->esq, word);
	}else if (strcmp(ar->info, word) < 0){
		ar->dir = deletaNo(ar->dir, word);
	}
	else {// achou o nó a remover
		// nó sem filhos
		if (ar->esq == NULL && ar->dir == NULL) {
			free (ar);
			ar = NULL;
		}
		// nó só tem filho p/ direita
		else if (ar->esq == NULL) {
			arv* t = ar;
			ar = ar->dir;
			free (t);
		}
		// só tem filho p/ esquerda
		else if (ar->dir == NULL) {
			arv* t = ar;
			ar = ar->esq;
			free (t);
		}
		// nó tem os dois filhos
		else {
			arv* f = ar->esq;
			//maior filho da esquerda substitui o no a ser removido
			while (f->dir != NULL) {
				f = f->dir;
			}
			ar->l=f->l;
			strcpy(ar->info, f->info); // troca info
			strcpy(f->info, word);
			ar->esq = deletaNo(ar->esq,word);//continua para que haja o reset e o retorno null e limpeza do nó mais adiante.
		}
	}
	return ar;
}