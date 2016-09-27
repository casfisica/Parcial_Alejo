#include <stdio.h>
#include <stdlib.h> /* for atoi() */
#include <string.h> /* for strtok*/
#include <math.h>  /*for sqrt*/

struct Particle
{
  int *FNid;
  float *Pos;
  float *FNdistance;

};//end estruct Particle

/*Declaro la función*/
float Distance(struct Particle *part1,struct Particle *part2);

void Compare(struct Particle *part1,int part1id,struct Particle *part2,int part2id,int NFN);


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
  float dis; //temp to evaluate de Diference function
  
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
	  //printf ("Pos[%i]= %f \n",DIM,bunch[i].Pos[DIM]);
	  pch = strtok (NULL, " ,");
	  DIM++;
	}
      //printf ("dimension: %i\n",DIM);    
      //printf ("bunch[i].Pos[1]=%f\n",bunch[i].Pos[1]);    
      i++;
    }

  for(j=0;j<NTP;j++)
    {
      for (int l=j+1;l<NTP;j++)
	{
	  //printf ("bunch[j].Pos[1]=%f\n",bunch[j].Pos[1]);
	  //printf ("bunch[%j].FNdistance[1]=%f\n",bunch[i].FNdistance[1]);
	  //dis=Distance(&bunch[0],&bunch[j]);
	  //printf ("Distancia[%i]=%f\n",j,dis); 
	  Compare(&bunch[j],j,&bunch[l],l,NFN);
	  printf ("bunch[j].FNid=%i\n",bunch[j].FNid[0]); 
	  printf ("bunch[%i].FNdistance[1]=%f\n",j,bunch[j].FNdistance[1]); 
	  //printf ("%i,%i\n",j,l); 
	  
	}
      
    }

  
  free(bunch);//Libero la memoria (Pregunta para Omar)
  return 0;
  
}


float Distance(struct Particle *part1,struct Particle *part2)
{
  int i=1;
  float dist;
  float sum=0;
  while(part1->Pos[i])
    {
      sum=sum + (part1->Pos[i]-part2->Pos[i])*(part1->Pos[i]-part2->Pos[i]);
      //      printf("%f, %f \n",part1->Pos[i],part2->Pos[i]);
      //      printf("sum=%f\n",sum);
      i++;
    }
  
  dist=sqrt(sum);
  //  printf("Dis=%f\n",dist);
  return dist;
};

void Compare(struct Particle *part1,int part1id,struct Particle *part2,int part2id,int NFN)
{
  float dist;
  dist=Distance(part1, part2);
  
  for(int i=0; i<NFN;i++)
    {
      //printf("%f, %f \n",part1->FNid[i],part2->FNid[i]);      
      if (part1->FNdistance[i] != 0)
	{
	  if (dist < part1->FNdistance[i])
	    {
	      part1->FNdistance[i]=dist;
	      part1->FNid[i]=part2id;
	    }
	}
      else
	{
	  part1->FNdistance[i]=dist;
	  part1->FNid[i]=part2id;
	}
    }
  
  for(int i=0; i<NFN;i++)
    {
      if (part2->FNdistance[i] != 0)
	{
	  if (dist < part2->FNdistance[i])
	    {
	      part2->FNdistance[i]=dist;
	      part2->FNid[i]=part1id;
	    }
	}
      else
	{
	  part1->FNdistance[i]=dist;
	  part1->FNid[i]=part1id;
	}
    }
    
};
