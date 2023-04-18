#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <string>
#include <fstream>

using namespace std;

void generar(int n)
{
	int area = 1000*1000;

	// Creamos el mapa
	vector<bool> mapa(area, false);

	// Posiciones generadas
	vector<pair<int,int>> generadas;
	// Iniciamos la semilla
	srand(time(NULL));

	int i = 0;
	int num=0;
	pair<int,int> posGenerada;
	while(i<n)
	{
		num = rand()%area;
		if(mapa[num] == false)
		{
			mapa[num] = true;

			// Parte entera para la x
			posGenerada.first	= (int)(num/1000);
			// Modulo para la y
			posGenerada.second	= num % 1000;

			generadas.push_back(posGenerada);

			i++;
		}
	}

	ofstream salida("./Generador-pvc/data/ciudades.dat", ofstream::out | ofstream::trunc);
	for(int j=0; j<generadas.size(); j++)
		salida << generadas[j].first << " " << generadas[j].second << endl;	
	
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
