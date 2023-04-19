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
#include <climits>

using namespace std;

struct Ciudad
{
	int indice;
	int x;
	int y;
};

float distEuclidea(Ciudad a, Ciudad b)
{
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

// Intercambia la ciudad a por la última de la lista y la borra y la borra
void intercambiarBorrar(int a, vector<Ciudad>& ciudades)
{
	int n = ciudades.size();

	ciudades[a] = ciudades[n-1];
	ciudades.resize(n-1);
}

// Función para obtener una lista de ciudades
vector<Ciudad> obtenerCiudades(int n)
{
	ifstream ciudadesGeneradas("./Generador-pvc/data/ciudades.dat");

	string linea, palabra;
	stringstream ss;
	int numero;
	vector<Ciudad> ciudades;
	Ciudad ciudad;
	int i = 0;

	while(getline(ciudadesGeneradas, linea) && i<n)
	{
		ciudad.indice = i;

		ss << linea;

		// x
		ss >> palabra;	
		stringstream(palabra) >> ciudad.x;

		// " "
		ss >> palabra;	

		// y
		ss >> palabra;	
		stringstream(palabra) >> ciudad.y;

		ciudades.push_back(ciudad);
		i += 1;
		ss.clear();
	}

	return ciudades;
}

vector<vector<float>> generarMatriz(vector<Ciudad> ciudades)
{
	int n = ciudades.size();

	vector<vector<float>>matrizAdy(ciudades.size(), vector<float>(ciudades.size(), 0.0));
	for(int i=0;i<n;i++)
		for(int j=i; j<n; j++)
			if(i!=j)
				matrizAdy[i][j] = distEuclidea(ciudades[i], ciudades[j]);

	for(int i=0; i<n; i++)
		for(int j=0; j<i; j++)
			matrizAdy[i][j] = matrizAdy[j][i];

	return matrizAdy;
}

// Resolución del problema mediante un algoritmo Greedy. Devuelve un vector con las ciudades en el orden que se visitan
// Inserción más económica
vector<Ciudad> solucionDyv2(vector<Ciudad> ciudades, vector<vector<float>> matrizAdy)
{
	vector<Ciudad> sol;
	vector<Ciudad> nVisitadas = ciudades;
	vector<Ciudad>::iterator it, cop;

	Ciudad siguiente;

	sol.push_back(nVisitadas[0]);
	intercambiarBorrar(0, nVisitadas);

	sol.push_back(nVisitadas[0]);
	intercambiarBorrar(0, nVisitadas);

	float tamin;

	while(nVisitadas.size()>0)
	{
		siguiente = nVisitadas[0];
		tamin = numeric_limits<float>::max();

		for(it=sol.begin()+1; it!=sol.end(); it++)
		{
			if(matrizAdy[(it-1)->indice][siguiente.indice]+matrizAdy[siguiente.indice][(it)->indice]<tamin)		
			{
				tamin = matrizAdy[(it-1)->indice][siguiente.indice]+matrizAdy[siguiente.indice][(it)->indice];
				cop = it;
			}
		}
		
		if(tamin > matrizAdy[sol[sol.size()-1].indice][siguiente.indice]+matrizAdy[siguiente.indice][0])	
			sol.push_back(siguiente);
		else
			sol.insert(cop, siguiente);

		intercambiarBorrar(0, nVisitadas);
	}

	return sol;
}

int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		cout << "Tienes que introducir 2 argumentos. El primero será el tamaño del problema y el segundo será la salida de la solución(archivo|ninguna)" << endl;
		return -1;
	}


	int n = atoi(argv[1]);

	vector<Ciudad> ciudades = obtenerCiudades(n);
	vector<vector<float>> matrizAdy = generarMatriz(ciudades);

	//Calculamos el tiempo de ejecución del algoritmo con Chrono
	std::chrono::high_resolution_clock::time_point t_antes, t_despues;
	std::chrono::duration<double> transcurrido;

	t_antes = std::chrono::high_resolution_clock::now();
	vector<Ciudad> sol = solucionDyv2(ciudades, matrizAdy);
	t_despues = std::chrono::high_resolution_clock::now();
  
	transcurrido = std::chrono::duration_cast<std::chrono::duration<double>>(t_despues - t_antes);

	// Imprimimos el tiempo de ejecución del algoritmo a través de la terminal
	cout << argv[1] << " " << transcurrido.count() << endl;

	// Imprimimos la solución en el archivo solucion.dat si la salida es archivo
	if(atoi(argv[2]) == 1)
	{
		float longitud = 0;

		ofstream salida("./Pvc2/data/solucion.dat", ofstream::out | ofstream::trunc);
		for(int i=0; i<sol.size(); i++)
		{
			salida << "Ciudad " << sol[i].indice << endl;
			longitud += distEuclidea(sol[i-1], sol[i]);
		}

		salida << "Ciudad " << sol[0].indice << endl; // Volvemos al origen
		longitud += distEuclidea(sol[sol.size()-1], sol[0]);

		salida << "La longitud del recorrido es: " << longitud << endl;
	}
}
