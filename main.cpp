#include <iostream>
#include <string>
#include <queue>
#include <vector>

// Actividad 3.2 Implementación de "Dijkstra and Floyd"
// Rogelio Guzman Cruzado - A01639914
// David - 

using namespace std;

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

int main() {
    int n;
    cin >> n;
    vector<vector<int>> adjmatrix(n, vector<int>(n));

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            int num;
            cin >> num;
            adjmatrix[i][j] = num;
        }
    }

    // Cambiamos el nodo source para hacer dijkstra entre todos los nodos
    for(int src = 0; src < n; src++){
        vector<int> dist(n, INT_MAX);
        dijkstra(adjmatrix, dist, src);
        for(int i = 0; i < n; i++){
            cout << "Node " << src + 1 << " to node " << i + 1 << " : " << dist[i] << endl;
        }
        cout << endl;
    }
}
