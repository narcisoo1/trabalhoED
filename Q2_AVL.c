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
	int altura;
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

word* criarFolha(char *palavraPT, char *wordEnglish){
	word* novoNo = (word*) malloc(sizeof(word));
	novoNo->esq = NULL;
	novoNo->dir = NULL;
	novoNo->english = (list*) malloc(sizeof(list));;
	strcpy(novoNo->pt,palavraPT);
	novoNo->english = insereFimLista(novoNo->english, wordEnglish);
	return novoNo;
}

list *criarLista(){
	return NULL;
}



void printAVL(word* raiz){
	if( raiz != NULL){
		printf("<");
		printf("%s ",raiz->pt );
		printLista(raiz->english);
		printAVL(raiz->esq);
		printAVL(raiz->dir);
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
	char** palavraPTBR = (char**) malloc(qtd * sizeof(char*));
	for(int x=0; x < qtd; x++)
		palavraPTBR[x] = (char*) malloc(sizeof(char));

	//adiciono as palavras na matriz alocada
	for(; string[i]!='\0'; i++){
		if(string[i] != ','){
			palavraPTBR[ (*contPala) ][ pos++] = string[i];
		}else{
			palavraPTBR[*contPala][pos] = '\0';
			(*contPala)++;
			pos=0;
		}
		if(string[i+1]=='\0'){
			palavraPTBR[*contPala][pos] = '\0';
		}
	}
	return palavraPTBR;	
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


//#################################################################################################

// Calcula altura
int altura(word *N) {
  if (N == NULL)
    return 0;
  return N->altura;
}

int maior(int a, int b) {
  return (a > b) ? a : b;
}

// Rotação para direita
word *dr(word *y) {
  word *x = y->esq;
  word *T2 = x->dir;

  x->dir = y;
  y->esq = T2;

  y->altura = maior(altura(y->esq), altura(y->dir)) + 1;
  x->altura = maior(altura(x->esq), altura(x->dir)) + 1;

  return x;
}

// Rotação para esquerda
word *er(word *x) {
  word *y = x->dir;
  word *T2 = y->esq;

  y->esq = x;
  x->dir = T2;

  x->altura = maior(altura(x->esq), altura(x->dir)) + 1;
  y->altura = maior(altura(y->esq), altura(y->dir)) + 1;

  return y;
}

// Verifica valor do balançeamento
int pegaBalan(word *N) {
  if (N == NULL)
    return 0;
  return altura(N->esq) - altura(N->dir);
}

word *menorNo(word *no) {
  word *current = no;

  while (current->esq != NULL)
    current = current->esq;

  return current;
}

// Deletar nó
word *deletarNo(word *raiz, char *buscaWord){
  // Localizar o nó e deletar
  if (raiz == NULL)
    return raiz;

	int comp = strcmp(buscaWord, raiz->pt);
  
  if (comp < 0)
    raiz->esq = deletarNo(raiz->esq, buscaWord);

  else if (comp > 0)
    raiz->dir = deletarNo(raiz->dir, buscaWord);

  else {


    if ((raiz->esq == NULL) || (raiz->dir == NULL)) {
      word *temp = raiz->esq ? raiz->esq : raiz->dir;

      if (temp == NULL) {
        temp = raiz;
        raiz = NULL;
      } else
        *raiz = *temp;
      free(temp);
    } else {
      word *temp = menorNo(raiz->dir);

      strcpy(raiz->pt, temp->pt);

      raiz->dir = deletarNo(raiz->dir, temp->pt);
    }
  }

  if (raiz == NULL)
    return raiz;

  // Atualiza o fator do balanceamento
  // Balancea a arvore
  raiz->altura = 1 + maior(altura(raiz->esq),
               altura(raiz->dir));

  int balanceamento = pegaBalan(raiz);
  if (balanceamento > 1 && pegaBalan(raiz->esq) >= 0)
    return dr(raiz);

  if (balanceamento > 1 && pegaBalan(raiz->esq) < 0) {
    raiz->esq = er(raiz->esq);
    return dr(raiz);
  }

  if (balanceamento < -1 && pegaBalan(raiz->dir) <= 0)
    return er(raiz);

  if (balanceamento < -1 && pegaBalan(raiz->dir) > 0) {
    raiz->dir = dr(raiz->dir);
    return er(raiz);
  }

  return raiz;
}

word *criaArv(char *Palavra) {
  word *no = (word *) malloc(sizeof(word));
  strcpy(no->pt, Palavra);
  no->esq = NULL;
  no->dir = NULL;
  no->altura = 1;
  return (no);
}

// Insere na nó na arvore
word *inserirNo(word *no, word *NOVO, char *info) {
  // Procurar posição correta de inserção
  if (no == NULL)
    return NOVO;

	int comp = strcmp(no->pt, info);
  if (comp < 0)
    no->esq = inserirNo(no->esq, NOVO, info);
  else if (comp > 0)
    no->dir = inserirNo(no->dir, NOVO, info);
  else
    return no;

  // Atualiza o fator do balanceamento
  // Balancea a arvore
  no->altura = 1 + maior(altura(no->esq),altura(no->dir));
  int balanceamento = pegaBalan(no);
  // <0
  if (balanceamento > 1 && (strcmp(info, no->esq->pt) > 0))
    return dr(no);
							// > 0
  if (balanceamento < -1 && (strcmp(info, no->dir->pt) < 0))
    return er(no);
							// > 0
  if (balanceamento > 1 && (strcmp(info, no->esq->pt) < 0)) {
    no->esq = er(no->esq);
    return dr(no);
  }

  if (balanceamento < -1 && (strcmp(info, no->dir->pt) > 0)) {
    no->dir = dr(no->dir);
    return er(no);
  }

  return no;
}


int main(){

	int qtdUnidades = 0, op=0, uni;
	char NameArquivo[50];
	
	clock_t inicioBusca, fimBusca;
	clock_t inicioInserir, fimInserir;
	float tempoBusca, tempoInserir;

	unit* livro = NULL;
	livro = (unit*) malloc(sizeof(unit));
	
	while(1){
		printf("\n1 - Importar Dados\n");			
		printf("2 - Remover Palavra\n");		
		printf("3 - Buscar Palavra PTBR\n"); 	
		printf("4 - Exibir Unidade\n");			
		printf("0 - SAIR\n");
		printf("Escolha uma Opção: ");
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
							char** palavraPTBR  = processarString(linha, wordEnglish, &contPala);
							
							for(int i =0; i<=contPala; i++){
								if(buscaPT(&(livro[pos].arv), palavraPTBR[i], wordEnglish,0) == 0){
									//Palavra PTBR não existir
									livro[pos].arv = inserirNo(livro[pos].arv,criarFolha(palavraPTBR[i], wordEnglish), wordEnglish);
								}
							}
							
						}
					}
					printf("\n-- %d Unidade(s) cadastrada(s) --\n",qtdUnidades);
					fclose(file);
					fimInserir = clock();
					tempoInserir = ((fimInserir - inicioInserir) * 1000000000) / CLOCKS_PER_SEC;
					printf("Tempo gasto para INSERIR: %.2fns \n", tempoInserir);
				}else{
					printf("\n - ERRO AO ABRIR ARQUIVO  %s -\n",NameArquivo );
				}
	    		break;
	    	
	    	case 2:
	    		printf("Informe a palavra em PTBR: ");
	    		char palavraBuscar2[50];
	    		scanf("%s", palavraBuscar2);

	    		if(qtdUnidades == 0){
	       			printf("\n -- Nenhuma unidade cadastrada --\n");
	       		}else{
		       		printf("list DE UNIDADES:\n");
		       		for(int x = 0; x<qtdUnidades; x++){
		       			printf("[%d] - %s\n",x, livro[x].nome );
		       		}
		       		printf("Escolha uma Unidade: ");
		       		scanf("%d", &uni);
		       		if(uni >= 0 && uni<qtdUnidades){
		       			livro[uni].arv = deletarNo(livro[uni].arv, palavraBuscar2);
		       		}else{
		       			printf("\n -- Unidade não Cadastrada --\n");
		       		}
		       	}
	    		break;
	      	
	      	case 3:
	      		printf("Informe a palavra em PTBR: ");
	    		char palavraBuscar[50];
	    		scanf("%s", palavraBuscar);
	    		
				if(qtdUnidades != 0){
					inicioBusca = clock();
					for(int x = 0; x<qtdUnidades; x++){		
						printf("\nUnidade [%s]: \n",livro[x].nome );
						if(buscaPT(&(livro[x].arv), palavraBuscar, "None",1) == 0)
							printf(" -- Palavra não encontrada --\n");

						printf("\n");
					}
					fimBusca = clock();
					tempoBusca = ((fimBusca - inicioBusca) * 1000000000) / CLOCKS_PER_SEC;
					printf("Tempo gasto para BUSCAR: %.2f \n", tempoBusca);
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
		       			printAVL(livro[uni].arv);
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

