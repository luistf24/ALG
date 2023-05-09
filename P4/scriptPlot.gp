#!/usr/local/bin/gnuplot --persist

print "Salida	: ", ARG1.".jpeg"
print "Datos	: ", ARG1 .".dat"
print "Título	: ", ARG2 
print "Carpeta	: ", ARG3
print "Orden	: ", ARG4

set terminal jpeg
set output ARG3."/img/".ARG1.".jpeg"


set xlabel "Tamaño"
set ylabel "Tiempo (seg)"
plot ARG3."/data/".ARG1.".dat" title ARG2 with lines
