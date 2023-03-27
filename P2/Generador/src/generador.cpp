#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <string>
#include <fstream>

using namespace std;

void generar(int tam, int pos)
{
	int area = tam*tam;
	if(area < pos)
		throw invalid_argument("No hay tantas posiciones en el mapa");

	// Creamos el mapa
	vector<bool> mapa(tam*tam, false);

	// Posiciones generadas
	vector<pair<int,int>> generadas;
	// Iniciamos la semilla
	srand(time(NULL));

	int i = 0;
	int num=0;
	pair<int,int> posGenerada;
	while(i<pos)
	{
		num = rand()%area;
		if(mapa[num] == false)
		{
			mapa[num] = true;

			// Parte entera para la x
			posGenerada.first	= (int)(num/tam);
			// Modulo para la y
			posGenerada.second	= num % tam;

			generadas.push_back(posGenerada);

			i++;
		}
	}

	ofstream salida("./Generador/data/posiciones.dat", ofstream::out | ofstream::trunc);
	for(int j=0; j<generadas.size(); j++)
		salida << generadas[j].first << " " << generadas[j].second << endl;	
	
	salida.close();
}

int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		cout << "Tienes que introducir 2 parámetros, el tamaño del mapa y el número de posiciones a generar" << endl;
		return -1;
	}

	try
	{
		generar(atoi(argv[1]), atoi(argv[2]));
		return 0;
	}
	catch(invalid_argument& e)
	{
		cerr << e.what() << endl;
		return -1;
	}
}
