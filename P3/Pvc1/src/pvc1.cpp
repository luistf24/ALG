#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <utility> //pair
#include <chrono>
#include <algorithm>

using namespace std;


// Función para obtener una matriz adyacente de un archivo
vector<vector<int>> obtenerCiudades(int n)
{
	vector<vector<int>> ciudades(n, vector<int>(n, 0));

	ifstream ciudadesGeneradas("./Generador-pvc/data/ciudades.dat");
	
	for (int i = 0; i < n; ++i) 
	{
    	for (int j = 0; j < n; ++j)
        	ciudadesGeneradas >> ciudades[i][j];

		ciudadesGeneradas.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	return ciudades;
}

// Resolución del problema mediante un algoritmo Greedy.

int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		cout << "Tienes que introducir 2 argumentos. El primero será el tamaño del problema y el segundo será la salida de la solución(archivo|ninguna)" << endl;
		return -1;
	}


	int n = atoi(argv[1]);

	vector<vector<int>> matrizAdy = obtenerCiudades(n);

	//Calculamos el tiempo de ejecución del algoritmo con Chrono
	std::chrono::high_resolution_clock::time_point t_antes, t_despues;
	std::chrono::duration<double> transcurrido;

	t_antes = std::chrono::high_resolution_clock::now();
	//vector<pair<int, int>> solucion = voraz(entrenadores, clientes);
	t_despues = std::chrono::high_resolution_clock::now();
  
	transcurrido = std::chrono::duration_cast<std::chrono::duration<double>>(t_despues - t_antes);

	// Imprimimos el tiempo de ejecución del algoritmo a través de la terminal
	cout << argv[1] << " " << transcurrido.count() << endl;

	// Imprimimos la solución en el archivo solucion.dat si la salida es archivo
	//if(atoi(argv[2]) == 1)
	//{

	//}
}
