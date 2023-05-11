#!/bin/bash 

rm $2/data/$1.dat


i=4
tam=20
jump=1

#if [ "$1" == "voraz" ]
#then
	#i=1000
	#tam=100000
	#jump=3000
#fi

while [ "$i" -le $tam ]
do
	echo "Tamaño : " $i
	Generador/bin/generador $i

	echo "Cota 1"
    $2/bin/$1 $i 0 0 >> $2/data/$1_0.dat

	echo "Cota 2"
    $2/bin/$1 $i 1 0 >> $2/data/$1_1.dat

	echo "Cota 3"
    $2/bin/$1 $i 2 0 >> $2/data/$1_2.dat

    i=$(( $i + $jump ))
done
      
