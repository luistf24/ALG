#!/bin/bash 

rm $2/data/$1.dat


i=1000
tam=101000
jump=5000

while [ "$i" -le $tam ]
do
	echo $i
    $2/bin/$1 $i $3 >> $2/data/$1.dat
     i=$(( $i + $jump ))
done
      
