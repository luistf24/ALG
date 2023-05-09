#!/bin/bash 

rm $2/data/$1.dat


i=100
tam=20000
jump=1000

if [ "$1" == "voraz" ]
then
	i=1000
	tam=100000
	jump=3000
fi

while [ "$i" -le $tam ]
do
	echo $i
    $2/bin/$1 $i $3 >> $2/data/$1.dat
     i=$(( $i + $jump ))
done
      
