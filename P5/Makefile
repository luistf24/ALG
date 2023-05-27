##############################
# MAKEFILE Práctica 5 ALG	 #
##############################


help: # Imprime mensaje con las distintas opciones del Makefile
	@grep -E '^[a-zA-Z0-9 -]+:.*#'  Makefile | sort | while read -r l; do printf "\033[1;32m$$(echo $$l | cut -f 1 -d':')\033[00m:$$(echo $$l | cut -f 2- -d'#')\n"; done

build: # Construir los programas: Generador y Pvc
	@echo -e "Construyendo el proyecto ..."
	g++ ./Generador/src/generador.cpp -o ./Generador/bin/generador -O3
	g++ ./Pvc/src/pvc.cpp  -o ./Pvc/bin/pvc -O3

runGen: # Ejecuta el generador de casos n=número de ciudades
	./Generador/bin/generador ${n}

runPvc: # Ejecuta el programa pvc n=numero de ciudades y s=salida(0 -> ninguna | 1 -> archivo)
	./Generador/bin/generador ${n}
	./Pvc/bin/pvc ${n} ${s}

runPvcScript: # Ejecuta el programa pvc con script 
	./mide-tiempos.sh pvc Pvc

imagen: # Crea las imágenes con gnuplot  

clean: # Limpia los proyectos
	@echo -e "Limpiando los binarios ..."
	rm ./Generador/bin/*
	rm ./Pvc/bin/*
	


