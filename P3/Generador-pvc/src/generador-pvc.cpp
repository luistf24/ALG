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
	vector<int> mapa;

	for(int i=0;i<area;i++)
		mapa.push_back(i);

	// Posiciones generadas
	vector<pair<int,int>> generadas;
	// Iniciamos la semilla
	srand(time(NULL));

	int num=0;
	pair<int,int> posGenerada;

	for(int i=0; i<n; i++)
	{
		num = rand()%mapa.size();

		// Parte entera para la x
		posGenerada.first	= (int)(mapa[num]/1000);
		// Modulo para la y
		posGenerada.second	= mapa[num] % 1000;

		generadas.push_back(posGenerada);

		mapa[num] = mapa[mapa.size()-1];
		mapa.resize(mapa.size()-1);
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
