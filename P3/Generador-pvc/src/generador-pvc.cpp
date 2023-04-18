#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <string>
#include <fstream>

using namespace std;

// Función para generar una matriz de adyacencia
void generar(int n)
{

	int matrizAdy[n][n];

	for(int i=0; i<n; i++)
	{
		matrizAdy[i][i] = 0;

		for(int j=i+1; j<n; j++)
			matrizAdy[i][j] = rand() % 100 + 1;
	}

	for(int i=1; i<n; i++)
		for(int j=0; j<i; j++)
			matrizAdy[i][j] = matrizAdy[j][i];

	// Iniciamos la semilla
	srand(time(NULL));

	ofstream salida("./Generador-pvc/data/ciudades.dat", ofstream::out | ofstream::trunc);

	// Tenemos que crear la matriz de adyacencia
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
			salida << matrizAdy[i][j] << " ";
		
		salida << endl;
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
		generar(atoi(argv[1]));
		return 0;
	}
	catch(invalid_argument& e)
	{
		cerr << e.what() << endl;
		return -1;
	}
}
