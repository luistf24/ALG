#!/usr/local/bin/gnuplot --persist

print "Salida	: ", ARG1.".jpeg"
print "Datos	: ", ARG1 .".dat"
print "Título	: ", ARG2 
print "Carpeta	: ", ARG3
print "Orden	: ", ARG4

set terminal jpeg
set output ARG3."/img/".ARG1."Empirica.jpeg"

set xlabel "Tamaño"
set ylabel "Tiempo (seg)"

if (ARG4 eq "lineal") {
	f(x) = a1*x+a0
	g(x) = b1*x+b0
	fit g(x) ARG3."/data/".ARG1.".dat" via b1, b0
	fit f(x) ARG3."/data/".ARG1.".dat" via a1, a0
}else {
	f(x) = a2*x*x+a1*x+a0;
	g(x) = b1*x+b0
	fit g(x) ARG3."/data/".ARG1.".dat" via b1, b0
	fit f(x) ARG3."/data/".ARG1.".dat" via a2, a1, a0
}


plot ARG3."/data/".ARG1.".dat" title ARG2 , f(x) title "Curva ajustada de ".ARG2 , g(x) title "Curva lineal de ".ARG2
