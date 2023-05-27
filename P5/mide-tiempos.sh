#!/bin/bash 

rm $2/data/$1_*.dat


i=4
tam=20
jump=1

while [ "$i" -le $tam ]
do
	echo "Tamaño : " $i

	Generador/bin/generador $i

    $2/bin/$1 $i 0 >> $2/data/$1.dat

    i=$(( $i + $jump ))
done
      
