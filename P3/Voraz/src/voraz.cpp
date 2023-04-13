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

struct Persona
{
	int indice;
	float peso;
};

bool compa(Persona a, Persona b)
{
	return a.peso < b.peso;
}

bool compd(Persona a, Persona b)
{
	return a.peso > b.peso;
}

// Función para obtener 2 listas de personas, una de entrenadores y otra de clientes
void obtenerPersonas(int n, vector<Persona>& entrenadores, vector<Persona>& clientes)
{
	ifstream posicionesGeneradas("./Generador/data/personas.dat");

	string linea, palabra;
	stringstream ss;
	int numero;
	Persona p;
	int i = 0;

	while(getline(posicionesGeneradas, linea) && i<n)
	{
		ss << linea;

		// Entrenador
		ss >> palabra;	
		p.indice=i;
		stringstream(palabra) >> p.peso;

		entrenadores.push_back(p);

		// " "
		ss >> palabra;	

		// Cliente
		ss >> palabra;	
		stringstream(palabra) >> p.peso;

		clientes.push_back(p);

		i += 1;
		ss.clear();
	}

}

// Resolución del problema mediante un algoritmo Greedy.
vector<pair<int,int>> voraz(vector<Persona> entrenadores, vector<Persona> clientes)
{
	sort(entrenadores.begin(), entrenadores.end(), compd);
	sort(clientes.begin(), clientes.end(), compa);

	pair<int,int> temp;
	vector<pair<int, int>> solucion;

	for(int i=0;i<entrenadores.size();i++)
	{
		temp.first = entrenadores[i].indice;
		temp.second = clientes[i].indice;
	
		solucion.push_back(temp);
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


	int n = atoi(argv[1]);
	vector<Persona> entrenadores;
	vector<Persona> clientes;

	obtenerPersonas(n, entrenadores, clientes);

	//Calculamos el tiempo de ejecución del algoritmo con Chrono
	std::chrono::high_resolution_clock::time_point t_antes, t_despues;
	std::chrono::duration<double> transcurrido;

	t_antes = std::chrono::high_resolution_clock::now();
	vector<pair<int, int>> solucion = voraz(entrenadores, clientes);
	t_despues = std::chrono::high_resolution_clock::now();
  
	transcurrido = std::chrono::duration_cast<std::chrono::duration<double>>(t_despues - t_antes);

	// Imprimimos el tiempo de ejecución del algoritmo a través de la terminal
	cout << argv[1] << " " << transcurrido.count() << endl;

	// Imprimimos la solución en el archivo solucion.dat si la salida es archivo
	float suma = 0;
	if(atoi(argv[2]) == 1)
	{
		ofstream salida("./Voraz/data/solucion.dat", ofstream::out | ofstream::trunc);
		salida << "Las parejas entrenador cliente son:" << endl;
		for(int i=0; i<solucion.size(); i++)
		{
			salida << "     Entrenador: " << solucion[i].first << " y Cliente: " << solucion[i].second << endl;
			suma += entrenadores[solucion[i].first].peso * (1 - clientes[solucion[i].second].peso); 
		}
		salida << "La suma total es: " << suma << endl;
	}
}
