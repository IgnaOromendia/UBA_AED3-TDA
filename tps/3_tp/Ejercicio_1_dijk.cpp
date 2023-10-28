#include<iostream>
#include<vector>
#include<queue>

using namespace std;

/*
Vamos a usar a dijkstra como caja negra, multiplicando el grafo 4 veces,
donde las aristas pasadizo te llevan de una componenete conexa a otra.
Vamos a tener 4 tiempos de t y vamos a elegir el menor de esos tiempos
*/

#define INF 1e9

struct edge {
    int to;
    int cost;
    edge() {}
    edge(int to, int cost) : to(to), cost(cost) {}
};

int n, N, m, betun, offset_G2, offset_G3, offset_G4; // G1 no tiene offset porque es el grafo original
vector<vector<edge> > adj;
vector<int> distances;

void dijkstra(int s) {
    priority_queue<pair<int, int> > min_heap;
    vector<bool> visited(N, false);

    distances[s] = 0;
    min_heap.push(make_pair(0, s));

    while(!min_heap.empty()) {
        int u = min_heap.top().second; min_heap.pop();

        if(visited[u]) continue;
        visited[u] = true;

        for(edge e: adj[u]) {
            if (distances[e.to] > distances[u] + e.cost) {
                distances[e.to] = distances[u] + e.cost;
                min_heap.push(make_pair(-distances[e.to], e.to));
            }
        }
        
    }
}

void add_edge(int from, int to) {
    int cost = to-from;
    // Agregamos a G1
    adj[from].push_back(edge(to, cost));

    // Agregamos a G2
    adj[from + offset_G2].push_back(edge(to + offset_G2, cost));

    // Agregamos a G3
    adj[from + offset_G3].push_back(edge(to + offset_G3, cost));

    // Agregamos a G4
    adj[from + offset_G4].push_back(edge(to + offset_G4, cost));
}

void add_pasadizo(int from, int to) {
    int cost = 2;
    // Agregamos desde G1 a G2
    adj[from].push_back(edge(to + offset_G2, cost));

    // Agregamos desde G2 a G3
    adj[from + offset_G2].push_back(edge(to + offset_G3, cost));

    // Agregamos desde G3 a G4
    adj[from + offset_G3].push_back(edge(to + offset_G4, cost));
}

int main() {
    int c; cin >> c; 
    while(c--) {
        offset_G2 = offset_G3 = offset_G4 = -1;
        cin >> n >> m;

        N = (n*4)+1;

        betun = n;
        offset_G2 = n;
        offset_G3 = 2*n;
        offset_G4 = 3*n;
        adj.assign(N, vector<edge>());
        distances.assign(N, INF);

        // Del comienzo al salon 1
        adj[0].push_back(edge(1,1));
        
        // Conectamos al i-esimo con el i+1-esimo
        for(int i = 1; i < n; i++) {
            add_edge(i,i+1);
        }

        while(m--) {
            int v,u; cin >> v >> u;
            add_pasadizo(v,u);
        }

        // Hacemos dijkstra desde el comienzo
        dijkstra(0);

        // Tomamos el minimo de los 4 caminos posibles
        int sin_pasadizos  = distances[betun];
        int un_pasadizo    = distances[betun + offset_G2];
        int dos_pasadizos  = distances[betun + offset_G3];
        int tres_pasadizos = distances[betun + offset_G4];

        int min_path = min(sin_pasadizos, min(un_pasadizo, min(dos_pasadizos, tres_pasadizos)));

        cout << min_path << endl;
    }
}