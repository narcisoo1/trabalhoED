#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct _no23{
    int nInfos;
    int Info1, Info2;
    struct _no23 *esq, *cen, *dir;
};

typedef struct _no23 no23;


int ehfolha(no23 *no){
    if ((no->esq == NULL) && (no->cen == NULL) && (no->dir == NULL)){
        return 1;
    }else{
        return 0;
    }
}

no23 * criaNo (int Valor, no23 *esq, no23 * centro, no23 *dir){
    no23 *no;
    no = (no23*)malloc(sizeof(no23));
    no->Info1 = Valor;
    (*no).nInfos = 1;
    (*no).esq = esq;
    (*no).cen = centro;
    (*no).dir = dir;
    return no;
}

no23 * adicionaNO (no23 *no, int valor, no23 *filho){
    if (no->Info1 < valor){
        no->Info2 = valor;
        (*no).dir = filho;
    }else{
        no->Info2 = no->Info1;
        no->Info1 = valor;
        (*no).dir = (*no).cen;
        (*no).cen = filho;
    }
    (*no).nInfos = 2;
    return no;
}

no23 *quebraNo(no23 **no, int valor, int *meio, no23 *subarvore){
    no23 *paux;
    if ((*no)->Info2 < valor){
        *meio = (*no)->Info2;
        paux = (*no)->dir;
        (*no)->dir = NULL;
        (*no)->nInfos = 1;
        return criaNo(valor, paux, subarvore, NULL);
    }else if ((*no)->Info1 < valor){
        *meio = valor;
        paux = (*no)->dir;
        (*no)->dir = NULL;
        (*no)->nInfos = 1;
        return criaNo((*no)->Info2, subarvore, paux, NULL);
    }else{
        *meio = (*no)->Info1;
        paux = criaNo((*no)->Info2, (*no)->cen, (*no)->dir, NULL);
        (*no)->Info1 = valor;
        (*no)->nInfos = 1;
        (*no)->dir = NULL;
        (*no)->cen = subarvore;
        return paux;
    }
}

no23 *insere (no23 **Raiz, int valor, int meio, no23 *Pai){
  no23 *paux, *paux2;
  int vaux;
  if (*Raiz == NULL){
    *Raiz = criaNo(valor, NULL,NULL,NULL);
    paux = NULL;
  }else{
    if(ehfolha(*Raiz)){
      if ((*Raiz)->nInfos == 1){
        *Raiz = adicionaNO(*Raiz, valor, NULL);
        paux = NULL;
      }else{
        paux = quebraNo(Raiz, valor, &vaux, NULL);
        (*Raiz)->Info2=0;
        meio = vaux;
      }
    }else{
      if (valor < (*Raiz)->Info1 ){
        paux = insere(&((*Raiz)->esq), valor, vaux, *Raiz);
      }else if (((*Raiz)->nInfos == 1)){
        paux = insere(&((*Raiz)->cen), valor, vaux, *Raiz);
      }else if(valor > (*Raiz)->Info2){
        paux = insere(&((*Raiz)->dir), valor, vaux, *Raiz);
      }else{
        paux = insere(&((*Raiz)->cen), valor, vaux, *Raiz);
      }
    }
  }
  if (paux == NULL){
    return NULL;
  }else{
    if (Pai == NULL){
      *Raiz = criaNo(vaux, *Raiz, paux, NULL);
      paux = NULL;
    }else if ((*Raiz)->nInfos == 1){
      *Raiz = adicionaNO(*Raiz, vaux, paux);
      paux = NULL;
    }else{
      paux = quebraNo(Raiz, vaux, &meio, paux);
      (*Raiz)->Info2=0;
    }
  }
  return paux;
}

no23 ** CriaArvore(){
  no23 **Raiz;
  Raiz = (no23**)malloc(sizeof(no23*));
  if (Raiz != NULL){
    *Raiz = NULL;
  }
  return Raiz;
}

void menorInfoDir(no23 *raiz, no23 **no, no23 **paiNo){
    if(raiz->esq != NULL){
        *paiNo = raiz;
        menorInfoDir(raiz->esq, no, paiNo);
    }else{
        *no = raiz;
    }
}

void maiorInfoEsq(no23 *raiz, no23 **no, no23 **paiNo){
    if(raiz->dir != NULL){
        *paiNo = raiz;
        maiorInfoEsq(raiz->dir, no, paiNo);
    }else{
        *no = raiz;
    }
}

//AQUI
int remover23(no23 **raiz, int valor, no23 **pai){
    int removeu = 0;
    no23 *no = NULL, *no1, *paiNo = NULL, *paiNo1 = NULL, **aux;
    aux=(no23**) malloc(sizeof(no23*));
    no1 = (no23*) malloc(sizeof(no23));
    if(*raiz != NULL){
        if(ehfolha(*raiz)){
            if((*raiz)->nInfos == 2){
                if(valor == (*raiz)->Info2){
                    (*raiz)->Info2 = 0;
                    (*raiz)->nInfos = 1;
                    removeu = 1;
                }else if(valor == (*raiz)->Info1){
                    (*raiz)->Info1 = (*raiz)->Info2;
                    (*raiz)->Info2 = 0;
                    (*raiz)->nInfos = 1;
                    removeu = 1;
                }
            }else if(valor == (*raiz)->Info1){
                if(*pai == NULL){
                    free(*raiz);
                    *raiz = NULL;
                    removeu = 1;
                }else if(*raiz == (*pai)->esq){
                    (*raiz)->Info1 = (*pai)->Info1;
                    paiNo = *pai;
                    menorInfoDir((*pai)->cen, &no, &paiNo);
                    (*pai)->Info1 = no->Info1;
                    removeu = 1;
                    if(no->nInfos == 2){
                        no->Info1 = no->Info2;
                        no->Info2 = 0;
                        no->nInfos = 1;
                    }else{
                        if(paiNo->nInfos == 1){
                            (*raiz)->Info2 = no->Info1;
                            (*raiz)->nInfos = 2;
                            free(no);
                            *pai = *raiz;
                        }else{
                            no->Info1 = paiNo->Info2;
                            paiNo1 = paiNo;
                            menorInfoDir(paiNo->dir, &no1, &paiNo1);
                            paiNo->Info2 = no1->Info1;
                            if(no1->nInfos == 2){
                                no1->Info1 = no1->Info2;
                                no1->Info2 = 0;
                                no1->nInfos = 1;
                            }else{
                                no->Info2 = paiNo->Info2;
                                no->nInfos=2;
                                paiNo->Info2, 0;
                                paiNo->nInfos = 1;
                                free(no1);
                                paiNo1->dir = NULL;
                            }
                        }
                    }
                }else if(*raiz == (*pai)->cen){
                    removeu = 1;
                    if((*pai)->nInfos == 1){
                        if(((*pai)->esq)->nInfos == 2){
                            (*raiz)->Info1 = (*pai)->Info1;
                            (*pai)->Info1 = ((*pai)->esq)->Info2;
                            ((*pai)->esq)->Info2 = 0;
                            ((*pai)->esq)->nInfos = 1;
                        }else{
                            ((*pai)->esq)->Info2 = (*pai)->Info1;
                            free(*raiz);
                            ((*pai)->esq)->nInfos = 2;
                            *aux = (*pai)->esq;
                            free(*pai);
                            *pai = *aux;
                        }
                    }else{
                        (*raiz)->Info1 = (*pai)->Info2;
                        paiNo = *pai;
                        menorInfoDir((*pai)->dir, &no, &paiNo);
                        (*pai)->Info2 = no->Info1;
                        if(no->nInfos == 2){
                            no->Info1 = no->Info2;
                            no->Info2 = 0;
                            no->nInfos = 1;
                        }else{
                            (*raiz)->nInfos = 2;
                            (*raiz)->Info2 = (*pai)->Info2;
                            (*pai)->Info2 = 0;
                            (*pai)->nInfos = 1;
                            free(no);
                            (*pai)->dir = NULL;
                        }
                    }
                }else{
                    removeu = 1;
                    paiNo = *pai;
                    maiorInfoEsq((*pai)->cen, &no, &paiNo);
                    if(no->nInfos == 1){
                        no->Info2 = (*pai)->Info2;
                        (*pai)->Info2 = 0;
                        (*pai)->nInfos = 1;
                        no->nInfos = 2;
                        free(*raiz);
                        *raiz = NULL;
                    }else{
                        (*raiz)->Info1 = (*pai)->Info2;
                        (*pai)->Info2 = no->Info2;
                        no->Info2 = 0;
                        no->nInfos = 1;
                    }
                }
            }
        }else{
            if(valor < (*raiz)->Info1){
                removeu = remover23(&(*raiz)->esq, valor, raiz);
            }else if(valor == (*raiz)->Info1){
                paiNo = *raiz;
                menorInfoDir((*raiz)->cen, &no, &paiNo);
                (*raiz)->Info1 = no->Info1;
                remover23(&(*raiz)->cen, (*raiz)->Info1, raiz);
                removeu = 1;
            }else if((*raiz)->nInfos == 1 || valor < (*raiz)->Info2){
                removeu = remover23(&(*raiz)->cen, valor, raiz);
            }else if(valor == (*raiz)->Info2){
                paiNo = *pai;
                menorInfoDir((*pai)->dir, &no, &paiNo);
                (*raiz)->Info2 = no->Info1;
                remover23(&(*raiz)->dir, (*raiz)->Info2, raiz);
                removeu = 1;
            }else{
                removeu = remover23(&(*raiz)->dir, valor, raiz);
            }
        }
    }
    return removeu;
}

void inOrdem(no23 **Raiz){
  if (*Raiz != NULL){
    //printf("Pai: %d, Esq: ",(*Raiz)->Info1);
    //printf("ESQUERDA\n");
    inOrdem(&(*Raiz)->esq);
    printf("%d\n", (*Raiz)->Info1);
    //printf("MEIO\n");
    inOrdem(&(*Raiz)->cen);
    if ((*Raiz)->nInfos > 1){
      printf("%d\n", (*Raiz)->Info2);
    }
    //printf("DIREITA\n");
    inOrdem(&(*Raiz)->dir);
  }
}




int main (){
  int Aux, Aux2;
  no23 **Raiz, **Aux_No;
  Raiz = CriaArvore();

  for (int x = 0; x < 5; x++){
    // Aux_No = insere(Raiz, (rand () % 1000), &Aux, NULL);
    scanf("%d", &Aux2);
    insere(Raiz, Aux2, NULL, NULL);
  }
  no23 **pai=(no23**)malloc(sizeof(no23*));
  *pai=NULL;
  remover23(Raiz,1,pai);
  printf("Exibir: \n");
  inOrdem(Raiz);

  return 0;
}
