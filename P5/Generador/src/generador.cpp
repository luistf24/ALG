#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <string>
#include <fstream>

using namespace std;

void generarMDist(int numCiudades)
{
	const int MAX_DISTANCE = 100;  // Máxima distancia permitida entre ciudades

	// Inicializar generador de números aleatorios
    std::srand(std::time(0));

    // Crear matriz de distancias
    vector<vector<int>> distancias(numCiudades, vector<int>(numCiudades, 0));
    
    // Generar valores aleatorios para las distancias entre ciudades
    for (int i = 0; i < numCiudades; ++i) {
        for (int j = i + 1; j < numCiudades; ++j) {
            int distancia = rand() % MAX_DISTANCE + 1;  // Distancia aleatoria entre 1 y 100
            distancias[i][j] = distancia;
            distancias[j][i] = distancia;  // La matriz es simétrica
        }
    }

	ofstream salida("./Generador/data/ciudades.dat", ofstream::out | ofstream::trunc);

	for (int i = 0; i < numCiudades; ++i) {
        for (int j = 0; j < numCiudades; ++j) {
            salida << distancias[i][j] << " ";
        }
        salida << std::endl;
    }
	
	salida.close();
}


int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		cout << "Tienes que introducir el número de ciudades" << endl;
		return -1;
	}

	try
	{
		generarMDist(atoi(argv[1]));
		return 0;
	}
	catch(invalid_argument& e)
	{
		cerr << e.what() << endl;
		return -1;
	}
}
