##############################
# MAKEFILE Práctica 2 ALG	 #
##############################


help: # Imprime mensaje con las distintas opciones del Makefile
	@grep -E '^[a-zA-Z0-9 -]+:.*#'  Makefile | sort | while read -r l; do printf "\033[1;32m$$(echo $$l | cut -f 1 -d':')\033[00m:$$(echo $$l | cut -f 2- -d'#')\n"; done

build: # Construir los programas: Generador, Especifico y Dyv
	@echo -e "Construyendo el proyecto ..."
	g++ ./Generador/src/generador.cpp -o ./Generador/bin/generador -O3

runGen: # Ejecuta el generador de casos m=tamaño del mapa n=numero de posiciones
	./Generador/bin/generador ${m} ${n}

runDyv: # Ejecuta el programa con el algoritmo Divide y Vencerás

runEsp: # Ejecuta el programa con el algoritmo Especifico 

imagen: # Crea las imágenes con gnuplot n=nombre de la foto  t=Titulo de gráfica 

clean: # Limpia los proyectos(Generador, Especifico y Dyv)
	@echo -e "Limpiando los binarios ..."
	rm ./Generador/bin/*

