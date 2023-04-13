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

	// Iniciamos la semilla
	srand(time(NULL));

	ofstream salida("./Generador/data/posiciones.dat", ofstream::out | ofstream::trunc);

	// Matriz nx2 col1 = entrenador, col2 = cliente 
	for(int i=0; i<n; i++)
		salida << (float) rand()/RAND_MAX << " " << (float) rand()/RAND_MAX << endl;	
	
	salida.close();
}

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		cout << "Tienes que introducir el número de personas" << endl;
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
