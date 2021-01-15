#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<unistd.h>

struct ing{
    char *eng;
    struct ing *prox;
};

typedef struct ing ing;

struct no23{
    char *chaveEsq;
    char *chaveDir;
    ing *l1,*l2;
    struct no23 *esq,*cen,*dir;
    int qtd;
};

typedef struct no23 no23;

struct capitulo{
    char *unidade;
    no23 *arv23;
    struct capitulo *prox;
};

typedef struct capitulo cap;

void Mostrar(cap *uni){
    if(uni!=NULL){
        Mostrar(uni->prox);
        printf("%s\n",uni->unidade);
        printEmOrdem(uni->arv23);
    }
}

void mostraLista(ing *lista){
    if(lista != NULL){
        printf("%s", lista->eng);
        if(lista->prox != NULL){
            printf(", ");
        }else{
            printf(".");
        }
        mostraLista(lista->prox);
    }
}

void apagarLista(ing **lista){
    if(*lista != NULL){
        apagarLista(&(*lista)->prox);
        free(*lista);
    }
    *lista = NULL;
}

void insereWordLista(ing **palavra, char *p){
    ing *new = (ing*) malloc(sizeof(ing));
    new->eng=(char*)malloc(sizeof(char)*100);
    strcpy(new->eng,p);
    new->prox = *palavra;
    *palavra = new;
}

no23 *criaNo(char *port,char *ingl,no23 *esq,no23 *cen,no23 *dir){
    no23 *no=(no23*)malloc(sizeof(no23));
    no->chaveEsq=(char*)malloc(sizeof(char)*100);
    no->chaveDir=(char*)malloc(sizeof(char)*100);
    strcpy(no->chaveEsq,port);
    no->l1=NULL;
    no->l2=NULL;
    insereWordLista(&(no->l1),ingl);
    no->qtd=1;
    no->esq=esq;
    no->cen=cen;
    no->dir=dir;
    return no;
}

no23 *criaNo1(char *port,ing *ingl,no23 *esq,no23 *cen,no23 *dir){
    no23 *no=(no23*)malloc(sizeof(no23));
    no->chaveEsq=(char*)malloc(sizeof(char)*100);
    no->chaveDir=(char*)malloc(sizeof(char)*100);
    strcpy(no->chaveEsq,port);
    copiaLista(&no->l1,ingl);
    no->l2=NULL;
    no->qtd=1;
    no->esq=esq;
    no->cen=cen;
    no->dir=dir;
    return no;
}

no23 *quebraNo(no23 **raiz,char *info,ing *ingl,char *promovePal,ing **promoveL,no23 *sub){
    no23 *aux;
    if(strcmp(info,(*raiz)->chaveEsq)<0){
        strcpy(promovePal,(*raiz)->chaveEsq);
        apagarLista(promoveL);
        copiaLista(promoveL,(*raiz)->l1);
        strcpy((*raiz)->chaveEsq,info);
        apagarLista(&(*raiz)->l1);
        copiaLista(&(*raiz)->l1,ingl);
        (*raiz)->qtd-=1;
        aux=criaNo1((*raiz)->chaveDir,(*raiz)->l2,(*raiz)->cen,(*raiz)->dir,NULL);
        (*raiz)->l2=NULL;
        (*raiz)->dir=NULL;
        (*raiz)->cen=sub;
    }else if(strcmp(info,(*raiz)->chaveDir)<0){
        strcpy(promovePal,info);
        apagarLista(promoveL);
        copiaLista(promoveL,ingl);
        (*raiz)->qtd-=1;
        aux=criaNo1((*raiz)->chaveDir,(*raiz)->l2,sub,(*raiz)->dir,NULL);

        (*raiz)->l2=NULL;
        (*raiz)->dir=NULL;
    }else{
        strcpy(promovePal,(*raiz)->chaveDir);
        apagarLista(promoveL);
        *promoveL=NULL;
        copiaLista(promoveL,(*raiz)->l2);
        apagarLista(&(*raiz)->l2);
        (*raiz)->qtd-=1;
        aux=criaNo1(info,ingl,(*raiz)->dir,sub,NULL);
        (*raiz)->l2=NULL;
        (*raiz)->dir=NULL;
    }
    return aux;
}

no23 *addNo(no23 *no,char *info,ing *lis,no23 *filho){
    if(strcmp(no->chaveEsq,info)<0){
        strcpy(no->chaveDir,info);
        no->l2=lis;
        no->dir=filho;
    }else{
        strcpy(no->chaveDir,no->chaveEsq);
        no->l2=no->l1;
        no->dir=no->cen;
        strcpy(no->chaveEsq,info);
        no->l1=lis;
        no->cen=filho;
    }
    no->qtd=2;
    return no;
}

int ehfolha(no23 *no){
    int r=0;
    if((no)->esq == NULL && (no)->cen == NULL && (no)->dir == NULL){
        r = 1;
    }
    return r;
}

no23 *inserir23(no23 **raiz,char *info,char *ingl,char *promove,ing **promoveL,no23 *pai){
    no23 *aux = NULL;
    ing *aux2=NULL;
    if(*promoveL==NULL){
        insereWordLista(&aux2,ingl);
    }    
    if(*raiz == NULL){
        *raiz=criaNo(info,ingl,NULL,NULL,NULL);
        aux=NULL;
    }else if(strcmp(info,(*raiz)->chaveEsq)==0){
        insereWordLista(&(*raiz)->l1,ingl);
    }else if((*raiz)->qtd == 2 && strcmp(info,(*raiz)->chaveDir) == 0){
        insereWordLista(&(*raiz)->l2,ingl);
    }else if(ehfolha(*raiz)){
        if((*raiz)->qtd == 1){
            *raiz=addNo(*raiz,info,aux2,NULL);
            aux=NULL;
        }else{
            aux=quebraNo(raiz,info,aux2,promove,promoveL,NULL);
        }
    }else{
        if(strcmp(info,(*raiz)->chaveEsq)<0){
            aux=inserir23(&((*raiz)->esq),info,ingl,promove,promoveL,*raiz);
        }else if((*raiz)->qtd==1 || strcmp(info,(*raiz)->chaveDir)<0){
            aux=inserir23(&((*raiz)->cen),info,ingl,promove,promoveL,*raiz);
        }else{
            aux=inserir23(&((*raiz)->dir),info,ingl,promove,promoveL,*raiz);
        }
    }
    if(aux!=NULL){
        char *copia=(char*)malloc(sizeof(char)*100);
        strcpy(copia,promove);
        ing *lista=NULL;
        copiaLista(&lista,*promoveL);
        if(pai==NULL){
            *raiz=criaNo1(promove,*promoveL,*raiz,aux,NULL);
            aux=NULL;
        }else if(pai->qtd==1){
            pai=addNo(pai,promove,*promoveL,aux);
            aux=NULL;
        }else{
            aux=quebraNo(&pai,copia,lista,promove,promoveL,aux);
        }
    }
    return aux;
}
//AQUI
void printEmOrdem(no23 *raiz){
    if(raiz!=NULL){
        printEmOrdem(raiz->esq);
        printf("%s | ",raiz->chaveEsq);
        mostraLista(raiz->l1);
        printf("\n");
        printEmOrdem(raiz->cen);
        if(raiz->qtd == 2){
            printf("%s | ",raiz->chaveDir);
            mostraLista(raiz->l2);
            printf("\n");
            printEmOrdem(raiz->dir);
        }
    }
}

//AQUI
void printUnidade(cap *uni, char *p){
    cap *aux=uni;
    for(uni; aux != NULL; aux=aux->prox){
        if(strcmp(aux->unidade, p) == 0){
            printf("Unidade: %s\n", aux->unidade);
            printEmOrdem(aux->arv23);
        }
    }
}

void *inserirCap(cap **uni ,char *nome){
    cap *new = (cap*) malloc(sizeof(cap));
    new->unidade=(char*)malloc(sizeof(char)*100);
    strcpy(new->unidade, nome);
    new->arv23 = NULL;
    new->prox = *uni;
    *uni = new; 
}

//AQUI
void abrirArquivo(char *caminho, cap **uni){
    FILE *fptr;
    int i, j;
    char *palavras, *nome, *ingles, *promove;
    promove=(char*)malloc(sizeof(char)*100);
    palavras=(char*)malloc(sizeof(char)*100);
    nome=(char*)malloc(sizeof(char)*100);
    ingles=(char*)malloc(sizeof(char)*100);
    ing *proLista = NULL;
    fptr = fopen(caminho, "r");
    if( fptr == NULL ){
        printf("Erro na abertura de arquivo!\n");
        return;        
    }else{
        printf("Arquivo aberto com sucesso!\n");
    }
    fscanf(fptr, "%s", palavras);
    while (!feof(fptr)){
        j = 0;
        if(palavras[0] == '%'){
            for(i=1; palavras[i] != '\0'; i++){
                nome[j] = palavras[i];
                j++;
            }
            nome[j] = '\0';
            inserirCap(uni, nome);
        }else{
            for(i=0; palavras[i] != ':'; i++){
                ingles[j] = palavras[i];
                j++;
            }
            ingles[j] = '\0';
            j = 0;
            for(i=i+1; palavras[i] != '\0'; i++){
                nome[j] = palavras[i];
                j++;
                if(palavras[i] == ','){
                    nome[j-1] = '\0';
                    inserir23(&(*uni)->arv23, nome, ingles, promove, &proLista, NULL);
                    proLista = NULL;
                    j = 0;
                }
            }
            nome[j] = '\0';
            inserir23(&(*uni)->arv23, nome, ingles, promove, &proLista, NULL);
            proLista = NULL;
        }
        fscanf(fptr, "%s", palavras);
    }
}

//AQUI
void copiaLista(ing **lista, ing *lis){
    if(lis != NULL){
        insereWordLista(lista, lis->eng);
        copiaLista(lista, lis->prox);
    }
}

void menorDir(no23 *raiz, no23 **no, no23 **paiNo){
    if(raiz->esq != NULL){
        *paiNo = raiz;
        menorDir(raiz->esq, no, paiNo);
    }else{
        *no = raiz;
    }
}

void maiorEsq(no23 *raiz, no23 **no, no23 **paiNo){
    if(raiz->dir != NULL){
        *paiNo = raiz;
        maiorEsq(raiz->dir, no, paiNo);
    }else{
        *no = raiz;
    }
}

//AQUI
int remover23(no23 **raiz, char *pal, no23 **pai){
    int removeu = 0;
    no23 *no = NULL, *no1, *paiNo = NULL, *paiNo1 = NULL, **aux;
    aux=(no23**) malloc(sizeof(no23*));
    no1 = (no23*) malloc(sizeof(no23));
    if(*raiz != NULL){
        if(ehfolha(*raiz)){
            if((*raiz)->qtd == 2){
                if(strcmp(pal, (*raiz)->chaveDir) == 0){
                    strcpy((*raiz)->chaveDir, " ");
                    apagarLista(&(*raiz)->l2);
                    (*raiz)->qtd = 1;
                    removeu = 1;
                }else if(strcmp(pal, (*raiz)->chaveEsq) == 0){
                    strcpy((*raiz)->chaveEsq, (*raiz)->chaveDir);
                    apagarLista(&(*raiz)->l1);
                    copiaLista(&(*raiz)->l1, (*raiz)->l2);
                    apagarLista(&(*raiz)->l2);
                    strcpy((*raiz)->chaveDir, " ");
                    (*raiz)->qtd = 1;
                    removeu = 1;
                }
            }else if(strcmp(pal, (*raiz)->chaveEsq) == 0){
                if(*pai == NULL){
                    free(*raiz);
                    *raiz = NULL;
                    removeu = 1;
                }else if(*raiz == (*pai)->esq){
                    strcpy((*raiz)->chaveEsq, (*pai)->chaveEsq);
                    apagarLista(&(*raiz)->l1);
                    copiaLista(&(*raiz)->l1, (*pai)->l1);
                    paiNo = *pai;
                    menorDir((*pai)->cen, &no, &paiNo);
                    strcpy((*pai)->chaveEsq, no->chaveEsq);
                    apagarLista(&(*pai)->l1);
                    copiaLista(&(*pai)->l1, no->l1);
                    removeu = 1;
                    if(no->qtd == 2){
                        strcpy(no->chaveEsq,no->chaveDir);
                        apagarLista(&no->l1);
                        copiaLista(&no->l1, no->l2);
                        strcpy(no->chaveDir," ");
                        apagarLista(&no->l2);
                        no->qtd = 1;
                    }else{
                        if(paiNo->qtd == 1){
                            strcpy((*raiz)->chaveDir, no->chaveEsq);
                            apagarLista(&(*raiz)->l2);
                            copiaLista(&(*raiz)->l2,no->l1);
                            (*raiz)->qtd = 2;
                            apagarLista(&no->l1);
                            free(no);
                            *pai = *raiz;
                        }else{
                            strcpy(no->chaveEsq,paiNo->chaveDir);
                            apagarLista(&no->l1);
                            copiaLista(&no->l1,paiNo->l2);
                            paiNo1 = paiNo;
                            menorDir(paiNo->dir, &no1, &paiNo1);
                            strcpy(paiNo->chaveDir,no1->chaveEsq);
                            apagarLista(&paiNo->l2);
                            copiaLista(&paiNo->l2,no1->l1);
                            if(no1->qtd == 2){
                                strcpy(no1->chaveEsq,no1->chaveDir);
                                apagarLista(&no1->l1);
                                copiaLista(&no1->l1,no1->l2);
                                strcpy(no1->chaveDir, " ");
                                apagarLista(&no1->l2);
                                no1->qtd = 1;
                            }else{
                                strcpy(no->chaveDir,paiNo->chaveDir);
                                apagarLista(&no->l2);
                                copiaLista(&no->l2,paiNo->l2);
                                no->qtd=2;
                                strcpy(paiNo->chaveDir, " ");
                                apagarLista(&paiNo->l2);
                                paiNo->qtd = 1;
                                apagarLista(&no1->l1);
                                apagarLista(&no1->l2);
                                free(no1);
                                paiNo1->dir = NULL;
                            }
                        }
                    }
                }else if(*raiz == (*pai)->cen){
                    removeu = 1;
                    if((*pai)->qtd == 1){
                        if(((*pai)->esq)->qtd == 2){
                            strcpy((*raiz)->chaveEsq, (*pai)->chaveEsq);
                            apagarLista(&(*raiz)->l1);
                            copiaLista(&(*raiz)->l1, (*pai)->l1);
                            strcpy((*pai)->chaveEsq, ((*pai)->esq)->chaveDir);
                            apagarLista(&(*pai)->l1);
                            copiaLista(&(*pai)->l1, ((*pai)->esq)->l2);
                            strcpy(((*pai)->esq)->chaveDir, " ");
                            apagarLista(&((*pai)->esq)->l2);
                            ((*pai)->esq)->qtd = 1;
                        }else{
                            strcpy(((*pai)->esq)->chaveDir, (*pai)->chaveEsq);
                            apagarLista(&((*pai)->esq)->l2);
                            copiaLista(&((*pai)->esq)->l2, (*pai)->l1);
                            apagarLista(&(*raiz)->l1);
                            apagarLista(&(*raiz)->l2);
                            free(*raiz);
                            ((*pai)->esq)->qtd = 2;
                            *aux = (*pai)->esq;
                            apagarLista(&(*pai)->l1);
                            apagarLista(&(*pai)->l1);
                            free(*pai);
                            *pai = *aux;
                        }
                    }else{
                        strcpy((*raiz)->chaveEsq, (*pai)->chaveDir);
                        apagarLista(&(*raiz)->l1);
                        copiaLista(&(*raiz)->l1, (*pai)->l2);
                        paiNo = *pai;
                        menorDir((*pai)->dir, &no, &paiNo);
                        strcpy((*pai)->chaveDir, no->chaveEsq);
                        apagarLista(&(*pai)->l2);
                        copiaLista(&(*pai)->l2,no->l1);
                        if(no->qtd == 2){
                            strcpy(no->chaveEsq, no->chaveDir);
                            apagarLista(&no->l1);
                            copiaLista(&no->l1, no->l2);
                            strcpy(no->chaveDir, " ");
                            apagarLista(&no->l2);
                            no->qtd = 1;
                        }else{
                            (*raiz)->qtd = 2;
                            strcpy((*raiz)->chaveDir, (*pai)->chaveDir);
                            apagarLista(&(*raiz)->l2);
                            copiaLista(&(*raiz)->l2, (*pai)->l2);
                            strcpy((*pai)->chaveDir, " ");
                            apagarLista(&(*pai)->l2);
                            (*pai)->qtd = 1;
                            free(no);
                            (*pai)->dir = NULL;
                        }
                    }
                }else{
                    removeu = 1;
                    paiNo = *pai;
                    maiorEsq((*pai)->cen, &no, &paiNo);
                    if(no->qtd == 1){
                        strcpy(no->chaveDir, (*pai)->chaveDir);
                        apagarLista(&no->l2);
                        copiaLista(&no->l2, (*pai)->l2);
                        strcpy((*pai)->chaveDir, " ");
                        apagarLista(&(*pai)->l2);
                        (*pai)->qtd = 1;
                        no->qtd = 2;
                        free(*raiz);
                        *raiz = NULL;
                    }else{
                        strcpy((*raiz)->chaveEsq, (*pai)->chaveDir);
                        apagarLista(&(*raiz)->l1);
                        copiaLista(&(*raiz)->l1, (*pai)->l2);
                        strcpy((*pai)->chaveDir, no->chaveDir);
                        apagarLista(&(*pai)->l2);
                        copiaLista(&(*pai)->l2,no->l2);
                        strcpy(no->chaveDir, " ");
                        apagarLista(&no->l2);
                        no->qtd = 1;
                    }
                }
            }
        }else{
            if(strcmp(pal, (*raiz)->chaveEsq)<0){
                removeu = remover23(&(*raiz)->esq, pal, raiz);
            }else if(strcmp(pal, (*raiz)->chaveEsq)==0){
                paiNo = *raiz;
                menorDir((*raiz)->cen, &no, &paiNo);
                strcpy((*raiz)->chaveEsq,no->chaveEsq);
                apagarLista(&(*raiz)->l1);
                copiaLista(&(*raiz)->l1, no->l1);
                printEmOrdem(*raiz);
                printf("\n\n");
                remover23(&(*raiz)->cen, (*raiz)->chaveEsq, raiz);
                printf("\n\n");
                printEmOrdem(*raiz);
                removeu = 1;
            }else if((*raiz)->qtd == 1 || strcmp(pal, (*raiz)->chaveDir)<0){
                removeu = remover23(&(*raiz)->cen, pal, raiz);
            }else if(pal == (*raiz)->chaveDir){
                paiNo = *pai;
                menorDir((*pai)->dir, &no, &paiNo);
                strcpy((*raiz)->chaveDir,no->chaveEsq);
                apagarLista(&(*raiz)->l2);
                copiaLista(&(*raiz)->l2, no->l1);
                remover23(&(*raiz)->dir, (*raiz)->chaveDir, raiz);
                removeu = 1;
            }else{
                removeu = remover23(&(*raiz)->dir, pal, raiz);
            }
        }
    }
    return removeu;
}

cap* procuraUnidade(cap *uni, char *p, int *certo){
    cap *aux=uni;
    for(uni;( aux != NULL && strcmp(aux->unidade, p) != 0); aux=aux->prox){

    }
    *certo = (aux != NULL)?1:0;    
    return aux;
}

int buscaWord(no23 *uni, char *p){
    int c = 0;
    if(uni != NULL){
        if(strcmp(p, uni->chaveEsq) < 0){
            c = buscaWord(uni->esq, p);
        }else if(strcmp(p, uni->chaveEsq) > 0 && strcmp(p, uni->chaveDir) < 0){
            c = buscaWord(uni->cen, p);
        }else if(strcmp(p, uni->chaveEsq) == 0){
            c = 1;
        }else if(strcmp(p, uni->chaveDir) > 0){
            c = buscaWord(uni->dir, p);
        }else if(strcmp(p, uni->chaveDir) == 0){
            c = 1;
        }
    }
    return c;
}



int main(){
    no23 *no;
    cap *uni = NULL, **aux;
    aux=(cap**)malloc(sizeof(cap*));
    int certo, op;
    char wordSearch[100], nomeArquivo[100],unidade[100];
    
    clock_t inicioBusca, fimBusca;
    clock_t inicioInserir, fimInserir;
    float tempoBusca, tempoInserir;

    while(1){
        printf("\n1 - Importar arquivo\n");
        printf("2 - Remover palavra\n");
        printf("3 - Buscar palavra\n");
        printf("4 - Exibir unidade\n");
        printf("0 - Sair\n");
        printf("\n");
        printf("Escolha uma Opção: ");
        scanf("%d", &op);
        switch(op){
            case 1:
                printf("Informe nome do arquivo: ");
                setbuf(stdin, NULL);
                scanf("%s", nomeArquivo);
                inicioInserir = clock();
                abrirArquivo(nomeArquivo, &uni);
                fimInserir = clock();
                tempoInserir = ((fimInserir - inicioInserir) * 1000000000) / CLOCKS_PER_SEC;
                printf("Tempo gasto inserindo: %.2fns \n", tempoInserir);
                break;
            
            case 2:
                
                certo = 0;
                printf("Informe a palavra: ");
                char wordSearch2[50];
                scanf("%s", wordSearch2);

                printf("Escolha uma Unidade: ");
                setbuf(stdin, NULL);
                scanf("%s", unidade);

                *aux = procuraUnidade(uni, unidade, &certo);
                if( certo == 1 ){
                    no23 **pai=(no23**)malloc(sizeof(no23*));
                    *pai=NULL;
                    remover23(&(*aux)->arv23, wordSearch2, pai);
                }else{
                    printf("\n -- Unidade não Cadastrada --\n");
                }
                
                break;
            
            case 3:
                certo = 0;
                printf("Informe a palavra em PTBR: ");
                char wordSearch[50];
                scanf("%s", wordSearch);

                printf("Escolha uma Unidade: ");
                setbuf(stdin, NULL);
                scanf("%s", unidade);

                inicioBusca = clock();
                *aux = procuraUnidade(uni, unidade, &certo);
                fimBusca = clock();
                tempoBusca = ((fimBusca - inicioBusca) * 1000) / CLOCKS_PER_SEC;
                printf("Tempo gasto para BUSCAR UNIDADE: %lf \n", tempoBusca);
                
                if(certo == 1){
                    inicioBusca = clock();
                    printf("\nUnidade [%s]: \n",unidade );

                    if(buscaWord((*aux)->arv23, wordSearch) == 1){
                        printf("Palavra Encontrada!\n");
                    }else{
                        printf(" -- Palavra não encontrada --\n");
                    }   

                    fimBusca = clock();
                    tempoBusca = ((fimBusca - inicioBusca) * 1000) / CLOCKS_PER_SEC;
                    printf("Tempo gasto para BUSCAR PALAVRA: %lf \n", tempoBusca);
                }
                break;
            
            case 4:
                printf("Escolha uma Unidade: ");
                scanf("%s", wordSearch);
                printUnidade(uni, wordSearch);
                break;
            case 0:
                exit(0);
                break;
            default:
                printf("\n -- Informe uma opção válida --\n");
                break;
        }
    }
}

