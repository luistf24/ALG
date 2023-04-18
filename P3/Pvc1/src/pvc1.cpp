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

struct Ciudad
{
	int indice;
	int x;
	int y;
};


// Función para obtener una lista de ciudades
vector<Ciudad> obtenerCiudades(int n)
{
	ifstream ciudadesGeneradas("./Generador-pvc/data/ciudades.dat");

	string linea, palabra;
	stringstream ss;
	int numero;
	vector<Ciudad> ciudades;
	Ciudad ciudad;
	int i = 0;

	while(getline(ciudadesGeneradas, linea) && i<n)
	{
		ciudad.indice = i;

		ss << linea;

		// x
		ss >> palabra;	
		stringstream(palabra) >> ciudad.x;

		// " "
		ss >> palabra;	

		// y
		ss >> palabra;	
		stringstream(palabra) >> ciudad.y;

		ciudades.push_back(ciudad);
		i += 1;
		ss.clear();
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

	vector<Ciudad> ciudades = obtenerCiudades(n);

	//Calculamos el tiempo de ejecución del algoritmo con Chrono
	std::chrono::high_resolution_clock::time_point t_antes, t_despues;
	std::chrono::duration<double> transcurrido;

	t_antes = std::chrono::high_resolution_clock::now();
	//vector<pair<int, int>> solucion = voraz(entrenadores, clientes);
	t_despues = std::chrono::high_resolution_clock::now();
  
	transcurrido = std::chrono::duration_cast<std::chrono::duration<double>>(t_despues - t_antes);

	// Imprimimos el tiempo de ejecución del algoritmo a través de la terminal
	cout << argv[1] << " " << transcurrido.count() << endl;

	for(int i = 0; i<ciudades.size(); i++)
	{
		cout << "Ciudad " << ciudades[i].indice << " " << ciudades[i].x << " " << ciudades[i].y << endl;
	}

	// Imprimimos la solución en el archivo solucion.dat si la salida es archivo
	//if(atoi(argv[2]) == 1)
	//{

	//}
}
