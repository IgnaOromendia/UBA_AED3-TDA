#include<vector>
#include<iostream>

using namespace std;

const int INF = 1e9;

vector<vector<bool> > grafo_vc;
vector<vector<bool> > grafo_va;
int n, m;
vector<int> mellizos;
vector<int> gemelos;

// O(n + m)
void encontrar_mellizos() {
    for(int v = 1; v < n; v++) {
        // Si ya es mellizo, no lo vuelvo a chequear
        if (mellizos[v]) continue;
        for(int u = 1; u < n; u++) {
            // Si es el mismo nodo, no lo chequeo
            if (v == u) continue;
            // Si ya es mellizo, no lo vuelvo a chequear
            if (mellizos[u]) continue;
            // Comparo los vecindarios cerrados
            if (grafo_vc[v] != grafo_vc[u]) continue;
            // Si son iguales, son mellizos
            mellizos[u] = true;
            mellizos[v] = true;
        }
    }
}

// O(n + m)
void encontrar_gemelos() {
    for(int v = 1; v < n; v++) {
        // Si ya es gemelo, no lo vuelvo a chequear
        if (gemelos[v]) continue;
        for(int u = 1; u < n; u++) {
            // Si es el mismo nodo, no lo chequeo
            if (v == u) continue;
            // Si ya es gemelo, no lo vuelvo a chequear
            if (gemelos[u]) continue;
            // Comparo los vecindarios
            if (grafo_va[v] != grafo_va[u]) continue;
            // Si son iguales, son gemelos
            gemelos[u] = true;
            gemelos[v] = true;
        }
    }
}

int main() {
    int c; cin >> c;
    while(c--) {
        cin >> n >> m;
        n++;
        grafo_va = vector<vector<bool> >(n, vector<bool>(n, false)); // O(n^2)
        grafo_vc = vector<vector<bool> >(n, vector<bool>(n, false)); // O(n^2)
        mellizos = vector<int>(n, false); // O(n)
        gemelos  = vector<int>(n, false); // O(n)

        while(m--) {                                      
            int u, v;
            cin >> u >> v;

            // Para facilitar el vecindario cerrado
            grafo_vc[u][u] = true;
            grafo_vc[v][v] = true;

            grafo_vc[u][v] = true;
            grafo_vc[v][u] = true;

            grafo_va[u][v] = true;
            grafo_va[v][u] = true;
        }

        encontrar_mellizos();
        cout << "Mellizos: " << endl;
        // Mostramos los mellizos
        for(int i = 1; i < n; i++) {
            if (mellizos[i]) cout << i << " ";
        }
        cout << endl;

        encontrar_gemelos();
        cout << "Gemelos: " << endl;
        // Mostramos los gemelos
        for(int i = 1; i < n; i++) {
            if (gemelos[i]) cout << i << " ";
        }
        cout << endl;

    }
    
}