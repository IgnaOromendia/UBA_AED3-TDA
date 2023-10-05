#include<vector>
#include<iostream>
#include<algorithm>
#include<queue>
#include<string>

using namespace std;

/*
-- Estrategia --
n = 10^6
m ≈ 4n = 4*10^6
tij = 10^7
Complejidad: 
O(n log n + 2(2(n+m) + n)) = 
O(n log n + 4n + 4m + 2n) = 
O(n log n + 6n + 4m) = 
O(n log n + n + m)
--
Operaciones: 
10^6 log 10^6 + 610^6 + 1610^6 =
28*10^6 < 10^9
--
Algoritmo
- Ordenamos por tiempo las manifestaciones                      O(n log n)
- BFS desde H guardando la distancia a cada nodo                O(n + m)
- Calcular camino a P:                                          O(n + m)
    Si min de manifestaciones < camino_P:                       
        Eliminar todos los nodos tq tiempo_hasta_manifiestacion_i > manifestacion_i
        BFS desde H guardando la distancia a cada nodo
- BFS desde P guardando la distancia a cada nodo                O(n + m)  
- Calcular camino a H:                                          O(n + m)
    Si min de manifestaciones < camino_H:
        Eliminar todos los nodos tq tiempo_hasta_manifiestacion_i + tiempo_hasta_p > manifestacion_i
        BFS desde P guardando la distancia a cada nodo
*/

// Constantes
#define IMPOSIBLE "IMPOSIBLE"

// Variables globales
int n, m, P, H, tiempo_hasta_H, tiempo_hasta_P;
vector<bool> marcados;
vector<int> tiempos;
vector<int> manifestaciones;
vector<vector<int> > ady;

// n = #cantidad de nodos
 
/// @brief Calucla las distancias desde el nodo s teniendo en cuenta las manifestaciones
/// @param s nodo por donde comineza
/// @param t tiempo que se le suma por si no es el primer viaje
void bfs(int s, int t) {
    queue<int> cola;
    vector<bool> visitado(n*m, false);
    tiempos.assign(n*m, -1);

    visitado[s] = true;
    tiempos[s] = 0;
    cola.push(s);

    while(not cola.empty()) {
        int v = cola.front(); cola.pop();

        for(int w : ady[v]) {
            // Si no fue marcado ni fue visitado, lo visitamos
            marcados[w] = manifestaciones[w] <= (t + tiempos[v] + 1) and manifestaciones[w] > 0;
            if(not visitado[w] and not marcados[w]) {
                visitado[w] = true;
                tiempos[w] = tiempos[v] + 1;
                cola.push(w);
            }
        }
    }
}

int main() {
    int c; cin >> c;
    while(c--) {
        cin >> n >> m;

        // Inicializamos las variables
        manifestaciones.assign(n*m, -1);
        marcados.assign(n*m, false);
        tiempos.assign(n*m, -1);
        ady.assign(n*m, vector<int>());

        // Generamos el grafo
        for(int v = 0; v < n*m; v++) {
            // Vecino de arriba
            if (v >= m) ady[v].push_back(v - m);

            // Vecino de la izquierda
            if (v % m != 0) ady[v].push_back(v - 1);

            // Vecino de la derecha
            if (v % m != m - 1) ady[v].push_back(v + 1);

            // Vecino de abajo
            if (v < n*m - m) ady[v].push_back(v + m);
        }

        // Leemos las manifestaciones
        for(int i = 0; i < n*m; i++) {
            int t; cin >> t;
            manifestaciones[i] = t;
        }

        // Leemos cooredenada de H y P
        int x,y;
        cin >> x >> y; H = (x * m) + y;
        cin >> x >> y; P = (x * m) + y;

        bfs(H, 0);
        tiempo_hasta_P = tiempos[P];

        bfs(P, tiempo_hasta_P);
        tiempo_hasta_H = tiempos[H];

        // Si son el mismo entonces ambos tiempos son 0
        if (P == H) tiempo_hasta_H = tiempo_hasta_P = 0;

        // Imprimimos el resultado
        if (tiempo_hasta_H == -1 or tiempo_hasta_P == -1) cout << IMPOSIBLE << endl;
        else cout << tiempo_hasta_P << " " << tiempo_hasta_H + tiempo_hasta_P << endl;
    }
}


