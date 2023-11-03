#include<iostream>
#include<vector>
#include<queue>

using namespace std;

const double INF = 1e9;

int n, Vred, s = 0, t, tag_fila = 0, tag_col = 0; 
vector<vector<bool> > tablero;
vector<vector<int> > red, capacity, part_hori, part_vert;

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
    // Los nodos del 1 al tag_fila+1 son las particiones horizontales
    // Los nodoos que representan las particiones verticales van del tag_fila+1 al tag_col+tag_fila+1
    // Los nodos que representan las celdas van del tag_col+tag_fila+1 hasta el final
    int offset_celda = tag_fila + tag_col + 1;
    int offset_verti = tag_fila + 1;

    // Agregamos las particiones horizionatales y las conectamos con s
    for(int i = 0; i < tag_fila; i++) {
        red[s].push_back(i+1);
        red[i+1].push_back(s);
        // cout << " uniendo fila: " << s << " con " << i + 1 << endl;
        capacity[s][i+1] = 1;
        capacity[i+1][s] = 0;
    }

    // Agregamos las columnas y las conectamos con t
    for(int i = 0; i < tag_col; i++) {
        int col = i + offset_verti;
        red[col].push_back(t);
        red[t].push_back(col);
        // cout << " uniendo columna: " << col << " con " << t << endl;
        capacity[col][t] = 1;
        capacity[t][col] = 0;
    }

    // Agregamos las celdas, las conectamos con su fila y cloumna correspondiente
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            int indice = (n * i) + j;
            if (tablero[i][j]) continue;
            int celda  = indice + offset_celda;

            // Nodos que represenatn la particion horizontal y vertical de la celda
            int h = part_hori[i][j] + 1;
            int v = part_vert[i][j] + offset_verti;

            red[h].push_back(v);
            red[v].push_back(h);
            capacity[v][h] = 0;
            capacity[h][v] = 1;
        }
    }
}

int main() {
    int c; cin >> c;
    while(c--) {
        cin >> n; 

        part_hori.assign(n,vector<int>(n,-1));
        part_vert.assign(n,vector<int>(n,-1));
        tablero.assign(n, vector<bool>(n, false));

        // Leo input y asigno una zona horizionatl a cada celda
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                bool b; cin >> b;

                tablero[i][j] = b;

                if (b and j > 0 and tablero[i][j-1] == 0) tag_fila++;

                // Asigno una zona horizontal a la celda
                part_hori[i][j] = tag_fila;                
            }
            tag_fila++;
        }

        // Asigno una zona vertical a cada celda
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if (tablero[j][i] and j > 0 and tablero[j-1][i] == 0) tag_col++;
                part_vert[j][i] = tag_col;                
            }
            tag_col++;
        }

        Vred = tag_fila + tag_col + 2;
        capacity.assign(Vred, vector<int>(Vred,0));
        red.assign(Vred, vector<int>());
        t = Vred - 1;

        armar_red();
        
        for(int i = 0; i < 0; i++) {
            cout << i << ": ";
            for(int u: red[i]) {
                cout << u << " c(" << capacity[i][u] << "), ";
            }
            cout << endl;
        }

        //cout << "-----" << endl;

        int max_torres = maxflow(s,t);
        cout << max_torres << endl;
        
        //cout << "-----" << endl;
        tag_col = 0;
        tag_fila = 0;
    }
}