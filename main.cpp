#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <cmath>

// Actividad 3.2 Implementación de "Dijkstra and Floyd"
// Rogelio Guzman Cruzado - A01639914
// David Alejandro González Ibarra - A01633817 

using namespace std;


const int INF = pow(10, 9); // Numero muy grande, porque hay problemas con INT_MAX.

// Funcion de relajacion, actualiza la distancia de un nodo a otro nodo
void relax(vector<vector<int>>& adjmatrix, vector<int>& dist, int u, int v) {
    if (dist[u] != INT_MAX && dist[u] + adjmatrix[u][v] < dist[v]) {
        dist[v] = dist[u] + adjmatrix[u][v];
    }
}

// Algoritmo de Dijkstra - Complejidad: O(V log V + E)
void dijkstra(vector<vector<int>>& adjmatrix, vector<int>& dist, int src){ 
    int n = adjmatrix.size();
    vector<bool> visited(n, false);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // min heap
    // Complejidad disminuye a O(V log V + E) gracias a pq

    dist[src] = 0;
    pq.push(make_pair(0, src));

    while(!pq.empty()){
        int u = pq.top().second;
        pq.pop();

        if (visited[u]){
            continue;
        }
        visited[u] = true;

        for(int v = 0; v < n; v++){ 
            if (adjmatrix[u][v] != -1){ // Como los casos de prueba tienen -1 en los lugares donde no hay conexion, se hace este checkeo.
                relax(adjmatrix, dist, u, v);
                pq.push(make_pair(dist[v], v));
            }
        }
    }
}


// Algoritmo de Floyd - Complejidad: O(V^3)
vector<vector<int>> floyd(const vector<vector<int>>& grafo){
    int n = grafo.size();
    vector<vector<int>> vecDistancia(n, vector<int>(n, INF)); // Creamos el vector de vectores (matriz) que tendra las distancias 
    // y lo inicializamos todo con infinito

    // Aqui la inicializamos con los primeros valores del grafo y ponemos en 0 la diagonal con sus mismos numeros

    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            if(i == j){
                vecDistancia[i][j] = 0;
            }
            else if(grafo[i][j]<0){
                vecDistancia[i][j] = INF;
            }
            else if(grafo[i][j] != 0){
                vecDistancia[i][j] = grafo[i][j];
            }
            
        }
    }

    // Aqui van los 3 for loops nesteados que son la parte mas importante del algoritmo
    // Se comparan los valores y van actualizando la matriz
    // recorriendo todos los nodos, y en cada uno checando cada dato.
    for(int k = 0; k<n; ++k){

        for(int i = 0; i<n; ++i){

            for(int j=0; j<n; ++j){

                    if(vecDistancia[i][k] != INF && vecDistancia[k][j] != INF){ // Checamos que lo que vamos a revisar no sean infinitos
                    // si no, se quedan igual

                        vecDistancia[i][j] = min(vecDistancia[i][j], vecDistancia[i][k] + vecDistancia[k][j]);

                        // Realizamos la comparacion para encontrar el valor minimo
                    }

            }
        }
    }


    return vecDistancia;
}


int main() {
    int n;
    cin >> n;
    vector<vector<int>> adjmatrix(n, vector<int>(n));
    vector<vector<int>> distanceFloyd(n, vector<int>(n));


    // Inicializamos las matrices
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            int num;
            cin >> num;
            adjmatrix[i][j] = num;
            distanceFloyd[i][j] = num;
        }
    }


    vector<vector<int>> distances = floyd(distanceFloyd); // Floyd

    // Cambiamos el nodo source para hacer dijkstra entre todos los nodos
    for(int src = 0; src < n; src++){
        vector<int> dist(n, INT_MAX);
        dijkstra(adjmatrix, dist, src); // Dijkstra para cada nodo
        for(int i = 0; i < n; i++){
            cout << "Node " << src + 1 << " to node " << i + 1 << " : " << dist[i] << endl;
        }
        cout << endl;
    }

    // Imprimimos las distancias de Floyd

    for(int i=0; i < n; ++i){
        for(int j =0; j<n; ++j){
            if(distances[i][j] == INF){
                cout<<"INF";
            }
            else{
                cout<<distances[i][j]<<" ";
            }
        }
        cout<<endl;
    }
}
