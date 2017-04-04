#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void llenar(int *red, int m, int n, float proba);//Llena una red dem por n con unos y ceros con proba proba
void imprimir(int *red, int m, int n);//Imprime la red en pantalla
int   hoshen(int *red, int m, int n); //Algoritmo de etiquetado
int   actualizar(int *red,int *clase,int s1,int frag);//Etiqueta el lugar s con frag en la red. -------------------------->¿Vector clase?
void  etiqueta_falsa(int *red,int *clase,int s1,int s2);
void  corregir_etiqueta(int *red,int *clase,int n);

int main(){
	int m=4;
	int n=15;
	float proba=0.6;
	int *red;
	red=malloc(sizeof(int)*m*n);
	printf("Filas: %d, Col: %d, Proba: %.2f \n",m, n, proba);

	llenar(red,m,n,proba);
	imprimir(red,m,n);
	hoshen(red,m,n);
	printf("---------------------------------------------------------\n");
	imprimir(red,m,n);
	
	free(red); 

	return 0;
	
}
void llenar(int *red, int m, int n, float proba){
	srand((unsigned int)time(NULL));
	int i;
	float r;	
	for(i=0;i<m*n;i++){
		r = (float)rand()/(float)RAND_MAX;
		if(r<proba){
			red[i] = 1;
		}else{
			red[i] = 0;	
		}
	}
}
void imprimir(int *red, int m, int n){
	int i,j;
	for(i=1;i<=m;i++){
		for(j=1;j<=n;j++){			
			printf("%d",red[i*n-(n-j+1)]);
		}
		printf("\n");	
	}
}
int hoshen(int *red, int m, int n)
{
  /*
    Esta funcion implementa en algoritmo de Hoshen-Kopelman.
    Recibe el puntero que apunta a la red y asigna etiquetas 
    a cada fragmento de red.
    Pienso el recorrido como:        | s2 |
 		                | s1 | s  |
  */

  int i,j,k,s,s1,s2,frag;
  int *clase;

  frag=0; //Numero de etiqueta actual
  
  clase=(int *)malloc(m*n*sizeof(int)); //Tal vez puede ser mas chico

  for(k=0;k<m*n;k++){ //Lleno el vector clase desde el 0
	 *(clase+k)=k;//------------------------------->Lo lleno con su lugar
  }
  
  // Hago el etiquetado para el primer elemento de la red

  s=0; //Primer elemento de la red
  frag=2; //Empiezo las etiquetas en el numero 2
  if (*red){// Quiere decir si lo que esta en el lugar 0 de red es 1 (es decir TRUE)
	frag=actualizar(red,clase,s,frag); // Si hay un 1 lo etiqueto con el 2. Si no va a quedar el 0.
  }
  
  // Etiquetado para la primera fila de la red

  for(s=1;s<n;s++) //Lugar en memoria hasta n-1
    {	
      printf("s: %d\n",*(red+s));
      if (*(red+s)) //Si hay un 1 en el lugar s de la primer fila
         {
           s1=*(red+s-1); //Elemento a la izquierda
	   printf("s-1: %d\n",s1);
	   if(s1!=0){
		printf("frag antes: %d\n",frag);
           	actualizar(red,clase,s,frag); // Actualizo y no cambio el frag
		printf("frag dsp: %d\n",frag); 
	   }else{
		printf("frag antes: %d\n",frag); 
		frag=actualizar(red,clase,s,frag); // Actualizo y sumo uno a frag. No tiene nada a izquierda.
		printf("frag dsp: %d\n",frag); 
	   }

         }
    }
  

  
  free(clase);

  return 0;
}
int   actualizar(int *red,int *clase,int s1,int frag){
	if(s1>0){
	    //No actualizo frag
	    *(red)=frag; //Realizo el etiquetado correcto buscando en clase
	    return frag;
	}else{
	    *(red)=frag; //Realizo el etiquetado. Nueva etiqueta falsa?
	    *(clase)=frag; //En el lugar s guardo que hay etiqueta frag
	    return frag+1;
	}	
}
