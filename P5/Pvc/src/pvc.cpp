#include <cstdlib>
#include <iostream>
#include <limits>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <utility> //pair
#include <chrono>
#include <algorithm>
#include <cmath>

using namespace std;

vector<vector<int>> matrizAdy;

vector<vector<int>> obtenerCiudades(int n)
{
	ifstream entrada("./Generador/data/ciudades.dat");

	string linea, palabra;
	stringstream ss;
	int numero;
	vector<vector<int>> conveniencia;
	int temporal = 0; 
	vector<int> fila;

	while(getline(entrada, linea))
	{
		ss << linea;
		
		while(ss >> palabra)
		{
			if(palabra != " ")
			{
				stringstream(palabra) >> temporal;
				fila.push_back(temporal);
			}

			temporal = 0;
		}

		ss.clear();

		conveniencia.push_back(fila);
		fila.resize(0);
	}

	return conveniencia;
}


pair<float, vector<int>> pvc()
{
	int n = matrizAdy.size();

	// Matriz de programación dinámica
	vector<vector<double>> dp(n, vector<double>(1 << n, numeric_limits<int>::max()));

	// Inicializar los casos base
	dp[0][1] = 0;


	// Calculamos la distancias mínimas y las almacenamos en la matriz de programación dinámica, conjunto será el conjunto de ciudades visitadas en bits: 1 sí, 0 no
	for (int conjunto=1; conjunto<(1 << n); conjunto++) 
	{
		for (int i=0; i<n; i++) 
		{
			if ((conjunto & (1 << i)) != 0)
			{
				for (int j=0; j<n; j++)
				{
					if (i == j || (conjunto & (1 << j)) != 0)
					{
						int grupoPrevio = conjunto ^ (1 << i);
						dp[i][conjunto] = min(dp[i][conjunto], dp[j][grupoPrevio] + matrizAdy[j][i]);
					}
				}
			}
		}
	}



	// Encontramos la última ciudad dentro del grupo con la solución mínima
	int ciudadF = -1;
	double distanciaTotal = 0;
	double distanciaMinima = numeric_limits<int>::max();
	for (int i = 1; i < n; i++) 
	{
		distanciaTotal = dp[i][(1 << n) - 1] + matrizAdy[i][0];
		if (distanciaTotal<distanciaMinima)
		{
			distanciaMinima = distanciaTotal;
			ciudadF = i;
		}
	}

	// Reconstruimos el camino óptimo
	bool salir = true;
	vector<int> ciudadesSolucion;
	int grupo = (1 << n) - 1;
	while (ciudadF != 0)
	{
		ciudadesSolucion.push_back(ciudadF);
		int grupoPrevio = grupo ^ (1 << ciudadF);
		for (int j=0; j<n && salir; j++) 
		{
			if (ciudadF != j && (grupoPrevio & (1 << j)) != 0 && dp[ciudadF][grupo] == dp[j][grupoPrevio] + matrizAdy[j][ciudadF])
			{
				ciudadF = j;
				grupo = grupoPrevio;
				salir = false;
			}
		}

		salir = true;
	}

	ciudadesSolucion.push_back(0);

	return pair<int,vector<int>>(distanciaMinima, ciudadesSolucion);
}

int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		cout << "Tienes que introducir 2 argumentos. El primero será el tamaño del problema y el segundo será la salida de la solución(archivo|ninguna)" << endl;
		return -1;
	}


	int n = atoi(argv[1]);

	vector<vector<float>> dp(1 << n, vector<float>(n,-1));
	int cost = 0;

	matrizAdy = obtenerCiudades(n);

	//Calculamos el tiempo de ejecución del algoritmo con Chrono
	std::chrono::high_resolution_clock::time_point t_antes, t_despues;
	std::chrono::duration<double> transcurrido;

	t_antes = std::chrono::high_resolution_clock::now();
	pair<float, vector<int>> solucion = pvc();
	t_despues = std::chrono::high_resolution_clock::now();
  
	transcurrido = std::chrono::duration_cast<std::chrono::duration<double>>(t_despues - t_antes);

	// Imprimimos el tiempo de ejecución del algoritmo a través de la terminal
	cout << argv[1] << " " << transcurrido.count() << endl;

	// Imprimimos la solución en el archivo solucion.dat si la salida es archivo
	if(atoi(argv[2]) == 1)
	{
		float longitud = 0;

		ofstream salida("./Pvc/data/solucion.dat", ofstream::out | ofstream::trunc);

		// Calculamos el recorrido de la última a la primera
		for(int i=solucion.second.size()-1; i>=0; i--)
			salida << "Ciudad " << solucion.second[i] << endl;

		salida << "La longitud del recorrido es: " << solucion.first << endl;
	}
}
