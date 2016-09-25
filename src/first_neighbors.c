#include <stdio.h>
#include <stdlib.h> /* for atoi() */


struct Particle
{
  int *FNid;
  float *Pos;
  float *FNdistance;

};//end estruct Particle


int main(int argc,char *argv[] )
/*Se le pasa como argumento Opcional input.dat,output.dat, NFN(#de primeros vecinos) */
{
  FILE *in;
  const char *inputfile;
  const char *outputfile;
  int NFN;
  int NTP=0; //argumento auxiliar de numero de particulas
  int DIM=2; //argumento auxiliar de dimension
  char * line = NULL; //Para leer el archivo
  size_t len = 0; //Para leer el archivo
  ssize_t read; //Para leer el archivo
  char * pch;  //Para partir las lineas del archivo

  
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

  in=fopen( inputfile, "r" ); //Abro el archivo de datos
  if (in == NULL)
        exit(EXIT_FAILURE);
  
  struct Particle *bunch = malloc(sizeof(struct Particle) * NTP);

  while ((read = getline(&line, &len, in)) != -1)
    {
      //      printf("La linea de tamaño %zu :\n", read);
      //      printf("%s \n", line);
      
      //Inicializa el vector de indices de primeros vecinos
      bunch[NTP].FNid=malloc(sizeof(int)*NFN);
      //Inicializa el vector de distancias de primeros vecinos
      bunch[NTP].FNdistance=malloc(sizeof(float)*NFN);
      //Inicializa el vector de posición
      bunch[NTP].Pos=malloc(sizeof(float)*DIM);
      NTP++; //Contador numero de particulas
    }
  

  

  //  free(bunch); //Me sale un error de liberado de memoria, sin eso si funciona
  return 0;
  
}
