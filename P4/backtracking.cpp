#include <iostream>
#include <vector>



using namespace std;

// Calculamos el nivel de conveniencia de una posible solucion: sumamos la conveniencia de todos los comensales respecto a los invitador a su derecha e izquierda
// Numero de elementos colocados en la solucion
int calcularNivelConveniencia(const vector<vector<int>>& conveniencia, const vector<int>& solucion_parcial, int elementos) {
    int nivelConveniencia = 0;
    int n = conveniencia.size(); // numero de comensales
    for (int i = 0; i < elementos; i++) {
        int izquierda = (i - 1 + n) % n;
        int derecha = (i + 1) % n;

        if( izquierda < elementos)
            nivelConveniencia += conveniencia[solucion_parcial[i]][solucion_parcial[izquierda]];
        if( derecha < elementos)
            nivelConveniencia += conveniencia[solucion_parcial[i]][solucion_parcial[derecha]];
    }
    // AQUI HABRIA QUE ANIADIR EL CALCULO ESPECIFICO PARA LA COTA USANDO LAS DIAPOS
    return nivelConveniencia;
}

// Cota superior
int cotaGlobal( const vector<vector<int>>& conveniencia ){
    int num_comensales = conveniencia.size();
    vector<int> pos_solucion(num_comensales);
    for( int i = 0; i < num_comensales; i++)
        pos_solucion[i] = i;

    int ret = calcularNivelConveniencia(conveniencia, pos_solucion, num_comensales);
    return ret;
}


void backtracking(vector<int>& solucion_final, const vector<vector<int>>& conveniencia, const vector<int> solucion_parcial, int & cota_sup, int elementos) {
    int num_comensales = conveniencia.size();

    if( elementos == num_comensales){
        int conveniencia_actual = calcularNivelConveniencia(conveniencia, solucion_parcial, num_comensales);
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
                int conveniencia_actual = calcularNivelConveniencia(conveniencia, nueva_solucion_parcial, sig_elementos);
                if( conveniencia_actual < cota_sup){
                    backtracking(solucion_final, conveniencia, nueva_solucion_parcial, cota_sup, sig_elementos);
                }
            }
        }
    }



}


// Usaremos el mismo algoritmo que se usa para el Problema del Viajante de Comercio
// Para ello realizaremos el cambio 'conveniencia_inv = 1000 - conveniencia' y conseguimos una suma a minimizar
int main() {
    int n;
    cout << "Introduce el numero de comensales " << endl;
    cin >> n;
    vector<vector<int>> conveniencia(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if( i == j){
                // No puede ocurrir, lo inicializo yo
                conveniencia[i][j] = 0;
            } else{
                cout << "Introduce el nivel de compatibilidad de " << i << " respecto a " << j << endl;
                cout << "Debe ser un entero entre 0 y 1000. En caso contrario, se truncará" << endl;
                cin >> conveniencia[i][j];
                if( conveniencia[i][j] < 0)
                    conveniencia[i][j] = 0;
                else if( conveniencia[i][j] > 1000)
                    conveniencia[i][j] = 1000;
            }
            
        }
    }

    vector<vector<int>> conveniencia_inv(n, vector<int>(n));
    for (int i = 0; i < n; i++) 
        for (int j = 0; j < n; j++) 
            conveniencia_inv[i][j] = 1000 - conveniencia[i][j];

    int cota_sup = cotaGlobal(conveniencia_inv);
    vector<int> solucion_parcial(n, -1);
    solucion_parcial[0] = 0; // No importa donde comience el ciclo -> elegimos el 0

    int elementos = 1;
    vector<int> mejorSolucion(n, -1);
    backtracking(mejorSolucion, conveniencia_inv, solucion_parcial, cota_sup, elementos); // Ya hemos colocado el primero -> nivel 1 completo

    cout << "Se ha encontrado la siguiente solucion: " << endl;
    for( int i = 0; i < n; i++){
        cout << mejorSolucion[i] << endl;
    }
    int conveniencia_final = calcularNivelConveniencia(conveniencia, mejorSolucion, num_comensales);
    cout << "La conveniencia alcanzada es: " << conveniencia_final << endl;

        
    return 0;
}
