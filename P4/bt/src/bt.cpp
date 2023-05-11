#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

vector<vector<int>> getConvenencia(int n)
{
	ifstream entrada("./Generador/data/conveniencia.dat");

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


// Calculamos el nivel de conveniencia de una posible solucion: sumamos la conveniencia de todos los comensales respecto a los invitador a su derecha e izquierda
// Numero de elementos colocados en la solucion
int calcularNivelConveniencia(const vector<vector<int>>& conveniencia, const vector<vector<int>>& conveniencia_ordenada, const vector<int>& solucion_parcial, int elementos, int cota) {
    int nivelConveniencia = 0;
    int n = conveniencia.size(); // numero de comensales
	vector<bool> noestan(conveniencia.size(),true);

	int quedan = conveniencia.size();

    for (int i = 0; i < elementos; i++)
	{
        int izquierda = (i - 1 + n) % n;
        int derecha = (i + 1) % n;

        if( izquierda < elementos)
            nivelConveniencia += conveniencia[solucion_parcial[i]][solucion_parcial[izquierda]];
        if( derecha < elementos)
            nivelConveniencia += conveniencia[solucion_parcial[i]][solucion_parcial[derecha]];

		noestan[solucion_parcial[i]] = false;
		quedan -= 1;
    }


    // AQUI HABRIA QUE ANIADIR EL CALCULO ESPECIFICO PARA LA COTA USANDO LAS DIAPOS

	int min = 1001;

	if(cota == 1)
	{
		for(int i=0; i<noestan.size() && quedan != 0; i++)
		{
			if(noestan[i])
				if(min > conveniencia[i][solucion_parcial[elementos-1]])		
					min	= conveniencia[i][solucion_parcial[elementos-1]];
			
		}

		nivelConveniencia += min*quedan;

	} else if (cota == 2)
	{
		for(int i=0; i<noestan.size() && quedan != 0; i++)
		{
			if(noestan[i])
			{
				min = conveniencia_ordenada[i][1];

				nivelConveniencia += min;
			}
		}
	}

    return nivelConveniencia;
}

// Cota superior
int cotaGlobal( const vector<vector<int>>& conveniencia, const vector<vector<int>>& conveniencia_ordenada, int cota){
    int num_comensales = conveniencia.size();
    vector<int> pos_solucion(num_comensales);
    for( int i = 0; i < num_comensales; i++)
        pos_solucion[i] = i;

    int ret = calcularNivelConveniencia(conveniencia, conveniencia_ordenada, pos_solucion, num_comensales, cota);
    return ret;
}


void backtracking(vector<int>& solucion_final, const vector<vector<int>>& conveniencia, const vector<vector<int>>& conveniencia_ordenada, const vector<int> solucion_parcial, int & cota_sup, int elementos, int cota) {
    int num_comensales = conveniencia.size();

    if( elementos == num_comensales){
        int conveniencia_actual = calcularNivelConveniencia(conveniencia, conveniencia_ordenada, solucion_parcial, num_comensales, cota);
        if( conveniencia_actual < cota_sup){
            cota_sup = conveniencia_actual;
            for( int i=0; i < num_comensales; i++){
                solucion_final[i] = solucion_parcial[i];
            }
        }
    } else if ( elementos < num_comensales ){
        for( int i = 1; i < num_comensales; i++){ // i es el comensal a aniadir

            // Comprobamos que el comensal no este colocado
            bool valido = true;
            for( int j = 0; j < elementos; j++){
                if( solucion_parcial[j] == i){
                    valido = false;
                }
            }

            if( valido ){
                vector<int> nueva_solucion_parcial(num_comensales, -1);
                // Aniadimos el comensal a la solucion parcial
                for( int j = 0; j < elementos; j++){
                    nueva_solucion_parcial[j] = solucion_parcial[j];
                }
                nueva_solucion_parcial[elementos] = i;
                int sig_elementos = elementos+1;
                
                // Llamada recursiva para seguir creando el arbol
                int conveniencia_actual = calcularNivelConveniencia(conveniencia, conveniencia_ordenada, nueva_solucion_parcial, sig_elementos, cota);
                if( conveniencia_actual < cota_sup){
                    backtracking(solucion_final, conveniencia, conveniencia_ordenada, nueva_solucion_parcial, cota_sup, sig_elementos, cota);
                }
            }
        }
    }



}


// Usaremos el mismo algoritmo que se usa para el Problema del Viajante de Comercio
// Para ello realizaremos el cambio 'conveniencia = 1000 - conveniencia' y conseguimos una suma a minimizar
int main(int argc, char *argv[])
{
	int n = atoi(argv[1]);
	int cota = atoi(argv[2]);

    vector<vector<int>> conveniencia = getConvenencia(n);

	vector<vector<int>> conveniencia_inversa = getConvenencia(n);

	vector<vector<int>> conveniencia_ordenada;

	for (int i = 0; i < n; i++) 
		for (int j = 0; j < n; j++) 
			conveniencia_inversa[i][j] = 1000 - conveniencia[i][j];

	vector<int> ordenar;
	for(int i=0; i<conveniencia.size(); i++)
	{
		ordenar = conveniencia[i];
		sort(conveniencia.begin(), conveniencia.end());

		conveniencia_ordenada.push_back(ordenar);
	}

	int cota_sup = cotaGlobal(conveniencia_inversa, conveniencia_ordenada, cota);
	vector<int> solucion_parcial(n, -1);
	solucion_parcial[0] = 0; // No importa donde comience el ciclo -> elegimos el 0


	int elementos = 1;
	vector<int> mejorSolucion(n, -1);


	//Calculamos el tiempo de ejecución del algoritmo con Chrono
	std::chrono::high_resolution_clock::time_point t_antes, t_despues;
	std::chrono::duration<double> transcurrido;

	t_antes = std::chrono::high_resolution_clock::now();
	backtracking(mejorSolucion, conveniencia_inversa, conveniencia_ordenada, solucion_parcial, cota_sup, elementos, cota); // Ya hemos colocado el primero -> nivel 1 completo
	t_despues = std::chrono::high_resolution_clock::now();
  
	transcurrido = std::chrono::duration_cast<std::chrono::duration<double>>(t_despues - t_antes);

	// Imprimimos el tiempo de ejecución del algoritmo a través de la terminal
	cout << argv[1] << " " << transcurrido.count() << endl;

	if(atoi(argv[3]) == 1)
	{
		ofstream salida("./bt/data/solucion.dat", ofstream::out | ofstream::trunc);
		salida << argv[1] << " " << transcurrido.count() << endl;
		salida << "Se ha encontrado la siguiente solucion: " << endl;
		for( int i = 0; i < n; i++)
		{
			salida << mejorSolucion[i] << endl;
		}

		int conveniencia_final = calcularNivelConveniencia(conveniencia, conveniencia_ordenada, mejorSolucion, n, cota);
		salida << "La conveniencia alcanzada es: " << conveniencia_final << endl;
	}

	return 0;
}
