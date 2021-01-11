#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Biblioteca.h"

int ehfolha(no23 *no){
    if ((no->esq == NULL) && (no->cen == NULL) && (no->dir == NULL)){
        return 1;
    }else{
        return 0;
    }
}

no23 * criaNo (char *Nome, no23 *esq, no23 * centro, no23 *dir){
    no23 *no;
    no = (no23*)malloc(sizeof(no23));
    strcpy(no->Info1, Nome);
    memset (&(*no).Info2, 0, sizeof((*no).Info2));
    (*no).nInfos = 1;
    (*no).esq = esq;
    (*no).cen = centro;
    (*no).dir = dir;
    return no;
}

no23 * adicionaNO (no23 *no, char *Nome, no23 *filho){
    if (strcmp((*no).Info1, Nome) < 0){
        strcpy((*no).Info2, Nome);
        (*no).dir = filho;
    }else{
        strcpy((*no).Info2, (*no).Info1);
        strcpy((*no).Info1, Nome);
        (*no).dir = (*no).cen;
        (*no).cen = filho;
    }
    (*no).nInfos = 2;
    return no;
}

no23 *quebraNo(no23 *no, char *Nome, char *promove, no23 *subarvore){
    no23 *paux;
    if (strcmp((*no).Info2, Nome) < 0){
        strcpy(promove, no->Info2);
        paux = no->dir;
        no->dir = NULL;
        no->nInfos = 1;
        return criaNo(Nome, paux, subarvore, NULL);
    }else if (strcmp((*no).Info1, Nome) < 0){
        strcpy(promove, Nome);
        paux = no->dir;
        no->dir = NULL;
        no->nInfos = 1;
        return criaNo(no->Info2, subarvore, paux, NULL);
    }else{
        strcpy(promove, no->Info1);
        paux = criaNo(no->Info2, no->cen, no->dir, NULL);
        strcpy(no->Info1, Nome);
        no->nInfos = 1;
        no->dir = NULL;
        no->cen = subarvore;
        return paux;
    }
}

no23 *insere (no23 **Raiz, char *Nome, char *Promove, no23 *Pai){
  no23 *paux, *paux2;
  char vaux[500], promov[500];
  if (*Raiz == NULL){
    *Raiz = criaNo(Nome, NULL,NULL,NULL);
    paux = NULL;
  }else{
    if(ehfolha(*Raiz)){
      if ((*Raiz)->nInfos == 1){
        *Raiz = adicionaNO(*Raiz, Nome, NULL);
        paux = NULL;
      }else{
        paux = quebraNo(*Raiz, Nome, vaux, NULL);
        strcpy(Promove, vaux);
      }
    }else{
      if (strcmp((*Raiz)->Info1, Nome) > 0){
        paux = insere(&((*Raiz)->esq), Nome, vaux, *Raiz);
      }else if (((*Raiz)->nInfos == 1) || (strcmp((*Raiz)->Info2, Nome) > 0)){
        paux = insere(&((*Raiz)->cen), Nome, vaux, *Raiz);
      }else{
        paux = insere(&((*Raiz)->dir), Nome, vaux, *Raiz);
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
      paux = quebraNo(*Raiz, vaux, Promove, paux);
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

void inOrdem(no23 **Raiz){
  if (*Raiz != NULL){
    inOrdem(&(*Raiz)->esq);
    printf("%s\n", (*Raiz)->Info1);
    if ((*Raiz)->nInfos > 1){
      printf("%s\n", (*Raiz)->Info2);
    }
    inOrdem(&(*Raiz)->cen);
    inOrdem(&(*Raiz)->dir);
  }
}
