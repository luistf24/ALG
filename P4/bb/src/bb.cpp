#include <iostream>
#include <vector>
#include <queue>
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

class Solucion {
private:
  std::vector<int> camino_parcial;
  int conveniencia;
  
public:
  // Constructor por defecto
  Solucion() : conveniencia(0) {}
  
  // Constructor con parámetros
  Solucion(const std::vector<int>& camino, int conveniencia) : camino_parcial(camino), conveniencia(conveniencia) {}

  // Constructor para camino
  Solucion(const std::vector<int>& camino, const vector<vector<int>>& Mconveniencia, const vector<vector<int>>& Mconveniencia_ordenada, int cota){
      camino_parcial = camino;
      calcularNivelConveniencia(Mconveniencia, Mconveniencia_ordenada, cota);
  }
  
  // Métodos para acceder y modificar el camino parcial y la conveniencia
  const std::vector<int>& get_camino() const { return camino_parcial; }
  int get_conveniencia() const { return conveniencia; }
  void set_camino(const std::vector<int>& nuevo_camino) { camino_parcial = nuevo_camino; }
  void set_conveniencia(int nueva_conveniencia) { conveniencia = nueva_conveniencia; }

  // Sobrecarga del operador < para que Solucion sea comparable en la cola de prioridad
    bool operator<(const Solucion& otra) const {
        return conveniencia > otra.conveniencia; // Menor conveniencia tiene mayor prioridad
    }

    // Sobrecarga del operador = 
    Solucion& operator=(const Solucion& otra) {
        if (this != &otra) {
            this->camino_parcial = otra.camino_parcial;
            this->conveniencia = otra.conveniencia;
        }
        return *this;
    }

  // Método de calculo de conveniencia, incluyendo heuristica (todavia sin implementar)
  int calcularNivelConveniencia(const vector<vector<int>>& Mconveniencia, const vector<vector<int>>& Mconveniencia_ordenada, int cota) {
    int nivelConveniencia = 0;
    int num_total = Mconveniencia.size(); // numero total posiciones
    int elementos = camino_parcial.size(); // posiciones colocadas
	vector<bool> noestan(Mconveniencia.size(),true);

    int quedan = Mconveniencia.size();

    for (int i = 0; i < elementos; i++) {
        int izquierda = (i - 1 + num_total) % num_total;
        int derecha = (i + 1) % num_total;

        if( izquierda < elementos)
            nivelConveniencia += Mconveniencia[camino_parcial[i]][camino_parcial[izquierda]];
        if( derecha < elementos)
            nivelConveniencia += Mconveniencia[camino_parcial[i]][camino_parcial[derecha]];

        noestan[camino_parcial[i]] = false;
		quedan -= 1;
    }
    // AQUI HABRIA QUE ANIADIR EL CALCULO ESPECIFICO PARA LA COTA USANDO LAS DIAPOS

    int min = 1001;

	if(cota == 1)
	{
		for(int i=0; i<noestan.size() && quedan != 0; i++)
		{
			if(noestan[i])
				if(min > Mconveniencia[i][camino_parcial[elementos-1]])		
					min	= Mconveniencia[i][camino_parcial[elementos-1]];
			
		}

		nivelConveniencia += min*quedan;

	} else if (cota == 2)
	{
		for(int i=0; i<noestan.size() && quedan != 0; i++)
		{
			if(noestan[i])
			{
				min = Mconveniencia_ordenada[i][1];

				nivelConveniencia += min;
			}
		}
	}
    
    set_conveniencia(nivelConveniencia);
    return nivelConveniencia;
  }

  // Mostrar contenido por pantalla
    void mostrarContenido(){
        cout << "El camino almacenado es: " << endl;
        int n = camino_parcial.size();
        for( int i = 0; i < n; i++){
            cout << camino_parcial[i] << endl;
    }

    cout << "La conveniencia alcanzada es: " << conveniencia << endl;

  }


};

void branchandbound(Solucion& mejorSolucion, const vector<vector<int>>& Mconveniencia, priority_queue<Solucion> & cola_de_prioridad, const vector<vector<int>>& Mconveniencia_ordenada, int cota) {

    int num_total = Mconveniencia.size();

    if( cola_de_prioridad.empty()){
        return;
    }
    
    Solucion nodoPadre = cola_de_prioridad.top();
    cola_de_prioridad.pop();

    if( nodoPadre.get_conveniencia() >= mejorSolucion.get_conveniencia()){
        return;
    }

    vector<int> camino_actual = nodoPadre.get_camino();
    int elementos = camino_actual.size();

    // Posible solucion
    if( elementos == num_total ){
        if( nodoPadre.get_conveniencia() < mejorSolucion.get_conveniencia()){
            mejorSolucion = nodoPadre;
        }
        return;
    }

    for( int i = 1; i < num_total; i++){
        //cout << "Calculamos los hijos." << endl;

        // Comprobamos que el comensal no este colocado
        bool valido = true;
        for( int j = 0; j < elementos; j++){
            if( camino_actual[j] == i){
                valido = false;
            }
        }

        if(valido){
            //cout << "Añado elemento numero: " << i << endl;

            vector<int> camino_nuevo = camino_actual;

            camino_nuevo.push_back(i);
            Solucion solucion_nueva(camino_nuevo, Mconveniencia, Mconveniencia_ordenada, cota);

            cola_de_prioridad.push(solucion_nueva);
        }
        
    }

    branchandbound(mejorSolucion, Mconveniencia, cola_de_prioridad, Mconveniencia_ordenada, cota);
}


int main(int argc, char *argv[]) {
    
    int n = atoi(argv[1]);
	int cota = atoi(argv[2]);

    vector<vector<int>> Mconveniencia = getConvenencia(n);

	vector<vector<int>> Mconveniencia_inversa = getConvenencia(n);

	vector<vector<int>> Mconveniencia_ordenada;

	for (int i = 0; i < n; i++) 
		for (int j = 0; j < n; j++) 
			Mconveniencia_inversa[i][j] = 1000 - Mconveniencia[i][j];

	vector<int> ordenar;
	for(int i=0; i<Mconveniencia.size(); i++)
	{
		ordenar = Mconveniencia[i];
		sort(Mconveniencia.begin(), Mconveniencia.end());

		Mconveniencia_ordenada.push_back(ordenar);
	}

    std::vector<int> camino = {0};
    Solucion solucion_parcial(camino, Mconveniencia_inversa, Mconveniencia_ordenada, cota);

    std::priority_queue<Solucion> cola_de_prioridad;
    cola_de_prioridad.push(solucion_parcial);

    std::vector<int> mejorCamino;
    for(int i = 0; i < n; i++) {
        mejorCamino.push_back(i);
    }

    Solucion mejorSolucion(mejorCamino, Mconveniencia_inversa, Mconveniencia_ordenada, cota);


    //Calculamos el tiempo de ejecución del algoritmo con Chrono
	std::chrono::high_resolution_clock::time_point t_antes, t_despues;
	std::chrono::duration<double> transcurrido;

	t_antes = std::chrono::high_resolution_clock::now();
    branchandbound(mejorSolucion, Mconveniencia_inversa, cola_de_prioridad, Mconveniencia_ordenada, cota);
    t_despues = std::chrono::high_resolution_clock::now();
  
	transcurrido = std::chrono::duration_cast<std::chrono::duration<double>>(t_despues - t_antes);

    // Imprimimos el tiempo de ejecución del algoritmo a través de la terminal
	cout << argv[1] << " " << transcurrido.count() << endl;

	if(atoi(argv[3]) == 1)
	{
		ofstream salida("./bb/data/solucion.dat", ofstream::out | ofstream::trunc);
		salida << argv[1] << " " << transcurrido.count() << endl;
		
        salida << "Se ha encontrado la siguiente solucion: " << endl;
        vector<int> solCamino = mejorSolucion.get_camino();
        for( int i = 0; i < n; i++){
            salida << solCamino[i] << endl;
        }

        mejorSolucion.calcularNivelConveniencia(Mconveniencia, Mconveniencia_ordenada, cota);
        salida << "La conveniencia alcanzada es: " << mejorSolucion.get_conveniencia() << endl;

    }

    return 0;
}
