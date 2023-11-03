#include<iostream>
#include<vector>
#include<queue>

using namespace std;

#define INF 1e9

int n, Vred, s = 0, t; 
vector<bool> marcado;
vector<int> part_fila, part_columna; // Particiones por fila y por columna
vector<vector<bool> > tablero;
vector<vector<int> > red, capacity;

int bfs(int s, int t, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int> > q;
    q.push(make_pair(s, INF));

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : red[cur]) {
            if (parent[next] == -1 && capacity[cur][next]) {
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                if (next == t)
                    return new_flow;
                q.push(make_pair(next, new_flow));
            }
        }
    }

    return 0;
}

int maxflow(int s, int t) {
    int flow = 0;
    vector<int> parent(Vred);
    int new_flow;

    while (new_flow = bfs(s, t, parent)) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}

void armar_red() {
    // Los nodos del 1 al n+1 son las filas
    // Las columnas van del n+1 al 2n+1
    // Las celdas van del 2n+1 hasta el final
    int offset_fila    = 1;
    int offset_celda   = 2*n+1;
    int offset_columna = n+1;

    for(int i = 0; i < n; i++) {
        // Agregamos las filas y las conectamos con s
        red[s].push_back(i+1);
        capacity[s][i+1] = capacity[i+1][s] = part_fila[i] + 1; // En caso de que tenga particiones se las sumamos
        
        // Agregamos las columnas y las conectamos con t
        int col = i + offset_columna;
        red[col].push_back(t);
        capacity[col][t] = capacity[t][col] = part_columna[i] + 1;
    }

    // Agregamos las celdas, las conectamos con su fila y cloumna correspondiente
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            int indice  = (n * i) + j;
            if (marcado[indice]) continue;
            int celda   = indice + offset_celda;
            int fila    = i + offset_fila;
            int columna = j + offset_columna;

            // cout << fila << " -> " << celda << " -> " << columna << endl;

            // Conectamos con fila
            red[fila].push_back(celda);
            capacity[fila][celda] = capacity[celda][fila] = 1;

            // Conectamos con columna
            red[celda].push_back(columna);
            capacity[celda][columna] = capacity[columna][celda] = 1;
        }
    }
}

int main() {
    int c; cin >> c;
    while(c--) {
        cin >> n;

        // n filas + n columnas + n^2 celdas + 2 (s y t)
        Vred = 2*n + n*n + 2; 

        t = Vred - 1;

        part_fila.assign(n,0);
        part_columna.assign(n,0);
        marcado.assign(n*n, false);
        red.assign(Vred, vector<int>());
        tablero.assign(n, vector<bool>(n, false));
        capacity.assign(Vred, vector<int>(Vred,0));

        // Marcamos los que son inaccesibles
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                int indice = (n * i) + j;
                // cout << indice << endl;

                bool b; cin >> b;
                tablero[i][j] = b;
                marcado[indice] = b;

                if (b and j > 0 and i < n-1 and tablero[i][j-1] == 0) part_fila[i]++;
                if (b and i > 0 and j < n-1 and tablero[i-1][j] == 0) part_columna[j]++;
            }
        }

        cout << "Fila" << endl;
        for(int i = 0; i < n; i++) {
            cout << i << ": " << part_fila[i] << endl;
        }

        cout << "Columna" << endl;
        for(int i = 0; i < n; i++) {
            cout << i << ": " << part_columna[i] << endl;
        }

        armar_red();

        for(int i = 0; i < red.size(); i++) {
            cout << i << ": ";
            for(int u: red[i]) {
                cout << u << " c(" << capacity[i][u] << "), ";
            }
            cout << endl;
        }

        cout << "-----" << endl;

        int max_torres = maxflow(s,t);
        cout << max_torres << endl;

        cout << "-----" << endl;
    }
}