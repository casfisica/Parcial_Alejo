#!/bin/bash


if [ $# -eq 3 ] #Copare the number of imputs($#) to 3
  then

  #sort -R $2: Reorder the lines in the second argument of the script ($1),
  #head -n $1: Toma las primeras $1 (primer argumento del script) y las escribe
  #en un archivo llamado $3 (tercer argumento del script)
      sort -R $2 | head -n $1 >$3 

else

    echo "Wrong number of arguments, use: $./pic.sh 100 coordenadas.dat data-sample.dat"

fi


    
  
