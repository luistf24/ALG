##############################
# MAKEFILE Práctica 2 ALG	 #
##############################


help: # Imprime mensaje con las distintas opciones del Makefile
	@grep -E '^[a-zA-Z0-9 -]+:.*#'  Makefile | sort | while read -r l; do printf "\033[1;32m$$(echo $$l | cut -f 1 -d':')\033[00m:$$(echo $$l | cut -f 2- -d'#')\n"; done

build: # Construir los programas: Generador, Especifico y Dyv
	@echo -e "Construyendo el proyecto ..."
	g++ ./Generador/src/generador.cpp -o ./Generador/bin/generador -O3
	g++ ./bt/src/bt.cpp -o ./bt/bin/bt -O3
	g++ ./bb/src/bb.cpp  -o ./bb/bin/bb -O3

runGen: # Ejecuta el generador de casos n=número de comensales
	./Generador/bin/generador ${n}

runBt: # Ejecuta el programa bt n=numero de comensales, c=cota(1,2 y 3) y s=salida(0 -> ninguna | 1 -> archivo)
	./Generador/bin/generador ${n}
	./bt/bin/bt ${n} ${c} ${s}

runBtScript: # Ejecuta el programa bt con script 
	./mide-tiempos.sh bt ./bt 

runBb: # Ejecuta el programa bb n=numero de comensales, c=cota(1,2 y 3) y s=salida(0 -> ninguna | 1 -> archivo)
	./Generador/bin/generador ${n}
	./bb/bin/bb ${n} ${c} ${s}

runBbScript: # Ejecuta el programa bb con script 
	./mide-tiempos.sh bb ./bb 
	
imagen: # Crea las imágenes con gnuplot  
	gnuplot -c scriptPlot.gp bt_0 BackTracking-Cota-0 bt nan
	gnuplot -c scriptPlot.gp bt_1 BackTracking-Cota-1 bt nan
	gnuplot -c scriptPlot.gp bt_2 BackTracking-Cota-2 bt nan
	gnuplot -c scriptPlotEmp.gp bt_0 BackTracking-Cota-0 bt nan
	gnuplot -c scriptPlotEmp.gp bt_1 BackTracking-Cota-1 bt nan
	gnuplot -c scriptPlotEmp.gp bt_2 BackTracking-Cota-2 bt nan
	gnuplot -c scriptPlot.gp bb_0 BranchAndBound-Cota-0 bb nan
	gnuplot -c scriptPlot.gp bb_1 BranchAndBound-Cota-1 bb nan
	gnuplot -c scriptPlot.gp bb_2 BranchAndBound-Cota-2 bb nan
	gnuplot -c scriptPlotEmp.gp bb_0 BranchAndBound-Cota-0 bb nan
	gnuplot -c scriptPlotEmp.gp bb_1 BranchAndBound-Cota-1 bb nan
	gnuplot -c scriptPlotEmp.gp bb_2 BranchAndBound-Cota-2 bb nan

clean: # Limpia los proyectos
	@echo -e "Limpiando los binarios ..."
	rm ./Generador/bin/*
	rm ./bt/bin/*
	rm ./bb/bin/*
	


