#include <stdio.h>
#include <stdlib.h> /* for atoi() */
 
int main(int argc,char *argv[] )/*Se le pasa como argumento el Xmax Opcional*/
{
  int Xmax,flag;
  if (argc<2)/*Si no se le pasa como argumento lo pregunta*/
    {
      printf( "Ingrese el valor de Xmax :");
      scanf("%d", &Xmax);
    }else
    {
      Xmax = atoi(argv[1]); 
    }//End if else

  //   printf("Xmax es %d \n", Xmax); /*Para depurar*/
  for (int i=1; i<=Xmax; i++)
    {
      flag=0;/*Se usa para contar los divisores*/
      for(int j=1;j<=i;j++)
	{
	  if (i%j==0)
	    {
	      flag++;
	    }//End if
	}//End for
      if(flag==2) /*Los divisores de los primos son 1 y el mismo (2)*/
	{
	  printf("%d, ", i);
	}//End if
    }//End for
  
  printf("\n");
  
  return 0;

  
}
