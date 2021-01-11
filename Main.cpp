#include "Funcoes.c"

int main (void){
  srand(time(NULL));
  char Aux[500], Aux2[500];
  no23 **Raiz, *Aux_No;
  Raiz = CriaArvore();

  for (int x = 0; x < 3; x++){
    // Aux_No = insere(Raiz, (rand () % 1000), &Aux, NULL);
    scanf("%s", Aux2);
    Aux_No = insere(Raiz, Aux2, Aux, NULL);
  }

  inOrdem(Raiz);
  system("pause");

  return 0;
}
