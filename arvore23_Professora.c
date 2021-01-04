#include <stdio.h>
#include <stdlib.h>

typedef struct _noArv23{
	int chaveEsq,
	    chaveDir,
	    nChaves;
struct _noArv23  *esq,
	             *centro,
	             *dir;
}noArv23;



noArv23* criaNo(int Info1, noArv23 *esq, noArv23 *centro)
{
	noArv23 *no;
	
	no = (noArv23 *) malloc(sizeof(noArv23));
	
	(*no).chaveEsq = Info1;
	(*no).chaveDir = 0;
	(*no).nChaves = 1;
	(*no).esq = esq;
	(*no).centro = centro;
	(*no).dir = NULL;
	
return(no);	
}


noArv23* adicionaNo(noArv23 *No, int Info, noArv23 *Novo)
{
  
 if(Info > (*No).chaveEsq)
  {
	(*No).chaveDir = Info;
	(*No).dir = Novo;
  }	
 else {
	    (*No).chaveDir = (*No).chaveEsq;
	    (*No).chaveEsq = Info; 
	    (*No).dir = (*No).centro;
	    (*No).centro = Novo;
      }
(*No).nChaves = 2;

	
return(No);	
}


int ehfolha(noArv23 *No)
{ int folha = 0;
	
	if((*No).esq == NULL && (*No).centro == NULL && (*No).dir == NULL)
	  folha = 1;
	
return(folha);	
}


noArv23 *quebraNo(noArv23 **Raiz, int Info, noArv23 *NovoNo,int *InfoMeio)
{ noArv23 *Novo;
	
	if(Info > (**Raiz).chaveDir)
	 {noArv23 *esq, *centro;
	   *InfoMeio = (**Raiz).chaveDir;
	   (**Raiz).chaveDir = 0;
	   (**Raiz).nChaves = 1; 
	   esq = (**Raiz).dir;
	   centro = NovoNo;	 
	   Novo = criaNo(Info, esq, centro);
	   (**Raiz).dir = NULL;
		
	}
	else if(Info > (**Raiz).chaveEsq)
	      {noArv23 *esq, *centro;
		   *InfoMeio = Info;
		   esq = NovoNo;
		   centro = (**Raiz).dir;
		   Novo = criaNo((**Raiz).chaveDir,esq, centro);
		   (**Raiz).chaveDir = 0;
		   (**Raiz).nChaves = 1;
		   (**Raiz).dir = NULL;
	      } 
	     else{ noArv23 *esq, *centro;
		       *InfoMeio = (**Raiz).chaveEsq;
		       centro = (**Raiz).dir;
		       esq = (**Raiz).centro;
		       Novo = criaNo((**Raiz).chaveDir, esq,centro);
		       (**Raiz).chaveEsq = Info;
		       (**Raiz).chaveDir = 0;
		       (**Raiz).nChaves = 1;
		       (**Raiz).dir = NULL;
		       (**Raiz).centro = Novo;
	          }

return(Novo);	
}


noArv23* insere(noArv23 *Pai,noArv23 **Raiz, int Info, int *InfoMeio)
{ noArv23 *novo;
	
	if (*Raiz == NULL)
	  {
	    *Raiz = criaNo(Info,NULL,NULL);	
	  }
	else{ 
		  if(ehfolha(*Raiz))
		   {
			if((**Raiz).nChaves == 1)
			  *Raiz = adicionaNo(*Raiz,Info,NULL);
			else {novo = quebraNo(Raiz,Info,NULL, InfoMeio);
			      if (Pai == NULL)
			        {*Raiz = criaNo(*InfoMeio,*Raiz,novo); 
			         novo = NULL;
			        }  
			     }
		   }
		 else{
			if (Info < (**Raiz).chaveEsq)
              novo = insere(*Raiz, &(**Raiz).esq, Info,InfoMeio);
            else if((**Raiz).nChaves == 1)
                   novo = insere(*Raiz, &(**Raiz).centro, Info,InfoMeio);
                 else if (Info < (**Raiz).chaveDir)
                        novo = insere(*Raiz, &(**Raiz).centro, Info,InfoMeio);
                      else novo = insere(*Raiz, &(**Raiz).dir, Info,InfoMeio); 
	          }
         if(novo != NULL)
          { if((**Raiz).nChaves == 1)
                {*Raiz = adicionaNo(*Raiz,*InfoMeio,novo);
                 novo = NULL;
                 }
            else { novo = quebraNo(Raiz,*InfoMeio,novo, InfoMeio);
					 if (Pai == NULL)
						{*Raiz = criaNo(*InfoMeio,*Raiz, novo);
						 novo = NULL; 
						}  
             }
         }

	     }
	return novo;	
}

int main(){
	noArv23 *ar = NULL;
	insere(ar, &ar, 12, NULL);
	printf("ok\n");
}