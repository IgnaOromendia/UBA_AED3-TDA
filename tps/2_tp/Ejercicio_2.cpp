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
        Eliminar todos los nodos tq camino_P < manifestacion_i
        BFS desde H guardando la distancia a cada nodo
- BFS desde P guardando la distancia a cada nodo                O(n + m)  
- Calcular camino a H:                                          O(n + m)
    Si min de manifestaciones < camino_H:
        Eliminar todos los nodos tq camino_H < manifestacion_i
        BFS desde P guardando la distancia a cada nodo
*/

// Constantes
const string IMPOSIBLE = "IMPOSIBLE";

// Estructura de manifestaciones
struct manifestacion {
    int nodo;
    int tiempo;
    manifestacion() : nodo(-1), tiempo(-1) {}
    manifestacion(int n, int t) : nodo(n), tiempo(t) {}
};

// Variables globales
int n, m, P, H, camino_H, camino_P;
manifestacion proxima_manifestacion;
vector<bool> marcados;
vector<int> tiempo_H, tiempo_P;
vector<manifestacion> manifestaciones;
vector<vector<int> > adyacentes;

// Complejidad: O(n + m)
void bfs(int s, vector<int> &distancia) {
    vector<bool> visitado(n*m, false);
    visitado[s] = true;
    distancia[s] = 0;
    queue<int> cola;
    cola.push(s);

    while(not cola.empty()) {
        int v = cola.front(); cola.pop();

        for(int w : adyacentes[v]) {
            // Si no fue marcado ni fue visitado, lo visitamos
            if(not visitado[w] and not marcados[w]) {
                visitado[w] = true;
                distancia[w] = distancia[v] + 1;
                cola.push(w);
            }
        }
    }
}

// Complejidad: O(n + m)
int calcular_camino_hasta_P() {
    // En caso de que el camino sea más rápido que la primer manifestación lo devolvemos
    if (tiempo_H[P] < proxima_manifestacion.tiempo) return tiempo_H[P];
    
    // Caso contrario, limpiamos el grafo de manifestaciones y volvemos a calcular el camino
    for(int i = 0; i < manifestaciones.size(); i++)
        marcados[manifestaciones[i].nodo] = manifestaciones[i].tiempo < tiempo_H[P];

    // Reinicamos los caminos debido a las manifestaciones
    tiempo_H = vector<int>(n*m, -1);

    bfs(H, tiempo_H);
    return tiempo_H[P];
}

// Complejidad: O(n + m)
int calcular_camino_hasta_H() {
    // En caso de que el camino sea más rápido que la primer manifestación lo devolvemos
    if (tiempo_P[H] + tiempo_H[P] < proxima_manifestacion.tiempo) return tiempo_P[H];
    
    // Caso contrario, limpiamos el grafo de manifestaciones y volvemos a calcular el camino
    for(int i = 0; i < manifestaciones.size(); i++)
        marcados[manifestaciones[i].nodo] = manifestaciones[i].tiempo < tiempo_P[H] + tiempo_H[P];

    // Reinicamos los caminos debido a las manifestaciones
    tiempo_P = vector<int>(n*m, -1);

    bfs(P, tiempo_P);
    return tiempo_P[H];
}

// Complejidad: O(n)
manifestacion proxima_manifestacion_para(int t) {
    int i = 0;
    while(manifestaciones[i].tiempo < t and i < manifestaciones.size()) i++;
    return manifestaciones[i];
}

bool comp_manifestaciones(manifestacion a, manifestacion b) {
    return a.tiempo < b.tiempo;
}

int main() {
    int c; cin >> c;
    while(c--) {
        cin >> n >> m;

        // Inicializamos las variables
        marcados = vector<bool>(n*m, false);
        tiempo_H = vector<int>(n*m, -1);
        tiempo_P = vector<int>(n*m, -1);
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
        cin >> x >> y; H = x + y;
        cin >> x >> y; P = x + y;

        // Imprimimos el grafo
        // cout << "G:" << endl;
        // for(int v = 0; v < n*m; v++) {
        //     cout << v << ": ";
        //     for(int w : adyacentes[v]) cout << w << " ";
        //     cout << endl;
        // }

        // Imprimimos las manifestaciones
        // cout << "Manifestaciones: " << endl;
        // for(int i = 0; i < manifestaciones.size(); i++)
        //     cout << "v: " << manifestaciones[i].nodo << ", t: " << manifestaciones[i].tiempo << endl;

        // cout << "H: " << H << endl;
        // cout << "P: " << P << endl;

        // Ordenamos las manifestaciones por tiempo
        sort(manifestaciones.begin(), manifestaciones.end(), comp_manifestaciones);

        // Calculamos el camino a P
        bfs(H, tiempo_H);

        // Mostramos los caminos desde H
        // cout << "Caminos desde H antes de calcular:" << endl;
        // for(int i = 0; i < n*m; i++)
        //     cout << "v: " << i << ", t:" << tiempo_H[i] << endl;

        proxima_manifestacion = proxima_manifestacion_para(tiempo_H[P]);

        // cout << "Proxima manifestacion para H: " << proxima_manifestacion.nodo << ", " << proxima_manifestacion.tiempo << endl;

        camino_P = calcular_camino_hasta_P();

        // Mostramos los marcados
        // cout << "Marcados post H:" << endl;
        // for(int i = 0; i < n*m; i++)
        //     cout << "v: " << i << ", m:" << marcados[i] << endl;

        // cout << "Caminos desde H post calcular:" << endl;
        // for(int i = 0; i < n*m; i++)
        //     cout << "v: " << i << ", t:" << tiempo_H[i] << endl;

        // Calculamos el camino a H
        bfs(P, tiempo_P);

        // Mostramos los caminos desde P
        // cout << "Caminos desde P antes de calcular:" << endl;
        // for(int i = 0; i < n*m; i++)
        //     cout << "v: " << i << ", t:" << tiempo_P[i] << endl;

        proxima_manifestacion = proxima_manifestacion_para(tiempo_P[H]);
        
        // cout << "Proxima manifestacion para P: " << proxima_manifestacion.nodo << ", " << proxima_manifestacion.tiempo << endl;

        camino_H = calcular_camino_hasta_H();
        
        // cout << "Marcados post P:" << endl;
        // for(int i = 0; i < n*m; i++)
        //     cout << "v: " << i << ", m:" << marcados[i] << endl;

        // cout << "Caminos desde P despues de calcular:" << endl;
        // for(int i = 0; i < n*m; i++)
        //     cout << "v: " << i << ", t:" << tiempo_P[i] << endl;

        if (camino_P == -1 or camino_H == -1) cout << IMPOSIBLE << endl;
        else cout << camino_P << " " << camino_H + camino_P << endl;

        manifestaciones.clear();
        // cout << " --- " << endl;
    }
}


