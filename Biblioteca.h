struct _no23{
    int nInfos;
    char Info1[500], Info2[500];
    struct _no23 *esq, *cen, *dir;
};

typedef struct _no23 no23;


no23 ** CriaArvore();
int ehfolha(no23 *no);
void inOrdem(no23 **Raiz);
// no23 * criaNo (int Info, no23 *esq, no23 * centro, no23 *dir);
// no23 * insere (no23 **Raiz, int Info, int *Promove, no23 *Pai);
// no23 * adicionaNO (no23 *no, int Info, no23 *filho);
// no23 * quebraNo(no23 *no, int Info, int *promove, no23 *subarvore);

no23 * criaNo (char *Nome, no23 *esq, no23 * centro, no23 *dir);
no23 * adicionaNO (no23 *no, char *Nome, no23 *filho);
no23 *insere (no23 **Raiz, char *Nome, char *Promove, no23 *Pai);
no23 *quebraNo(no23 *no, char *Nome, char *promove, no23 *subarvore);
