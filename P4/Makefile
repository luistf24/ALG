##############################
# MAKEFILE Práctica 2 ALG	 #
##############################


help: # Imprime mensaje con las distintas opciones del Makefile
	@grep -E '^[a-zA-Z0-9 -]+:.*#'  Makefile | sort | while read -r l; do printf "\033[1;32m$$(echo $$l | cut -f 1 -d':')\033[00m:$$(echo $$l | cut -f 2- -d'#')\n"; done

build: # Construir los programas: Generador, Especifico y Dyv
	@echo -e "Construyendo el proyecto ..."
	g++ ./Generador/src/generador.cpp -o ./Generador/bin/generador -O3
	g++ ./bt/src/bt.cpp -o ./bt/bin/bt -O3

runGen: # Ejecuta el generador de casos n=número de comensales
	./Generador/bin/generador ${n}

runBt: # Ejecuta el programa bt n=numero de comensales y s=salida(0 -> ninguna | 1 -> archivo)
	./bt/bin/bt ${n} ${s}

runBtScript: # Ejecuta el programa bt con script s=salida(0 -> ninguna | 1 -> archivo)
	./mide-tiempos.sh bt ./bt ${s}
	
imagen: # Crea las imágenes con gnuplot  
	

clean: # Limpia los proyectos(Generador, Especifico y Dyv)
	@echo -e "Limpiando los binarios ..."
	rm ./Generador/bin/*
	rm ./bt/bin/*
	


