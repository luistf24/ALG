#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <utility> //pair
#include <chrono>
#include <algorithm>
#include <map>

using namespace std;

struct punto
{
	int index;
	int x;
	int y;
};

bool comp(punto a, punto b)
{
	return a.x<b.x || (a.x==b.x && a.y < b.y);
}

bool compy(punto a, punto b)
{
	return a.y<b.y || (a.y==b.y && a.x < b.x);
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

	int i = 0;

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

		posicion.index = i;
		i++;

		ss.clear();
	}

	if(posiciones.size() < pos)
		throw invalid_argument("No hay tantas posiciones generadas");

	return posiciones;
}


void solucionDyv(vector<vector<int>>& sol, vector<punto> puntos, vector<punto> dominantes, int inicio, int fin)
{
	if((fin-inicio)<101)
	{
		sort(dominantes.begin(),dominantes.end(), compy);
		for(int i=inicio;i<fin;i++)
		{
			for(int j=dominantes.size()-1; j>=0 && puntos[i].y<dominantes[j].y; j--)
			{
					if(puntos[i].x<dominantes[j].x)
						sol[dominantes[j].index].push_back(puntos[i].index);
			}
		}
		return;
	}

	int med=(inicio+fin)/2;
	solucionDyv(sol, puntos, dominantes, inicio, med);
	solucionDyv(sol, puntos, dominantes, med, fin);
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

	sort(posiciones.begin(), posiciones.end(), comp);

	// Modificamos los índices con el nuevo orden
	for(int i=0; i<posiciones.size(); i++)
		posiciones[i].index = i;

	vector<vector<int>> solucion;
	for(int i=0;i<posiciones.size();i++)
		solucion.push_back({posiciones[i].index});

	//Calculamos el tiempo de ejecución del algoritmo con Chrono
	std::chrono::high_resolution_clock::time_point t_antes, t_despues;
	std::chrono::duration<double> transcurrido;

	t_antes = std::chrono::high_resolution_clock::now();
	solucionDyv(solucion, posiciones, posiciones, 0, posiciones.size()-1);
	t_despues = std::chrono::high_resolution_clock::now();
  
	transcurrido = std::chrono::duration_cast<std::chrono::duration<double>>(t_despues - t_antes);

	// Imprimimos el tiempo de ejecución del algoritmo a través de la terminal
	cout << argv[1] << " " << transcurrido.count() << endl;


	// Imprimimos la solución en el archivo solucion.dat si la salida es archivo
	if(atoi(argv[2]) == 1)
	{
		ofstream salida("./Dyv/data/solucion.dat", ofstream::out | ofstream::trunc);
		for(int i=0; i<solucion.size(); i++)
		{
			salida << "Las posiciones alcanzables desde la posición " << i << " (" << posiciones[i].x << "," << posiciones[i].y << ") son:" << endl; 	

			if(solucion[i].size()>1)
			{
				for(int j=1; j<solucion[i].size(); j++)
				{
					salida << "  - Posición: " << solucion[i][j] <<  " (" << posiciones[solucion[i][j]].x << "," << posiciones[solucion[i][j]].y << ")" << endl;
				}
			}
			else
				salida << "  - Ninguna" << endl;
		}
	}
}
