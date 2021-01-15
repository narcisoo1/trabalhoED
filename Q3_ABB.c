#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define repeat 30

typedef struct palavra word;
typedef struct lista list;

struct lista{
	char nome[50];
	list *prox;
};

struct palavra{
	char pt[50];
	list *english;
	word *esq, *dir;
};

typedef struct {
	char nome[25];
	word *arv;
}unit;

word* criarArv(){
	return NULL;
}

list* insereFimLista(list *lista, char *wordEnglish){
	list *novo;
	novo = (list*) malloc(sizeof(list));
	strcpy(novo->nome, wordEnglish);
	
	if( lista == NULL){
		novo->prox = novo;
		return novo;
	}else{
		list *aux;
		for(aux=lista; aux->prox!=NULL; aux = aux->prox);
		aux->prox = novo;
		return lista;
	}
}

word* criarFolha(char *wordPort, char *wordEnglish){
	word* novoNo = (word*) malloc(sizeof(word));
	novoNo->esq = NULL;
	novoNo->dir = NULL;
	novoNo->english = (list*) malloc(sizeof(list));;
	strcpy(novoNo->pt,wordPort);
	novoNo->english = insereFimLista(novoNo->english, wordEnglish);
	return novoNo;
}

list *criarLista(){
	return NULL;
}

void printABB(word* raiz){
	if( raiz != NULL){
		printf("<");
		printf("%s ",raiz->pt );
		printLista(raiz->english);
		printABB(raiz->esq);
		printABB(raiz->dir);
		printf(">");
	}
}

void printLista(list* lista){
	list *aux;
	for(aux=lista; aux != NULL; aux= aux->prox)
		printf("%s ",aux->nome );
	
}

char** processarString(char* string, char* wordEnglish, int* contPala){
	strcpy(*(&wordEnglish), "");
	int i = 0, pos=0;
	
	for(; string[i]!=':'; i++)	
		wordEnglish[i] = string[i];
	wordEnglish[i] = '\0';
	i++;

	int qtd=1;
	//contar quantidade de palavras por linha
	for(int x=0;string[x]!='\0'; x++){
		if(string[x]==',') 
			qtd++;
	}
	char** wordPortugues = (char**) malloc(qtd * sizeof(char*));
	for(int x=0; x < qtd; x++)
		wordPortugues[x] = (char*) malloc(sizeof(char));

	//adiciono as palavras na matriz alocada
	for(; string[i]!='\0'; i++){
		if(string[i] != ','){
			wordPortugues[ (*contPala) ][ pos++] = string[i];
		}else{
			wordPortugues[*contPala][pos] = '\0';
			(*contPala)++;
			pos=0;
		}
		if(string[i+1]=='\0'){
			wordPortugues[*contPala][pos] = '\0';
		}
	}
	return wordPortugues;	
}

void insereABB(word** raiz, word* NO){	
	if(*raiz==NULL){
		*raiz = NO;
	}else{
		int comp = strcmp(NO->pt, (*raiz)->pt);
		if( comp < 0)
			insereABB( &((*raiz)->esq), NO);
		else
			insereABB( &((*raiz)->dir), NO);
	}
}

void addWordENG(word** raiz, char* wordEnglish){
	list* aux;
	int  flag = 0;
	for(aux = (*raiz)->english; aux->prox !=NULL; aux = aux->prox){
		if(strcmp(aux->nome, wordEnglish) == 0){
			flag = 1; 		//nao adiciona caso a palavra já exista
			break;
		}
	}
	if(flag == 0)
		(*raiz)->english = insereFimLista((*raiz)->english, wordEnglish);
}

int buscaPT(word** raiz, char *buscaWord, char* wordEnglish, int flag){
	int find = 0;
	if(*raiz != NULL){
		int comp = strcmp(buscaWord, (*raiz)->pt);
		if(comp == 0){
			if(flag == 0){
				addWordENG(raiz, wordEnglish);
			}else{
				printLista((*raiz)->english);
			}
			find = 1;
		}else if(comp < 0)
			find = buscaPT(&(*raiz)->esq, buscaWord, wordEnglish, flag);
		else
			find = buscaPT(&(*raiz)->dir, buscaWord, wordEnglish, flag);
	}
	return find;
}

void removeABB(word** raiz, char *buscaWord){

	if(* raiz != NULL){
		int comp = strcmp(buscaWord, (*raiz)->pt);
		if(comp < 0)
			removeABB(&(*raiz)->esq, buscaWord);
		else if( comp > 0){
			removeABB(&(*raiz)->dir, buscaWord);
		}else{

			word* aux;
			word* pai = NULL;
			
			//Eh Folha
			if((*raiz)->dir == NULL && (*raiz)->esq == NULL){
				free(*raiz);
				*raiz = NULL;
			}else if( (*raiz)->esq == NULL ){
				aux = (*raiz)->dir;
				free(*raiz);
				*raiz = aux;
			
			}else if((*raiz)->dir == NULL){
				aux = (*raiz)->esq;
				free(*raiz);
				*raiz = aux;
			
			}else if((*raiz)->dir != NULL && (*raiz)->esq != NULL){
				aux = (*raiz)->dir;
				while(aux->esq!= NULL){
					pai = aux;
					aux = aux->esq;
				}
				strcpy((*raiz)->pt,aux->pt);
				(*raiz)->english = aux->english;
				strcpy(aux->pt, buscaWord);
				removeABB(&(*raiz)->dir, buscaWord);
			}
		}
	}
}

int main(){

	int qtdUnidades = 0, op=0, uni;
	char NameArquivo[50];
	
	clock_t inicioBusca, fimBusca;
	clock_t inicioInserir, fimInserir;
	float tempoBusca, tempoInserir;

	unit* livro = NULL;
	livro = (unit*) malloc(sizeof(unit));
	
	while(1 == 1){
		printf("\n1 - Importar Dados\n");			//Criar Unidades
		printf("2 - Remover Palavra\n");		//Uma Unidade
		printf("3 - Buscar Palavra PTBR\n"); 	//TODAS AS UNIDADES
		printf("4 - Exibir Unidade\n");			// PT -> Eng
		printf("0 - SAIR\n");
		printf("\nEscolha uma Opção: ");
		scanf("%d", &op);
	    switch(op){
	    	case 1:
	    		printf("Informe nome do arquivo: ");
	    		scanf("%s", NameArquivo);

	    		inicioInserir = clock();
	    		FILE *file;
				if ( (file = fopen( NameArquivo, "r")) != NULL){
					char linha[10000];

					while ( fscanf(file, "%s\n",linha) != EOF ) {						
						if(linha[0] == '%'){
							//nova unidade
							livro = (unit*) realloc( livro, (qtdUnidades+1) * sizeof(unit));

							char nameUnidade[50];
							strcpy(nameUnidade,"");
							int x;
							for(x = 1; linha[x]!='\0'; x++)
								nameUnidade[x-1] = linha[x];
							nameUnidade[x-1] = '\0';
							strcpy(livro[qtdUnidades].nome,nameUnidade);
							(qtdUnidades)++;
						}else{
							int contPala = 0, pos = (qtdUnidades)-1;
							char wordEnglish[50];
							char** wordPortugues  = processarString(linha, wordEnglish, &contPala);
							
							for(int i =0; i<=contPala; i++){
								if(buscaPT(&(livro[pos].arv), wordPortugues[i], wordEnglish,0) == 0){
									//Palavra PTBR não existir
									insereABB(&(livro[pos].arv),criarFolha(wordPortugues[i], wordEnglish));
								}
							}
							
						}
					}
					printf("\n-- %d Unidade(s) cadastrada(s) --\n",qtdUnidades);
					fclose(file);
					fimInserir = clock();
					tempoInserir = ((fimInserir - inicioInserir) * 1000) / CLOCKS_PER_SEC;
					printf("Tempo gasto para INSERIR: %lf \n", tempoInserir);
				}else{
					printf("\n - ERRO AO ABRIR ARQUIVO  %s -\n",NameArquivo );
				}
	    		break;
	    	
	    	case 2:
	    		printf("Informe a palavra em PTBR: ");
	    		char wordSearch2[50];
	    		scanf("%s", wordSearch2);

	    		if(qtdUnidades == 0){
	       			printf("\n -- Nenhuma unidade cadastrada --\n");
	       		}else{
		       		printf("LISTA DE UNIDADES:\n");
		       		for(int x = 0; x<qtdUnidades; x++){
		       			printf("[%d] - %s\n",x, livro[x].nome );
		       		}
		       		printf("Escolha uma Unidade: ");
		       		scanf("%d", &uni);
		       		if(uni >= 0 && uni<qtdUnidades){
		       			removeABB(&livro[uni].arv, wordSearch2);
		       		}else{
		       			printf("\n -- Unidade não Cadastrada --\n");
		       		}
		       	}
	    		break;
	      	
	      	case 3:
	      		printf("Informe a palavra em PTBR: ");
	    		char wordSearch[50];
	    		scanf("%s", wordSearch);
	    		
				if(qtdUnidades != 0){
					inicioBusca = clock();
					for(int x = 0; x<qtdUnidades; x++){		
						printf("\nUnidade [%s]: \n",livro[x].nome );
						if(buscaPT(&(livro[x].arv), wordSearch, "None",1) == 0)
							printf(" -- Palavra não encontrada --\n");

						printf("\n");
					}
					fimBusca = clock();
					tempoBusca = ((fimBusca - inicioBusca) * 1000) / CLOCKS_PER_SEC;
					printf("Tempo gasto para BUSCAR: %lf \n", tempoBusca);
				}else{
					printf("\n -- Nenhuma unidade cadastrada --\n");
				}
	    		break;
	       	
	       	case 4:
	       		if(qtdUnidades == 0){
	       			printf("\n -- Nenhuma unidade cadastrada --\n");
	       		}else{
		       		//printf("\nLISTA DE UNIDADES:\n");
					printf("------------------------------\n");
					for(int x = 0; x<qtdUnidades; x++)
		       			printf("[%d] - %s\n",x, livro[x].nome );
					printf("------------------------------\n");

					printf("Escolha uma Unidade: ");
		       		scanf("%d", &uni);
		       		if(uni >= 0 && uni<qtdUnidades){
		       			printABB(livro[uni].arv);
		       		}else{
						printf("\n -- Unidade não Cadastrada --\n");
					}
		       	}
	    		break;
	    	
	    	case 0:
	    		exit(0);
	    		break;
			default:
				printf("\n -- Informe uma opção válida --\n");
				break;
	    }
	}
	return 0;
}




