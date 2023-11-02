#include<iostream>
#include<vector>
#include<queue>

using namespace std;
typedef pair<int, int> node;

#define INF 1e9
#define IMP "IMPOSIBLE"
#define POS "POSIBLE"

int n;
vector<vector<int> > distancia, velocidad, adj;

// Verificamos que las velocidades minimas sean validas
bool verificar() {
    for(int k = 1; k <= n; k++) {
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                if (k == i or k == j or i == j) continue;
                //if (velocidad[i][j] < velocidad[i][k] + velocidad[k][j]) adj[i][j] = adj[j][i] = 1;
                if (velocidad[i][j] > velocidad[i][k] + velocidad[k][j]) return false; 
            }
        }
    }
    return true;
}

void armar_grafo() {
    // Armamos el grafo
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if (i == j) continue;
            adj[i][j] = adj[j][i] = 1;
        }
    }

    // Eliminamos las aristas no necesarias
    for(int k = 1; k <= n; k++) {
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                if (k == i or k == j or i == j) continue;
                if (velocidad[i][j] == velocidad[i][k] + velocidad[k][j]) adj[i][j] = adj[j][i] = 0;
            }
        }
    }
}

// BFS para enocntrar las distancias en aristas
void bfs(int s) {
    queue<int> cola;
    vector<bool> visitado(n+1, false);

    visitado[s] = true;
    distancia[s][s] = 0;
    cola.push(s);

    while(not cola.empty()) {
        int v = cola.front(); cola.pop();

        for(int w = 1; w <= n+1; w++) {
            if(adj[v][w] == 1 and !visitado[w]) {
                visitado[w] = true;
                distancia[s][w] = distancia[s][v] + 1;
                cola.push(w);
            }
        }
    }
}

int main() {
    int c; cin >> c;
    while(c--) {
        cin >> n;
        
        adj.assign(n+1, vector<int>(n+1, 0));
        distancia.assign(n+1, vector<int>(n+1, 0));
        velocidad.assign(n+1, vector<int>(n+1, INF));

        for(int i = 1; i <= n; i++) velocidad[i][i] = 0;

        int i = 2, j = 1;
        while(i <= n) {
            int vel; cin >> vel;
            velocidad[i][j] = velocidad[j][i] = vel;
            j++;
            if (i == j) {i++;j=1;}
        }

        if (!verificar()) {
            cout << IMP << endl;
        } else {
            armar_grafo();

            for(int i = 1; i <= n; i++) bfs(i);

            cout << POS << endl;
            for(int i = 1; i <= n; i++) {
                for(int j = 1; j <= n; j++) {
                    cout << distancia[i][j] << " ";
                }
                cout << endl;
            }
        }
    }
}
