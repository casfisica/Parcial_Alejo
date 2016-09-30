#include <stdio.h>
#include <stdlib.h> /* for atoi() */
#include <string.h> /* for strtok*/
#include <math.h>  /*for sqrt*/

struct Particle
{
  int *FNid;
  float *Pos;
  float *FNdistance;
  float CMdistance;
  int Ntri;

};//end estruct Particle

/*Declaro las funciones*/
struct Particle *Getdata(const char *inputfile, int NFN, int *num);
float Distance(struct Particle *part1,struct Particle *part2);
void Compare(struct Particle *part1,int part1id,struct Particle *part2,int part2id,int NFN);
void Gettrinagles(struct Particle *part1,int part1id,struct Particle *part2,int part2id);


int main(int argc,char *argv[] )
/*Se le pasa como argumento Opcional input.dat,output.dat, NFN(#de primeros vecinos) */
{
  struct Particle *bunch;
  const char *inputfile;
  const char *outputfile;
  char input[100];
  char output[100];
  int NFN;
  float dis; //temp to evaluate de Diference function
  int num=0;
  
  if (argc<3)/*Si no se le pasa como argumento lo pregunta*/
    {
      printf( "Enter inputfile outputfile NFN:");
      scanf("%s %s %i", &input, &output, &NFN);
      inputfile=input;
      outputfile=output; 
    }else
    {
      inputfile=argv[1];
      outputfile=argv[2];
      NFN = atoi(argv[3]); 
    }//End if else

  bunch = Getdata(inputfile,NFN,&num);//Lleno el vector de estructuras
  //printf ("dimension: %i\n",num);
  num=10;
  for (int i=0; i<num; i++)
    {
      for (int j=i+1; j<num;j++)
	{
	  printf("i= %i ,j= %i\n",i,j);
	  Compare(&bunch[i],i,&bunch[j],j, NFN);
	}
    }
  for (int i=0; i<num; i++)
    {
      printf ("distancia[%i]: %f\n",i,bunch[i].FNdistance[0]);
      printf ("distancia[%i]: %f\n",i,bunch[i].FNdistance[1]);
    }
  printf ("distancia[7]: %f\n",bunch[7].FNdistance[0]);
  printf ("distancia[7]: %f\n",bunch[7].FNdistance[1]);
  
  return 0;
  
}//End main


struct Particle *Getdata(const char *inputfile, int NFN, int *num)
{
  FILE *in;
  fpos_t position;
  char * line = NULL; //Para leer el archivo
  size_t len = 0; //Para leer el archivo
  ssize_t read; //Para leer el archivo
  char * pch;  //Para contar las columnas
  char * pch1;  //Para partir las lineas del archivo
  int ch=0;
  int NTP=0; //argumento auxiliar de numero de particulas
  int DIM=0; //argumento auxiliar de dimension
  int i=0;
  float * tmp;

  in=fopen( inputfile, "r" ); //Abro el archivo de datos
  if (in == NULL)
    {
      printf("Specify input file, or is not in the path\n");
      exit(EXIT_FAILURE);
    }
  
  fgetpos(in, &position); //Adquiere la posicion dentro del archivo(inicial)

  while(!feof(in))//feof search the end of de file, para contar el número de particulas
    {
      ch = fgetc(in);
      if(ch == '\n')
	{
	  NTP++;
	}
    }
  *num=NTP;
  fsetpos(in, &position);//manda el puntero a la pos inicial
  
  struct Particle *bunch = malloc(sizeof(struct Particle) * NTP);
  
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
  
      i++;
    }
  fclose(in);

  return bunch;
}//End Getdata


float Distance(struct Particle *part1,struct Particle *part2)
{
  int i=1;
  float dist;
  float sum=0;
  while(part1->Pos[i])
    {
      sum=sum + (part1->Pos[i]-part2->Pos[i])*(part1->Pos[i]-part2->Pos[i]);
      //printf("%f, %f \n",part1->Pos[i],part2->Pos[i]);
      //printf("sum=%f\n",sum);
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
  printf("Distancia=%f\n",dist);
  int condition=0;
  
  for(int i=0; i<NFN;i++)
    {
      if (part1->FNdistance[i] != 0)
	{
	  if (part1->FNdistance[i]>dist)
	    {
	      condition=0;
	      for(int j=0; j<NFN;j++)//No perder ya encontrados
		{
		  if(part1->FNid[j]==part2id)
		    condition=1;
		}
	      if(condition==0)
		{
		  part1->FNdistance[i]=dist;
		  part1->FNid[i]=part2id;
		}
	    }
	}
      else
	{
	  condition=0;
	      for(int j=0; j<NFN;j++)//No perder ya encontrados
		{
		  if(part1->FNid[j]==part2id)
		    condition=1;
		}
	      if(condition==0)
		{
		  part1->FNdistance[i]=dist;
		  part1->FNid[i]=part2id;
		}
	}
      printf("part1->FNid[%i]= %i\n",i,part1->FNid[i]);
      printf("part1->FNdistance[%i]=%f \n",i,part1->FNdistance[i]);
    }
  
  for(int i=0; i<NFN;i++)
    {
      if (part2->FNdistance[i] != 0)
	{
	  if (part2->FNdistance[i]>dist)
	    {
	      condition=0;
	      for(int j=0; j<NFN;j++)//No perder ya encontrados
		{
		  if(part2->FNid[j]==part1id)
		    condition=1;
		}
	      if(condition==0)
		{
		  part2->FNdistance[i]=dist;
		  part2->FNid[i]=part1id;
		}
	    }
	}
      else
	{
	   condition=0;
	   for(int j=0; j<NFN;j++)//No perder ya encontrados
	     {
	       if(part2->FNid[j]==part1id)
		 condition=1;
	     }
	   if(condition==0)
	     {
	       part2->FNdistance[i]=dist;
	       part2->FNid[i]=part1id;
	     }
	}
      //printf("part2->FNid[%i]= %i\n",i,part2->FNid[i]);
      //printf("part2->FNdistance[%i]=%f \n",i,part2->FNdistance[i]);      
    }
  
};
