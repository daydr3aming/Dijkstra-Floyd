#include <iostream>
#include <string>
#include <queue>
#include <vector>

// Actividad 3.2 Implementación de "Dijkstra and Floyd"
// Rogelio Guzman Cruzado - A01639914
// David Alejandro González Ibarra - A01633817 

using namespace std;


const int INF = 200;

// Funcion de relajacion, actualiza la distancia de un nodo a otro nodo
void relax(vector<vector<int>>& adjmatrix, vector<int>& dist, int u, int v) {
    if (dist[u] != INT_MAX && dist[u] + adjmatrix[u][v] < dist[v]) {
        dist[v] = dist[u] + adjmatrix[u][v];
    }
}

void dijkstra(vector<vector<int>>& adjmatrix, vector<int>& dist, int src){
    int n = adjmatrix.size();
    vector<bool> visited(n, false);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
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



vector<vector<int>> floyd(const vector<vector<int>>& graph){
    int n = graph.size();
    vector<vector<int>> distance(n, vector<int>(n, INF)); // Creamos el vector de vectores (matriz) que tendra las distancias 
    // y lo inicializamos todo con numeros max para llenarla en un principio



    // Aqui la inicializamos con los primeros valores del grafo y ponemos en 0 la diagonal con sus mismos numeros

    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            if(i == j){
                distance[i][j] = 0;
            }
            else if(graph[i][j]<0){
                distance[i][j] = INF;
            }
            else if(graph[i][j] != 0){
                distance[i][j] = graph[i][j];
            }
            
        }
    }

    // Aqui van los 3 for loops nesteados que son la parte mas importante del algoritmo
    // Se comparan los valores y van actualizando la matriz
    // recorriendo todos los nodos, y en cada uno checando cada dato.
    for(int k = 0; k<n; ++k){

        for(int i = 0; i<n; ++i){

            for(int j=0; j<n; ++j){

                    if(distance[i][k] != INF && distance[k][j] != INF){ // Checamos que lo que vamos a revisar no sean infinitos
                    // si no, se quedan igual

                        distance[i][j] = min(distance[i][j], distance[i][k] + distance[k][j]);

                        // Realizamos la comparacion para encontrar el valor minimo
                    }

            }
        }
    }


    return distance;
}


int main() {
    int n;
    cin >> n;
    vector<vector<int>> adjmatrix(n, vector<int>(n));
    vector<vector<int>> distanceFloyd(n, vector<int>(n));


    // Agregamos los valores a las matrices
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            int num;
            cin >> num;
            adjmatrix[i][j] = num;
            distanceFloyd[i][j] = num;
        }
    }


    vector<vector<int>> distances = floyd(distanceFloyd); // Llamamos la funcion de floyd

    // Cambiamos el nodo source para hacer dijkstra entre todos los nodos
    for(int src = 0; src < n; src++){
        vector<int> dist(n, INT_MAX);
        dijkstra(adjmatrix, dist, src);
        for(int i = 0; i < n; i++){
            cout << "Node " << src + 1 << " to node " << i + 1 << " : " << dist[i] << endl;
        }
        cout << endl;
    }

    // Imprimimos el vector que nos regresa con las distancias de Floyd

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
