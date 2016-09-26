#include <stdio.h>
#include <stdlib.h> /* for atoi() */
#include <string.h> /* for strtok*/

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
  int NFN,j,i;
  int NTP=0; //argumento auxiliar de numero de particulas
  int DIM=0; //argumento auxiliar de dimension
  char * line = NULL; //Para leer el archivo
  size_t len = 0; //Para leer el archivo
  ssize_t read; //Para leer el archivo
  char * pch;  //Para contar las columnas
  char * pch1;  //Para partir las lineas del archivo
  int ch=0;
  fpos_t position;
  float * tmp;
  
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

  //printf("Inputfile: %s, outputfile: %s, Número de primeros vecinos: %i \n", inputfile, outputfile, NFN);

  in=fopen( inputfile, "r" ); //Abro el archivo de datos
  if (in == NULL)
        exit(EXIT_FAILURE);
  
  fgetpos(in, &position); //Adquiere la posicion dentro del archivo(inicial)
  
  while(!feof(in))
    {
      ch = fgetc(in);
      if(ch == '\n')
	{
	  NTP++;
	}
    }
  fsetpos(in, &position);//manda el puntero a la pos inicial

  struct Particle *bunch = malloc(sizeof(struct Particle) * NTP);
  i=0;
  //Mientras no se acabe el archivo lee las lineas en line
  while ((read = getline(&line, &len, in)) != -1)
    {
      //printf("La linea de tamaño %zu :\n", read);
      //printf("Contenido de la linea: %s \n", line);

      //Mientras la linea no se acabe, lee elementos separados por ,- y espacios
      pch1 = strtok (line," ,"); //Para contar
      pch =pch1; //Para llenar

      //Inicializa el vector de indices de primeros vecinos
      bunch[i].FNid=malloc(sizeof(int)*NFN);
      //Inicializa el vector de distancias de primeros vecinos
      bunch[i].FNdistance=malloc(sizeof(float)*NFN);
      //Inicializa el vector de posición
      DIM=1;
      while (pch != NULL)//Para contar la dimension
	{
	  if ((tmp = realloc(bunch[i].Pos, sizeof(float) * (sizeof(bunch[i].Pos) + 1))) == NULL)//Es una alocación dinámica de memoria.
	    {
	      fprintf(stderr, "ERROR: realloc failed");
	    }
	  bunch[i].Pos= tmp;
	  bunch[i].Pos[DIM]=atof(pch);
	  //	  printf ("Pos[%i]= %f \n",DIM,bunch[i].Pos[DIM]);
	  pch = strtok (NULL, " ,");
	  DIM++;
	}

      //printf ("dimension: %i\n",DIM);
    
    }
  

  

  //  free(bunch); //Me sale un error de liberado de memoria, sin eso si funciona
  return 0;
  
}
