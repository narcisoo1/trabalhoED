#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define repeat 30

typedef struct pala PALAVRA;
typedef struct lista LISTA;

struct lista{
	char nome[50];
	LISTA *prox;
};

struct pala{
	char pt[50];
	int altura;
	LISTA *english;
	PALAVRA *esq, *dir;
};

typedef struct {
	char nome[25];
	PALAVRA *arv;
}UNIDADE;

//############################################################
//DELETA
PALAVRA *deletarNo(PALAVRA *raiz, char *palavraBusca);
PALAVRA *menorNo(PALAVRA *no);
int pegaBalan(PALAVRA *N);
PALAVRA *er(PALAVRA *x);
PALAVRA *dr(PALAVRA *y);
int maior(int a, int b);
int altura(PALAVRA *N);
//INSERE
PALAVRA *criaArv(char *Palavra);
PALAVRA *inserirNo(PALAVRA *no, PALAVRA *NOVO, char *info);


PALAVRA* criarArv();
PALAVRA* criarFolha(char *palavraPT, char *palavraEnglish);
LISTA* inserirFinal(LISTA *lista, char *palavraEnglish);
void exibirABB(PALAVRA* raiz);
void imprimirLista(LISTA* lista);
char** processarString(char* string, char* palavraEnglish, int* contPala);
// void inserirABB(PALAVRA** raiz, PALAVRA* NO);
void addPalavraENG(PALAVRA** raiz, char* palavraEnglish);
int buscarPTBR(PALAVRA** raiz, char *palavraBusca, char* palavraEnglish, int flag);
// void removerABB(PALAVRA** raiz, char *palavraBusca);



int main(){

	int qtdUnidades = 0, op=0, uni;
	char NameArquivo[50];
	
	clock_t tempoBuscaI, tempoBuscaF;
	clock_t tempoInserirI, tempoInserirF;
	float tempoBuscaDecorrido, tempoInserirDecorrido;

	UNIDADE* livro = NULL;
	livro = (UNIDADE*) malloc(sizeof(UNIDADE));
	
	while(1 == 1){
		printf("\n------------------------------\n");
		printf(" [1] - Importar Dados\n");			//Criar Unidades
		printf(" [2] - Remover Palavra\n");		//Uma Unidade
		printf(" [3] - Buscar Palavra PTBR\n"); 	//TODAS AS UNIDADES
		printf(" [4] - Exibir Unidade\n");			// PT -> Eng
		printf(" [0] - SAIR\n");
		printf("------------------------------\n");
		printf("Escolha uma Opção: ");
		scanf("%d", &op);
	    switch(op){
	    	case 1:
	    		printf("Informe nome do arquivo (+ .txt): ");
	    		scanf("%s", NameArquivo);

	    		tempoInserirI = clock();
	    		FILE *file;
				if ( (file = fopen( NameArquivo, "r")) != NULL){
					char linha[10000];

					while ( fscanf(file, "%s\n",linha) != EOF ) {						
						if(linha[0] == '%'){
							//nova unidade
							livro = (UNIDADE*) realloc( livro, (qtdUnidades+1) * sizeof(UNIDADE));

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
							char palavraEnglish[50];
							char** palavraPTBR  = processarString(linha, palavraEnglish, &contPala);
							
							for(int i =0; i<=contPala; i++){
								if(buscarPTBR(&(livro[pos].arv), palavraPTBR[i], palavraEnglish,0) == 0){
									//Palavra PTBR não existir
									livro[pos].arv = inserirNo(livro[pos].arv,criarFolha(palavraPTBR[i], palavraEnglish), palavraEnglish);
								}
							}
							
						}
					}
					printf("\n-- %d Unidade(s) cadastrada(s) --\n",qtdUnidades);
					fclose(file);
					tempoInserirF = clock();
					tempoInserirDecorrido = ((tempoInserirF - tempoInserirI) * 1000) / CLOCKS_PER_SEC;
					printf("Tempo gasto para INSERIR: %lf \n", tempoInserirDecorrido);
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
		       		printf("LISTA DE UNIDADES:\n");
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
					tempoBuscaI = clock();
					for(int x = 0; x<qtdUnidades; x++){		
						printf("\nUnidade [%s]: \n",livro[x].nome );
						if(buscarPTBR(&(livro[x].arv), palavraBuscar, "None",1) == 0)
							printf(" -- Palavra não encontrada --\n");

						printf("\n");
					}
					tempoBuscaF = clock();
					tempoBuscaDecorrido = ((tempoBuscaF - tempoBuscaI) * 1000) / CLOCKS_PER_SEC;
					printf("Tempo gasto para BUSCAR: %lf \n", tempoBuscaDecorrido);
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
		       			exibirABB(livro[uni].arv);
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

PALAVRA* criarArv(){
	return NULL;
}

PALAVRA* criarFolha(char *palavraPT, char *palavraEnglish){
	PALAVRA* novoNo = (PALAVRA*) malloc(sizeof(PALAVRA));
	novoNo->esq = NULL;
	novoNo->dir = NULL;
	novoNo->english = (LISTA*) malloc(sizeof(LISTA));;
	strcpy(novoNo->pt,palavraPT);
	novoNo->english = inserirFinal(novoNo->english, palavraEnglish);
	return novoNo;
}

LISTA *criarLista(){
	return NULL;
}

LISTA* inserirFinal(LISTA *lista, char *palavraEnglish){
	LISTA *novo;
	novo = (LISTA*) malloc(sizeof(LISTA));
	strcpy(novo->nome, palavraEnglish);
	
	if( lista == NULL){
		novo->prox = novo;
		return novo;
	}else{
		LISTA *aux;
		for(aux=lista; aux->prox!=NULL; aux = aux->prox);
		aux->prox = novo;
		return lista;
	}
}

void exibirABB(PALAVRA* raiz){
	if( raiz != NULL){
		printf("<");
		printf("%s ",raiz->pt );
		imprimirLista(raiz->english);
		exibirABB(raiz->esq);
		exibirABB(raiz->dir);
		printf(">");
	}
}

void imprimirLista(LISTA* lista){
	LISTA *aux;
	for(aux=lista; aux != NULL; aux= aux->prox)
		printf("%s ",aux->nome );
	
}

char** processarString(char* string, char* palavraEnglish, int* contPala){
	strcpy(*(&palavraEnglish), "");
	int i = 0, pos=0;
	
	for(; string[i]!=':'; i++)	
		palavraEnglish[i] = string[i];
	palavraEnglish[i] = '\0';
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

void addPalavraENG(PALAVRA** raiz, char* palavraEnglish){
	LISTA* aux;
	int  flag = 0;
	for(aux = (*raiz)->english; aux->prox !=NULL; aux = aux->prox){
		if(strcmp(aux->nome, palavraEnglish) == 0){
			flag = 1; 		//nao adiciona caso a palavra já exista
			break;
		}
	}
	if(flag == 0)
		(*raiz)->english = inserirFinal((*raiz)->english, palavraEnglish);
}

int buscarPTBR(PALAVRA** raiz, char *palavraBusca, char* palavraEnglish, int flag){
	int find = 0;
	if(*raiz != NULL){
		int comp = strcmp(palavraBusca, (*raiz)->pt);
		if(comp == 0){
			if(flag == 0){
				addPalavraENG(raiz, palavraEnglish);
			}else{
				imprimirLista((*raiz)->english);
			}
			find = 1;
		}else if(comp < 0)
			find = buscarPTBR(&(*raiz)->esq, palavraBusca, palavraEnglish, flag);
		else
			find = buscarPTBR(&(*raiz)->dir, palavraBusca, palavraEnglish, flag);
	}
	return find;
}


//#################################################################################################

// Calcula altura
int altura(PALAVRA *N) {
  if (N == NULL)
    return 0;
  return N->altura;
}

int maior(int a, int b) {
  return (a > b) ? a : b;
}

// Rotação para direita
PALAVRA *dr(PALAVRA *y) {
  PALAVRA *x = y->esq;
  PALAVRA *T2 = x->dir;

  x->dir = y;
  y->esq = T2;

  y->altura = maior(altura(y->esq), altura(y->dir)) + 1;
  x->altura = maior(altura(x->esq), altura(x->dir)) + 1;

  return x;
}

// Rotação para esquerda
PALAVRA *er(PALAVRA *x) {
  PALAVRA *y = x->dir;
  PALAVRA *T2 = y->esq;

  y->esq = x;
  x->dir = T2;

  x->altura = maior(altura(x->esq), altura(x->dir)) + 1;
  y->altura = maior(altura(y->esq), altura(y->dir)) + 1;

  return y;
}

// Verifica valor do balançeamento
int pegaBalan(PALAVRA *N) {
  if (N == NULL)
    return 0;
  return altura(N->esq) - altura(N->dir);
}

PALAVRA *menorNo(PALAVRA *no) {
  PALAVRA *current = no;

  while (current->esq != NULL)
    current = current->esq;

  return current;
}

// Deletar nó
PALAVRA *deletarNo(PALAVRA *raiz, char *palavraBusca){
  // Localizar o nó e deletar
  if (raiz == NULL)
    return raiz;

	int comp = strcmp(palavraBusca, raiz->pt);
  
  if (comp < 0)
    raiz->esq = deletarNo(raiz->esq, palavraBusca);

  else if (comp > 0)
    raiz->dir = deletarNo(raiz->dir, palavraBusca);

  else {


    if ((raiz->esq == NULL) || (raiz->dir == NULL)) {
      PALAVRA *temp = raiz->esq ? raiz->esq : raiz->dir;

      if (temp == NULL) {
        temp = raiz;
        raiz = NULL;
      } else
        *raiz = *temp;
      free(temp);
    } else {
      PALAVRA *temp = menorNo(raiz->dir);

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

PALAVRA *criaArv(char *Palavra) {
  PALAVRA *no = (PALAVRA *) malloc(sizeof(PALAVRA));
  strcpy(no->pt, Palavra);
  no->esq = NULL;
  no->dir = NULL;
  no->altura = 1;
  return (no);
}

// Insere na nó na arvore
PALAVRA *inserirNo(PALAVRA *no, PALAVRA *NOVO, char *info) {
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
  if (balanceamento > 1 && (strcmp(info, no->esq->pt) < 0))
    return dr(no);
							// > 0
  if (balanceamento < -1 && (strcmp(info, no->dir->pt) > 0))
    return er(no);
							// > 0
  if (balanceamento > 1 && (strcmp(info, no->esq->pt) > 0)) {
    no->esq = er(no->esq);
    return dr(no);
  }

  if (balanceamento < -1 && (strcmp(info, no->dir->pt) < 0)) {
    no->dir = dr(no->dir);
    return er(no);
  }

  return no;
}
