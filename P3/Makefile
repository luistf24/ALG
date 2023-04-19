##############################
# MAKEFILE Práctica 2 ALG	 #
##############################


help: # Imprime mensaje con las distintas opciones del Makefile
	@grep -E '^[a-zA-Z0-9 -]+:.*#'  Makefile | sort | while read -r l; do printf "\033[1;32m$$(echo $$l | cut -f 1 -d':')\033[00m:$$(echo $$l | cut -f 2- -d'#')\n"; done

build: # Construir los programas: Generador, Especifico y Dyv
	@echo -e "Construyendo el proyecto ..."
	g++ ./Generador/src/generador.cpp -o ./Generador/bin/generador -O3
	g++ ./Voraz/src/voraz.cpp -o ./Voraz/bin/voraz -O3
	g++ ./Generador-pvc/src/generador-pvc.cpp -o ./Generador-pvc/bin/generador-pvc -O3
	g++ ./Pvc1/src/pvc1.cpp -o ./Pvc1/bin/pvc1 -O3
	g++ ./Pvc2/src/pvc2.cpp -o ./Pvc2/bin/pvc2 -O3

runGen: # Ejecuta el generador de casos n=número de entrenadores y deportistas
	./Generador/bin/generador ${n}

runGenPvc: # Ejecuta el generador de casos para el problema del viajante de comercio n=número de ciudades
	./Generador-pvc/bin/generador-pvc ${n}

runVor: # Ejecuta el programa n=número de personas y s=salida(0 -> ninguna | 1 -> archivo)
	./Voraz/bin/voraz ${n} ${s}

runPvc1: # Ejecuta el programa pvc1 n=numero de ciudades y s=salida(0 -> ninguna | 1 -> archivo)
	./Pvc1/bin/pvc1 ${n} ${s}

runPvc2: # Ejecuta el programa pvc2 n=numero de ciudades y s=salida(0 -> ninguna | 1 -> archivo)
	./Pvc2/bin/pvc2 ${n} ${s}

imagen: # Crea las imágenes con gnuplot  
	gnuplot -c scriptPlot.gp voraz Algoritmo-Voraz Voraz nlog
	gnuplot -c scriptPlotEmp.gp voraz Algoritmo-Voraz Voraz nlog

clean: # Limpia los proyectos(Generador, Especifico y Dyv)
	@echo -e "Limpiando los binarios ..."
	rm ./Generador/bin/*
	rm ./Generador-pvc/bin/*
	rm ./Voraz/bin/*
	rm ./Pvc1/bin/*

