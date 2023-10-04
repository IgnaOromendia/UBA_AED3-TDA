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

// Estructura de manifestaciones
struct manifestacion {
    int nodo;
    int tiempo;
    manifestacion() : nodo(-1), tiempo(-1) {}
    manifestacion(int n, int t) : nodo(n), tiempo(t) {}
};

// Variables globales
int n, m, P, H, tiempo_hasta_H, tiempo_hasta_P;
vector<bool> marcados;
vector<int> tiempos;
vector<manifestacion> manifestaciones;
vector<vector<int> > adyacentes;

// n = #cantidad de nodos

// Complejidad: O(n)
void bfs(int s) {
    vector<bool> visitado(n*m, false);
    tiempos = vector<int>(n*m, -1);
    visitado[s] = true;
    tiempos[s] = 0;
    queue<int> cola;
    cola.push(s);

    while(not cola.empty()) {
        int v = cola.front(); cola.pop();

        for(int w : adyacentes[v]) {
            // Si no fue marcado ni fue visitado, lo visitamos
            if(not visitado[w] and not marcados[w]) {
                visitado[w] = true;
                tiempos[w] = tiempos[v] + 1;
                cola.push(w);
            }
        }
    }
}

// Complejidad: O(n)
void eliminar_nodos_manifestaciones(int t) {
    for(int i = 0; i < manifestaciones.size(); i++) {
        // Si el tiempo a llegar a la manifestacion es mayor o igual al tiempo en el que inicia entonces marcamos el nodo
        if (not marcados[manifestaciones[i].nodo])
            marcados[manifestaciones[i].nodo] = manifestaciones[i].tiempo <= (tiempos[manifestaciones[i].nodo] + t);
    } 
}

// Complejidad: O(n)
void calcular_tiempos_desde(int v, int t) {
    // Para obtener las distancias iniciales
    bfs(v);

    // Limpiamos el grafo de manifestaciones
    eliminar_nodos_manifestaciones(t);

    // Caluclamos los tiempos contando las manifestaciones
    bfs(v);

    if (v == H) tiempo_hasta_P = tiempos[P];
    else tiempo_hasta_H = tiempos[H];
}

bool comp_manifestaciones(manifestacion a, manifestacion b) {
    return a.tiempo < b.tiempo;
}

int main() {
    int c; cin >> c;
    while(c--) {
        cin >> n >> m;

        // Inicializamos las variables
        marcados   = vector<bool>(n*m, false);
        tiempos    = vector<int>(n*m, -1);
        adyacentes = vector<vector<int> >(n*m, vector<int>());

        // Generamos el grafo
        for(int v = 0; v < n*m; v++) {
            // Vecino de arriba
            if (v >= m) adyacentes[v].push_back(v - m);

            // Vecino de la izquierda
            if (v % m != 0) adyacentes[v].push_back(v - 1);

            // Vecino de la derecha
            if (v % m != m - 1) adyacentes[v].push_back(v + 1);

            // Vecino de abajo
            if (v < n*m - m) adyacentes[v].push_back(v + m);
        }

        // Leemos las manifestaciones
        for(int i = 0; i < n*m; i++) {
            int t; cin >> t;
            if (t > 0) manifestaciones.push_back(manifestacion(i,t));
        }

        // Leemos cooredenada de H y P
        int x,y;
        cin >> x >> y; H = (x * n) + y;
        cin >> x >> y; P = (x * n) + y;

        // Ordenamos las manifestaciones por tiempo
        sort(manifestaciones.begin(), manifestaciones.end(), comp_manifestaciones);

        // Calculamos el camino a P
        calcular_tiempos_desde(H, 0);

        // // Guardamos el camino hasta P
        calcular_tiempos_desde(P, tiempo_hasta_P);

        // Si son el mismo entonces ambos tiempos son 0
        if (P == H) tiempo_hasta_H = tiempo_hasta_P = 0;

        // Imprimimos el resultado
        if (tiempo_hasta_H == -1 or tiempo_hasta_P == -1) cout << IMPOSIBLE << endl;
        else cout << tiempo_hasta_P << " " << tiempo_hasta_H + tiempo_hasta_P << endl;

        manifestaciones.clear();
    }
}


