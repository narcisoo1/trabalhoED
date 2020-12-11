#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct arvAvl arvAvl;

typedef struct record record;

typedef struct data data;


// Cria estrutura da arvore
struct arvAvl{
  int num;
  arvAvl *esq;
  arvAvl *dir;
  int altura;
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

int maior(int a, int b);

// Calcula altura
int altura(arvAvl *N) {
  if (N == NULL)
    return 0;
  return N->altura;
}

int maior(int a, int b) {
  return (a > b) ? a : b;
}

// Criar arvore
arvAvl *criaArv(int num) {
  arvAvl *no = (arvAvl *) malloc(sizeof(arvAvl));
  no->num = num;
  no->esq = NULL;
  no->dir = NULL;
  no->altura = 1;
  return (no);
}

arvAvl *criaNull() {
  arvAvl *no = (arvAvl *) malloc(sizeof(arvAvl));
  no->num = NULL;
  no->esq = NULL;
  no->dir = NULL;
  no->altura = 1;
  return (no);
}

// Rotação para direita
arvAvl *dr(arvAvl *y) {
  arvAvl *x = y->esq;
  arvAvl *T2 = x->dir;

  x->dir = y;
  y->esq = T2;

  y->altura = maior(altura(y->esq), altura(y->dir)) + 1;
  x->altura = maior(altura(x->esq), altura(x->dir)) + 1;

  return x;
}

// Rotação para esquerda
arvAvl *er(arvAvl *x) {
  arvAvl *y = x->dir;
  arvAvl *T2 = y->esq;

  y->esq = x;
  x->dir = T2;

  x->altura = maior(altura(x->esq), altura(x->dir)) + 1;
  y->altura = maior(altura(y->esq), altura(y->dir)) + 1;

  return y;
}

// Verifica valor do balançeamento
int pegaBalan(arvAvl *N) {
  if (N == NULL)
    return 0;
  return altura(N->esq) - altura(N->dir);
}

// Insere na nó na arvore
arvAvl *inserirNo(arvAvl *no, int num) {
  // Procurar posição correta de inserção
  if (no == NULL)
    return (criaArv(num));

  if (num < no->num)
    no->esq = inserirNo(no->esq, num);
  else if (num > no->num)
    no->dir = inserirNo(no->dir, num);
  else
    return no;

  // Atualiza o fator do balanceamento
  // Balancea a arvore
  no->altura = 1 + maior(altura(no->esq),altura(no->dir));
  int balanceamento = pegaBalan(no);
  if (balanceamento > 1 && num < no->esq->num)
    return dr(no);

  if (balanceamento < -1 && num > no->dir->num)
    return er(no);

  if (balanceamento > 1 && num > no->esq->num) {
    no->esq = er(no->esq);
    return dr(no);
  }

  if (balanceamento < -1 && num < no->dir->num) {
    no->dir = dr(no->dir);
    return er(no);
  }

  return no;
}

arvAvl *menorNo(arvAvl *no) {
  arvAvl *current = no;

  while (current->esq != NULL)
    current = current->esq;

  return current;
}

// Deletar nó
arvAvl *deletarNo(arvAvl *raiz, int num) {
  // Localizar o nó e deletar
  if (raiz == NULL)
    return raiz;

  if (num < raiz->num)
    raiz->esq = deletarNo(raiz->esq, num);

  else if (num > raiz->num)
    raiz->dir = deletarNo(raiz->dir, num);

  else {
    if ((raiz->esq == NULL) || (raiz->dir == NULL)) {
      arvAvl *temp = raiz->esq ? raiz->esq : raiz->dir;

      if (temp == NULL) {
        temp = raiz;
        raiz = NULL;
      } else
        *raiz = *temp;
      free(temp);
    } else {
      arvAvl *temp = menorNo(raiz->dir);

      raiz->num = temp->num;

      raiz->dir = deletarNo(raiz->dir, temp->num);
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

// exibe a arvore
void exibir(arvAvl *raiz) {
  if (raiz != NULL) {
    printf("%d ", raiz->num);
    exibir(raiz->esq);
    exibir(raiz->dir);
  }
}

int buscaArv(arvAvl *arv, const int elemento, FILE *arq, int *tamPath){	
	if(arv != NULL){
		if(arv->num == elemento){
			(*tamPath) += 1;
			fprintf(arq, "%d\n", elemento);
			//printf("%d\n", elemento);
			return 1;
		}else if(arv->num > elemento){
			fprintf(arq, "%d\n", arv->num);
			//printf("%d\n", arv->dado);
			(*tamPath) += 1;
			buscaArv(arv->dir, elemento, arq, tamPath);
		}else{
			fprintf(arq, "%d\n", arv->num);
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

void liberaArv(arvAvl *arv){
	if(arv != NULL){
		liberaArv(arv->esq);
		liberaArv(arv->dir);
		free(arv);
	}
}

int geraAleatorio(const int inicio, const int limite){
	srand(time(NULL));
	return abs(inicio+ (rand()%limite));
}

arvAvl* geraValores(arvAvl *arv, const int tamAltura){
	
	int h = 0;
	int inicio = 1;
	int limite = 2147483647;

	for(int i = 1; i < 2147483647 && h < tamAltura; ++i){
		
		srand(i);
		
		int aleatorio = abs(geraAleatorio(inicio, limite) - rand());
		
		abs((aleatorio %= i));

		if(aleatorio <= 0)
			aleatorio = 1+rand();

		arv=inserirNo(arv, aleatorio);
		
		int antH = h;
		h = altura(arv);
		
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

