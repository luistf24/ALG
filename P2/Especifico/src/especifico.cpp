#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <utility> //pair
#include <chrono>
#include <algorithm>

using namespace std;

struct punto
{
	int x;
	int y;
};

bool comp(punto a, punto b)
{
	return a.x<b.x || (a.x==b.x && a.y < b.y);
}

// Función para extraer todas las posiciones de los datos generados, además comprueba 
// que existan suficientes posiciones generadas.
vector<punto> obtenerPosiciones(int pos)
{
	ifstream posicionesGeneradas("./Generador/data/posiciones.dat");

	string linea, palabra;
	stringstream ss;
	int numero;
	vector<punto> posiciones;
	punto posicion;

	while(getline(posicionesGeneradas, linea))
	{
		ss << linea;

		// x
		ss >> palabra;	
		stringstream(palabra) >> posicion.x;

		// " "
		ss >> palabra;	

		// y
		ss >> palabra;	
		stringstream(palabra) >> posicion.y;

		posiciones.push_back(posicion);
		ss.clear();
	}

	if(posiciones.size() < pos)
		throw invalid_argument("No hay tantas posiciones generadas");

	return posiciones;
}

// Resolución del problema de posiciones alcanzables de manera específica.
vector<vector<int>> solucionEspecifica(vector<punto> posiciones)
{
	vector<vector<int>> solucion;
	vector<int> posicionesi;
	
	sort(posiciones.begin(), posiciones.end(), comp);

	for(int i=0; i<posiciones.size(); i++)
	{
		posicionesi.push_back(i);

		for(int j=i-1; j>=0; j--)
		{
			if(posiciones[i].y >= posiciones[j].y)
				posicionesi.push_back(j);
				
		}

		solucion.push_back(posicionesi);
		posicionesi.resize(0);
	}

	return solucion;
}

int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		cout << "Tienes que introducir 2 argumentos. El primero será el tamaño del problema y el segundo será la salida de la solución(archivo|ninguna)" << endl;
		return -1;
	}

	vector<punto> posiciones;
	try
	{
		posiciones = obtenerPosiciones(atoi(argv[1]));

		// Nos quedamos con las n primeras generadas
		posiciones.resize(atoi(argv[1]));
	}
	catch(invalid_argument& e)
	{
		cerr << e.what() << endl;
		return -1;
	}

	//Calculamos el tiempo de ejecución del algoritmo con Chrono
	std::chrono::high_resolution_clock::time_point t_antes, t_despues;
	std::chrono::duration<double> transcurrido;

	t_antes = std::chrono::high_resolution_clock::now();
	vector<vector<int>> alcanzables = solucionEspecifica(posiciones);
	t_despues = std::chrono::high_resolution_clock::now();
  
	transcurrido = std::chrono::duration_cast<std::chrono::duration<double>>(t_despues - t_antes);

	// Imprimimos el tiempo de ejecución del algoritmo a través de la terminal
	cout << argv[1] << " " << transcurrido.count() << endl;

	sort(posiciones.begin(), posiciones.end(), comp);

	// Imprimimos la solución en el archivo solucion.dat si la salida es archivo
	if(atoi(argv[2]) == 1)
	{
		ofstream salida("./Especifico/data/solucion.dat", ofstream::out | ofstream::trunc);
		for(int i=0; i<alcanzables.size(); i++)
		{
			salida << "Las posiciones alcanzables desde la posición " << i << " (" << posiciones[i].x << "," << posiciones[i].y << ") son:" << endl; 	

			if(alcanzables[i].size()>1)
			{
				for(int j=1; j<alcanzables[i].size(); j++)
				{
					salida << "  - Posición: " << alcanzables[i][j] <<  " (" << posiciones[alcanzables[i][j]].x << "," << posiciones[alcanzables[i][j]].y << ")" << endl;
				}
			}
			else
				salida << "  - Ninguna" << endl;
		}
	}
}
