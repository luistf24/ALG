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

	ofstream salida("./Generador/data/conveniencia.dat", ofstream::out | ofstream::trunc);

	vector<vector<int>> conveniencia(n, vector<int>(n,0));

	for(int i=0; i<n; i++)
		for(int j=i+1; j<n; j++)
			conveniencia[i][j] = (rand()%1001)+1;

	for(int i=0; i<n; i++)
		for(int j=0; j<i; j++)
			conveniencia[i][j] = conveniencia[j][i];

	// Matriz nx2 col1 = entrenador, col2 = cliente 
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
			salida << conveniencia[i][j] << " ";

		salida << endl;
	}
	
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
