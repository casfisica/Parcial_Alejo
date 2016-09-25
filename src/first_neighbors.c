#include <stdio.h>
#include <stdlib.h> /* for atoi() */


struct Particle
{
  int *FNid;
  float *FNdistance;

};//end estruct Particle


int main(int argc,char *argv[] )
/*Se le pasa como argumento Opcional input.dat,output.dat, NFN(#de primeros vecinos) */
{
  char *inputfile;
  char *outputfile;
  int NFN;
  int NTP=10; //argumento auxiliar de numero de particulas
  if (argc<3)/*Si no se le pasa como argumento lo pregunta*/
    {
      printf( "Enter inputfile outputfile NFN:");
      scanf("%s %s %i", &inputfile, &outputfile, &NFN);
    }else
    {
      inputfile=argv[1];
      outputfile=argv[2];
      NFN = atoi(argv[3]); 
    }//End if else

  //  printf("Inputfile: %s, outputfile: %s, Número de primeros vecinos: %i \n", inputfile, outputfile, NFN);
  
  struct Particle *bunch = malloc(sizeof(struct Particle) * NTP);

  for(int i=0;i<=NTP;i++)
    {
      bunch[i].FNid=malloc(sizeof(int)*NFN);
      bunch[i].FNdistance=malloc(sizeof(float)*NFN);
      
      for (int j=i+1;j<=NTP;j++)
	{


	  
	}
      

    }
  

  

  free(bunch);
  return 0;
  
}
