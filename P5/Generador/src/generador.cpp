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
    std::vector<std::vector<int>> distancias(numCiudades, std::vector<int>(numCiudades));

	 // Generar distancias aleatorias
    for (int i = 0; i < numCiudades; ++i) {
        for (int j = 0; j < numCiudades; ++j) {
            if (i == j) {
                distancias[i][j] = 0;  // Distancia entre una ciudad y ella misma es cero
            } else {
                // Generar distancia aleatoria entre 1 y MAX_DISTANCE
                distancias[i][j] = 1 + std::rand() % MAX_DISTANCE;
            }
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
