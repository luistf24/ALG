import java.util.InputMismatchException;
import java.util.Scanner;   // Trabajar con la entrada estándar
import java.util.Random;    // Generar números aleatorios
 

public class propio{
        
    static void CalcularRecorrido(int matriz[][]){
        
        // DECLARACIÓN DE VARIABLES
        int num_nodos = matriz[0].length;
        int dist_total = 0;
        int contr = 0;
        
        int[] path = new int[num_nodos];
        boolean[] visitados = new boolean[num_nodos];
        
        for (int j=0; j<num_nodos;++j){
            visitados[j]=false;
        }
        
        
        // seleccionamos 4 nodos aleatorios y creamos el recorrido inicial
        Random rand = new Random();
        int random;
        
        while(contr < 4){
            random = rand.nextInt(num_nodos-1);
            if(!visitados[random]){
                path[contr] = random;
                contr++;
                visitados[random] = true;
            }
        }

        for(int i = 0; i < contr-1; i++){
            dist_total+=matriz[path[i]][path[i+1]];
        }
        dist_total+=matriz[path[0]][path[contr-1]];
        
        //en cada iteración añadimos un nodo a visitados
        //realizamos este while mientras queden nodos por visitar
        while (contr < num_nodos){
            
            int nodo_menor = -1;
            int nodo_cercano = -1;
            int dist_menor = Integer.MAX_VALUE;
            
            //buscamos el hueco en el que cabe un nodo no visitado y provoque
            //el menor aumento de distancias
            for(int i = 0; i < contr-1; i++){
                for(int j = 0; j < num_nodos; j++){
                    if(!visitados[j]){
                        int ps=matriz[path[i]][j] + matriz[path[i+1]][j]-matriz[path[i]][path[i+1]];
                        if(dist_total + ps < dist_menor){
                            nodo_menor = i;
                            nodo_cercano = j;
                            dist_menor = dist_total+ps;
                        }
                    }
                }
            }

            //para que compruebe también la dist menor teniendo en cuenta 
            //el hueco entre el primer y el ultimo nodo
            for(int j = 0; j < num_nodos; j++){
                if(!visitados[j]){
                    int ps=matriz[path[0]][j] + matriz[path[contr-1]][j]-matriz[path[0]][path[contr -1]];
                    if(dist_total + ps < dist_menor){
                        nodo_menor =contr-1;
                        nodo_cercano = j;
                        dist_menor = dist_total+ps;
                    }
                }
            }

            // añadimos nodo_cercano al path justo después de nodo_menor
            dist_total=dist_menor;
            for(int j = contr; j > nodo_menor; j--){
                path[j]=path[j-1];
            }
            path[nodo_menor+1]=nodo_cercano;
            contr++;
            visitados[nodo_cercano]=true;

        }
        
        // mostramos por pantalla
        System.out.println("Longitud ruta: " + dist_total);

        System.out.println("Ruta: ");
            for(int i = 0; i < path.length; i++)
                System.out.print(path[i]+1 + "\t");
    }

        

    public static void main(String[] arg){
        int number_of_nodes;
        Scanner scanner = null;
        try{

            scanner = new Scanner(System.in);
            number_of_nodes = scanner.nextInt();
            int adjacency_matrix[][] = new int[number_of_nodes][number_of_nodes];

            for (int i = 0; i < number_of_nodes; i++){
                for (int j = 0; j < number_of_nodes; j++){
                    adjacency_matrix[i][j] = scanner.nextInt();
                }
            }

            System.out.println("Recorrido de 16 ciudades con Inserción Cercana");
            long start1 = System.nanoTime();
            propio .CalcularRecorrido(adjacency_matrix);
            long end1 = System.nanoTime();

            System.out.println("Elapsed Time in nano seconds: "+ (end1-start1));

        } catch (InputMismatchException inputMismatch){
             System.out.println("Wrong Input format");
        }
        scanner.close();
        
    }    
}




